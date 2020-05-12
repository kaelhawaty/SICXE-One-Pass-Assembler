//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
#define SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
#include <unordered_map>
#include <forward_list>
#include <string>
#include <ostream>
using namespace std;
struct symbolentry{
    bool found;
    int address;
    int format;
    forward_list<pair<int,int>>list;
};
class SymbolTable {
public:
 unordered_map<string , symbolentry> map;
 SymbolTable();
 void request(const string& symbol,int location,int format);
 void define(const string& symbol,int address);
 bool contains(const string& symbol);
 int get(const string& symbol);
};


#endif //SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
