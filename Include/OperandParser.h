//
// Created by omara on 5/12/2020.
//
#ifndef SICXEONEPASSASSEMBLER_OPERANDPARSER_H
#define SICXEONEPASSASSEMBLER_OPERANDPARSER_H
#include <string>
#include <vector>
#include "SymbolTable.h"
namespace OperandParser {
    bool isSymbol(const string& s);

    bool isExpression(const string& s);

    bool isLiteral(const string& s);

    bool isNumber(const string& s);

    int parseOperand(std ::string operand, int& locationCounter,SymbolTable &symbolTable);

    string parseLiteral(const string& operand);

    int hexCharToInt(const char &hexChar);

    int hexStringToInt(const string &hexString);

    string numToHexString(int num, int halfBytes = 1);
}
#endif //SICXEONEPASSASSEMBLER_OPERANDPARSER_H
