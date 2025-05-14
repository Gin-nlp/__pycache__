%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* prototypes so implicit‐declaration warnings go away */
int yylex(void);
void yyerror(const char *s);
%}

/* semantic value */
%union {
    double dval;
    char  *sval;
}

/* tokens */
%token <sval> IDENTIFIER
%token <dval> NUMBER
%token POW LOG

/* precedence */
%left '+' '-'
%left '*' '/'
%right UMINUS

%type  <dval> expr

%%

input:
    /* one statement then end‐of‐file */
    stmt '\n'   { /* done */ }
  ;

stmt:
    IDENTIFIER '=' expr
  {
    printf("%s = %g\n", $1, $3);
    free($1);
  }
  ;

expr:
    expr '+' expr   { $$ = $1 + $3; }
  | expr '-' expr   { $$ = $1 - $3; }
  | expr '*' expr   { $$ = $1 * $3; }
  | expr '/' expr   { $$ = $1 / $3; }
  | '-' expr  %prec UMINUS { $$ = -$2; }
  | '(' expr ')'    { $$ = $2; }
  | NUMBER          { $$ = $1; }
  | POW '(' expr ',' expr ')' { $$ = pow($3, $5); }
  | LOG '(' expr ')'          { $$ = log($3); }
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main(void) {
    return yyparse();
}
