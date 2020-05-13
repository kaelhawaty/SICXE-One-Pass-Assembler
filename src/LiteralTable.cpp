
//
// Created by Karim on 5/11/2020.
//

#include "../Include/LiteralTable.h"
#include "../Include/OperandParser.h";
LiteralTable:: LiteralTable() {
    literalTable.clear();
}
bool LiteralTable::containsLiteral(std::string literal) {
    if(literalTable.count(literal)){
        return true;
    }
    return false;
}

int LiteralTable::getAddressOfLiteral(std::string literal){
    if(!LiteralTable::containsLiteral(literal)){
        throw std::runtime_error("Literal doesn't Exist");
    }
    return literalTable[literal];
}

void LiteralTable::addRequestToLiteral(std::string literal, int address){
    if(!LiteralTable::containsLiteral(literal)){
        throw std::runtime_error("Literal exist");
    }

    UnAssignedLiterals[literal].push_front(address);
}

int getCountBytes(std::string literal){
    std:: string str = OperandParser::parseLiteral(literal);
    return str.size()/2;
}

void LiteralTable:: organize(int& address) {
    for(auto entry : UnAssignedLiterals){
        literalTable[entry.first] = address;
        int cnt = getCountBytes(entry.first);
        for(int x : entry.second){
            //parser.writeTextRecord(address, cnt, x);
        }
        address += cnt;
    }
    UnAssignedLiterals.erase(UnAssignedLiterals.begin(), UnAssignedLiterals.end());
}
