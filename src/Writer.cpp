
//
// Created by magdy on 5/13/2020.
//

#include "../Include/Writer.h"
using namespace std;
ofstream fs ("../hi.txt");
const int MAX = 30;
Writer::Writer(int start,std::string name){
    startOfProgram = start;
    programName = name;
    startOfRecord = curPos = start;
    lengthOfProgram=0;
    fs << "H";
    fs << programName;
    for(int i = programName.size(); i < 6; ++i)
        fs << ' ';
    fs << "            \n";
}
void Writer::reserve(int cnt){
    if(curPos-startOfRecord+cnt>=MAX){
        cutText(curPos);
    }
}
void Writer:: cutText(int newStart) {
    if(curPos==startOfRecord)
        return;
    fs << "T";
    char str[6];
    sprintf(str, "%06X", startOfRecord);
    fs << str;
    char length[2];
    sprintf(length, "%02X", curPos-startOfRecord);
    fs << length;
    startOfRecord = curPos =newStart;
    for(auto i : record)
        fs << i;
    fs << "\n";
    record.clear();
}

void Writer::writeModificationRecord(int address){
    cutText(curPos);
    fs << "M";
    char str[6];
    sprintf(str, "%06X", address);
    fs << str;
    fs << "05";
    fs << "\n";
}
void Writer::writeTextRecord(std::string Hexa, int address) {
    if(address!=curPos)
        cutText(curPos);
    reserve(Hexa.size());
    record.push_back(Hexa);
    curPos+=Hexa.size();
    lengthOfProgram+=Hexa.size();
}
void Writer::writeEndRecord() {
    cutText(curPos);
    fs << "E";
    char str[6];
    sprintf(str, "%06X", startOfProgram);
    fs << str;
    fs.seekp(7,ios::beg);
    sprintf(str, "%06X", lengthOfProgram);
    fs << str;
    fs.close();
}

