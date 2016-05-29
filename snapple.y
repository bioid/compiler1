%{
#include <cstdio>
#include <iostream>
#include "SymbolTable.h"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

extern int line_num;
void yyerror(const char *s);
SymbolTable *ST = new SymbolTable();
%}
// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union { 
        int ival;
        float fval;
        char *sval;
        SymbolTable *ST;
}

// define the constant-string tokens:
%token END ENDL VAR
%token EQUALS PLUS MINUS SLASH ASTERISK
// define the "terminal symbol" token types
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%type <ival> expr
%%

// this is the actual grammar that bison will parse
// the first rule defined is the highest-level rule

snapple:
        template body_section footer { cout << "done!" << endl; }
        ;
template:
        typelines; 
typelines:
        typelines typeline
        | typeline
        ;
typeline:
        VAR STRING STRING ENDLS { 
                if (ST->addSymbol($3, $2) == NULL)
                        yyerror("Symbol already defined"); 
                printf("New type defined: %s %s\n", $2, $3);
        }
        ;
body_section:
        body_lines
        ;
body_lines:
        body_lines body_line
        | body_line
        ;
body_line: 
        STRING EQUALS expr ENDLS     { 
                if (ST->setValue($1, $3) < 0) 
                        yyerror("Symbol referenced but not declared");
                printf("Set %s to %d\n", $1, $3);        
        }
        | expr ENDLS
        | STRING ENDLS {
                symbol *val;
                if ((val = ST->getSymbol($1)) == NULL)
                        yyerror("Symbol referenced but not declared");
                printf("%s is %d\n", $1, *((int*)val->val));
        }
        ;
expr:
        INT PLUS INT          { $$ = $1 + $3; }
        | INT MINUS INT       { $$ = $1 - $3; }
        | expr PLUS expr      { $$ = $1 + $3; }
        | expr MINUS expr     { $$ = $1 - $3; } 
        | INT                 { $$ = $1; }
        ;
footer:
        END ENDLS
        ;
ENDLS:
        ENDLS ENDL
        | ENDL 
        ;       
%%

int main(int, char* argv[]) {
        // open the file:
        FILE *source = fopen(argv[1], "r");
        if (!source) {
                cout << "Can't open the file!" << endl;
                return -1; 
        }
        yyin = source;
        // lex through the input
        do {
                yyparse();
        } while (!feof(yyin));
}

void yyerror(const char *s) {
        cout << "Parse error! Line: " << line_num << " Message: " << s << endl;
        // might as well halt now
        exit(-1);
}
