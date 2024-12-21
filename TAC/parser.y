%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function prototypes
int yylex(void);
void yyerror(const char *s); // Declare yyerror
%}

%union {
    int intVal;
    char* strVal;
}

%token <intVal> NUM
%token <strVal> IDENTIFIER STRING
%token PROGRAM INTEGER READ PRINT DO END
%token ASSIGNOP COMMA PLUS MINUS TIMES DIVIDE LPAREN RPAREN

%%
program:
    PROGRAM declarations statements END PROGRAM IDENTIFIER
    ;

declarations:
    declarations declaration
    | /* empty */
    ;

declaration:
    INTEGER IDENTIFIER
    ;

statements:
    statements statement
    | /* empty */
    ;

statement:
    READ COMMA IDENTIFIER
    | PRINT COMMA STRING COMMA IDENTIFIER
    | IDENTIFIER ASSIGNOP expression
    | DO IDENTIFIER ASSIGNOP expression COMMA expression statements END DO
    ;

expression:
    expression PLUS term
    | expression MINUS term
    | term
    ;

term:
    term TIMES factor
    | term DIVIDE factor
    | factor
    ;

factor:
    NUM
    | IDENTIFIER
    | LPAREN expression RPAREN
    ;
%%

// Define yyerror function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
