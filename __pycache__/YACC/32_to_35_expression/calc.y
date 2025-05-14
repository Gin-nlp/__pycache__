%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
    double d;
}

%token <d> NUM
%type  <d> expr term factor

%left '+' '-'
%left '*' '/'

%%

input:
    expr         { printf("Result = %g\n", $1); }
  ;

expr:
    expr '+' term   { $$ = $1 + $3; }
  | expr '-' term   { $$ = $1 - $3; }
  | term            { $$ = $1;       }
  ;

term:
    term '*' factor { $$ = $1 * $3; }
  | term '/' factor { $$ = $1 / $3; }
  | factor          { $$ = $1;       }
  ;

factor:
    NUM              { $$ = $1;       }
  | '(' expr ')'     { $$ = $2;       }
  ;

%%

int main(void) {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
