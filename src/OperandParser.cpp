//
// Created by omara on 5/12/2020.
//
#include "../Include/OperandParser.h"
#include <iostream>
#include <bitset>
#include <algorithm>
#include <cmath>

using namespace std;

long long OperandParser::parseOperand(string &operand, int &locationCounter, SymbolTable &symbolTable) {
    int address = 0, sign = 1;
    for (int i = 0; i < operand.size(); i++) {
        string temp;
        if (operand[i] == '*') {
            address += sign * locationCounter;
            sign = 1;
        } else if (operand[i] == '-')sign *= -1;
        else if (operand[i] == '+')sign *= 1; //IDK
        else {
            while (i < operand.size() && isalpha(operand[i])) {
                temp += operand[i];
                i++;
            }
            address += symbolTable.get(temp) * sign;
        }
    }
    return address;
}

string OperandParser::parseLiteral(const string &operand) {
    string newOperand, str;
    int i = 0;
    bool start = false,isLetter =false, isInt = false;
    if (operand[i] == '=')i++;
    while(i<operand.size()&&operand[i]==' ')i++;
    if (operand[i] == 'C') {
        isLetter = true;
        i++;
    }else if(operand[i]=='W'){
        isInt = true;
        i++;
    }
    while(i<operand.size()&&operand[i]==' ')i++;
    for (int i = 0; i < operand.size(); i++) {
        if (operand[i] == '\'' && !start) { start = true; }
        else if (operand[i] == ' ' && !start);
        else if (operand[i] == '\'' && start) {
            start = false;
            break;
        } else if (operand[i] == ' ' && isLetter == false)throw runtime_error("Wrongly formatted hexa Code");
        else
            newOperand += operand[i];
    }
    if (i != operand.size())throw runtime_error("Literal is not correctly formatted");
    if (isLetter) {
        for (i = 0; i < newOperand.size(); i++)str += numToHexString((int) newOperand[i], 2);
    } else if(isInt){
        int n = atoi(newOperand.c_str());
        int halfbytes = (int)ceil(log2(n));
        halfbytes = halfbytes/4*4 + (halfbytes%4 != 0);
        return numToHexString(n, halfbytes);
    }else{
        return newOperand;
    }
    return str;
}

int OperandParser::hexCharToInt(const char &hexChar) {
    return (isalpha(hexChar) ? (hexChar - 'A') : (hexChar - '0'));
}

int OperandParser::hexStringToInt(const string &hexString) {
    int address = 0;
    for (int i = 0; i < hexString.size(); i++) {
        address |= hexCharToInt(hexString[i]);
        address <<= 4;
    }
    return address;
}

string OperandParser::numToHexString(int num, int halfBytes) {
    string str;
    int numTemp = 0, numTemp2 = 0;
    if(num<0)num+=(1<<12);
    for (int i = halfBytes; i > 0; i--) {
        numTemp2 = num >> 4;
        numTemp = numTemp2<<4;
        numTemp = num - numTemp;
        num = numTemp2;
        if (numTemp > 9)str += 'A' + numTemp-10;
        else str += (char)((int)'0' + numTemp);
    }
    if (num != 0)throw runtime_error("provided number needs more Bytes than specified");
    std::reverse(str.begin(), str.end());
    return str;
}
