# CMakeList.txt: LoxInterpreter 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_executable (LoxInterpreter "LoxInterpreter.cpp" "LoxInterpreter.h" "scanner.h" "Lox.h" "Lox.cpp" "scanner.cpp")

