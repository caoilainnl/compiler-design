#ifndef UNIQUE_PARSER_H
#define UNIQUE_PARSER_H

#include "lexer.h"

typedef struct {
    int error;
    int line;
} ParseResult;

#define NONE 0
#define SYNTAX_ERROR 1

int initializeParser(const char *filename);
ParseResult parseFile();
int parseStatement();
int parseBlock();
int parseFunction();
int parseExpression();
int parseDeclaration();
int parseConditional();
int parseLoop();
int parseProgram();
int closeParser();

#endif
