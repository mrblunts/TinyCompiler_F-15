%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
extern int yyerror(char *s);
%}

%token ID NUM RELOP ADDOP MULOP ASSIGNOP

%left ADDOP
%left MULOP
%nonassoc RELOP

%%
stmt_list:
        | stmt_list ';' stmt
        | stmt
        ;

stmt:
        ID ASSIGNOP expression
        ;

expression:
        simple_expression
        | simple_expression RELOP simple_expression
        ;

simple_expression:
        term
        | simple_expression ADDOP term
        ;

term:
        factor
        | term MULOP factor
        ;

factor:
        ID
        | NUM
        | '(' expression ')'
        | ID '[' expression ']'
        | '!' factor
        ;
%%

int yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
    return 0;
}