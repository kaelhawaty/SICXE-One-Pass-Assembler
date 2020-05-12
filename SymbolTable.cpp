//
// Created by Karim on 5/11/2020.
//

#include "SymbolTable.h"
#include <iostream>
#include <vector>
using namespace std;

// first for format
// second.first for location in memory
// second.second for operand
vector<pair<int,pair<int,int>>>v;

void SymbolTable::add(string symbol,int adress,bool found,int format){
    if(!found)
        map[symbol].list.push_front(make_pair(adress,format));
    else {
        map[symbol].adress = adress;
        map[symbol].found = true;
        forward_list<pair<int,int>>::iterator itr = map[symbol].list.begin();
        while (itr !=  map[symbol].list.end()){
             pair<int,pair<int,int>> pair;
             pair.first = itr->first;
             pair.second.first = itr->second;
             pair.second.second = map[symbol].adress;
             v.push_back(pair);
           }
        }
    }


int SymbolTable::get(string symbol){
     if(map[symbol].found == true)
         return map[symbol].adress;
     else
         return -1;
}
