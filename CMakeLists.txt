# CMakeList.txt: LoxInterpreter 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project(Lox)
set(CMAKE_CXX_STANDARD 17)

# 将源代码添加到此项目的可执行文件。
add_executable (LoxInterpreter "LoxInterpreter.cpp" "LoxInterpreter.h" "scanner.h" "Lox.h" "Lox.cpp" "scanner.cpp" AST.cpp AST.h token.cpp token.h visitor.h AST_Printer.cpp AST_Printer.h parser.cpp parser.h interpreter.cpp interpreter.h lox_object.cpp lox_object.h interpreter_exceptions.h environment.cpp environment.h lox_callable.cpp lox_callable.h native_functions.cpp native_functions.h resolver.cpp resolver.h lox_class.cpp lox_class.h lox_instance.cpp lox_instance.h interpreter_exceptions.cpp)

