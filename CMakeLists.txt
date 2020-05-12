# cmake_minimum_required(VERSION <specify CMake version here>)
project(SICXEOnePassAssembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(SICXEOnePassAssembler src/main.cpp src/Interpreter.cpp Include/Interpreter.h src/Parser.cpp Include/Parser.h src/SymbolTable.cpp Include/SymbolTable.h src/LiteralTable.cpp Include/LiteralTable.h src/Registers.cpp Include/Registers.h)