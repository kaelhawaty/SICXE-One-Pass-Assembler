//
// Created by magdy on 5/13/2020.
//

#ifndef SICXEONEPASSASSEMBLER_WRITER_H
#define SICXEONEPASSASSEMBLER_WRITER_H

#include <iostream>
#include <fstream>
#include <string>

class Writer{
public:
    int startoftext;
    int &location;
    int startofprogram;
    std::string programname;
    Writer(int  &locationcounter,std::string name);
    void write (long long instruction , int numberofbits);
    void writeModificatinRecord(long long adress, int length);
    void writeHeaderRecord(int &locationCounter);
    void writeTextRecord(long long adress,int length, long long val);
    std::string lltohex(long long number,int length);
    void cutText();
    void end();
};

#endif //SICXEONEPASSASSEMBLER_WRITER_H
