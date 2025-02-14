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
#include "Writer.h"
using namespace std;
class Interpreter {
private:
    Parser parser;
    Writer writer;
    SymbolTable symbolTable;
    LiteralTable literalTable;
    int locationCounter;
public:
    Interpreter(ifstream& file, ofstream& outfile);
    void Assemble();
    int evaluateExpression(const string &operand);
};


#endif //SICXEONEPASSASSEMBLER_INTERPRETER_H
