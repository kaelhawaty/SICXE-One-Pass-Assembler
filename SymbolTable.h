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
 unordered_map<string , symbolentry> map;
 void add(string symbol,int adress,bool found,int format);
 int get(string symbol);
};


#endif //SICXEONEPASSASSEMBLER_SYMBOLTABLE_H
