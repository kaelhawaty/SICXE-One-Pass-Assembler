//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_LITERALTABLE_H
#define SICXEONEPASSASSEMBLER_LITERALTABLE_H
#include <unordered_map>
#include <forward_list>
#include "../Include/Writer.h"

class LiteralTable {
private:
    std::unordered_map<std::string, int> literalTable;
    std::unordered_map<std::string, std::forward_list<int>> UnAssignedLiterals;
    Writer &writer;
public:
    LiteralTable(Writer &w);
    bool containsLiteral(std::string literal);
    int getAddressOfLiteral(std::string literal);
    void addRequestToLiteral(std::string literal, int address);
    void organize(int& locationCounter);

};


#endif //SICXEONEPASSASSEMBLER_LITERALTABLE_H

