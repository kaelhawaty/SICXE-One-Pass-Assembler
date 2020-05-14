//
// Created by Karim on 5/11/2020.
//

#include <array>
#include <regex>
#include "../Include/Interpreter.h"
#include "../Include/OPTable.h"
#include "../Include/Registers.h"

Interpreter::Interpreter(ifstream &file, ofstream &outfile) : parser(Parser(file)), writer(Writer(outfile)),
                                                              literalTable(writer), symbolTable(writer) {
    locationCounter = -1;
}
static bool isSymbol(const string& s){
    regex e("^(([a-zA-Z]\\w*(\\,X\\w*)?\\s*)|([#@]?[a-zA-Z]\\w*\\s*))$");
    return regex_match(s, e);
}

static bool isLiteral(const string& s){
    regex e("^(=[XWC]'\\w+')$");
    return regex_match(s, e);
}

static bool isNumber(const string& s){
    regex e("(#?\\d+)");
    return regex_match(s, e);
}

void Interpreter::Assemble() {
    string line;
    while (parser) {
        parser >> line;
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
        } else if (arr[0] != "" && arr[0]!="EQU") {
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
                string str = OperandParser::numToHexString(OPTable::getOpcode(arr[1]),2);
                str += OperandParser::numToHexString(r1);
                if (r2)str += OperandParser::numToHexString(r2);
                else str += "0";
                writer.writeTextRecord(str, locationCounter);
                locationCounter += 2;
            } else {
                int byte = OPTable::getOpcode(arr[1]);
                byte |= addressingType == AdressingType::IMMEDIATE ? 1 : (addressingType == AdressingType::INDIRECT
                                                                          ? 2 : 3);
                if(arr[1]=="RSUB"){
                    writer.writeTextRecord("4F0000", locationCounter);
                    locationCounter += 3;
                    continue;
                }
                byte <<= 1;
                if (addressingType == AdressingType::INDEXED) {
                    byte |= 1;
                }
                byte <<= 3;
                if (format == Format::FORMAT3) {
                    byte |= 2;
                } else {
                    byte |= 1;
                }
                int x;
                if (isSymbol(arr[2])){
                    if(arr[2][0] == '#' || arr[2][0] == '@'){
                        arr[2].erase(0, 1);
                    }else if(addressingType == AdressingType::INDEXED){
                        arr[2] = arr[2].substr(0, (int)arr[2].find(","));
                    }
                    if(symbolTable.contains(arr[2])){
                        x = symbolTable.get(arr[2]);
                        if(format == Format::FORMAT4){
                            writer.writeModificationRecord(locationCounter);
                        }
                    }else{
                        symbolTable.request(arr[2], locationCounter, byte & 0b1111);
                        x = locationCounter + 3;
                    }
                }else if(isNumber(arr[2])){
                    if(arr[2][0] == '#'){
                        arr[2].erase(0, 1);
                    }
                    x = std::atoi(arr[2].c_str());
                    byte -= (format == Format::FORMAT4) ? 0 : 2;
                }else if(isLiteral(arr[2])){
                    string str = OperandParser::parseLiteral(arr[2]);
                    if(literalTable.containsLiteral(str)){
                        x = literalTable.getAddressOfLiteral(arr[2]);
                        if(format == Format::FORMAT4){
                            writer.writeModificationRecord(locationCounter);
                        }
                    }else{
                        literalTable.addRequestToLiteral(arr[2], locationCounter, byte & 0b1111);
                        x = locationCounter + 3;
                    }
                }else if(arr[2]=="*"){
                    x=locationCounter+3;
                    if(format==Format::FORMAT4){
                        writer.writeModificationRecord(locationCounter+1);
                    }
                }
                else{
                    throw runtime_error("Unknown operand!");
                }
                if(format == Format::FORMAT3 && (byte&2) != 0) {
                    x -= locationCounter + 3;
                }
                string str = OperandParser::numToHexString(byte,3);
                str += OperandParser::numToHexString(x, ((format == Format::FORMAT3) ? 3 : 5));
                writer.writeTextRecord(str, locationCounter);
                format == Format::FORMAT3 ? locationCounter += 3 : locationCounter += 4;
            }
        } else {
            if (arr[1] == "START") {
                if (locationCounter != -1) {
                    throw runtime_error("Error the program includes more than one START directive");
                }
                locationCounter = OperandParser::hexStringToInt(arr[2]);
                writer.createHeader(locationCounter, arr[0]);
            } else if (arr[1] == "END") {
                literalTable.organize(locationCounter);
                symbolTable.finish();
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
                locationCounter += literal.size()/2;
            } else if (arr[1] == "WORD") {
                int size = atoi(arr[2].c_str());
                string literal = OperandParser::numToHexString(size,6);
                writer.writeTextRecord(literal,locationCounter);
                locationCounter += 3;
            } else if (arr[1] == "RESB") {
                int size = atoi(arr[2].c_str());
                locationCounter += size;
                writer.addLength(size);
            } else if (arr[1] == "RESW") {
                int size = atoi(arr[2].c_str());
                locationCounter += size * 3;
                writer.addLength(size*3);
            }
        }
    }
    throw runtime_error("program doesn't include END directive");
}
