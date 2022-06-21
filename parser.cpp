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

    return call();
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
    if(match(LEFT_BRACE))
        return new Block_Stmt(block());
    if(match(IF))
        return if_stmt();
    if(match(WHILE))
        return while_stmt();
    if(match(FOR))
        return for_stmt();
    if(match(RETURN))
        return return_stmt();
    return expression_stmt();
}

Stmt *parser::print_stmt()
{
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return new Print_Stmt(value);
}

Stmt *parser::expression_stmt()
{
    Expr* value = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return new Expression_Stmt(value);
}

Stmt *parser::declaration()
{
    try {
        if(match(VAR))
            return var_declaration();
        if(match(FUN))
            return function("function");
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
    return new Var_Stmt(name, initializer);
}

Expr *parser::assignment()
{
    Expr* expr = logical_or();
    if(match(EQUAL))
    {
        Token* equals = previous();
        Expr* value = assignment();

        if(auto*  var_expr = dynamic_cast<Variable_Expr*>(expr))
        {
            auto* name = new Token(*(var_expr->name));
            return new Assignment_Expr(name, value);
        }

        error(*equals, "Invalid assignment target.");
    }

    return expr;
}

vector<Stmt *> *parser::block()
{
    auto res = new vector<Stmt*>();
    while(!check(RIGHT_BRACE) && !is_end())
        res->push_back(declaration());

    consume(RIGHT_BRACE, "Expect '}' after block.");
    return res;
}

Stmt *parser::if_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    Expr* condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after if condition.");

    Stmt* then_branch = statement();
    Stmt* else_branch = nullptr;

    if(match(ELSE))
        else_branch = statement();
    return new If_Stmt(condition, then_branch, else_branch);
}

Expr *parser::logical_or()
{
    Expr* expr = logical_and();
    while(match(OR))
    {
        Token* op = previous();
        Expr* right = logical_and();
        expr = new Logical_Expr(expr, op, right);
    }

    return expr;
}

Expr *parser::logical_and()
{
    Expr* expr = equality();

    while(match(AND))
    {
        Token* op = previous();
        Expr* right = equality();
        expr = new Logical_Expr(expr, op, right);
    }

    return expr;
}

Stmt *parser::while_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    Expr* condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition.");
    Stmt* body = statement();
    return new While_Stmt(condition, body);
}

Stmt *parser::for_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'for'.");

    Stmt* initializer = nullptr;
    if(match(SEMICOLON))
        initializer = nullptr;
    else if(match(VAR))
        initializer = var_declaration();
    else
        initializer = expression_stmt();

    Expr* condition = nullptr;
    if(!check(SEMICOLON))
        condition = expression();
    consume(SEMICOLON, "Expect ';' after loop condition.");

    Expr* increment = nullptr;
    if(!check(RIGHT_PAREN))
        increment = expression();
    consume(RIGHT_PAREN, "Expect ')' after for clauses.");

    Stmt* body = statement();

    if(increment != nullptr)
    {
        auto* tmp = new vector<Stmt*>();
        tmp->push_back(body);
        tmp->push_back(new Expression_Stmt(increment));
        body = new Block_Stmt(tmp);
    }
    if(condition == nullptr)
        condition = new Literal_Expr(new Token(TRUE, "true", {}, 0));
    body = new While_Stmt(condition, body);
    if(initializer != nullptr)
    {
        auto* tmp = new vector<Stmt*>();
        tmp->push_back(initializer);
        tmp->push_back(body);
        body = new Block_Stmt(tmp);
    }

    return body;
}

Expr *parser::call()
{
    Expr* expr = primary();

    while(true)
    {
        if(match(LEFT_PAREN))
            expr = finish_call(expr);
        else
            break;
    }

    return expr;
}

Expr *parser::finish_call(Expr* callee)
{
    auto* arguments = new vector<Expr*>();
    if(!check(RIGHT_PAREN))
    {
        do
        {
            if(arguments->size() >= 255)
                error(*peek(), "Can't have more than 255 arguments.");;
            arguments->push_back(expression());
        } while(match(COMMA));
    }
    Token* paren = consume(RIGHT_PAREN,"Expect ')' after arguments.");
    return new Call_Expr(callee, paren, arguments);
}

Function_Stmt *parser::function(const string& kind)
{
    Token* name = consume(IDENTIFIER, "Expect " + kind + " name.");
    consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
    auto* parameters = new vector<Token*>();
    if(!check(RIGHT_PAREN))
    {
        do {
            if (parameters->size() >= 255)
                error(*peek(), "Can't have more than 255 parameters.");
            parameters->push_back(consume(IDENTIFIER, "Expect parameter name."));
        } while(match(COMMA));
    }
    consume(RIGHT_PAREN, "Expect ')' after parameters.");

    consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");

    auto body = block();
    return new Function_Stmt(name, parameters, body);
}

Stmt *parser::return_stmt()
{
    Token* keyword = previous();
    Expr* value = nullptr;
    if(!check(SEMICOLON))
        value = expression();
    consume(SEMICOLON, "Expect ';' after return value.");
    return new Return_Stmt(keyword, value);
}







