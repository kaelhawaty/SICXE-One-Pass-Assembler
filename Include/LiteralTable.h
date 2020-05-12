//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_LITERALTABLE_H
#define SICXEONEPASSASSEMBLER_LITERALTABLE_H
#include <unordered_map>
#include <forward_list>

class LiteralTable {
private:
    std::unordered_map<long long, int> literalTable;
    std::unordered_map<long long, std::forward_list<int>> UnAssignedLiterals;
public:
    LiteralTable();
    bool containsLiteral(long long literal);
    int getAddressOfLiteral(long long literal);
    void addRequestToLiteral(long long literal, int address);
    void organize(int& locationCounter);

};


#endif //SICXEONEPASSASSEMBLER_LITERALTABLE_H

