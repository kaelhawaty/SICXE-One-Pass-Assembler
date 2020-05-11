# cmake_minimum_required(VERSION <specify CMake version here>)
project(SICXEOnePassAssembler)

set(CMAKE_CXX_STANDARD 17)

add_executable(SICXEOnePassAssembler main.cpp Interpreter.cpp Interpreter.h Parser.cpp Parser.h SymbolTable.cpp SymbolTable.h LiteralTable.cpp LiteralTable.h)