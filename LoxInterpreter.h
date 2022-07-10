#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "scanner.h"
#include "parser.h"
#include "resolver.h"
#include "interpreter.h"


using namespace std;

class LoxInterpreter {
private:

	void run_file(const string& file);

    [[noreturn]] void run_prompt();

	void run_code(string code);

public:
	LoxInterpreter(int argc, char** argv);
};