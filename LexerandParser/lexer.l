%{
#define INTEGER 1
#define STRING 2
#define IDENTIFIER 3
#define READ 4
#define PRINT 5
#define IF 6
#define THEN 7
#define ELSE 8
#define DO 9
#define PROGRAM 10
#define END 11
#define GT 12
#define LT 13
#define EQ 14
#define PLUS 15
#define MINUS 16
#define TIMES 17
#define DIVIDE 18
#define LPAREN 19
#define RPAREN 20
#define LBRACKET 21
#define RBRACKET 22
#define COMMA 23
#define SEMICOLON 24
#define COLON 25
#define ASSIGN 26


#include <stdlib.h>
#include <string.h>

typedef union {
    int intVal;
    char* strVal;
} YYSTYPE;

YYSTYPE yylval;
%}


%%
"PROGRAM"          { return PROGRAM; }
"INTEGER"          { return INTEGER; }
"READ"             { return READ; }
"PRINT"            { return PRINT; }
"IF"               { return IF; }
"THEN"             { return THEN; }
"ELSE"             { return ELSE; }
"DO"               { return DO; }
"END"              { return END; }
".GT."             { return GT; }
".LT."             { return LT; }
".EQ."             { return EQ; }
[0-9]+        { yylval.intVal = atoi(yytext); return INTEGER; }
[a-z][a-z]* { yylval.strVal = strdup(yytext); return IDENTIFIER; }
\"[^\"\n]*\"  { yylval.strVal = strdup(yytext); return STRING; }
"+"                { return PLUS; }
"-"                { return MINUS; }
"*"                { return TIMES; }
"/"                { return DIVIDE; }
"("                { return LPAREN; }
")"                { return RPAREN; }
"["                { return LBRACKET; }
"]"                { return RBRACKET; }
","                { return COMMA; }
";"                { return SEMICOLON; }
":"                { return COLON; }
"="                { return ASSIGN; }
[\n]+              { /* Ignore new lines */ }
[\t ]+             { /* Ignore whitespaces */ }
"!".*              { /* Ignore comments */ }
.                  { printf("Unrecognized token: %s\n", yytext); exit(1); }
%%

int yywrap() {
    return 1;
}