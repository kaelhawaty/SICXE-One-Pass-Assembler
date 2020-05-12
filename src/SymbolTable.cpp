//
// Created by Karim on 5/11/2020.
//

#include "../Include/SymbolTable.h"
#include <iostream>
#include <vector>
using namespace std;

void SymbolTable::request(const string& symbol,int location,int format){
        map[symbol].list.push_front(make_pair(location,format));
}
void SymbolTable::define(const string& symbol,int address){
       map[symbol].address = address;
       map[symbol].found = true;
       forward_list<pair<int,int>>::iterator itr = map[symbol].list.begin();
       while (itr != map[symbol].list.end()){
           //print location + 02 for 3 format or 05 for 4 format + adress
       }
};

bool SymbolTable::contains(const string& symbol){
  return map[symbol].found;
};


int SymbolTable::get(const string& symbol){
     if(map[symbol].found == true)
         return map[symbol].address;
    throw runtime_error("Not found!");
}
