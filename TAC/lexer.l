%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%
"PROGRAM"           { return PROGRAM; }
"INTEGER"           { return INTEGER; }
"READ"              { return READ; }
"PRINT"             { return PRINT; }
"DO"                { return DO; }
"END"               { return END; }
[A-Za-z][A-Za-z0-9]* { yylval.strVal = strdup(yytext); return IDENTIFIER; }
[0-9]+              { yylval.intVal = atoi(yytext); return NUM; }
"="                 { return ASSIGNOP; }
","                 { return COMMA; }
"*"                 { return TIMES; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"/"                 { return DIVIDE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
\"[^\"]*\"          { yylval.strVal = strdup(yytext); return STRING; }
[ \t\n]+            { /* ignore whitespace */ }
.                   { return yytext[0]; }
%%

int yywrap() {
    return 1;
}