%{
#include <stdio.h>
#include <string.h>
%}

%%

"the"|"a"|"an"                                 { printf("%s : Article\n", yytext); }
"he"|"she"|"it"|"they"|"we"|"you"|"I"          { printf("%s : Pronoun\n", yytext); }
"from"|"to"|"in"|"on"|"at"|"with"              { printf("%s : Preposition\n", yytext); }
"and"|"or"|"but"|"because"                     { printf("%s : Conjunction\n", yytext); }
"run"|"dread"|"arrives"|"go"|"come"|"eat"      { printf("%s : Verb\n", yytext); }
"destiny"|"time"|"man"|"power"|"stone"         { printf("%s : Noun\n", yytext); }
"."|"!"|"?"                                     { printf("%s : Punctuation\n", yytext); }
[ \t\n]+                                        { /* skip whitespace */ }
[a-zA-Z]+                                       { printf("%s : Unknown\n", yytext); }

%%

int main(int argc, char **argv)
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
