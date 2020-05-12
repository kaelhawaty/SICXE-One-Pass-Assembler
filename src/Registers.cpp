//
// Created by Karim on 5/12/2020.
//

#include "../Include/Registers.h"
using namespace std;
unordered_map<string, int> Registers::table{
        {"A", 0}, {"X", 1}, {"L", 2}, {"B", 3},
        {"S", 4}, {"T", 5}, {"F", 6}
};

bool Registers::isRegister(const std::string &s) {
    return table.find(s) != table.end();
}
int Registers::getRegister(const std::string &s) {
    return table[s];
}