//
// Created by omara on 5/12/2020.
//
#include "../Include/OperandParser.h"
#include <iostream>
using namespace std;

long long OperandParser::parseOperand(string &operand,int &locationCounter,SymbolTable &symbolTable){
    int address = 0 ,sign =1 ;
    for (int i = 0; i < operand.size(); i++) {
        string temp = "";
        if (operand[i] == '*'){address += sign * locationCounter;sign =1 ;}
        else if (operand[i] == '-')sign *= -1;
        else if (operand[i] == '+')sign *= 1; //IDK
        else {
            while (i<operand.size()&& isalpha(operand[i])) {
                temp += operand[i];
                i++;
            }
            address += symbolTable.get(temp) * sign;
        }
    }
    return address;
}
