#include "token.h"
#include <sstream>
#include <utility>

Token::Token(TokenType type, string lexeme, iteral it, int line):type(type), lexeme(move(lexeme)), it(move(it)), line(line)
{

}

string Token::to_string() const
{
    string s;
    switch (this->type)
    {
        case LEFT_PAREN :
            s = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            s = "RIGHT_PAREN";
            break;
        case LEFT_BRACE:
            s = "LEFT_BRACE";
            break;
        case RIGHT_BRACE:
            s = "RIGHT_BRACE";
            break;
        case COMMA:
            s = "COMMA";
            break;
        case DOT:
            s = "DOT";
            break;
        case MINUS:
            s = "MINUS";
            break;
        case PLUS:
            s = "PLUS";
            break;
        case SEMICOLON:
            s = "SEMICOLON";
            break;
        case SLASH:
            s = "SLASH";
            break;
        case STAR:
            s = "STAR";
            break;
        case BANG:
            s = "BANG";
            break;
        case BANG_EQUAL:
            s = "BANG_EQUAL";
            break;
        case EQUAL:
            s = "EQUAL";
            break;
        case EQUAL_EQUAL:
            s = "EQUAL_EQUAL";
            break;
        case GREATER:
            s = "GREATER";
            break;
        case GREATER_EQUAL:
            s = "GREATER_EQUAL";
            break;
        case LESS:
            s = "LESS";
            break;
        case LESS_EQUAL:
            s = "LESS_EQUAL";
            break;

        case ENDOFFILE:
            s = "ENDOFFILE";
            break;

        case STRING:
            s = "STRING";
            s += "\tlexeme:";
            s += this->lexeme;
            break;
        case NUMBER:
            s = "NUMBER";
            s += "\tliteral:";
            s += std::to_string(this->it.val);
            break;
        case IDENTIFIER:
            s = "IDENTIFIER";
            s += "\tlexeme:";
            s += this->lexeme;
            break;

        case AND:
            s = "AND";
            break;
        case CLASS:
            s = "CLASS_TYPE";
            break;
        case ELSE:
            s = "ELSE";
            break;
        case FALSE:
            s = "FALSE";
            break;
        case FUN:
            s = "FUN";
            break;
        case FOR:
            s = "FOR";
            break;
        case IF:
            s = "IF";
            break;
        case PRINT:
            s = "PRINT";
            break;
        case RETURN:
            s = "RETURN";
            break;
        case SUPER:
            s = "SUPER";
            break;
        case THIS:
            s = "THIS";
            break;
        case TRUE:
            s = "TRUE";
            break;
        case VAR:
            s = "VAR";
            break;
        case WHILE:
            s = "WHILE";
            break;
        default:
            break;
    }
    stringstream ss;
    ss << this->line;
    string tmp;
    ss >> tmp;
    s += "\tline: ";
    s += tmp;
    return s;
}

void Token::update_line(int l)
{
    this->line = l;
}