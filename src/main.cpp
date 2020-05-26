#include <iostream>
#include <fstream>
#include "../Include/SymbolTable.h"
#include "../Include/Parser.h"
#include "../Include/Interpreter.h"
#include "../Include/Writer.h"

using namespace std;

int main() {
    string assem, s;
    ofstream err("err.txt");
    try {
        cin >> assem >> s;
        if(assem != "assembler"){
            throw runtime_error("Command must start with 'assembler <source-file-name>'");
        }
        ifstream ifs(s+".txt");
        ofstream out("objCode.txt");
        if(!ifs || !out){
            throw runtime_error("I/O Exception: Couldn't open/create file");
        }
        Interpreter interpreter(ifs, out);
        interpreter.Assemble();
        ifs.close();
        out.close();
    }catch(exception& e){
        err << e.what();
    }
    return 0;
}
