#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *sourceFile;
int currentLine;

int initLexer(const char *filename) {
    sourceFile = fopen(filename, "r");
    if (!sourceFile) {
        perror("Error opening file");
        return 0;
    }
    currentLine = 1;
    return 1;
}

Token getNextToken() {
    Token token = {0};
    char lexeme[256] = "";
    char c;

    while ((c = fgetc(sourceFile)) != EOF) {
        if (isspace(c)) {
            if (c == '\n') currentLine++;
            continue;
        }

        if (isalpha(c)) {
            int i = 0;
            do {
                lexeme[i++] = c;
                c = fgetc(sourceFile);
            } while (isalnum(c) || c == '_');
            lexeme[i] = '\0';
            ungetc(c, sourceFile);
            strcpy(token.lexeme, lexeme);
            token.type = IDENTIFIER;
            token.line = currentLine;
            return token;
        }

        if (isdigit(c)) {
            int i = 0;
            do {
                lexeme[i++] = c;
                c = fgetc(sourceFile);
            } while (isdigit(c));
            lexeme[i] = '\0';
            ungetc(c, sourceFile);
            strcpy(token.lexeme, lexeme);
            token.type = NUMBER;
            token.line = currentLine;
            return token;
        }

        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = SYMBOL;
        token.line = currentLine;
        return token;
    }

    strcpy(token.lexeme, "EOF");
    token.type = END_OF_FILE;
    token.line = currentLine;
    return token;
}

int closeLexer() {
    fclose(sourceFile);
    return 1;
}
