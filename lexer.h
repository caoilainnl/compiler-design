#ifndef UNIQUE_LEXER_H
#define UNIQUE_LEXER_H

typedef struct {
    char lexeme[64];
    int type;
    int line;
} Token;

int initLexer(const char *filename);
Token getNextToken();
int closeLexer();

#endif