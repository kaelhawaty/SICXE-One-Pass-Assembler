#include <iostream>
#include <fstream>
#include "../Include/SymbolTable.h"
#include "../Include/Parser.h"
#include "../Include/Interpreter.h"
#include "../Include/Writer.h"

using namespace std;

int main() {
    /* int x = 0;
   Writer wr(x,"copy");
   wr.write(347324,6);
   wr.cutText();
     wr.write(54655656,6);
     wr.cutText();
     wr.writeModificatinRecord(343,2);
     wr.writeTextRecord(4343,4,47632746324);
     wr.end();*/
    ifstream ifs;
    ifs.open("../test.txt", ifstream::in);
    Interpreter interpreter(ifs);
    interpreter.Assemble();
}
