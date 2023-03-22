cmake_minimum_required (VERSION 3.8)

project(Lox)
set(CMAKE_CXX_STANDARD 14)


if(NOT DEFINED ENV{LLVM_DIR})
    set(ENV{LLVM_DIR} /usr/local/opt/llvm/)
endif()


find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable (LoxInterpreter "Lox.cpp" "Lox.h" "scanner.h" "LoxInterpreter.h" "LoxInterpreter.cpp" "scanner.cpp" AST.cpp AST.h token.cpp token.h visitor.h AST_Printer.cpp AST_Printer.h parser.cpp parser.h interpreter.cpp interpreter.h lox_object.cpp lox_object.h interpreter_exceptions.h environment.cpp environment.h lox_callable.cpp lox_callable.h native_functions.cpp native_functions.h resolver.cpp resolver.h lox_class.cpp lox_class.h lox_instance.cpp lox_instance.h interpreter_exceptions.cpp Codegen_visitor.h LLVM_codegen.cpp LLVM_codegen.h)

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(LoxInterpreter ${llvm_libs})

