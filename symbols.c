#include "symbols.h"
#include <string.h>
#include <stdio.h>

SymbolTable globalTable;

void resetSymbolTable() {
    globalTable.count = 0;
}

void addSymbol(const char *name, const char *type) {
    if (globalTable.count >= MAX_SYMBOLS) {
        fprintf(stderr, "Error: Symbol table overflow\n");
        return;
    }
    Symbol *sym = &globalTable.symbols[globalTable.count++];
    strncpy(sym->name, name, sizeof(sym->name));
    strncpy(sym->type, type, sizeof(sym->type));
}

Symbol *findSymbol(const char *name) {
    for (int i = 0; i < globalTable.count; i++) {
        if (strcmp(globalTable.symbols[i].name, name) == 0) {
            return &globalTable.symbols[i];
        }
    }
    return NULL;
}

void printSymbolTable() {
    printf("Symbol Table:\n");
    for (int i = 0; i < globalTable.count; i++) {
        printf("%s: %s\n", globalTable.symbols[i].name, globalTable.symbols[i].type);
    }
}

void removeSymbol(const char *name) {
    for (int i = 0; i < globalTable.count; i++) {
        if (strcmp(globalTable.symbols[i].name, name) == 0) {
            for (int j = i; j < globalTable.count - 1; j++) {
                globalTable.symbols[j] = globalTable.symbols[j + 1];
            }
            globalTable.count--;
            return;
        }
    }
}

void listAllSymbols() {
    printf("Listing all symbols:\n");
    for (int i = 0; i < globalTable.count; i++) {
        printf("%d. %s (%s)\n", i + 1, globalTable.symbols[i].name, globalTable.symbols[i].type);
    }
}

int countSymbolsOfType(const char *type) {
    int count = 0;
    for (int i = 0; i < globalTable.count; i++) {
        if (strcmp(globalTable.symbols[i].type, type) == 0) {
            count++;
        }
    }
    return count;
}

void removeSymbolsByType(const char *type) {
    for (int i = 0; i < globalTable.count; i++) {
        if (strcmp(globalTable.symbols[i].type, type) == 0) {
            for (int j = i; j < globalTable.count - 1; j++) {
                globalTable.symbols[j] = globalTable.symbols[j + 1];
            }
            globalTable.count--;
            i--;
        }
    }
}

void testSymbolOperations() {
    addSymbol("a", "int");
    addSymbol("b", "float");
    addSymbol("c", "int");
    printSymbolTable();
    printf("Count of int symbols: %d\n", countSymbolsOfType("int"));
    printf("Removing all int symbols\n");
    removeSymbolsByType("int");
    printSymbolTable();
}

