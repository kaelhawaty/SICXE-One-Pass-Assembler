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
    std::array<std::string, 3>  parseLine(std::string& s);
    bool isComment(const std::string& line);
    Format formatType(const std::string& operation);
    AdressingType addressType(const std::string& operand);
    operator bool() const;
    friend Parser& operator>>(Parser& in, std::string&s);


};


#endif //SICXEONEPASSASSEMBLER_PARSER_H