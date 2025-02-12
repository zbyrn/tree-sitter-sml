; Functions and Variables
;--------------

; Generic variables
(identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @variable))

; Datatype constructors
(constructor . [(alphanum_identifier) (symbolic_identifier)] @constructor)

; Probably datatype constructor
(
 (identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @constructor))
 (#match? @constructor "^[A-Z]")
)

; Patterns are binding forms
(identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @variable.parameter))

; Probably datatype constructor pattern
(
 (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @constructor))
 (#match? @constructor "^[A-Z]")
)

; Structure names
[(structure_identifier) (functor_identifier) (signature_identifier)] @module

; Since the parser doesn't know about infix operators, this is only a heuristic.
; Disable the following if the false positive rate is too high.

; Highlight the first, unqualified identifier.
(fvalbind (clause (lhs .
  (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)])) @function
  (_))))

; If the first symbol is a application pattern, highlight the middle.
(fvalbind (clause (lhs .
  (parenthesized_pattern
    (application_pattern .
      (_) .
      (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)])) @function .
      (_)))
  (_))))

; Highlight f in val f = fn => _ syntax
(valbind
  (lhs (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)]) @function))
  (rhs (function_expression)))

[(int_label) (identifier_label)] @property

(record_selector_expression) @function.builtin

; Types
;----------------

(type_identifier) @type

(
 (type_identifier) @type.builtin
 (#match? @type.builtin "^(unit|int|word|real|char|string|substring|exn|array|vector|ref|bool|option|order|list)$")
)

(tyvar) @label

; Punctuation
;--------------

[ "." "," ":" ";" "|" "=" "=>" "->" ":>" (wildcard_row) ] @punctuation.delimiter

[ "(" ")" "[" "#[" "]" "{" "}" ] @punctuation.bracket


; Keywords
;--------------

[ "abstype" "and" "andalso" "as" "case" "datatype" "do" "end"
  "exception" "fn" "fun" "handle" "in" "infix" "infixr" "let" "local"
  "nonfix" "of" "op" "orelse" "raise" (rec) "type" "val" "with"
  "withtype" "while" "eqtype" "functor" "sharing" "sig" "signature"
  "struct" "structure" "where" ] @keyword

[ "if" "then" "else" ] @keyword.conditional

[ "include" "open" ] @keyword.import


; Operators
;--------------
(
 (identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @operator))
 (#match? @operator
    "^(div|mod|before|\\*|\\+|^|::|@|=|<>|>|>=|<|<=|:=|o)$")
)



; Constants
;--------------

(
 (identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @constant.builtin))
 (#match? @constant.builtin
    "^(true|false)$")
)

(
 (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @constant.builtin))
 (#match? @constant.builtin
    "^(true|false)$")
)

[(integer_literal) (word_literal) (real_literal)] @number

(string_literal) @string

(char_literal) @character

(unit_expression) @constant.builtin

; Comments
;--------------

(comment) @comment

(
 (comment)+ @comment.documentation
 (function_declaration)
)

(
 (comment)+ @comment.documentation
 (structure_declaration)
)

(
 (comment)+ @comment.documentation
 (functor_declaration)
)

(
 (comment)+ @comment.documentation
 (signature_declaration)
)

(
 (comment)+ @comment.documentation
 (value_spec)
)
