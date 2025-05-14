%option noyywrap
%{
#include "y.tab.h"
%}

%%

[0-9]+(\.[0-9]+)?    { yylval.d = atof(yytext); return NUM; }
[ \t\r\n]+           { /* skip whitespace */ }
"*"                  { return '*'; }
"/"                  { return '/'; }
"+"                  { return '+'; }
"-"                  { return '-'; }
"("                  { return '('; }
")"                  { return ')'; }
.                    { /* ignore other */ }

%%
