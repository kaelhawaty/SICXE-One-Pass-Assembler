//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
#define SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
#include <unordered_map>
#include <forward_list>
#include <string>
#include <ostream>
#include "../Include/Writer.h"
using namespace std;
class SymbolTable {
private:
    struct SymbolEntry{
        int address;
        // Address to be modified, first half byte
        forward_list<pair<int,int>>list;
    };
    unordered_map<string , SymbolEntry> map;
    Writer& writer;

public:
    SymbolTable(Writer& w);
    void request(const string& symbol, int location, int firstHalfByte);
    void define(const string& symbol,int address);
    bool contains(const string& symbol);
    int get(const string& symbol);
};


#endif //SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
