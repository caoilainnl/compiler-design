#ifndef UNIQUE_SYMBOLS_H
#define UNIQUE_SYMBOLS_H

#define MAX_SYMBOLS 256

typedef struct {
    char name[64];
    char type[64];
} Symbol;

typedef struct {
    Symbol symbols[MAX_SYMBOLS];
    int count;
} SymbolTable;

void resetSymbolTable();
void addSymbol(const char *name, const char *type);
Symbol *findSymbol(const char *name);
void printSymbolTable();
void removeSymbol(const char *name);
void listAllSymbols();
void testSymbolTable();

#endif
