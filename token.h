#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <string>

using namespace std;

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    ENDOFFILE
};

struct iteral
{
    bool boolean;
    double val;
    string str;
};

class Token
{
public:
    TokenType type;
    string lexeme;
    iteral it;
    int line;

    Token(TokenType type, string lexeme, iteral it, int line);
    Token(const Token& t) = default;
    string to_string() const;
    void update_line(int l);
};

#endif //LOX_TOKEN_H
