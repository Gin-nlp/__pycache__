%{
#include <stdio.h>
%}

%%

"int"|"float"                 { printf("%s : Keyword\n", yytext); }
[0-9]*\.[0-9]+|[0-9]+         { printf("%s : Number\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*        { printf("%s : Identifier\n", yytext); }
"="                           { printf("%s : Assignment Operator\n", yytext); }
"+"                           { printf("%s : Arithmetic Operator\n", yytext); }
"-"                           { printf("%s : Arithmetic Operator\n", yytext); }
"*"                           { printf("%s : Arithmetic Operator\n", yytext); }
"/"                           { printf("%s : Arithmetic Operator\n", yytext); }
"("                           { printf("%s : Parenthesis\n", yytext); }
")"                           { printf("%s : Parenthesis\n", yytext); }
"{"                           { printf("%s : Block Delimiter\n", yytext); }
"}"                           { printf("%s : Block Delimiter\n", yytext); }
";"                           { printf("%s : Semicolon\n", yytext); }
[ \t\n]+                      { /* skip whitespace */ }
.                             { printf("%s : Unknown Token\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
