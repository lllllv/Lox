#include "Lox.h"
#include "scanner.h"


void Lox::run_file(string file)
{
	ifstream f1(file, std::ios::binary | std::ios::ate);
	if (!f1)
	{
		cout << "Cannot open file: " << file;
		exit(255);
	}

	size_t len = f1.tellg();
	f1.seekg(ios::beg);
	string code(len, 0);
	f1.read(&code[0], len);
	run_code(code);

	f1.close();
}

[[noreturn]] void Lox::run_promt()
{
	string code;
	while (true)
	{
		cout << "> ";
		getline(cin, code);
		if (code.length()== 0)
			continue;
		

		run_code(code);
	}
}

void Lox::run_code(string code)
{

	scanner s(code);
	vector<Token> tokens = s.scan_Tokens();
	cout << tokens.size() << " tokens." << endl;
	for (auto i : tokens)
		cout << i.to_string() << endl;
}

Lox::Lox(int argc, char** argv)
{
	if (argc > 2)
	{
		cout << "Usage: lox [script]" << endl;
		exit(0);
	}
	else if (argc == 2)
	{
		run_file(argv[1]);
	}
	else
	{
		run_promt();
	}
	//run_file("a.txt");
}
