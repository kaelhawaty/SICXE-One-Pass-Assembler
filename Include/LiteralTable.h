
#ifndef SICXEONEPASSASSEMBLER_LITERALTABLE_H
#define SICXEONEPASSASSEMBLER_LITERALTABLE_H
#include <unordered_map>
#include <forward_list>
#include "../Include/Writer.h"

class LiteralTable {
private:

    std::unordered_map<std::string, int> literalTable;
    std::unordered_map<std::string, std::forward_list<std::pair<int, int>>> UnAssignedLiterals;
    Writer &writer;
public:
    LiteralTable(Writer &w);
    bool containsLiteral(const std::string& literal);
    int getAddressOfLiteral(const std::string& literal);
    void addRequestToLiteral(const std::string& literal, int address, int firstHalfByte);
    void organize(int& locationCounter);
};


#endif //SICXEONEPASSASSEMBLER_LITERALTABLE_H
