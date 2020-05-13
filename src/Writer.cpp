//
// Created by magdy on 5/13/2020.
//

#include "../Include/Writer.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include <string.h>
#include<sstream>
using namespace std;
vector<string> v;

unordered_map <string ,string > um;
stringstream ss;
string str = "";
ofstream fs ("../hi.txt");
int length;

string toStr(long long x){
    ss << x;
    ss >> str;
    return str;
}


Writer::Writer(int &locationcounter,std::string name) : location(locationcounter){
    startofprogram = locationcounter;
    programname = name;
    um["0000"] = '0';
    um["0001"] = '1';
    um["0010"] = '2';
    um["0011"] = '3';
    um["0100"] = '4';
    um["0101"] = '5';
    um["0110"] = '6';
    um["0111"] = '7';
    um["1000"] = '8';
    um["1001"] = '9';
    um["1010"] = 'a';
    um["1011"] = 'b';
    um["1100"] = 'c';
    um["1101"] = 'd';
    um["1110"] = 'e';
    um["1111"] = 'f';
    fs << "H";
    fs << programname;
    fs << "   ";
    fs << lltohex(location,6);
    fs << "      ";
    fs << "\n";
}

void Writer::write (long long instruction , int numberofhexabits){
    string str = lltohex(instruction,numberofhexabits);
    if(v.empty()) {
        startoftext = location;
        length = 0;
    }
    v.push_back(str);
    length+= numberofhexabits;
};

void Writer:: cutText() {
    fs << "T";
    fs << lltohex(startoftext,6);
    fs << lltohex(length,2);
    for(auto i : v)
        fs << i;
    fs << "\n";
    v.clear();
}

void Writer::writeModificatinRecord(long long adress, int length){
    fs << "M";
    fs << lltohex(adress,6);
    fs << lltohex(length,2);
    fs << "\n";
};

void Writer::writeHeaderRecord(int &locationCounter){

};
void Writer::writeTextRecord(long long adress,int length, long long val){
    fs << "T";
    fs << lltohex(adress,6);
    fs << lltohex(length,2);
    fs << lltohex(val,length);
    fs << "\n";
};


string Writer::lltohex(long long num,int length) {
    std::string binary = std::bitset<64>(num).to_string();
    string hexa = "";
    int cnt = 0;
    for(int i = binary.size()-4 ; i>0 ; i-=4){
        hexa = um[binary.substr(i,4)] + hexa;
        cnt++;
        if(cnt == length)
            break;
    }
    cout << hexa;
    return hexa;
}

void Writer::end() {
    fs << "E";
    fs << lltohex(startofprogram,6);
    fs.seekp(0,ios::beg);
    fs << "H";
    fs<<programname;
    fs << "   ";
    fs << lltohex(startofprogram,6);
    fs << lltohex(location - startofprogram,6);
    fs.close();
}




