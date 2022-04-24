#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>



using namespace std;

class Lox
{
private:
	void run_file(string file);

    [[noreturn]] void run_promt();

	void run_code(string code);

public:
	Lox(int argc, char** argv);
};