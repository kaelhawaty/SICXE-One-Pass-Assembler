//
// Created by Karim on 5/11/2020.
//

#include <array>
#include <sstream>
#include <iostream>
#include "../Include/Interpreter.h"
#include "../Include/OPTable.h"
#include "../Include/Registers.h"

Interpreter::Interpreter(string path) {
    in.open(path);
    if (in.fail()) {
        throw runtime_error("Can't open the file");
    }
    parser = new Parser(in);
    locationCounter = -1;
}

//TODO
int evaluateExpression(string expression) {
    return 0;
}

void Interpreter::Assemble() {
    string line;
    while (*parser >> line) {
        if (parser->isComment(line)) {
            continue;
        }
        array<string, 3> arr;
        arr = parser->parseLine(line);
        if (locationCounter == -1 && arr[1] != "START") {
            throw runtime_error("The program must starts with START directive");
        }
        Format format = parser->formatType(arr[1]);
        AdressingType addressingType = parser->addressType(arr[2]);
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
                format == Format::FORMAT3 ? locationCounter += 3 : locationCounter += 4;
            }
        } else {
            if (arr[1] == "START") {
                if (locationCounter != -1) {
                    throw runtime_error("Error the program includes more than one START directive");
                }
                locationCounter = 0;//TODO HexaToInt(arr[2])
                //Writer.writeHeaderRecord(//TODO)
            } else if (arr[1] == "END") {
                //Writer.writeEndRecord(//ToDo)
                return;
            } else if (arr[1] == "ORG") {
                //locationCounter = HexaToInt(arr[2]);
            } else if (arr[1] == "LTROG") {
                literalTable.organize(locationCounter);
            } else if (arr[1] == "EQU") {
                //vector<string> operand = OperandParser::parseOperand(arr[2]);
                int sign = 1, address =OperandParser::parseOperand(arr[2],locationCounter,symbolTable) ;
                /*for (int i = 0; i < operand.size(); i++) {
                    if (operand[i] == "*")address += sign * locationCounter;
                    else if (operand[i] == "-")sign *= -1;
                    else if (operand[i] == "+")sign *= 1; //IDK
                    else
                        address += symbolTable.get(operand[i]) * sign;
                }*/
                symbolTable.define(arr[0], address);
            } else if (arr[1] == "BYTE") {
                //
                int i = 1;
                //bool letterOrHex = arr[2][0] == 'X';
                string newOperand = "";
                /*for (; i < arr[2].size(); i++) {
                    if (arr[2][i] != ' ' && arr[2][i] != '\'')newOperand += arr[2][i];
                }*/
                long long literall = -1;
                //if(letterOrHex)literall =HexaToInt(newOperand);
                //else literall = LetterToInt(newOperand);
                //literalTable.addRequestToLiteral(literall, locationCounter);
                symbolTable.define(arr[0], locationCounter);
                locationCounter += newOperand.size() + 1;
            } else if (arr[1] == "RESB") {
                int size = atoi(arr[2].c_str());
                symbolTable.define(arr[0], locationCounter);
                locationCounter += size + 1;
            } else if (arr[1] == "WORD") {
                long long literall = atoll(arr[2].c_str());
                //literalTable.addRequestToLiteral(literall, locationCounter);
                symbolTable.define(arr[0], locationCounter);
                locationCounter += 4;
            } else if (arr[1] == "RESW") {
                int size = atoi(arr[2].c_str());
                symbolTable.define(arr[0], locationCounter);
                locationCounter += size * 3 + 1;
            }

        }
    }
    throw runtime_error("program doesn't include END directive");
}