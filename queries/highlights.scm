; Functions and Variables
;--------------

; Generic variables
(
 (identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @variable))
 (#not-match? @variable "^[A-Z]")
)

; Datatype constructors
(constructor . [(alphanum_identifier) (symbolic_identifier)] @constructor)
(condesc . [(alphanum_identifier) (symbolic_identifier)] @constructor)

(exbind . [(alphanum_identifier) (symbolic_identifier)] @constructor)
(exdesc [(alphanum_identifier) (symbolic_identifier)] @constructor)

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
; Disabled because the false positive rate is too high.

; Highlight the first, unqualified identifier.
;(fvalbind (clause (lhs .
;  (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)])) @function
;  (_))))

; If the first symbol is a application pattern, highlight the middle.
;(fvalbind (clause (lhs .
;  (parenthesized_pattern
;    (application_pattern .
;      (_) .
;      (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)])) @function .
;      (_)))
;  (_))))

; Highlight f in val f = fn => _ syntax
;(valbind
;  (lhs (identifier_pattern (qualified_identifier [(alphanum_identifier) (symbolic_identifier)]) @function))
;  (rhs (function_expression)))

; Highlight selectors
(record_row [(int_label) (identifier_label)] @property)

(pattern_row [(int_label) (identifier_label)] @property)

(type_row [(int_label) (identifier_label)] @property)

(record_selector_expression) @property

; Types
;----------------

(datbind (lhs [(alphanum_identifier) (symbolic_identifier)] @type))
(tybind  (lhs [(alphanum_identifier) (symbolic_identifier)] @type))

(type_identifier (alphanum_identifier) @type)

(
 (type_identifier (alphanum_identifier) @type.builtin)
 (#match? @type.builtin "^(unit|int|word|real|char|string|substring|exn|array|vector|ref|bool|option|order|list)$")
)

(tyvar) @variable.parameter

; Punctuation
;--------------

[ "." "," ":" ";" "|" "=" "=>" "->" ":>" ] @punctuation.delimiter

[(wildcard) (wildcard_row)] @variable.parameter.builtin

[ "(" ")" "[" "#[" "]" "{" "}" ] @punctuation.bracket


; Keywords
;--------------

[ "and" "as" "case" "do" "end"
  "in" "infix" "infixr" "let" "local"
  "nonfix" "of" "op" "val" "with"
  "functor" "sharing" "sig" "signature"
  "struct" "structure" "where" ] @keyword

[ "fn" "fun" ] @keyword.function
[ "andalso" "orelse" ] @keyword.operator
[ "abstype" "datatype" "type" "eqtype" "withtype" ] @keyword.type
[ (rec) ] @keyword.modifier
[ "while" "do" ] @keyword.repeat
[ "exception" "raise" "handle" ] @keyword.exception

[ "if" "then" "else" ] @keyword.conditional

[ "include" "open" ] @keyword.import


; Operators
;--------------
(
 (identifier_expression (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @function.builtin))
 (#match? @function.builtin
    "^(div|mod|before|\\*|\\+|^|::|\\@|\\=|\\<\\>|\\>|\\>\\=|\\<|\\<\\=|:\\=|o|!)$")
 (#set! priority 101)
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

; Set priority over brackets
((unit_expression) @constant.builtin (#set! priority 101))
((unit_pattern) @constant.builtin (#set! priority 101))

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
