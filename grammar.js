/**
 * @file Tree-sitter parser for Standard ML
 * @author Byron Zhong <zhongbangyuan@gmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

const PREC = {
  prefix: 19,
  dot: 18,
  hash: 17,
  app: 16,
  neg: 15,
  pow: 14,
  mult: 13,
  add: 12,
  cons: 11,
  concat: 10,
  rel: 9,
  and: 8,
  or: 7,
  prod: 6,
  assign: 5,
  if: 4,
  seq: 3,
  case: 2
};

const INT    = /[1-9][0-9]*/;
const NUM    = /[0-9]+/;
const HEXNUM = /[0-9a-fA-F]+/;
const FRAC   = /\.[0-9]+/;
const EXPO   = /[eE]~?[0-9]+/;
const IDA    = /[A-Za-z][A-Za-z'_0-9]*/;
const IDS    = /[!%&$#+\-/:<=>?@\\~'^|*]+/;

// 1) Multiline/ignored sequences:  \ [format-chars]+ \
//    (Allows line continuation by escaping newlines, etc.)
const IGNORED_SEQ = /\\[ \t\n\r\f]+\\/;

// 2) Recognized escape sequences:
//    \a \b \t \n \v \f \r
//    \^@ .. \^_  (ASCII 64..95 after '^')
//    \ddd (NOTE: Allow out-of-range sequence?)
//    \uxxxx
//    \"  \\
const ESCAPE_CHAR =
  /\\(a|b|t|n|v|f|r|"|\\|\^[\x40-\x5F]|[0-9]{3}|u[0-9A-Fa-f]{4})/;

// 3) Ordinary characters: anything except backslash, quote, or newline.
//    NOTE: The standard said the ordinary characters can only be
//    ASCII 33..126, but SML/NJ seems to allow any unicode code points
//    except newlines.
const ORD_CHAR = /[^"\\\n\r]+/;

module.exports = grammar({
  name: "sml",

  extras: $ => [
    /\s/,
    $.comment
  ],

  externals: $ => [
    $.comment
  ],

  supertypes: $ => [
    $._expression,
    $._local_declaration,
    $._declaration,
    $._literal,
    $._atomic_expression,
    $._label,
  ],

  word: $ => $._alphanum_identifier,

  rules: {
    source_file: $ => choice(
      $._declaration
    ),

    // lexical analysis
    _alphanum_identifier: $ => token(IDA),
    _symbolic_identifier: $ => token(IDS),

    _identifier: $ => choice($._alphanum_identifier, $._symbolic_identifier),
    identifier: $ => $._identifier,
    _int: $ => token(INT),

    _qualified_identifier: $ => seq(
      field("path", repeat(seq($._alphanum_identifier, "."))),
      $._identifier
    ),

    real_literal: $ => token(seq(
      optional("~"),
      choice(
        seq(NUM, optional(FRAC), EXPO),
        seq(NUM, FRAC, optional(EXPO))
      )
    )),

    integer_literal: $ => token(choice(
      NUM,
      seq("~", NUM),
      seq("0x", HEXNUM),
      seq("~0x", HEXNUM)
    )),

    word_literal: $ => token(choice(
      seq("0w", NUM),
      seq("0wx", HEXNUM)
    )),

    string_literal: $ => token(seq(
      "\"",
      repeat(choice(IGNORED_SEQ, ESCAPE_CHAR, ORD_CHAR)),
      "\""
    )),

    char_literal: $ => token(seq(
      "#", "\"",
      repeat(IGNORED_SEQ),
      choice(ESCAPE_CHAR, ORD_CHAR),
      repeat(IGNORED_SEQ), "\""
    )),

    _literal: $ => choice(
      $.integer_literal,
      $.real_literal,
      $.word_literal,
      $.string_literal,
      $.char_literal
    ),

    identifier_expression: $ => seq(optional("op"), $._qualified_identifier),
    int_label: $ => $._int,
    identifier_label: $ => $._identifier,
    _label: $ => choice($.int_label, $.identifier_label),

    record_row: $ => seq(
      $._label,
      "=",
      $._expression
    ),

    record_expression: $ => seq("{", sep(",", $.record_row), "}"),

    let_expression: $ => seq(
      "let",
      $._local_declaration,
      "in",
      $._expression,
      "end"
    ),

    _atomic_expression: $ => choice(
      $._literal,
      $.record_expression,
    ),

    _expression: $ => choice(
      $._atomic_expression,
    ),

    value_declaration: $ => seq("val", $._valbind),

    wildcard: _ => token("_"),
    literal_pattern: $ => $._literal,
    identifier_pattern: $ => seq(optional("op"), $._qualified_identifier),
    list_pattern: $ => seq("[", sep(",", $._pattern), "]"),
    record_pattern: $ => seq("{", sep(",", $.pattern_row), "}"),
    vector_pattern: $ => seq("#[", sep(",", $._pattern), "]"),

    _atomic_pattern1: $ => choice(
      $.wildcard,
      $.literal_pattern,
      $.identifier_pattern,
      $.list_pattern,
      $.record_pattern,
      $.vector_pattern,
    ),

    pattern_row: $ => choice(
      seq($._label, "=", $._pattern),
      seq($.identifier_label, optional(seq(":", $._type)), optional(seq("as", $._pattern)))
    ),

    parenthesized_pattern: $ => parenthesize(sep(choice("|",","), $._pattern)),

    _atomic_pattern: $ => choice(
      $._atomic_pattern1,
      $.parenthesized_pattern,
    ),

    constraint_pattern: $ => prec(2, seq($._pattern, ":", $._type)),
    layered_pattern: $ => prec.right(1, seq($._pattern, "as", $._pattern)),
    _pattern: $ => choice(
      $.constraint_pattern,
      $.layered_pattern,
      repeat1($._atomic_pattern),
    ),

    _valbind1: $ => seq(optional("lazy"),
      alias($._pattern, $.lhs),
      "=",
      alias($._expression, $.rhs)
    ),

    _valbind: $ => sep1("and", $._valbind1),

    _local_declaration: $ => choice(
      $.value_declaration,
    ),

    expression_declaration: $ => $._expression,

    structure_level_declaration: $ => choice(
      $._local_declaration,
    ),

    _declaration: $ => choice(
      $.structure_level_declaration,
      $.expression_declaration
    ),

    _type: $ => token("int"),
  },

  /* See PR: https://github.com/tree-sitter/tree-sitter/pull/3896 */
  reserved: {
    global: _ => [
      "abstype",
      "and",
      "andalso",
      "as",
      "case",
      "datatype",
      "do",
      "else",
      "end",
      "exception",
      "fn",
      "fun",
      "handle",
      "if",
      "in",
      "infix",
      "infixr",
      "let",
      "local",
      "nonfix",
      "of",
      "op",
      "open",
      "orelse",
      "raise",
      "rec",
      "then",
      "type",
      "val",
      "with",
      "withtype",
      "while",
      "(", ")",
      "[", "]",
      "{", "}",
      ",", ":", ";", "...", "_",
      "|", "=", "=>", "->", "#",

      "eqtype",
      "functor",
      "include",
      "sharing",
      "sig",
      "signature",
      "struct",
      "structure",
      "where",
      ":>",
    ],
  },

});

function sequential(rule) {
  return seq(rule, repeat(seq(optional(";"), rule)))
}

function sep(delimiter, rule) {
  return optional(sep1(delimiter, rule))
}

function sep1(delimiter, rule) {
  return seq(rule, repeat(seq(delimiter, rule)))
}

function repeat2(rule) {
  return seq(rule, repeat1(rule))
}

function parenthesize(rule) {
  return seq('(', rule, ')')
}

function path(prefix, final) {
  return choice(final, seq(prefix, '.', final))
}
