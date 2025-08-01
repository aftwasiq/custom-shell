#include <stdlib.h>

#ifndef PARSER_H
#define PARSER_H

#define TOKEN_BUFFER 1
#define INITIAL_CAPACITY 8

/*
    Lexer/Parser structs
    cmd, t_type, & token itself
*/

typedef struct {
    char *arg;
    char **argv; // the first arg will always be the cmd
    int argc;

} COMMAND;

// cmd->arg = "cd"
// cmd->argv = ["cd", "dir", NULL]
// cmd->argc = 2

typedef enum {
    WORD,
    PIPE,
    AMPERSAND,
    NEWLINE,

} TYPE;

typedef struct {
    TYPE t_type;
    char *literal;

} TOKEN;

/*
    Lexer/Parser function headers
*/

TOKEN* tokenize(char *input, size_t *count);
COMMAND *parse(TOKEN *tokens, size_t count);
int execute(COMMAND *cmd);

void free_tokens(TOKEN *tokens, size_t count);
void free_commands(COMMAND *cmd);

#endif
