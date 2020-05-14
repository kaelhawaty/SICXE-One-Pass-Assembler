
//
// Created by magdy on 5/13/2020.
//

#include "../Include/Writer.h"
#include  <iomanip>
using namespace std;
const int MAX = 30;
Writer::Writer(ofstream& file) : fs(file){
}
void Writer::createHeader(int start, const std::string &name) {
    startOfProgram = start;
    programName = name;
    record = "";
    startOfRecord = curPos = start;
    lengthOfProgram=0;
    fs << "H";
    fs << programName;
    for(int i = programName.size(); i < 6; ++i)
        fs << ' ';
    fs << "^            \n";
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
    fs << setfill('0') << setw(6) << hex << startOfRecord << "^";
    fs << setfill('0') << setw(2) << hex << (curPos-startOfRecord) << "^";
    startOfRecord = curPos =newStart;
    fs<<record;
    fs << "\n";
    record.clear();
}

void Writer::writeModificationRecord(int address){
    cutText(address);
    fs << "M";
    fs << setfill('0') << setw(6) << hex << address;
    fs << "^05";
    fs << "\n";
}
void Writer::writeTextRecord(const std::string& Hexa, int address) {
    if(address!=curPos)
        cutText(address);
    reserve(Hexa.size());
    record+=Hexa;
    curPos+=Hexa.size()/2;
    lengthOfProgram+=Hexa.size()/2;
}
void Writer::addLength(int cnt) {
    lengthOfProgram += cnt;
}
void Writer::writeEndRecord() {
    cutText(curPos);
    fs << "E";
    fs << setfill('0') << setw(6) << hex << startOfProgram;
    fs.seekp(8,ios::beg);
    fs << setfill('0') << setw(6) << hex << startOfProgram << "^";
    fs << setfill('0') << setw(6) << hex << lengthOfProgram-1;
}

