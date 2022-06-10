//
// Created by lvxia on 2022/6/5.
//

#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <vector>
#include <exception>
#include "token.h"
#include "AST.h"
#include "interpreter_exceptions.h"



class parser {
public:
    explicit parser(vector<Token>&& t);

    vector<Stmt*> parse();

private:
    vector<Token> tokens;
    int current;

    Expr* expression();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();

    Stmt* declaration();
    Stmt* statement();
    Stmt* print_stmt();
    Stmt* expression_stmt();
    Stmt* var_declaration();


    bool match(TokenType t);
    bool check(TokenType t);
    Token* peek();
    Token* previous();
    bool is_end();
    Token* eat();
    Token* consume(TokenType t, const string& msg);
    void synchronize();


    static void report(int line, const string& where, const string& msg);
    static void error(const Token& t, const string& msg);
    parse_error report_error(const Token& t, const string& msg);
};


#endif //LOX_PARSER_H
