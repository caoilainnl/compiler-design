#ifndef UNIQUE_COMPILER_H
#define UNIQUE_COMPILER_H

#include "parser.h"

int initializeCompiler();
CompilerResult compileDirectory(const char *directory);
int finalizeCompiler();
int getCompilerPhase();
char *getOutputFilePath();

#endif
