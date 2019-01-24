/////////////// NOYAU DE LA GRAMMAIRE DU PASCAL : les règles syntaxiques
PROGRAM ::= program ID; BLOCK.
BLOCK   ::= CONSTS VARS INSTS
CONSTS  ::= const ID = NUM; { ID = NUM; } | epsilon  
VARS    ::= var ID {, ID }; | epsilon
INSTS   ::= begin INST {; INST } end
INST    ::= INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | epsilon
AFFEC   ::= ID := EXPR
SI      ::= if COND then INST 
TANTQUE ::= while COND do INST 
ECRIRE  ::= write (EXPR {, EXPR}) 
LIRE    ::= read ( ID { , ID } )
COND    ::= EXPR [= | <> | < | > | <= | >=] EXPR
EXPR    ::= TERM { [+|-] FACT}
TERM    ::= FACT { [*|/] FACT }
FACT    ::= ID | NUM | (EXPR)