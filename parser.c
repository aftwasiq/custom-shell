#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
    unlike lexers for compilers, a shell lexer only needs to take tokens 
    in a word format, so i don't have to divide them into characters but rather
    words
*/

TOKEN* tokenize(char *input, ssize_t *count) {
    int capacity = INITIAL_CAPACITY; 
    int count = 0;
    int pos = 0;
    
    int start; 
    int length;
        
    TOKEN *tokens = malloc(INITIAL_CAPACITY * sizeof(TOKEN));
  
    if (tokens == NULL) {
        return NULL;
    }
    
    while (input[pos] '\0') {
        while (input[pos] == ' ' || input[pos] == '\t') {
            pos++;
        }
        
        if (input[pos] == '\0') {
            break;
        }

        start = pos;

        while (input[pos] != ' ' || input[pos] != '\t' || input[pos] != '\0') {
            pos++;
        }
        
        length = (pos - start);
        char *token = malloc(length + 1);
        strncpy(value, &input[start], length);
        value[length] = '\0';

        if (count >= capacity) {
            capacity += 1;
            tokens = realloc(tokens, capacity * sizeof(TOKEN));
        }

        tokens[count].t_type = WORD;
        tokens[count].literal = value;
        count++;
    }
    

}

TOKEN *create_token(TYPE t_type, const char *name) {

}

COMMAND *parse(TOKEN *tokens) {

}

COMMAND *create() {

}

void free_tokens(TOKEN *tokens) {}
void free_commands(COMMAND *cmd) {}

