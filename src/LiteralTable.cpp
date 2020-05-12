
//
// Created by Karim on 5/11/2020.
//

#include "../Include/LiteralTable.h"

LiteralTable:: LiteralTable() {
    literalTable.clear();
}
bool LiteralTable::containsLiteral(long long literal) {
    if(literalTable.count(literal)){
        return true;
    }
    return false;
}
int LiteralTable::getAddressOfLiteral(long long literal){
    if(!LiteralTable::containsLiteral(literal)){
        throw std::runtime_error("Literal doesn't Exist");
    }
    return literalTable[literal].literalAddress;
}
void LiteralTable::addRequestToLiteral(long long literal, int address){
    if(!LiteralTable:containsLiteral(literal)){
        throw std::runtime_error("Literal exist");
    }
    UnAssignedLiterals[literal].push_front(address);
}
int getCountBytes(long long literal){
    int ans = 0;
    while(literal >>= 8){
        ans++;
    }
    return ans;
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
