#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOKEN_BUFFER 1
#define INITIAL 8

/*
    Lexer/Parser structs
*/

typedef struct {
    char **argv;
    char *cmd;
    char *infile;
    char *outfile;
    int background; 
    int argc;

} COMMAND;

typedef enum {
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_IN,
    SEMICOLON,
    AMPERSAND,
    NEWLINE,

} TYPE;

typedef struct {
    TYPE t_type;
    char *literal;

} TOKEN;

// Lexer struct itself

typedef struct {
    const char *input;
    size_t position;

} LEXER;

/*
    Lexer/Parser funciton headers
*/

TOKEN* tokenize(char *input, size_t *count);
TOKEN *create_token(TYPE t_type, const char *name);
void free_tokens(TOKEN *tokens);

COMMAND *parse(TOKEN *tokens);
COMMAND *create();
void free_commands(COMMAND *cmd);

#endif PARSER_H
