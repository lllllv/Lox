#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <memory>

#include "token.h"

using namespace std;

class scanner
{
private:
	string& code;
	int start, end, current, line;

	vector<shared_ptr<Token>> tokens;
	map<string, Token> keyword_table;

	bool is_end() const;
	static bool is_digit(char c);
	static bool is_alpha(char c);
	static bool is_aldigit(char c);
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
	vector<shared_ptr<Token>> scan_Tokens();
};
