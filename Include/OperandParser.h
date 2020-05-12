//
// Created by omara on 5/12/2020.
//
#ifndef SICXEONEPASSASSEMBLER_OPERANDPARSER_H
#define SICXEONEPASSASSEMBLER_OPERANDPARSER_H
#include <string>
#include <vector>
#include "SymbolTable.h"
namespace OperandParser {
    long long parseOperand(std ::string &operand,int &locationCounter,SymbolTable &symbolTable);
}
#endif //SICXEONEPASSASSEMBLER_OPERANDPARSER_H
