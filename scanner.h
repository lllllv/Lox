#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

#include "token.h"

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

union iteral
{
	bool boolean;
	double val;
};

class Token
{
public:
	TokenType type;
	string lexeme;
	iteral it;
	int line;

	Token(TokenType type, string lexeme, iteral it, int line);
	string to_string();
	void update_line(int line);
};



class scanner
{
private:
	string& code;
	int start, end, current, line;
	vector<Token> tokens;
	map<string, Token> keyword_table;

	bool is_end();
	bool is_digit(char c);
	bool is_alpha(char c);
	bool is_aldigit(char c);
	void scan_Token();
	char eat();
	char peek();
	char peek_next();
	bool match(char c);
	void handle_string();
	void handle_number();
	void handle_identifier();
public:
	scanner(string& code);
	vector<Token> scan_Tokens();
};
