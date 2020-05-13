//
// Created by Karim on 5/11/2020.
//

#include <array>
#include <sstream>
#include <iostream>
#include "../Include/Interpreter.h"
#include "../Include/OPTable.h"
#include "../Include/Registers.h"

Interpreter::Interpreter(ifstream &file, ofstream &outfile) : parser(Parser(file)), writer(Writer(outfile)),
                                                              literalTable() {
    locationCounter = -1;
}
//TODO
int Interpreter::evaluateExpression(const string &operand) {
    int address = 0, sign = 1;
    for (int i = 0; i < operand.size(); i++) {
        string temp = "";
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

    return 0;
}

void Interpreter::Assemble() {
    string line;
    while (parser >> line) {
        if (parser.isComment(line)) {
            continue;
        }
        array<string, 3> arr;
        arr = parser.parseLine(line);
        if (locationCounter == -1 && arr[1] != "START") {
            throw runtime_error("The program must starts with START directive");
        }
        Format format = parser.formatType(arr[1]);
        AdressingType addressingType = parser.addressType(arr[2]);
        if (symbolTable.contains(arr[0])) {
            throw runtime_error("redefinition of Label " + arr[0]);
        } else if (arr[0] != "") {
            symbolTable.define(arr[0], locationCounter);
        }
        if (OPTable::isOp(arr[1])) {
            if (format == Format::FORMAT2) {
                string split;
                int r1, r2 = 0;
                stringstream st(arr[2]);
                getline(st, split, ',');
                r1 = Registers::getRegister(split);
                st >> split;
                if (split != "")
                    r2 = Registers::getRegister(split);
                cout << OPTable::getOpcode(arr[1]) << ' ' << r1 << ' ' << r2 << '\n';
                string str = "";
                str += OperandParser::numToHexString(OPTable::getOpcode(arr[1]),2);
                str += OperandParser::numToHexString(r1);
                if (r2)str += OperandParser::numToHexString(r2);
                else str += "0";
                writer.writeTextRecord(str, locationCounter);
                locationCounter += 2;
            } else {
                int byte1 = OPTable::getOpcode(arr[1]);
                byte1 |= addressingType == AdressingType::IMMEDIATE ? 1 : (addressingType == AdressingType::INDIRECT
                                                                           ? 2 : 3);
                int byte2 = 0;
                if (addressingType == ::AdressingType::INDEXED) {
                    byte2 = 1;
                }
                byte2 <<= 3;
                if (format == Format::FORMAT3) {
                    byte2 |= 2;
                } else {
                    byte2 |= 1;
                }
                //cout << byte1 << ' ' << byte2 << ' ' << evaluateExpression(arr[2]);
                string str = OperandParser::numToHexString(byte1,2);
                str += OperandParser::numToHexString(byte2);
                int x;
                //arr[2]-locationCounter;
                if (isalpha(arr[2][0]))x = symbolTable.get(arr[2]);
                else x = std::atoi(arr[2].c_str());
                x -= locationCounter;
                str += OperandParser::numToHexString(x, 3);
                writer.writeTextRecord(str, locationCounter);
                format == Format::FORMAT3 ? locationCounter += 3 : locationCounter += 4;
            }
        } else {
            if (arr[1] == "START") {
                if (locationCounter != -1) {
                    throw runtime_error("Error the program includes more than one START directive");
                }
                //TODO EDIT WHEN WRITER CONSTRUCTOR EDITED
                locationCounter = OperandParser::hexStringToInt(arr[2]);
                writer.createHeader(locationCounter, arr[0]);
            } else if (arr[1] == "END") {
                writer.writeEndRecord();
                return;
            } else if (arr[1] == "ORG") {
                locationCounter = symbolTable.get(arr[2]);
            } else if (arr[1] == "LTROG") {
                literalTable.organize(locationCounter);
            } else if (arr[1] == "EQU") {
                int address = OperandParser::parseOperand(arr[2], locationCounter, symbolTable);
                symbolTable.define(arr[0], address);
            } else if (arr[1] == "BYTE") {
               string literal = OperandParser::parseLiteral(arr[2]) ;
                writer.writeTextRecord(literal,locationCounter);
                locationCounter += literal.size()/2 + 1;
            } else if (arr[1] == "WORD") {
                int size = atoll(arr[2].c_str()) ;
                string literal ;
                literal= OperandParser::numToHexString(size,3);
                writer.writeTextRecord(literal,locationCounter);
                locationCounter += 4;
            } else if (arr[1] == "RESB") {
                int size = atoi(arr[2].c_str());
                locationCounter += size + 1;
                writer.cutText(locationCounter);
            } else if (arr[1] == "RESW") {
                int size = atoi(arr[2].c_str());
                locationCounter += size * 3 + 1;
                writer.cutText(locationCounter);
            }

        }
    }
    throw runtime_error("program doesn't include END directive");
}