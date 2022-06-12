//
// Created by lvxia on 2022/6/5.
//

#include "parser.h"


parser::parser(vector<Token> &&t) {
    this->current = 0;
    this->tokens = t;
}

bool parser::match(TokenType t) {
    if(check(t))
    {
        eat();
        return true;
    }
    else
        return false;

}

bool parser::check(TokenType t) {
    if(is_end())
        return false;
    return peek()->type == t;
}

Token* parser::peek() {
    return &tokens[current];
}

Token* parser::previous() {
    return &tokens[current - 1];
}

bool parser::is_end() {
    return this->tokens[current].type == ENDOFFILE;
}

Token* parser::eat() {
    if(!is_end())
        current++;
    return previous();
}

Token *parser::consume(TokenType t, const string& msg) {
    if(check(t))
        return eat();
    else
        throw report_error(*peek(), msg);
}


Expr* parser::expression() {
    return assignment();
}

Expr* parser::equality() {
    Expr* expr = comparison();

    while(match(BANG_EQUAL) || match(EQUAL_EQUAL))
    {
        Token* op = previous();
        Expr* rhs = comparison();
        expr = new Binary_Expr(op, expr, rhs);
    }
    return expr;
}


Expr* parser::comparison() {
    Expr* expr = this->term();

    while(match(GREATER) || match(GREATER_EQUAL) || match(LESS) || match(LESS_EQUAL))
    {
        Token* op = previous();
        Expr* rhs = term();
        expr = new Binary_Expr(op, expr, rhs);
    }

    return expr;
}

Expr *parser::term() {
    Expr* expr = factor();

    while(match(MINUS) || match(PLUS))
    {
        Token* op = previous();
        Expr* rhs = factor();
        expr = new Binary_Expr(op, expr, rhs);
    }
    return expr;
}

Expr *parser::factor() {
    Expr* expr = unary();

    while(match(SLASH) || match(STAR))
    {
        Token* op = previous();
        Expr* rhs = unary();
        expr = new Binary_Expr(op, expr, rhs);
    }
    return expr;
}

Expr *parser::unary() {
    if(match(BANG) || match(MINUS))
    {
        Token* op = previous();
        Expr* operand = unary();
        return new Unary_Expr(op, operand);
    }
    else
        return primary();
}

Expr *parser::primary() {

    if(match(NIL) || match(TRUE) || match(FALSE) ||
            match(NUMBER) || match(STRING))
        return new Literal_Expr(previous());

    if(match(LEFT_PAREN))
    {
        Expr* expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return new Grouping_Expr(expr);
    }

    if(match(IDENTIFIER))
        return new Variable_Expr(previous());
    
    throw report_error(*peek(), "Expect expression.");
}





void parser::error(const Token& t, const string& msg) {
    if(t.type == ENDOFFILE)
        report(t.line, " at end.", msg);
    else
        report(t.line, " at '" + t.lexeme + "'", msg);
}

void parser::report(int line, const string& where, const string& msg) {
    cout <<  "[line " + to_string(line) + "] Error" + where + ": " + msg;
}


parse_error parser::report_error(const Token &t, const string &msg) {
    error(t, msg);
    return {};
}



void parser::synchronize() {
    eat();

    while(!is_end())
    {
        if (previous()->type == SEMICOLON) return;
        switch (peek()->type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return;
        }

        eat();
    }
}

vector<Stmt *> parser::parse()
{
    vector<Stmt*> res;
    while(!is_end())
        res.push_back(declaration());
    return res;
}

Stmt *parser::statement()
{
    if(match(PRINT))
        return print_stmt();
    else
        return expression_stmt();
}

Stmt *parser::print_stmt()
{
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return new Print(value);
}

Stmt *parser::expression_stmt()
{
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return new Expression(value);
}

Stmt *parser::declaration()
{
    try {
        if(match(VAR))
            return var_declaration();
        else
            return statement();
    } catch (parse_error& e) {
        synchronize();
        return nullptr;
    }
}

Stmt *parser::var_declaration()
{
    Token* name = consume(IDENTIFIER, "Expect variable name.");
    Expr* initializer = nullptr;
    if(match(EQUAL))
        initializer = expression();
    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return new Var(name, initializer);
}

Expr *parser::assignment()
{

}







