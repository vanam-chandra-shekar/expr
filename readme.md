

NUMBER : [0-9]+ ('.' [0-9]+)?;  
PLUS   : '+' ;  
MINUS  : '-' ;  
MULT   : '*' ;  
DIV    : '/' ;  
LPAREN : '(' ;  
RPAREN : ')' ;  
WS     : [ \t\r\n]+ -> skip ;  
CARROT : '^';  
SIN : 'sin';  
COS : 'cos';  
TAN : 'tan';  
LN : 'ln';  
PI :  'PI';  
E: 'E';  


$$expr   \rightarrow binary; $$
$$binary \rightarrow  term ((PLUS | MINUS) term)*;  $$
$$term   \rightarrow  unary ((DIV | MULT) unary)*;$$
$$unary  \rightarrow  MINUS unary | expo;$$
$$expo : func (CARROT func)*;$$
$$func : SIN primary 
    | COS primary | TAN primary| LN primary | primary;$$
$$primary: NUMBER | PI | E |LPAREN expr RPAREN;$$
