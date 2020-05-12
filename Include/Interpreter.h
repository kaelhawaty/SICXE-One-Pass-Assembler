//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_INTERPRETER_H
#define SICXEONEPASSASSEMBLER_INTERPRETER_H


#include <fstream>
#include "Parser.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include <vector>
#include "OperandParser.h"
using namespace std;
class Interpreter {
private:
    ifstream in;
    Parser *parser;
    SymbolTable symbolTable;
    LiteralTable literalTable;
    int locationCounter;
public:
    Interpreter(string path);
    void Assemble();
};


#endif //SICXEONEPASSASSEMBLER_INTERPRETER_H
