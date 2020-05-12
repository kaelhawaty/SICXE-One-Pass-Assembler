//
// Created by Karim on 5/12/2020.
//

#ifndef SICXEONEPASSASSEMBLER_REGISTERS_H
#define SICXEONEPASSASSEMBLER_REGISTERS_H


#include <string>
#include <unordered_map>

namespace Registers{
    bool isRegister(const std::string& s);
    int getRegister(const std::string& s);
};

#endif //SICXEONEPASSASSEMBLER_REGISTERS_H
