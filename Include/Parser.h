//
// Created by Karim on 5/11/2020.
//

#ifndef SICXEONEPASSASSEMBLER_PARSER_H
#define SICXEONEPASSASSEMBLER_PARSER_H

#include <fstream>


enum class Format{FORMAT2, FORMAT3, FORMAT4};
enum class AdressingType{IMMEDIATE, INDIRECT, INDEXED, DIRECT};

class Parser {
private:
    std::ifstream& file;


public:
    Parser(std::ifstream& file);
    std::array<std::string, 3>  parseLine();
    Format formatType(const std::string& operation);
    AdressingType addressType(const std::string& operand);


};


#endif //SICXEONEPASSASSEMBLER_PARSER_H