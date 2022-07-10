#include "LoxInterpreter.h"

bool had_error;

void LoxInterpreter::run_file(const string& file)
{
	ifstream f1(file, std::ios::binary | std::ios::ate);
	if (!f1)
	{
		cout << "Cannot open file: " << file;
		exit(255);
	}

	int len = f1.tellg();
	f1.seekg(ios::beg);
	string code(len, 0);
	f1.read(&code[0], len);
	run_code(code);

	f1.close();
}

[[noreturn]] void LoxInterpreter::run_prompt()
{
    interpreter i;
    resolver r(i);


	string code;
	while (true)
	{
		cout << "> ";
		getline(cin, code);
		if (code.length()== 0)
			continue;
		

		//run_code(code);
        scanner s(code);
        parser p(s.scan_Tokens());
        if(code.find(';') == string::npos)
        {
            auto expr = p.parse_expr();
            r.resolve(expr);
            i.eval(expr);
        } else
        {
            auto stmts = p.parse_stmt();
            r.resolve(stmts);
            if(!had_error)
                i.interpret(stmts);
        }


        cout << endl;
	}
}

void LoxInterpreter::run_code(string code)
{
	scanner s(code);

	auto tokens = s.scan_Tokens();
    /*cout << "*****************Scanner*****************" << endl;
	cout << tokens.size() << " tokens." << endl;
	for (const auto& i : tokens)
		cout << i->to_string() << endl;
    cout << endl;
    cout << "*****************Parser*****************" << endl;*/
    parser p(move(tokens));
    auto stmts = p.parse_stmt();

    /*//AST_Printer printer;
    //printer.print(stmts);
    cout << endl;
    cout << "*****************Interpreter*****************" << endl;*/

    interpreter i;
    resolver r(i);
    r.resolve(stmts);
    if(!had_error)
        i.interpret(stmts);

}

LoxInterpreter::LoxInterpreter(int argc, char** argv)
{
    had_error = false;
	if (argc > 2)
	{
		cout << "Usage: lox [script]" << endl;
		exit(0);
	}
	else if (argc == 2)
		run_file(argv[1]);
	else
        run_prompt();
}
