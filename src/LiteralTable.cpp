//
// Created by Karim on 5/11/2020.
//

#include "../Include/LiteralTable.h"
#include "../Include/OperandParser.h"


LiteralTable::LiteralTable(Writer &w) : writer(w) {

}
bool LiteralTable::containsLiteral(const std::string& literal) {
    if(literalTable.count(literal)){
        return true;
    }
    return false;
}

int LiteralTable::getAddressOfLiteral(const std::string& literal){
    if(!LiteralTable::containsLiteral(literal)){
        throw std::runtime_error("Literal doesn't Exist");
    }
    return literalTable[literal];
}

void LiteralTable::addRequestToLiteral(const std::string& literal, int address, int firstHalfByte){
    if(LiteralTable::containsLiteral(literal)){
        throw std::runtime_error("Literal exist");
    }
    UnAssignedLiterals[literal].push_front({address, firstHalfByte});
}


void LiteralTable:: organize(int& address) {
    for(auto entry: UnAssignedLiterals){
        literalTable[entry.first] = address;
        std::string str = OperandParser::parseLiteral(entry.first);
        writer.writeTextRecord(str, address);
        address += str.size()/2;
    }
    for(auto entry : UnAssignedLiterals){
        for(auto x : entry.second){
            int format = ((x.second)&1) ? 6 : 4;
            int bytesToWrite = x.second;
            bytesToWrite <<= (format-1)*4;
            bytesToWrite |= literalTable[entry.first];
            if(format == 4){
                bytesToWrite -= (x.first+3);
                writer.writeTextRecord(OperandParser::numToHexString(bytesToWrite, 4), x.first+1);
            }else{
                writer.writeTextRecord(OperandParser::numToHexString(bytesToWrite, 6), x.first+1);
                writer.writeModificationRecord(x.first+1);
            }
        }
    }
    UnAssignedLiterals.erase(UnAssignedLiterals.begin(), UnAssignedLiterals.end());
}
