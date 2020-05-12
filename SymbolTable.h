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
    int adress;
    int format;
    forward_list<pair<int,int>>list;
};
class SymbolTable {
public:
 unordered_map<string , symbolentry> map;
 void request(string symbol,int location,int format);
 void define(string symbol,int adress);
 bool contains(string symbol);
 int get(string symbol);
};


#endif //SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
