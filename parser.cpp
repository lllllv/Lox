#include "parser.h"


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

shared_ptr<Token> parser::peek() {
    return tokens[current];
}

shared_ptr<Token> parser::previous() {
    return tokens[current - 1];
}

bool parser::is_end() {
    return this->tokens[current]->type == ENDOFFILE;
}

shared_ptr<Token> parser::eat() {
    if(!is_end())
        current++;
    return previous();
}

shared_ptr<Token> parser::consume(TokenType t, const string& msg) {
    if(check(t))
        return eat();
    else
        throw report_error(*peek(), msg);
}


shared_ptr<Expr> parser::expression() {
    return assignment();
}

shared_ptr<Expr> parser::equality() {
    auto expr = comparison();

    while(match(BANG_EQUAL) || match(EQUAL_EQUAL))
    {
        auto op = previous();
        auto rhs = comparison();
        expr = make_shared<Binary_Expr>(op, expr, rhs);
    }
    return expr;
}


shared_ptr<Expr> parser::comparison() {
    auto expr = this->term();

    while(match(GREATER) || match(GREATER_EQUAL) || match(LESS) || match(LESS_EQUAL))
    {
        auto op = previous();
        auto rhs = term();
        expr = make_shared<Binary_Expr>(op, expr, rhs);
    }

    return expr;
}

shared_ptr<Expr> parser::term() {
    shared_ptr<Expr> expr = factor();

    while(match(MINUS) || match(PLUS))
    {
        auto op = previous();
        auto rhs = factor();
        expr = make_shared<Binary_Expr>(op, expr, rhs);
    }
    return expr;
}

shared_ptr<Expr> parser::factor() {
    shared_ptr<Expr> expr = unary();

    while(match(SLASH) || match(STAR))
    {
        auto op = previous();
        auto rhs = unary();
        expr = make_shared<Binary_Expr>(op, expr, rhs);
    }
    return expr;
}

shared_ptr<Expr> parser::unary() {
    if(match(BANG) || match(MINUS))
    {
        auto op = previous();
        auto operand = unary();
        return make_shared<Unary_Expr>(op, operand);
    }

    return call();
}

shared_ptr<Expr> parser::primary() {

    if(match(NIL) || match(TRUE) || match(FALSE) ||
            match(NUMBER) || match(STRING))
        return make_shared<Literal_Expr>(previous());

    if(match(LEFT_PAREN))
    {
        auto expr = expression();
        consume(RIGHT_PAREN, "Expect ')' after expression.");
        return make_shared<Grouping_Expr>(expr);
    }

    if(match(IDENTIFIER))
        return make_shared<Variable_Expr>(previous());

    if(match(THIS))
        return make_shared<This_Expr>(previous());

    if(match(SUPER))
    {
        auto keyword = previous();
        consume(DOT, "Expect '.' after 'super'.");
        auto method = consume(IDENTIFIER,"Expect superclass method name.");
        return make_shared<Super_Expr>(keyword, method);
    }

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
            default:
                break;
        }

        eat();
    }
}

vector<shared_ptr<Stmt>> parser::parse_stmt()
{
    vector<shared_ptr<Stmt>> res;
    while(!is_end())
        res.push_back(declaration());
    return res;
}

shared_ptr<Stmt> parser::statement()
{
    if(match(PRINT))
        return print_stmt();
    if(match(LEFT_BRACE))
        return make_shared<Block_Stmt>(block());
    if(match(IF))
        return if_stmt();
    if(match(WHILE))
        return while_stmt();
    if(match(FOR))
        return for_stmt();
    if(match(RETURN))
        return return_stmt();
    if(match(CLASS))
        return class_declaration();
    return expression_stmt();
}

shared_ptr<Stmt> parser::print_stmt()
{
    auto value = expression();
    consume(SEMICOLON, "Expect ';' after value.");
    return make_shared<Print_Stmt>(value);
}

shared_ptr<Stmt> parser::expression_stmt()
{
    auto value = expression();
    consume(SEMICOLON, "Expect ';' after expression.");
    return make_shared<Expression_Stmt>(value);
}

shared_ptr<Stmt> parser::declaration()
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

shared_ptr<Stmt> parser::var_declaration()
{
    auto name = consume(IDENTIFIER, "Expect variable name.");
    shared_ptr<Expr> initializer = nullptr;
    if(match(EQUAL))
        initializer = expression();
    consume(SEMICOLON, "Expect ';' after variable declaration.");
    return make_shared<Var_Stmt>(name, initializer);
}

shared_ptr<Expr> parser::assignment()
{
    shared_ptr<Expr> expr = logical_or();
    if(match(EQUAL))
    {
        auto equals = previous();
        auto value = assignment();

        try {
            auto& var_expr = dynamic_cast<Variable_Expr&>(*expr);
            auto name = make_shared<Token>(*var_expr.name);
            return make_shared<Assignment_Expr>(name, value);

        } catch(bad_cast&) {
            try {
                auto& get_expr = dynamic_cast<Get_Expr&>(*expr);
                return make_shared<Set_Expr>(get_expr.object, get_expr.name,
                                             value);
            } catch(bad_cast&) {
                error(*equals, "Invalid assignment target.");
            }

        }

        /*if(auto var_expr = dynamic_cast<Variable_Expr&>(*expr))
        {
            auto* name = new Token(*(var_expr->name));
            return new Assignment_Expr(name, value);
        }
        else if(auto* get_expr = dynamic_cast<Get_Expr*>(expr))
        {
            return new Set_Expr(get_expr->object, get_expr->name, value);
        }

        error(*equals, "Invalid assignment target.");*/
    }

    return expr;
}

