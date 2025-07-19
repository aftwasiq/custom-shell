#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

TOKEN* tokenize(char *input, size_t *count) {
    LEXER lexer;
    lexer.input = input;
    lexer.count = 0;
    
    TOKEN *tokens = malloc(INITIAL * sizeof(TOKEN));
    if (tokens == NULL) {
        return;
    }

    while 
    

}

TOKEN *create_token(TYPE t_type, const char *name) {

}

COMMAND *parse(TOKEN *tokens) {

}

COMMAND *create() {

}

void free_tokens(TOKEN *tokens) {}
void free_commands(COMMAND *cmd) {}

