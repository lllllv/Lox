//
// Created by lvxia on 2022/6/5.
//

#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <vector>
#include <exception>
#include "token.h"
#include "AST.h"

class parse_error : public exception {

    const char * what () const noexcept override
    {
        return "parse error!";
    }
};


class parser {
public:
    explicit parser(vector<Token>&& t);

    Expr* parse();

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
