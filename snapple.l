%{
#include "SymbolTable.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "snapple.tab.h" // to get the token types

int line_num = 1;
%}
%%
[ \t]         ;
var             { return VAR; }
end             { return END; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"/"             { return SLASH; }
"*"             { return ASTERISK; }
[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+          { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z0-9]+    { 
        // make a copy of the string
        yylval.sval = strdup(yytext);
        return STRING;
 }
=               { return EQUALS; }
\n              { ++line_num; return ENDL; }
.               ;
%%