shared_ptr<vector<shared_ptr<Stmt>>> parser::block()
{
    auto res = make_shared<vector<shared_ptr<Stmt>>>();
    while(!check(RIGHT_BRACE) && !is_end())
        res->push_back(declaration());

    consume(RIGHT_BRACE, "Expect '}' after block.");
    return res;
}

shared_ptr<Stmt> parser::if_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    auto condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after if condition.");

    auto then_branch = statement();
    shared_ptr<Stmt> else_branch = nullptr;

    if(match(ELSE))
        else_branch = statement();
    return make_shared<If_Stmt>(condition, then_branch, else_branch);
}

shared_ptr<Expr> parser::logical_or()
{
    auto expr = logical_and();
    while(match(OR))
    {
        auto op = previous();
        auto right = logical_and();
        expr = make_shared<Logical_Expr>(expr, op, right);
    }

    return expr;
}

shared_ptr<Expr> parser::logical_and()
{
    auto expr = equality();

    while(match(AND))
    {
        auto op = previous();
        auto right = equality();
        expr = make_shared<Logical_Expr>(expr, op, right);
    }

    return expr;
}

shared_ptr<Stmt> parser::while_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    auto condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition.");
    auto body = statement();
    return make_shared<While_Stmt>(condition, body);
}

shared_ptr<Stmt> parser::for_stmt()
{
    consume(LEFT_PAREN, "Expect '(' after 'for'.");

    shared_ptr<Stmt> initializer = nullptr;
    if(match(SEMICOLON))
        initializer = nullptr;
    else if(match(VAR))
        initializer = var_declaration();
    else
        initializer = expression_stmt();

    shared_ptr<Expr> condition = nullptr;
    if(!check(SEMICOLON))
        condition = expression();
    consume(SEMICOLON, "Expect ';' after loop condition.");

    shared_ptr<Expr> increment = nullptr;
    if(!check(RIGHT_PAREN))
        increment = expression();
    consume(RIGHT_PAREN, "Expect ')' after for clauses.");

    auto body = statement();

    if(increment != nullptr)
    {
        auto tmp = make_shared<vector<shared_ptr<Stmt>>>();
        tmp->push_back(body);
        tmp->push_back(make_shared<Expression_Stmt>(increment));
        body = make_shared<Block_Stmt>(tmp);
    }
    if(condition == nullptr)
        condition = make_shared<Literal_Expr>(make_shared<Token>(TRUE, "true", iteral{}, 0));

    body = make_shared<While_Stmt>(condition, body);
    if(initializer != nullptr)
    {
        auto tmp = make_shared<vector<shared_ptr<Stmt>>>();
        tmp->push_back(initializer);
        tmp->push_back(body);
        body = make_shared<Block_Stmt>(tmp);
    }

    return body;
}

shared_ptr<Expr> parser::call()
{
    auto expr = primary();

    while(true)
    {
        if(match(LEFT_PAREN))
            expr = finish_call(expr);
        else if(match(DOT))
        {
            auto name = consume(IDENTIFIER,"Expect property name after '.'.");
            expr = make_shared<Get_Expr>(expr, name);
        }
        else
            break;
    }

    return expr;
}

shared_ptr<Expr> parser::finish_call(shared_ptr<Expr> callee)
{
    auto arguments = make_shared<vector<shared_ptr<Expr>>>();
    if(!check(RIGHT_PAREN))
    {
        do
        {
            if(arguments->size() >= 255)
                error(*peek(), "Can't have more than 255 arguments.");;
            arguments->push_back(expression());
        } while(match(COMMA));
    }
    auto paren = consume(RIGHT_PAREN,"Expect ')' after arguments.");
    return make_shared<Call_Expr>(callee, paren, arguments);
}

shared_ptr<Function_Stmt> parser::function(const string& kind)
{
    auto name = consume(IDENTIFIER, "Expect " + kind + " name.");
    consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
    auto parameters = make_shared<vector<shared_ptr<Token>>>();
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
    return make_shared<Function_Stmt>(name, parameters, body);
}

shared_ptr<Stmt> parser::return_stmt()
{
    auto keyword = previous();
    shared_ptr<Expr> value = nullptr;
    if(!check(SEMICOLON))
        value = expression();
    consume(SEMICOLON, "Expect ';' after return value.");
    return make_shared<Return_Stmt>(keyword, value);
}

shared_ptr<Stmt> parser::class_declaration()
{
    auto name = consume(IDENTIFIER, "Expect class name.");
    shared_ptr<Variable_Expr> super_class = nullptr;

    if(match(LESS))
    {
        consume(IDENTIFIER, "Expect superclass name.");
        super_class = make_shared<Variable_Expr>(previous());
    }

    consume(LEFT_BRACE, "Expect '{' before class body.");
    auto methods = make_shared<vector<shared_ptr<Function_Stmt>>>();
    while (!check(RIGHT_BRACE) && !is_end())
        methods->push_back(function("method"));

    consume(RIGHT_BRACE, "Expect '}' after class body.");
    return make_shared<Class_Stmt>(name, super_class, methods);
}


parser::parser(vector<shared_ptr<Token>> tokens)
{
    this->current = 0;
    this->tokens = move(tokens);
}

shared_ptr<Expr> parser::parse_expr()
{
    return expression();
}







