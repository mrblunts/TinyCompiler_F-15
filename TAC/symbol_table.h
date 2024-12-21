#ifndef __PARSER_H
#define __PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

/* External Variables */
extern int next_instr, temp_count, address_ind;

/* Enum Definitions */
typedef enum quad_data_types {
    DEFAULT_, PLUS, MINUS, INTO, DIV, PERCENT, U_PLUS, U_MINUS, BW_U_NOT, U_NEGATION, 
    SL, SR, LT, LTE, GT, GTE, EQ, NEQ, BW_AND, BW_XOR, PARAM, RETURN_EXP, RETURN_, Function,
    BW_INOR, LOG_AND, LOG_OR, goto_LT, goto_LTE, goto_GT, goto_GTE, goto_EQ, goto_NEQ, call,
    EQ_BRACKET, EQ_ADDR_BRACKET, BRACKET_EQ, U_ADDR, U_STAR, ASSIGN, GOTO_, IF_GOTO, IF_FALSE_GOTO, 
    STAR_EQUAL, STAR_BRACKET_EQ, STAR_EQ_BRACKET, ADDR_BRACKET_EQ
} quad_data_types;

typedef enum date_types {
    ARRAY, PTR, FUNCTION, VOID_, CHAR_, INT_, DOUBLE_, BOOL_, STRING_, INT_PTR, CHAR_PTR
} date_types;

/* Linked List Node for Backpatching */
typedef struct lnode {
    int index_list;
    struct lnode *next;
} lnode;

/* Type Node */
typedef struct tNode {
    date_types up;
    date_types down;
    int* l;
    struct tNode *r;
} tNode;

/* Symbol Table Record */
typedef struct symbol_table_record {
    char* name;
    char** type;
    char* initial_value;
    int size;
    int offset;
    int array_ind;
    struct symbol_table* nested_table;
} symbol_table_record;

/* Symbol Table */
typedef struct symbol_table {
    symbol_table_record* list;
    int size;
    int curr_size;
    int curr_offset;
    char* name;
    int return_ind;
} symbol_table;

/* Parameter List */
typedef struct parameter_list {
    symbol_table_record* parameter;
    struct parameter_list* next;
} parameter_list;

/* Fields for Quad Representation */
typedef struct fields_quad {
    char* arg1;
    char* arg2;
    char* res;
    quad_data_types op;
    symbol_table_record* arg1_loc;
    symbol_table_record* arg2_loc;
    symbol_table_record* res_loc;
} fields_quad;

/* Quad Array */
typedef struct quadArray {
    fields_quad* quad_Table;
} quadArray;

/* Union for Attributes */
typedef union attribute {
    int int_data;
    double double_data;
    char char_data;
    char* str_data;
} attribute;

/* Expression Attributes */
typedef struct attribute_expression {
    symbol_table_record* loc;
    lnode* TL;
    lnode* FL;
    lnode* NL;
    tNode* type;
    symbol_table_record* array;
    symbol_table_record* loc1;
    attribute val;
    int ind;
    int pointer_ind;
} attribute_expression;

/* Data Type */
typedef struct data_type {
    char* name;
    char* type;
    int pointer_indicator;
    int size;
    char* value;
    symbol_table_record* loc;
    int array_ind;
} data_type;

/* Parameter Type */
typedef struct parameter_type {
    char** parameters;
    char** names;
} parameter_type;

/* Function Prototypes */
tNode* new_node(date_types, int);
tNode* merge_node(tNode*, tNode*);
lnode* makelist(int);
lnode* merge(lnode*, lnode*);
void backpatch(lnode*, int);
int typecheck(tNode*, tNode*);
void conv2Bool(attribute_expression*);
parameter_list* make_param_list(symbol_table_record*);
parameter_list* merge_param_list(parameter_list*, parameter_list*);
int compute_width(tNode*);
char* converter(date_types temp);

/* Symbol Table and Quad Array Globals */
extern symbol_table* global_table;
extern symbol_table* curr_table;
extern quadArray* quad_;

#endif
