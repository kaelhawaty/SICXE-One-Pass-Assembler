//
// Created by Karim on 5/12/2020.
//

#ifndef SICXEONEPASSASSEMBLER_OPTABLE_H
#define SICXEONEPASSASSEMBLER_OPTABLE_H


#include <string>
#include <unordered_map>

namespace OPTable {
     bool isOp(std::string operation);
     int getOpcode(std::string operation);
};


#endif //SICXEONEPASSASSEMBLER_OPTABLE_H
