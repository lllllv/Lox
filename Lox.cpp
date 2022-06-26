#include "Lox.h"
#include "AST_Printer.h"
#include "scanner.h"
#include "parser.h"
#include "resolver.h"
#include "interpreter.h"

bool had_error;

void Lox::run_file(const string& file)
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
        cout << endl;
	}
}

void Lox::run_code(string code)
{
	scanner s(code);

	vector<Token> tokens = s.scan_Tokens();
    cout << "*****************Scanner*****************" << endl;
	cout << tokens.size() << " tokens." << endl;
	for (auto i : tokens)
		cout << i.to_string() << endl;
    cout << endl;
    cout << "*****************Parser*****************" << endl;
    parser p(move(tokens));
    vector<Stmt*> stmts = p.parse();

    AST_Printer printer;
    printer.print(stmts);
    cout << endl;
    cout << "*****************Interpreter*****************" << endl;

    interpreter i;
    resolver r(&i);
    r.resolve(&stmts);
    if(!had_error)
        i.interpret(stmts);

}

Lox::Lox(int argc, char** argv)
{
    had_error = false;
	/*if (argc > 2)
	{
		cout << "Usage: lox [script]" << endl;
		exit(0);
	}
	else if (argc == 2)
	{
        cout << argv[1] << endl;
		run_file(argv[1]);
	}
	else
	{
		run_promt();
	}*/
	run_file("test.txt");
}
