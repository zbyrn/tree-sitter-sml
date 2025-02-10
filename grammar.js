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
const IDS    = /[!%&$#+\-/:<>?@\\~'^|=*]+/;
/* NOTE: There are restrictions on where ASTERISKs and EQUALOPs can be used as
 * identifiers. Specifically, a single * and = cannot be used as tycons and a
 * single = cannot be used as unqualified vid. I think this restriction is there
 * to simplify lexing. But since tree-sitter uses context-sensitive lexing, I
 * don't think there is any benefit in handling these cases specifically.
 *
 * As an example, `val = = 3;` is accepted in tree-sitter while both smlnj and
 * mlton complained.
 */

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
const ORD_CHAR = /[^"\\\n\r]/;

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
    $._atomic_expression,
    $._local_level_declaration,
    $._declaration,
    $._literal,
    $._label,
    $._atomic_pattern,
    $._pattern,
  ],

  word: $ => $._alphanum_identifier,

  rules: {
    source_file: $ => choice(
      $._declaration
    ),

    /************************ IDENTIFIERS ********************************/
    _alphanum_identifier: $ => token(IDA),
    _symbolic_identifier: $ => token(IDS),

    _identifier: $ => choice($._alphanum_identifier, $._symbolic_identifier),
    // _identifier: $ => token(choice(IDA, IDS)),
    identifier: $ => $._identifier,
    index: $ => token(INT),

    qualified_identifier: $ => seq(
      repeat(seq(alias($._alphanum_identifier, $.structure_name), ".")),
      $.identifier
    ),

    // _id: $ => $.identifier,
    // _qualified_id: $ => seq(
    //   field("path", repeat(seq($._alphanum_identifier, "."))),
    //   $._id
    // ),

    real_literal: $ => token(seq(
      optional("~"),
      choice(
        seq(NUM, optional(FRAC), EXPO),
        seq(NUM, FRAC, optional(EXPO))
      )
    )),

    /************************ LITERAL VALUES ****************************/
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

    /************************ ATOMIC EXPRESSIONS ****************************/

    /*  Records */
    identifier_expression: $ => seq(optional("op"), $.qualified_identifier),
    int_label: $ => $.index,
    identifier_label: $ => $.identifier,
    _label: $ => choice($.int_label, $.identifier_label),

    record_row: $ => seq(
      $._label,
      "=",
      $._expression
    ),

    record_expression: $ => seq("{", sep(",", $.record_row), "}"),

    /************************ EXPRESSIONS ****************************/
    let_expression: $ => seq(
      "let",
      optional($._local_level_declarations),
      "in",
      sep1(";", $._expression),
      "end"
    ),

    identifier_expression: $ => seq(
      optional("op"),
      $.qualified_identifier
    ),

    record_selector_expression: $ => seq(
      "#",
      $._label,
    ),

    unit_expression: $ => seq(
      "(", ")"
    ),

    tuple_expression: $ => parenthesize(
      sep2(",", $._expression)
    ),

    list_expression: $ => seq(
      "[",
      sep(",", $._expression),
      "]"
    ),

    sequence_expression: $ => parenthesize(
      sep2(";", $._expression)
    ),

    parenthesized_expression: $ => parenthesize(
      $._expression
    ),

    _atomic_expression: $ => choice(
      $._literal,
      $.record_expression,
      $.let_expression,
      $.identifier_expression,
      $.record_selector_expression,
      $.unit_expression,
      $.tuple_expression,
      $.list_expression,
      $.sequence_expression,
      $.parenthesized_expression,
    ),

    application_expression: $ => repeat2($._atomic_expression),

    typed_expression: $ => prec.left(10, seq(
      $._expression,
      ":",
      $._type
    )),

    conjunction_expression: $ => prec.left(9, seq(
      $._expression,
      "andalso",
      $._expression
    )),

    disjunction_expression: $ => prec.left(8, seq(
      $._expression,
      "orelse",
      $._expression
    )),

    handle_expression: $ => prec(7, seq(
      $._expression,
      "handle",
      $.match,
    )),

    raise_expression: $ => prec(6, seq(
      "raise",
      $._expression
    )),

    conditional_expression: $ => prec(5, seq(
      "if",
      field("if", $._expression),
      "then",
      field("then", $._expression),
      "else",
      field("else", $._expression)
    )),

    iteration_expression: $ => prec(4, seq(
      "while",
      field("while", $._expression),
      "do",
      field("do", $._expression),
    )),

    case_expression: $ => prec(2, seq(
      "case",
      $._expression,
      "of",
      $.match
    )),

    function_expression: $ => prec(1, seq(
      "fn",
      $.match
    )),

    rule: $ => seq(
      $._pattern,
      "=>",
      $._expression
    ),

    match: $ => prec.right(3, sep1("|", $.rule)),

    _expression: $ => choice(
      $._atomic_expression,
      $.application_expression,
      $.typed_expression,
      $.conjunction_expression,
      $.disjunction_expression,
      $.handle_expression,
      $.raise_expression,
      $.conditional_expression,
      $.iteration_expression,
      $.case_expression,
      $.function_expression
    ),

    /************************ PATTERNS ****************************/
    wildcard: _ => token("_"),
    literal_pattern: $ => $._literal,
    identifier_pattern: $ => choice(
      seq("op", $.qualified_identifier),
      seq($.qualified_identifier),
    ),
    list_pattern: $ => seq("[", sep(",", $._pattern), "]"),
    record_pattern: $ => seq("{", sep(",", $.pattern_row), "}"),
    vector_pattern: $ => seq("#[", sep(",", $._pattern), "]"),

    pattern_row: $ => choice(
      alias("...", $.wildcard_row),
      seq($._label, "=", $._pattern),
      seq($.identifier_label, optional(seq(":", $._type)), optional(seq("as", $._pattern)))
    ),

    unit_pattern: $ => seq("(", ")"),
    parenthesized_pattern: $ => parenthesize($._pattern),
    or_pattern: $ => parenthesize(sep2("|", $._pattern)),
    tuple_pattern: $ => parenthesize(sep2(",", $._pattern)),

    _atomic_pattern: $ => choice(
      $.wildcard,
      $.literal_pattern,
      $.identifier_pattern,
      $.list_pattern,
      $.record_pattern,
      $.vector_pattern,
      $.unit_pattern,
      $.tuple_pattern,
      $.or_pattern,
      $.parenthesized_pattern,
    ),

    application_pattern: $ => repeat2($._atomic_pattern),
    constraint_pattern: $ => prec(1, seq($._pattern, ":", $._type)),
    layered_pattern: $ => prec.right(2, seq($._pattern, "as", $._pattern)),
    _pattern: $ => choice(
      $.constraint_pattern,
      $.layered_pattern,
      $._atomic_pattern,
      $.application_pattern,
    ),

    /************************ TYPES ****************************/

    type_identifier: $ => $._identifier,
    _tycon: $ => $.type_identifier,
    qualified_tycon: $ => seq(
      repeat(seq(alias($._alphanum_identifier, $.structure_name), ".")),
      $._tycon
    ),
    tyvar: _ => token(seq("'", IDA)),
    tyvarseq: $ => choice($.tyvar, parenthesize(sep2(",", $.tyvar))),
    type_row: $ => seq($._label, ":", $._type),
    record_type: $ => seq("{", sep(",", $.type_row), "}"),
    tuple_type: $ => sep2("*", $._type0),
    tyapp: $ => seq(
      choice($._type0, parenthesize(sep2(",", $._type))),
      $.qualified_tycon
    ),
    arrow_type: $ => prec.right(1, seq($._type, "->", $._type)),
    _type0: $ => choice(
      $.tyvar,
      $.record_type,
      $.tyapp,
      $.qualified_tycon,
      parenthesize($._type)
    ),
    _type: $ => choice(
      $.tuple_type,
      $.arrow_type,
      $._type0
    ),

    /************************ DECL ****************************/
    value_declaration: $ => seq("val", optional($.tyvarseq), $._valbinds),
    _valbind: $ => choice(
      seq(optional("lazy"), alias($._pattern, $.lhs), "=", alias($._expression, $.rhs)),
      seq(alias("rec", $.rec), $._valbind)
    ),
    _valbinds: $ => sep1("and", alias($._valbind, $.valbind)),


    function_declaration: $ => seq("fun", optional($.tyvarseq), $._fvalbinds),
    _fvalbind_clause: $ => seq(
      alias(repeat1($._atomic_pattern), $.lhs),
      optional(seq(":", field("return_type", $._type))),
      "=",
      alias($._expression, $.rhs)
    ),
    fvalbind: $ => sep1("|", alias($._fvalbind_clause, $.clause)),
    _fvalbinds: $ => sep1("and", $.fvalbind),


    type_declaration: $ => seq("type", $._tybinds),
    tybind: $ => seq(
      optional($.tyvarseq),
      alias($._tycon, $.lhs),
      "=",
      alias($._type, $.rhs)
    ),
    _tybinds: $ => sep1("and", $.tybind),


    datatype_declaration: $ => seq("datatype", $._datbinds),
    datbind: $ => seq(
      optional($.tyvarseq),
      $._tycon,
      "=",
      sep1("|", $._con_or_replication_bind)
    ),
    _datbinds: $ => sep1("and", $.datbind),
    _conbind: $ => seq(
      optional("op"),
      $.identifier,
      optional(seq("of", $._type))
    ),
    _replication_bind: $ => seq(
      "datatype",
      $.qualified_tycon
    ),
    _con_or_replication_bind: $ => choice(
      alias($._conbind, $.constructor),
      alias($._replication_bind, $.replication)
    ),

    abstype_declaration: $ => seq(
      "abstype",
      $._datbinds,
      "with",
      optional($._local_level_declarations),
      "end"
    ),

    exception_declaration: $ => seq(
      "exception",
      $._exbinds
    ),
    exbind: $ => choice(
      seq(optional("op"), $.identifier, optional(seq("of", $._type))),
      seq(optional("op"), $.identifier, "=", optional("op"), $.qualified_identifier)
    ),
    _exbinds: $ => sep1("and", $.exbind),


    local_declaration: $ => seq(
      "local",
      alias(optional($._local_level_declarations), $.local),
      "in",
      alias(optional($._local_level_declarations), $.exposed),
      "end"
    ),


    open_declaration: $ => seq(
      "open",
      repeat1($.qualified_identifier)
    ),


    infixl_declaration: $ => seq(
      "infix",
      optional(/[0-9]/),
      repeat1($.identifier)
    ),

    infixr_declaration: $ => seq(
      "infixr",
      optional(/[0-9]/),
      repeat1($.identifier)
    ),

    nonfix_declaration: $ => seq(
      "nonfix",
      repeat1($.identifier)
    ),

    _local_level_declaration: $ => choice(
      $.value_declaration,
      $.function_declaration,
      $.type_declaration,
      $.datatype_declaration,
      $.abstype_declaration,
      $.exception_declaration,
      $.local_declaration,
      $.open_declaration,
      $.infixl_declaration,
      $.infixr_declaration,
      $.nonfix_declaration,
    ),
    _local_level_declarations: $ => repeat1(
      choice($._local_level_declaration, ";")
    ),

    expression_declaration: $ => $._expression,

    structure_level_declaration: $ => choice(
      $._local_level_declarations,
    ),

    _declaration: $ => choice(
      $.structure_level_declaration,
      $.expression_declaration
    ),
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
  return choice(
    rule,
    parenthesize(sep1(",", rule))
  )
}

function sep(delimiter, rule) {
  return optional(sep1(delimiter, rule))
}

function sep1(delimiter, rule) {
  return seq(rule, repeat(seq(delimiter, rule)))
}

function sep2(delimiter, rule) {
  return seq(rule, repeat1(seq(delimiter, rule)))
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
