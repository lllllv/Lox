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
    explicit parser(vector<shared_ptr<Token>> tokens);

    vector<shared_ptr<Stmt>> parse_stmt();
    shared_ptr<Expr> parse_expr();

private:
    vector<shared_ptr<Token>> tokens;
    int current;

    shared_ptr<Expr> expression();
    shared_ptr<Expr> assignment();
    shared_ptr<Expr> equality();
    shared_ptr<Expr> comparison();
    shared_ptr<Expr> term();
    shared_ptr<Expr> factor();
    shared_ptr<Expr> unary();
    shared_ptr<Expr> primary();
    shared_ptr<Expr> logical_or();
    shared_ptr<Expr> logical_and();
    shared_ptr<Expr> call();
    shared_ptr<Expr> finish_call(shared_ptr<Expr> callee);

    shared_ptr<Stmt> declaration();
    shared_ptr<Stmt> statement();
    shared_ptr<Stmt> print_stmt();
    shared_ptr<Stmt> expression_stmt();
    shared_ptr<Stmt> var_declaration();
    shared_ptr<vector<shared_ptr<Stmt>>> block();
    shared_ptr<Stmt> if_stmt();
    shared_ptr<Stmt> while_stmt();
    shared_ptr<Stmt> for_stmt();
    shared_ptr<Function_Stmt> function(const string&);
    shared_ptr<Stmt> return_stmt();
    shared_ptr<Stmt> class_declaration();


    bool match(TokenType t);
    bool check(TokenType t);
    shared_ptr<Token> peek();
    shared_ptr<Token> previous();
    bool is_end();
    shared_ptr<Token> eat();
    shared_ptr<Token> consume(TokenType t, const string& msg);
    void synchronize();


    static void report(int line, const string& where, const string& msg);
    static void error(const Token& t, const string& msg);
    static parse_error report_error(const Token& t, const string& msg);
};


#endif //LOX_PARSER_H
