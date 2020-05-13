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

    string & parseLiteral(string &operand, int &locationCounter, SymbolTable &symbolTable);

    int hexCharToInt(unordered_map<char,int> &uh ,const char &hexChar);
    int hexStringToInt(const string &hexString);
   // long long int letterStringToll(const char letterChar);
    string &numToHexString(int num, int hexaBytes = 1);
}
#endif //SICXEONEPASSASSEMBLER_OPERANDPARSER_H
