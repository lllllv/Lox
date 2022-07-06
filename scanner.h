#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "token.h"

using namespace std;

class scanner
{
private:
	string& code;
	int start, end, current, line;
	// unique_ptr ?
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
	explicit scanner(string& code);
	// unique_ptr?
	vector<Token> scan_Tokens();
};
