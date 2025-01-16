#include "compiler.h"
#include "symbols.h"
#include "parser.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compilerPhase = 1;
char *outputFilePath;

int initializeCompiler() {
    resetSymbolTable();
    setupProgramScope();
    return 1;
}

int getCompilerPhase() {
    return compilerPhase;
}

char *getOutputFilePath() {
    return outputFilePath;
}

CompilerResult compileDirectory(const char *directory) {
    CompilerResult result = {0};
    DIR *dir = opendir(directory);

    if (!dir) {
        fprintf(stderr, "Error: Cannot open directory %s\n", directory);
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".jack")) {
            char fullPath[512];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", directory, entry->d_name);

            if (!initializeParser(fullPath)) {
                fprintf(stderr, "Parser initialization failed for file %s\n", fullPath);
                exit(EXIT_FAILURE);
            }

            if (compilerPhase == 2) {
                outputFilePath = strdup(fullPath);
                char *ext = strrchr(outputFilePath, '.');
                if (ext) strcpy(ext, ".vm");
            }

            result = parseFile();

            if (result.error != NONE) {
                fprintf(stderr, "Error in parsing file %s\n", fullPath);
                closedir(dir);
                return result;
            }
        }
    }

    closedir(dir);

    if (checkUndefinedSymbols() > 0) {
        fprintf(stderr, "Undefined symbols detected\n");
        result.error = UNDEFINED_SYMBOL;
    }

    return result;
}

int finalizeCompiler() {
    compilerPhase = 1;
    resetSymbolTable();
    return 1;
}
