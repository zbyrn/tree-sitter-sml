; Scopes

(clause) @local.scope
(match) @local.scope
(let_expression) @local.scope
(structure_local_expression) @local.scope
(local) @local.scope
(sig_expression) @local.scope
(struct_expression) @local.scope

; Definitions
(identifier_pattern 
  (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @local.definition))

(constructor [(alphanum_identifier) (symbolic_identifier)] @local.definition)

; Uses
(identifier_expression
  (qualified_identifier [(alphanum_identifier) (symbolic_identifier)] @local.reference))

