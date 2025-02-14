//
// Created by Karim on 5/11/2020.
//

#include <array>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <sstream>
#include "../include/Registers.h"
#include "../include/OPTable.h"
#include "../Include/Parser.h"

using namespace std;
enum class Need {
    OPTIONAL, NEEDED, FORBIDDEN
};

const unordered_map<string, array<Need, 3>> mp = {
        {"END",   {Need::FORBIDDEN, Need::NEEDED,   Need::OPTIONAL}},
        {"ORG",   {Need::FORBIDDEN, Need::NEEDED,   Need::OPTIONAL}},
        {"EQU",   {Need::NEEDED,    Need::NEEDED,   Need::NEEDED}},
        {"LTORG", {Need::FORBIDDEN, Need::NEEDED,   Need::FORBIDDEN}},
        {"START", {Need::OPTIONAL,  Need::OPTIONAL, Need::OPTIONAL}},
        {"RESB",  {Need::NEEDED,    Need::NEEDED,   Need::NEEDED}},
        {"RESW",  {Need::NEEDED,    Need::NEEDED,   Need::NEEDED}},
        {"BYTE",  {Need::NEEDED,    Need::NEEDED,   Need::NEEDED}},
        {"WORD",  {Need::NEEDED,    Need::NEEDED,   Need::NEEDED}},
        {"RSUB",  {Need::OPTIONAL,  Need::NEEDED,   Need::FORBIDDEN}}
};

const unordered_set<string> isFormat2{
        "ADDR", "CLEAR", "COMPR", "DIVR",
        "MULR", "RMO", "SHIFTL", "SHIFTR",
        "SUBR", "TIXR"
};
const regex e("^\\s*([a-zA-Z]\\w*\\s+)?\\+?\\w+(((\\s+[a-zA-Z]\\w*(\\,[AXLBSTF]\\w*)?\\s*)|(\\s+[#@]?[a-zA-Z]\\w*\\s*))|(\\s+[@#]?\\d+)|(\\s+\\*)|(\\s+=?[XWC]'\\w+')|(\\s+(([@#]?[a-zA-Z]\\w*)|(\\s+\\*))\\s*[+-]\\s*(([a-zA-Z]\\w*)|\\d+)))?\\s*$");
const regex startRegex("^\\s*([a-zA-Z]\\w*\\s+)?START\\s+[A-F0-9]+\\s*$");

Parser::Parser(std::ifstream &file) : file(file) {
}

bool Parser::isComment(const std::string &line) {
    return line.find_first_not_of(' ') == string::npos || line[0] == '.';
}

static bool checkNotOpcodeorDirective(string s) {
    if(s[0]=='+')
        s.erase(s.begin());
    return !OPTable::isOp(s) && mp.find(s) == mp.end();
}

array<string, 3> Parser::parseLine(string &s) {
    std::for_each(s.begin(), s.end(), [val{false}](char &c) mutable {
        if(c == '\''){
            val = val^1;
        }
        if(!val) {
            c = ::toupper(c);
        }
    });
    if (!regex_match(s, e) && !regex_match(s, startRegex)) {
        throw runtime_error("Unknown line!");
    }
    vector<string> result;
    istringstream iss(s);
    for (std::string s; iss >> s;)
        result.push_back(s);
    array<string, 3> arr;
    // Conjecture LULW, If it is 1 word then its opcode, otherwise its opcode and operand, otherwide all 3
    if (result.size() == 1) {
        arr = {"", result[0], ""};
    } else if (result.size() == 2) {
        if (result[1] == "RSUB") {
            arr = {result[0], result[1], ""};
        } else {
            arr = {"", result[0], result[1]};
        }
    } else {
        arr = {result[0], result[1], result[2]};
    }
    auto it = mp.find(arr[1]);
    // Not Opcode nor Directive
    if (checkNotOpcodeorDirective(arr[1])) {
        throw runtime_error("Not OPcode nor Directive");
    }
    if (!checkNotOpcodeorDirective(arr[0])) {
        throw runtime_error("Label is a reserved word");
    }

    if ( !checkNotOpcodeorDirective(arr[2])) {
        throw runtime_error("Operand is a reserved word");
    }
    // Checking Need
    if (it != mp.end()) {
        array<Need, 3> cur = it->second;
        for (int i = 0; i < 3; i++) {
            if (cur[i] == Need::NEEDED && arr[i] == "") {
                throw runtime_error("Line lacks one of Label/Opcode/Operand!");
            }
            if (cur[i] == Need::FORBIDDEN && arr[i] != "") {
                throw runtime_error("Line has a forbidden combination of Label/Opcode/Operand!");
            }
        }
    } else if (arr[1] == "" || arr[2] == "") {
        throw runtime_error("Line lacks one of Label/Opcode/Operand!");
    }
    // If format 2 then operands are registers
    if (isFormat2.count(arr[1])) {
        istringstream temp(arr[2]);
        string split;
        while (getline(temp, split, ',')) {
            if (!Registers::isRegister(split)) {
                throw runtime_error("Operands aren't Registers, Format 2");
            }
        }
    }
    return arr;
}

Format Parser::formatType(const string &operation) {
    if (operation.empty()) {
        throw runtime_error("Undefined operation format");
    }
    if (isFormat2.count(operation)) {
        return Format::FORMAT2;
    }
    return (operation[0] == '+') ? Format::FORMAT4 : Format::FORMAT3;
}

AdressingType Parser::addressType(const string &operand) {
    if (operand.empty()) {
        return AdressingType::DIRECT;
    }
    bool flag = operand.find(",") != string::npos;
    if ((operand[0] == '#' || operand[0] == '@') && flag) {
        throw runtime_error("Illegal Indexing mode!");
    }
    if (operand[0] == '#') {
        return AdressingType::IMMEDIATE;
    }
    if (operand[0] == '@') {
        return AdressingType::INDIRECT;
    }
    if (flag) {
        return AdressingType::INDEXED;
    }
    return AdressingType::DIRECT;
}

Parser &operator>>(Parser &in, string &s) {
    getline(in.file, s);
    return in;
}

Parser::operator bool() const {
    return !file.eof();
}