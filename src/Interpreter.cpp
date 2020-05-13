//
// Created by Karim on 5/11/2020.
//

#include <array>
#include <sstream>
#include <iostream>
#include "../Include/Interpreter.h"
#include "../Include/OPTable.h"
#include "../Include/Registers.h"

Interpreter::Interpreter(ifstream &file) : parser(Parser(file)) {
    locationCounter = -1;
}

//TODO
int evaluateExpression(string expression) {
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
                //Writer.appendToTextRecord(//ToDo);
                //writer(OperandParser::numToHexString(OPTable::getOpcode(arr[1])));
                //writer(OperandParser::numToHexString(r1));
                //writer(OperandParser::numToHexString(r2));
                locationCounter += 2;
            } else {
                int byte1 = (OPTable::getOpcode(arr[1]) << 2) |
                            (addressingType == AdressingType::IMMEDIATE ? 2 : (addressingType == AdressingType::INDIRECT
                                                                               ? 1 : 3));
                int byte2 = 0;
                if (addressingType == ::AdressingType::INDEXED) {
                    byte2 = 1;
                }
                byte2 <<= 4;
                if (format == Format::FORMAT3) {
                    byte2 |= 2;
                } else {
                    byte2 |= 1;
                }
                cout << byte1 << ' ' << byte2 << ' ' << evaluateExpression(arr[2]);
                //Writer.appendToTextRecord(//ToDo);
                //writer(OperandParser::numToHexString(byte1));
                //writer(OperandParser::numToHexString(byte2));
                format == Format::FORMAT3 ? locationCounter += 3 : locationCounter += 4;
            }
        } else {
            if (arr[1] == "START") {
                if (locationCounter != -1) {
                    throw runtime_error("Error the program includes more than one START directive");
                }
                //TODO EDIT WHEN WRITER CONSTRUCTOR EDITED
                locationCounter = OperandParser::hexStringToInt(arr[2]);
                writer = new Writer(locationCounter, arr[0]);
            } else if (arr[1] == "END") {
                writer->end();
                return;
            } else if (arr[1] == "ORG") {
                locationCounter = symbolTable.get(arr[2]);
            } else if (arr[1] == "LTROG") {
                literalTable.organize(locationCounter);
            } else if (arr[1] == "EQU") {
                int address = OperandParser::parseOperand(arr[2], locationCounter, symbolTable);
                symbolTable.define(arr[0],address);
            } else if (arr[1] == "BYTE") {
               /* bool isLetter = arr[2][0] == 'C';
                long long literal;
                int size = 0, i = 1;
                while (arr[2][i] != '\'')i++;
                for (; i < arr[2].size(); i++) {
                    if (arr[2][i] == '\'')break;
                    size++;
                    if (isLetter) {
                        literal = OperandParser::letterStringToll(arr[2][i]);
                    } else {
                        literal = OperandParser::hexStringToll("" + arr[2][i]);
                    }
                    writer->write(literal, 1);
                }*/
               string literal = OperandParser::parseLiteral(arr[2]) ;
                writer-> write(literal);
                locationCounter += literal.size()/2 + 1;
            } else if (arr[1] == "WORD") {
                int size = atoll(arr[2].c_str()) ;
                string literal = OperandParser::numToHexString(size,3);
                writer->write(literal);
                locationCounter += 4;
            } else if (arr[1] == "RESB") {
                int size = atoi(arr[2].c_str());
                locationCounter += size + 1;
                writer->cutText();
            } else if (arr[1] == "RESW") {
                int size = atoi(arr[2].c_str());
                locationCounter += size * 3 + 1;
                writer->cutText();
            }

        }
    }
    throw runtime_error("program doesn't include END directive");
}