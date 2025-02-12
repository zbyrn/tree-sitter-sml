; Scopes

(clause) @local.scope
(match) @local.scope
(let_expression) @local.scope
(structure_local_expression) @local.scope
(local) @local.scope
(sig_expression) @local.scope
(struct_expression) @local.scope

; Var Definitions
(identifier_pattern
  (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @local.definition.var))

(constructor [(alphanum_identifier) (symbolic_identifier)] @local.definition.enum)

(fvalbind
  (clause
    (lhs .
         (identifier_pattern
           (qualified_identifier
             [(alphanum_identifier) (symbolic_identifier)]
             @local.definition.var
             (#set! definition.var.scope "parent"))))))

; Type Definitions
(tybind (lhs [(alphanum_identifier) (symbolic_identifier)] @local.definition.type))
(datbind (lhs
           [(alphanum_identifier) (symbolic_identifier)] @local.definition.type))

; Uses
(identifier_expression
  (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @local.reference))

(type_identifier [(alphanum_identifier) (symbolic_identifier)] @local.reference)
