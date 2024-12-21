#include "symbol_table.h"

FILE* fptr;
char* currentFunction;

symbol_table* global_table = NULL;
symbol_table* curr_table = NULL;

/* Initialize size constants */
const int size_of_int = 4;
const int size_of_char = 1;
const int size_of_pointer = 8;

/* Initialize temporary counter */
int temp_count = 0;

/* Helper Function to Copy Type Array */
char** copy_type(char** type, int type_count) {
    if (!type || type_count <= 0) return NULL;
    char** new_type = (char**)malloc(type_count * sizeof(char*));
    for (int i = 0; i < type_count; i++) {
        new_type[i] = strdup(type[i]);
    }
    return new_type;
}

/* Assign Function */
void assign(symbol_table_record* this, const symbol_table_record* x) {
    this->name = strdup(x->name);
    this->type = copy_type(x->type, x->array_ind); // Assuming array_ind stores type count
    this->initial_value = x->initial_value ? strdup(x->initial_value) : NULL;
    this->size = x->size;
    this->offset = x->offset;
    this->nested_table = x->nested_table;
    this->array_ind = x->array_ind;
}

/* Print Record */
void print_record(symbol_table_record* this) {
    char outputFilePath[256];
    snprintf(outputFilePath, sizeof(outputFilePath), "../%s.txt", currentFunction);
    FILE* outputStream = fopen(outputFilePath, "a");
    if (!outputStream) {
        fprintf(stderr, "Error: Unable to open file for writing symbol table records.\n");
        return;
    }

    fprintf(outputStream, "%s\t", this->name);
    if (this->type == NULL || this->array_ind <= 0) {
        fprintf(outputStream, "undefined\t");
    } else {
        for (int i = 0; i < this->array_ind - 1; i++) {
            fprintf(outputStream, "%s^", this->type[i]);
        }
        fprintf(outputStream, "%s\t", this->type[this->array_ind - 1]);
    }
    fprintf(outputStream, "%s\t%d\t%d\t%s\t%d\n",
            this->initial_value ? this->initial_value : "0",
            this->size,
            this->offset,
            this->nested_table ? this->nested_table->name : "null",
            this->array_ind);
    fclose(outputStream);
}

/* Create Symbol Table */
symbol_table* create_symbol_table(int capacity) {
    symbol_table* table = (symbol_table*)malloc(sizeof(symbol_table));
    table->list = (symbol_table_record*)malloc(capacity * sizeof(symbol_table_record));
    table->size = capacity;
    table->curr_size = 0;
    table->curr_offset = 0;
    table->name = NULL;
    return table;
}

/* Lookup in Symbol Table */
symbol_table_record* lookup(symbol_table* this, const char* t) {
    for (int i = 0; i < this->curr_size; i++) {
        if (strcmp(t, this->list[i].name) == 0) {
            return &(this->list[i]);
        }
    }
    return NULL;
}

/* Insert into Symbol Table */
void insert(symbol_table* this, const symbol_table_record* x) {
    if (this->curr_size == this->size) {
        fprintf(stderr, "Error: Symbol table capacity exceeded.\n");
        return;
    }
    symbol_table_record* newRecord = &this->list[this->curr_size++];
    assign(newRecord, x);
    newRecord->offset = this->curr_offset;
    this->curr_offset += newRecord->size;
}

/* Generate Temporary Variable */
symbol_table_record* gentemp(symbol_table* this, enum date_types temp) {
    char tempName[20];
    snprintf(tempName, sizeof(tempName), "t%d", temp_count++);
    symbol_table_record* newTemp = (symbol_table_record*)malloc(sizeof(symbol_table_record));
    newTemp->name = strdup(tempName);
    newTemp->array_ind = 1;
    newTemp->type = (char**)malloc(sizeof(char*));

    switch (temp) {
        case INT_:
            newTemp->size = size_of_int;
            newTemp->type[0] = strdup("INT");
            break;
        case CHAR_:
            newTemp->size = size_of_char;
            newTemp->type[0] = strdup("CHAR");
            break;
        case INT_PTR:
            newTemp->size = size_of_pointer;
            newTemp->type[0] = strdup("INT*");
            break;
        case CHAR_PTR:
            newTemp->size = size_of_pointer;
            newTemp->type[0] = strdup("CHAR*");
            break;
        case PTR:
            newTemp->size = size_of_pointer;
            newTemp->type[0] = strdup("VOID*");
            break;
        default:
            fprintf(stderr, "Error: Unsupported temporary type.\n");
            free(newTemp->name);
            free(newTemp);
            return NULL;
    }
    insert(this, newTemp);
    return newTemp;
}

/* Dummy Function for Quad Array Creation */
quadArray* create_quadArray(int capacity) {
    quadArray* qa = (quadArray*)malloc(sizeof(quadArray));
    qa->quad_Table = (fields_quad*)malloc(capacity * sizeof(fields_quad));
    return qa;
}

/* Dummy Print Function for Symbol Table */
void print_symbol_table(symbol_table* table) {
    printf("Symbol Table: %s\n", table->name);
    for (int i = 0; i < table->curr_size; i++) {
        printf("%s\n", table->list[i].name);
    }
}

/* Dummy Print Function for Quad Array */
void print_quadArray(quadArray* qa) {
    printf("Printing Quad Array...\n");
}

/* Main Function */
int main() {
    global_table = create_symbol_table(10000);
    global_table->name = strdup("global");
    curr_table = global_table;

    quadArray* quad_array = create_quadArray(100000);
    fptr = fopen("../three_address_input.txt", "w");
    if (!fptr) {
        fprintf(stderr, "Error: Unable to open output file for TAC.\n");
        return 1;
    }

    int parseResult = 0; // Replace `yyparse()` if necessary
    if (parseResult == 0) {
        printf("Parsing successful.\n");
    } else {
        fprintf(stderr, "Parsing failed.\n");
    }

    // Print global table and quad array
    print_symbol_table(global_table);
    print_quadArray(quad_array);
    fclose(fptr);
    return 0;
}
