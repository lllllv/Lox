cmake_minimum_required (VERSION 3.8)

project(Lox)
set(CMAKE_CXX_STANDARD 14)

add_executable (LoxInterpreter "Lox.cpp" "Lox.h" "scanner.h" "LoxInterpreter.h" "LoxInterpreter.cpp" "scanner.cpp" AST.cpp AST.h token.cpp token.h visitor.h AST_Printer.cpp AST_Printer.h parser.cpp parser.h interpreter.cpp interpreter.h lox_object.cpp lox_object.h interpreter_exceptions.h environment.cpp environment.h lox_callable.cpp lox_callable.h native_functions.cpp native_functions.h resolver.cpp resolver.h lox_class.cpp lox_class.h lox_instance.cpp lox_instance.h interpreter_exceptions.cpp)

