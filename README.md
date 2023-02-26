# A Tree-walk Lox Interpreter 

C++ implementation of the Lox interpreter in [*Crafting Interpreters*](http://craftinginterpreters.com). The original 
implementation in the book is in Java. 

# Build and Usages
To build the project, CMake 3.8 or higher is required.
```shell
mkdir build && cd build
cmake .. && make
```
Execute a Lox source file:
```shell
./LoxInterpreter <filename>
```
Start a REPL:
```shell
./LoxInterpreter
```

# The Lox Programming Language

Lox is a dynamically typed, lexical scoping language supports
automatic memory management. It also supports classes and inheritance.
More details about Lox can be found in [this page](http://craftinginterpreters.com/the-lox-language.html).

# About The Book

> *Crafting Interpreters* contains everything you need to implement a full-featured, efficient scripting language. 
> You’ll learn both high-level concepts around parsing and semantics and gritty details like bytecode representation 
> and garbage collection. Your brain will light up with new ideas, and your hands will get dirty and calloused. 
> It’s a blast.
