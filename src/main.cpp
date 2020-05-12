#include <iostream>
#include "../Include/SymbolTable.h"
int main() {
    SymbolTable s;
    cout << s.contains("hey");
    s.define("by",1);
    cout << s.contains("hey");
    s.request("hhh",21,2);
    cout << s.map.size();
}
