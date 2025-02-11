/*
 * @file Tree-sitter parser for Standard ML
 * @author Byron Zhong <zhongbangyuan@gmail.com>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

const INT    = /[1-9][0-9]*/;
const NUM    = /[0-9]+/;
const HEXNUM = /[0-9a-fA-F]+/;
const FRAC   = /\.[0-9]+/;
const EXPO   = /[eE]~?[0-9]+/;
const IDA    = /[A-Za-z][A-Za-z'_0-9]*/;
const IDS    = /[!%&$#+\-/:<>?@\\~`^|=*][!%&$#+\-/:<>?@\\~`^|=*]*/;
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
//    \Uxxxxxxxx
//    \"  \\
const ESCAPE_CHAR =
  /\\(a|b|t|n|v|f|r|"|\\|\^[\x40-\x5F]|[0-9]{3}|u[0-9A-Fa-f]{4}|U[0-9A-Fa-f]{8})/;

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
    $._atomic_expression,
    $._atomic_pattern,
    $._expression,
    $._label,
    $._literal,
    $._local_level_declaration,
    $._pattern,
    $._signature_expression,
    $._spec,
    $._structure_expression,
    $._structure_level_declaration,
    $._top_level_declaration,
  ],

  inline: $ => [
    $._identifier,
    $._label,
    $._valbinds,
    $._fvalbinds,
    $._tybinds,
    $._datbinds,
    $._exbinds,
    $._strbinds,
    $._sigbinds,
    $._funbinds,
  ],

  conflicts: $ => [
    // The `where` expressions as specified is not in LR(1) because we have
    //   structure ... and ...
    // as well as
    //   where type ... and type ...
    //
    // So, if the parser state reaches something like following:
    //   structure A : S where type t = int (·) and
    // peaking at one token is not able to determine if the last `and` should
    // attach to `where type` or `structure`.
    //
    // Examples:
    //     structure A : S where type t = int and type u = bool
    //     and       B : S where type t = int and type u = bool
    // vs
    //     structure A : S
    //       where type t1 = t2
    //         and type t3 = t4
    //         and type t5 = t6
    [$._where_equations]
  ],

  word: $ => $._alphanum_identifier,

  rules: {
    source_file: $ => seq(
      optional($.expression_declaration),
      repeat(choice(
        $._top_level_declaration,
        ";",
        seq(";", $.expression_declaration),
      ))
    ),

    /**************************************************************************/
    /*                                CORE                                    */
    /**************************************************************************/

    /** IDENTIFIERS */
    _alphanum_identifier: $ => token(IDA),
    _symbolic_identifier: $ => token(IDS),

    /* This is vid in the Definition. */
    _identifier: $ => choice(
      $._alphanum_identifier,
      $._symbolic_identifier,
    ),
    identifier: $ => $._identifier,

    /* Indices are positive integers */
    index: $ => token(INT),

    /* Longvid */
    qualified_identifier: $ => seq(
      repeat(seq($.structure_identifier, ".")),
      $.identifier
    ),

    /** LITERAL VALUES */
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

    /** ATOMIC EXPRESSIONS (p.77, fig. 20, atexp) */

    // value identifier
    identifier_expression: $ => seq(
      optional("op"),
      $.qualified_identifier
    ),

    // record
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

    // record selector
    record_selector_expression: $ => seq(
      "#",
      $._label,
    ),

    // 0-tuple
    unit_expression: $ => seq(
      "(", ")"
    ),

    // n-tuple, n >= 2
    tuple_expression: $ => parenthesize(
      sep2(",", $._expression)
    ),

    // list, n >= 0
    list_expression: $ => seq(
      "[",
      sep(",", $._expression),
      "]"
    ),

    // vector, n >= 0 (SML/NJ extension)
    vector_expression: $ => seq(
      "#[",
      sep(",", $._expression),
      "]"
    ),

    // sequence, n >= 2
    sequence_expression: $ => parenthesize(
      sep2(";", $._expression)
    ),

    // local declaration, n >= 1
    let_expression: $ => seq(
      "let",
      optional($._local_level_declarations),
      "in",
      sep1(";", $._expression),
      "end"
    ),

    // expression, making parentheses visible for highlighting
    parenthesized_expression: $ => parenthesize(
      $._expression
    ),

    // atexp
    _atomic_expression: $ => choice(
      $._literal,
      $.record_expression,
      $.let_expression,
      $.identifier_expression,
      $.record_selector_expression,
      $.unit_expression,
      $.tuple_expression,
      $.list_expression,
      $.vector_expression,
      $.sequence_expression,
      $.parenthesized_expression,
    ),

    /** EXPRESSIONS (p. 77, fig. 20) */

    // application expression
    // This is just a list of atexps with no special care about the fixities.
    atomic_application_expression: $ => prec.left(11,
      repeat1($._atomic_expression)
    ),

    // typed
    typed_expression: $ => prec.left(10, seq(
      $._expression,
      $._kw_colon,
      $._type
    )),

    // conjunction
    conjunction_expression: $ => prec.left(9, seq(
      $._expression,
      "andalso",
      $._expression
    )),

    // disjunction
    disjunction_expression: $ => prec.left(8, seq(
      $._expression,
      "orelse",
      $._expression
    )),

    // handle exception
    handle_expression: $ => prec(7, seq(
      $._expression,
      "handle",
      $.match,
    )),

    // raise exception
    raise_expression: $ => prec(6, seq(
      "raise",
      $._expression
    )),

    // conditional
    conditional_expression: $ => prec(5, seq(
      "if",
      field("if", $._expression),
      "then",
      field("then", $._expression),
      "else",
      field("else", $._expression)
    )),

    // iteration
    iteration_expression: $ => prec(4, seq(
      "while",
      field("while", $._expression),
      "do",
      field("do", $._expression),
    )),

    // case analysis
    case_expression: $ => prec(2, seq(
      "case",
      $._expression,
      "of",
      $.match
    )),

    // function
    function_expression: $ => prec(1, seq(
      "fn",
      $.match
    )),

    // mrule
    rule: $ => seq(
      $._pattern,
      $._kw_darrow,
      prec.right($._expression),
    ),

    // match
    match: $ => prec.right(seq($.rule, repeat(seq($._kw_bar, $.rule)))),

    // exp
    _expression: $ => choice(
      $.atomic_application_expression,
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

    /** patterns (p. 79, fig. 22) */

    // wildcard
    wildcard: _ => token("_"),

    // special constant
    literal_pattern: $ => $._literal,

    // value identifier
    identifier_pattern: $ => seq(
      optional("op"),
      $.qualified_identifier
    ),

    // 0-tuple
    unit_pattern: $ => seq("(", ")"),

    // n-tuple, n >= 2
    tuple_pattern: $ => parenthesize(sep2(",", $._pattern)),

    // list pattern, n >= 0
    list_pattern: $ => seq("[", sep(",", $._pattern), "]"),

    // record
    record_pattern: $ => seq("{", sep(",", $.pattern_row), "}"),

    // vector (SMLNJ extension)
    vector_pattern: $ => seq("#[", sep(",", $._pattern), "]"),

    // patrow
    pattern_row: $ => choice(
      alias("...", $.wildcard_row),
      seq($._label, "=", $._pattern),
      seq(
        $.identifier_label,
        optional(seq($._kw_colon, $._type)),
        optional(seq("as", $._pattern))
      )
    ),

    parenthesized_pattern: $ => parenthesize($._pattern),

    // or pattern (SML/NJ extension)
    or_pattern: $ => parenthesize(sep2($._kw_bar, $._pattern)),

    // atpat
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

    // constructed value
    // Same as application expression, this does not care about fixity.
    application_pattern: $ => repeat2($._atomic_pattern),

    // NOTE:  pat : type  as pat  : type is parsed as:
    //      ((pat : type) as pat) : type

    // typed
    constraint_pattern: $ => prec(1, seq($._pattern, $._kw_colon, $._type)),

    // layered
    layered_pattern: $ => prec.right(2, seq($._pattern, "as", $._pattern)),

    // pat
    _pattern: $ => choice(
      $.constraint_pattern,
      $.layered_pattern,
      $._atomic_pattern,
      $.application_pattern,
    ),

    /** TYPES (p. 79, fig. 23) */

    // tycon
    type_identifier: $ => $._identifier,

    // longtycon
    qualified_identifier: $ => seq(
      repeat(seq(alias($._alphanum_identifier, $.structure_name), ".")),
      $.type_identifier
    ),

    // tyvar
    tyvar: _ => token(seq("'", /[A-Za-z'_0-9]*/)),

    // non-empty tyvarseq
    tyvarseq: $ => choice($.tyvar, parenthesize(sep2(",", $.tyvar))),

    // record type expression
    record_type: $ => seq("{", sep(",", $.type_row), "}"),

    // tyrow
    type_row: $ => seq($._label, $._kw_colon, $._type),

    // tuple type, n >= 2
    tuple_type: $ => sep2("*", $._type0),

    // type construction
    tyapp: $ => seq(
      choice($._type0, parenthesize(sep2(",", $._type))),
      $.qualified_identifier
    ),

    // function type expression
    arrow_type: $ => prec.right(1, seq($._type, $._kw_arrow, $._type)),

    // _type0 are the atomic types
    _type0: $ => choice(
      $.tyvar,
      $.record_type,
      $.tyapp,
      $.qualified_identifier,
      parenthesize($._type)
    ),

    // ty
    _type: $ => choice(
      $.tuple_type,
      $.arrow_type,
      $._type0
    ),

    /** local level declarations (p. 78, fig. 21) */

    value_declaration: $ => seq("val", optional($.tyvarseq), $._valbinds),
    _valbind: $ => choice(
      seq(optional("lazy"), alias($._pattern, $.lhs), "=", alias($._expression, $.rhs)),
      seq(alias("rec", $.rec), $._valbind)
    ),
    _valbinds: $ => sep1("and", alias($._valbind, $.valbind)),

    function_declaration: $ => seq("fun", optional($.tyvarseq), $._fvalbinds),
    _clause_arguments: $ => repeat1($._atomic_pattern),
    clause: $ => prec.right(0, seq(
      alias($._clause_arguments, $.lhs),
      optional(seq($._kw_colon, field("return_type", $._type))),
      "=",
      alias(prec.right($._expression), $.rhs)
    )),
    fvalbind: $ => prec.right(0, seq(
      $.clause,
      repeat(seq($._kw_bar, $.clause)),
    )),
    _fvalbinds: $ => sep1("and", $.fvalbind),

    type_declaration: $ => seq("type", $._tybinds),
    tybind: $ => seq(
      optional($.tyvarseq),
      alias($.type_identifier, $.lhs),
      "=",
      alias($._type, $.rhs)
    ),
    _tybinds: $ => sep1("and", $.tybind),

    datatype_declaration: $ => seq(
      "datatype",
      $._datbinds,
      optional($.withtype)
    ),
    datbind: $ => seq(
      optional($.tyvarseq),
      $.type_identifier,
      "=",
      sep1($._kw_bar, $._con_or_replication_bind)
    ),
    _datbinds: $ => sep1("and", $.datbind),
    _conbind: $ => seq(
      optional("op"),
      $.identifier,
      optional(seq("of", $._type))
    ),
    _replication_bind: $ => seq(
      "datatype",
      $.qualified_identifier
    ),
    _con_or_replication_bind: $ => choice(
      alias($._conbind, $.constructor),
      alias($._replication_bind, $.replication)
    ),
    withtype: $ => seq(
      "withtype",
      $._tybinds,
    ),

    abstype_declaration: $ => seq(
      "abstype",
      $._datbinds,
      optional($.withtype),
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

    open_declaration: $ => seq(
      "open",
      prec.left(repeat1($.qualified_structure_identifier)),
    ),

    infixl_declaration: $ => seq(
      "infix",
      optional(/[0-9]/),
      prec.left(repeat1($.identifier))
    ),

    infixr_declaration: $ => seq(
      "infixr",
      optional(/[0-9]/),
      prec.left(repeat1($.identifier))
    ),

    nonfix_declaration: $ => seq(
      "nonfix",
      prec.left(repeat1($.identifier))
    ),

    local_declaration: $ => seq(
      "local",
      alias(optional($._local_level_declarations), $.local),
      "in",
      alias(optional($._local_level_declarations), $.exposed),
      "end"
    ),

    // dec
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
      choice(
        $._local_level_declaration,
        ";",
      )
    ),

    /**************************************************************************/
    /*                              MODULES                                   */
    /**************************************************************************/

    // strid
    structure_identifier: $ => $._alphanum_identifier,

    // longstrid
    qualified_structure_identifier: $ => seq(
      repeat(seq($.structure_identifier, ".")),
      $.structure_identifier
    ),

    /** STRUCTURE EXPRESSIONS (p. 14, fig. 6) */

    struct_expression: $ => seq(
      "struct",
      optional($._structure_level_declarations),
      "end"
    ),

    struct_identifier_expression: $ => $.qualified_structure_identifier,

    transparent_constraint_expression: $ => seq(
      $._structure_expression,
      $._kw_colon,
      $._signature_expression
    ),

    opaque_constraint_expression: $ => seq(
      $._structure_expression,
      ":>",
      $._signature_expression
    ),

    functor_application_expression: $ => seq(
      $.functor_identifier,
      "(",
        choice(
          $._structure_expression,
          optional($._structure_level_declarations),
        ),
      ")"
    ),

    structure_local_expression: $ => seq(
      "let",
      optional($._structure_level_declarations),
      "in",
      $._structure_expression,
      "end"
    ),

    // strexp
    _structure_expression: $ => choice(
      $.struct_expression,
      $.struct_identifier_expression,
      $.transparent_constraint_expression,
      $.opaque_constraint_expression,
      $.functor_application_expression,
      $.structure_local_expression
    ),

    /** STRUCTURE DECLARATIONS (p. 14, fig. 6) */

    structure_declaration: $ => seq(
      "structure",
      $._strbinds
    ),
    strbind: $ => choice(
      seq($.structure_identifier, "=", $._structure_expression),
      seq($.structure_identifier, $._kw_colon, $._signature_expression, "=", $._structure_expression),
      seq($.structure_identifier, ":>", $._signature_expression, "=", $._structure_expression),
    ),
    _strbinds: $ => sep1("and", $.strbind),

    structure_local_declaration: $ => seq(
      "local",
      alias(optional($._structure_level_declarations), $.local),
      "in",
      alias(optional($._structure_level_declarations), $.exposed),
      "end"
    ),

    // strdec
    // _local_level_declaration is inlined here except for $.local_declaration
    // to avoid conflict with $.structure_local_declaration.
    _structure_level_declaration: $ => choice(
      $.value_declaration,
      $.function_declaration,
      $.type_declaration,
      $.datatype_declaration,
      $.abstype_declaration,
      $.exception_declaration,
      $.open_declaration,
      $.infixl_declaration,
      $.infixr_declaration,
      $.nonfix_declaration,
      $.structure_declaration,
      $.functor_declaration,
      $.signature_declaration,
      $.structure_local_declaration,
    ),
    _structure_level_declarations: $ => repeat1(
      choice($._structure_level_declaration, ";")
    ),

    /** SIGNATURES (p. 14, fig. 6) */

    sig_expression: $ => seq(
      "sig",
      optional($._specs),
      "end"
    ),
    signature_identifier: $ => $._alphanum_identifier,
    signature_identifier_expression: $ => $.signature_identifier,
    type_realization_expression: $ => seq(
      $._signature_expression,
      "where",
      $._where_equations,
    ),
    where_equation: $ => choice(
      seq("type", optional($.tyvarseq), $.qualified_identifier, "=", $._type),
      seq($.qualified_structure_identifier, "=", $.qualified_structure_identifier)
    ),
    _where_equations: $ => sep1("and", $.where_equation),

    // sigexp
    _signature_expression: $ => choice(
      $.sig_expression,
      $.signature_identifier_expression,
      $.type_realization_expression,
    ),

    sigbind: $ => seq(
      $.signature_identifier,
      "=",
      $._signature_expression,
    ),
    _sigbinds: $ => sep1("and", $.sigbind),

    // sigdec
    signature_declaration: $ => seq(
      "signature",
      $._sigbinds,
    ),

    /** SPEC (p. 15, fig. 7) */

    value_spec: $ => seq(
      "val", $._valdescs
    ),
    valdesc: $ => seq(
      $.identifier, $._kw_colon, $._type
    ),
    _valdescs: $ => sep1("and", $.valdesc),

    type_spec: $ => seq(
      "type", choice(
        $._typdescs,
        $._tybinds
      ),
    ),
    typdesc: $ => seq(
      optional($.tyvarseq),
      $.type_identifier
    ),
    _typdescs: $ => sep1("and", $.typdesc),

    eqtype_spec: $ => seq(
      "eqtype", $._typdescs
    ),

    datatype_spec: $ => seq(
      "datatype", $._datdescs
    ),
    datdesc: $ => seq(
      optional($.tyvarseq),
      $.type_identifier,
      "=",
      $._condescs
    ),
    _datdescs: $ => sep1("and", $.datdesc),
    condesc: $ => seq(
      $.identifier,
      optional(seq("of", $._type))
    ),
    _condescs: $ => sep1($._kw_bar, $.condesc),

    replication_spec: $ => seq(
      "datatype",
      $.type_identifier,
      "=",
      "datatype",
      $.qualified_identifier
    ),

    exception_spec: $ => seq(
      "exception",
      $._exdescs
    ),
    exdesc: $ => seq(
      $.identifier,
      optional(seq("of", $._type)),
    ),
    _exdescs: $ => sep1("and", $.exdesc),

    structure_spec: $ => seq(
      "structure",
      $._strdescs,
    ),
    strdesc: $ => seq(
      $.structure_identifier,
      $._kw_colon,
      $._signature_expression
    ),
    _strdescs: $ => sep1("and", $.strdesc),

    include_spec: $ => seq(
      "include",
      choice(
        repeat1($.signature_identifier_expression),
        $.sig_expression,
        $.type_realization_expression,
      ),
    ),

    sharing_spec: $ => prec.left(0, seq(
      optional($._specs),
      "sharing",
      choice(
        seq("type", sep2("=", $.qualified_identifier)),
        sep2("=", $.qualified_structure_identifier)
      ),
    )),

    // spec
    _spec: $ => choice(
      $.value_spec,
      $.type_spec,
      $.eqtype_spec,
      $.datatype_spec,
      $.replication_spec,
      $.exception_spec,
      $.structure_spec,
      $.include_spec,
      $.sharing_spec
    ),
    _specs: $ => prec.left(1, repeat1(
      prec.left(1, choice($._spec, ";"))
    )),

    /** FUNCTORS (p. 15, fig. 8) */

    functor_declaration: $ => seq(
      "functor",
      $._funbinds
    ),
    functor_identifier: $ => $._alphanum_identifier,
    funbind: $ => seq(
      $.functor_identifier,
      optional(seq("(",
        choice(
          seq($.structure_identifier, $._kw_colon, $._signature_expression),
          optional($._specs),
        ),
      ")")),
      optional(seq(
        choice($._kw_colon, ":>"),
        $._signature_expression
      )),
      "=",
      $._structure_expression
    ),
    _funbinds: $ => sep1("and", $.funbind),

    /** TOP LEVEL */
    expression_declaration: $ => $._expression,

    _top_level_declaration: $ => $._structure_level_declaration,

    _kw_colon: $ => ":",
    _kw_bar: $ => "|",
    _kw_darrow: $ => "=>",
    _kw_arrow: $ => "->",
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
