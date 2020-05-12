#include <iostream>
#include <fstream>
#include "../Include/SymbolTable.h"
#include "../Include/Parser.h"
using namespace std;
int main() {
    ifstream in("../Q2.txt");
    if(!in){
        cout << "failure";
        return 0;
    }
    Parser par(in);
    string line;
    while(par >> line){
        if(par.isComment(line)){
            continue;
        }
        array<string, 3> arr;
        try {
             arr= par.parseLine(line);
        }catch(exception& e){
            cout << e.what();
            break;
        }
        for(int i = 0; i < 3; i ++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
