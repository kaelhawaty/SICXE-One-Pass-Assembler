//
// Created by magdy on 5/13/2020.
//

#ifndef SICXEONEPASSASSEMBLER_WRITER_H
#define SICXEONEPASSASSEMBLER_WRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Writer{
private:
    int startOfProgram, startOfRecord, curPos, lengthOfProgram;
    std::string programName;
    std::vector<std::string>record;
public:
    Writer(int start,std::string name);
    void writeModificationRecord(int address);
    void writeTextRecord(std::string Hexa, int address);
    void cutText(int newAddress);
    void reserve(int cnt);
    void writeEndRecord();
};

#endif //SICXEONEPASSASSEMBLER_WRITER_H
