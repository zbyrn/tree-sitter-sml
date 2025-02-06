/**
 * @file Tree-sitter parser for Standard ML
 * @author Byron Zhong <zhongbangyuan@gmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

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
    $._atomic_expression
  ],

  rules: {
    source_file: $ => choice(
      $._atomic_expression
    ),

    // lexical analysis
    _alphanum_identifier: $ => token(IDA),
    _symbolic_identifier: $ => token(IDS),

    real_constant: $ => token(seq(
      optional("~"),
      choice(
        seq(NUM, optional(FRAC), EXPO),
        seq(NUM, FRAC, optional(EXPO))
      )
    )),
    integer_constant: $ => token(choice(
      NUM,
      seq("~", NUM),
      seq("0x", HEXNUM),
      seq("~0x", HEXNUM)
    )),
    word_constant: $ => token(choice(
      seq("0w", NUM),
      seq("0wx", HEXNUM)
    )),

    string_constant: $ => token(seq(
      "\"",
      repeat(choice(IGNORED_SEQ, ESCAPE_CHAR, ORD_CHAR)),
      "\""
    )),

    char_constant: $ => token(seq(
      "#", "\"",
      repeat(IGNORED_SEQ),
      choice(ESCAPE_CHAR, ORD_CHAR),
      repeat(IGNORED_SEQ), "\""
    )),

    _atomic_expression: $ => choice(
      $.integer_constant,
      $.real_constant,
      $.word_constant,
      $.string_constant,
      $.char_constant
    ),
  }
});
