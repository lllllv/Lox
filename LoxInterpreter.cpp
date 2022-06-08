// LoxInterpreter.cpp: 定义应用程序的入口点。
//

#include "LoxInterpreter.h"
#include "Lox.h"

#include "AST.h"
#include "AST_Printer.h"

using namespace std;

int main(int argc, char** argv)
{

	Lox l(argc, argv);


    /*Binary_Expr exp = Binary_Expr(new Token(STAR, "*", iteral{}, 1),
                           new Unary_Expr(new Token(MINUS, "-", iteral{}, 1),
                                          new Literal_Expr(new Token(NUMBER, "123", iteral{false, 123, ""}, 1))),
                           new Grouping_Expr(new Literal_Expr(new Token(NUMBER, "45.67", iteral{false, 45.67, ""}, 1))));

    AST_Printer p;
    p.print(&exp);*/


	return 0;
}
