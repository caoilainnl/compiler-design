#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

Token currentToken;

int initializeParser(const char *filename) {
    if (!initLexer(filename)) {
        return 0;
    }
    currentToken = getNextToken();
    return 1;
}

ParseResult parseFile() {
    ParseResult result = {0};

    while (currentToken.type != END_OF_FILE) {
        if (!parseStatement()) {
            result.error = SYNTAX_ERROR;
            result.line = currentToken.line;
            return result;
        }
        currentToken = getNextToken();
    }

    result.error = NONE;
    return result;
}

int parseStatement() {
    if (currentToken.type == IDENTIFIER) {
        currentToken = getNextToken();
        if (currentToken.type == SYMBOL && currentToken.lexeme[0] == ';') {
            return 1;
        }
    }
    return 0;
}

int parseBlock() {
    if (currentToken.type == SYMBOL && currentToken.lexeme[0] == '{') {
        currentToken = getNextToken();
        while (currentToken.type != SYMBOL || currentToken.lexeme[0] != '}') {
            if (!parseStatement()) {
                return 0;
            }
            currentToken = getNextToken();
        }
        return 1;
    }
    return 0;
}

int parseFunction() {
    if (currentToken.type == IDENTIFIER) {
        currentToken = getNextToken();
        if (currentToken.type == SYMBOL && currentToken.lexeme[0] == '(') {
            currentToken = getNextToken();
            while (currentToken.type != SYMBOL || currentToken.lexeme[0] != ')') {
                currentToken = getNextToken();
            }
            currentToken = getNextToken();
            return parseBlock();
        }
    }
    return 0;
}

int parseProgram() {
    while (currentToken.type != END_OF_FILE) {
        if (!parseFunction()) {
            return 0;
        }
        currentToken = getNextToken();
    }
    return 1;
}

int parseExpression() {
    if (currentToken.type == IDENTIFIER || currentToken.type == NUMBER) {
        currentToken = getNextToken();
        if (currentToken.type == SYMBOL && (currentToken.lexeme[0] == '+' || currentToken.lexeme[0] == '-')) {
            currentToken = getNextToken();
            return parseExpression();
        }
        return 1;
    }
    return 0;
}

int parseDeclaration() {
    if (currentToken.type == IDENTIFIER) {
        currentToken = getNextToken();
        if (currentToken.type == IDENTIFIER) {
            currentToken = getNextToken();
            if (currentToken.type == SYMBOL && currentToken.lexeme[0] == ';') {
                return 1;
            }
        }
    }
    return 0;
}

int parseConditional() {
    if (currentToken.type == SYMBOL && strcmp(currentToken.lexeme, "if") == 0) {
        currentToken = getNextToken();
        if (currentToken.type == SYMBOL && currentToken.lexeme[0] == '(') {
            currentToken = getNextToken();
            if (parseExpression()) {
                if (currentToken.type == SYMBOL && currentToken.lexeme[0] == ')') {
                    currentToken = getNextToken();
                    return parseBlock();
                }
            }
        }
    }
    return 0;
}

int parseLoop() {
    if (currentToken.type == SYMBOL && strcmp(currentToken.lexeme, "while") == 0) {
        currentToken = getNextToken();
        if (currentToken.type == SYMBOL && currentToken.lexeme[0] == '(') {
            currentToken = getNextToken();
            if (parseExpression()) {
                if (currentToken.type == SYMBOL && currentToken.lexeme[0] == ')') {
                    currentToken = getNextToken();
                    return parseBlock();
                }
            }
        }
    }
    return 0;
}
