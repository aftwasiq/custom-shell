#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
    unlike lexers for compilers, a shell lexer only needs to take tokens 
    in a word format, so i don't have to divide them into characters explicity,
    but rather words (the commands) 
*/

TOKEN* tokenize(char *input, size_t *count_out) {
    int capacity = INITIAL_CAPACITY;
    int token_count = 0;
    int pos = 0;
    
    TOKEN *tokens = malloc(capacity * sizeof(TOKEN));
    if (!tokens) {
        return NULL;
    }

    while (input[pos] != '\0') {
        while (input[pos] == ' ' || input[pos] == '\t') {
            pos++;
        }
        
        if (input[pos] == '\0') {
            break;
        }

        int start = pos;
        
        while (input[pos] != ' ' && input[pos] != '\t' && input[pos] != '\0') {
            pos++;
        }

        int length = (pos - start);
        char *value = malloc(length + 1);
        strncpy(value, &input[start], length);
        value[length] = '\0';

        if (token_count >= capacity) {
            capacity += 8;
            tokens = realloc(tokens, capacity * sizeof(TOKEN));
        }

        tokens[token_count].t_type = WORD;
        tokens[token_count].literal = value;
        token_count++;
    }

    *count_out = token_count;
    return tokens;
}

COMMAND *parse(TOKEN *tokens, size_t count) {
    // cmds: help, cd, ls, mkdir, exit, pwd
    COMMAND *cmd = malloc(sizeof(COMMAND));
    if (!cmd) {
        return NULL;
    }

    int i = 0;
    cmd->argc = 0;
    cmd->argv = malloc(sizeof(char*) * (i + 2));

    for (size_t i = 0; i < count; i++) {
        // for now; just handling words, ill add other types later
        if (tokens[i].t_type == WORD) {
            cmd->arg = tokens[i].literal;
            cmd->argc += 1;

            if (i != 0) {
                cmd->argv = realloc(cmd->argv, sizeof(char*) * (i + 2)); 
            }

            cmd->argv[i] = tokens[i].literal;
            cmd->argv[i + 1] = NULL;
        } 
    }

    return cmd; 
}

void free_tokens(TOKEN *tokens, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        free(tokens[i].literal);
    }
    free(tokens);
}
void free_commands(COMMAND *cmd) {
    free(cmd->argv);
    free(cmd);
}
