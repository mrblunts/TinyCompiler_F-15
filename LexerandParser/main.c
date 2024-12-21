#include <stdio.h>
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
#define EOF_TOKEN 27

extern int yylex();
extern union {
    int intVal;
    char* strVal;
} yylval;
extern char* yytext;

int main(void) {
    int token;
    while((token = yylex())) {
        switch(token) {
            case INTEGER:
                printf("INTEGER: %d\n", yylval.intVal);
                break;
                
            case STRING:
                printf("STRING: %s\n", yylval.strVal);
                break;
            case IDENTIFIER:
                printf("IDENTIFIER: %s\n", yylval.strVal);
                break;
                case PLUS:
    printf("PLUS\n");
    break;
case MINUS:
    printf("MINUS\n");
    break;
case TIMES:
    printf("TIMES\n");
    break;
case DIVIDE:
    printf("DIVIDE\n");
    break;
case LPAREN:
    printf("LPAREN\n");
    break;
case RPAREN:
    printf("RPAREN\n");
    break;
case LBRACKET:
    printf("LBRACKET\n");
    break;
case RBRACKET:
    printf("RBRACKET\n");
    break;
case COMMA:
    printf("COMMA\n");
    break;
case SEMICOLON:
    printf("SEMICOLON\n");
    break;
case COLON:
    printf("COLON\n");
    break;
case ASSIGN:
    printf("ASSIGN\n");
    break;

            default:
                printf("KEYWORD:  Text: %s\n", yytext);
                break;

        }
    }
    return 0;
}