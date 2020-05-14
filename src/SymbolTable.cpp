//
// Created by Karim on 5/11/2020.
//

#include "../Include/SymbolTable.h"
#include "../Include/OperandParser.h"
#include <iostream>
#include <vector>
using namespace std;
SymbolTable::SymbolTable(Writer& w) :writer(w) {

}
void SymbolTable::request(const string& symbol, int location, int  firstHalfByte){
    if(contains(symbol)){
        throw runtime_error("Symbol is already defined, Can't request!");
    }
    map[symbol].list.push_front(make_pair(location,firstHalfByte));
}
void SymbolTable::define(const string& symbol,int address){
    if (map[symbol].list.empty())throw runtime_error("Symbol is already defined!");
    map[symbol].address = address;
    auto itr = map[symbol].list.begin();
    while (itr != map[symbol].list.end()){
        int format = ((itr->second)&1) ? 6 : 4;
        int bytesToWrite = itr->second;
        bytesToWrite <<= (format-1)*4;
        bytesToWrite |= address;
        if(format == 4){
            bytesToWrite -= (itr->first+3);
            writer.writeTextRecord(OperandParser::numToHexString(bytesToWrite, format), itr->first+1);
        }else{
            writer.writeTextRecord(OperandParser::numToHexString(bytesToWrite, format), itr->first+1);
            writer.writeModificationRecord(itr->first+1);
        }
    }
};

bool SymbolTable::contains(const string& symbol){
    if(map.find(symbol) == map.end()){
        return false;
    }
    return  !map[symbol].list.empty();
};


int SymbolTable::get(const string& symbol){
    if(!map.at(symbol).list.empty()){
        throw runtime_error("Symbol is not defined!");
    }
    return map.at(symbol).address;
}
