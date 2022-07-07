//
// Created by lvxia on 2022/6/5.
//

#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <vector>
#include <exception>
#include <memory>
#include "token.h"
#include "AST.h"
#include "interpreter_exceptions.h"



class parser {
public:
    explicit parser(unique_ptr<vector<unique_ptr<Token>>> tokens);

    unique_ptr<vector<Stmt*>> parse();

private:
    unique_ptr<vector<unique_ptr<Token>>> tokens;
    int current;

    unique_ptr<Expr> expression();
    unique_ptr<Expr> assignment();
    unique_ptr<Expr> equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();
    unique_ptr<Expr> logical_or();
    Expr* logical_and();
    Expr* call();
    Expr* finish_call(Expr* callee);

    Stmt* declaration();
    Stmt* statement();
    Stmt* print_stmt();
    Stmt* expression_stmt();
    Stmt* var_declaration();
    vector<Stmt*>* block();
    Stmt* if_stmt();
    Stmt* while_stmt();
    Stmt* for_stmt();
    Function_Stmt* function(const string&);
    Stmt* return_stmt();
    Stmt* class_declaration();


    bool match(TokenType t);
    bool check(TokenType t);
    unique_ptr<Token> peek();
    unique_ptr<Token> previous();
    bool is_end();
    unique_ptr<Token> eat();
    unique_ptr<Token> consume(TokenType t, const string& msg);
    void synchronize();


    static void report(int line, const string& where, const string& msg);
    static void error(const Token& t, const string& msg);
    parse_error report_error(const Token& t, const string& msg);
};


#endif //LOX_PARSER_H
