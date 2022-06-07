#include "scanner.h"

bool scanner::is_end()
{
	return this->current >= this->end;
}

bool scanner::is_digit(char c)
{
	return '0' <= c && c <= '9';
}

bool scanner::is_alpha(char c)
{
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}

bool scanner::is_aldigit(char c)
{
	return is_alpha(c) || is_digit(c);
}

void scanner::scan_Token()
{
	char c = this->eat();
	
	switch (c)
	{
		case '(':
		{
			this->tokens.emplace_back(Token(LEFT_PAREN, "(", iteral{},  line));
			break;
		}
		case ')':
		{
			this->tokens.emplace_back(Token(RIGHT_PAREN, ")", iteral{}, line));
			break;
		}
		case '{':
		{
			this->tokens.emplace_back(Token(LEFT_BRACE, "{", iteral{}, line));
			break;
		}
		case '}':
		{
			this->tokens.emplace_back(Token(RIGHT_BRACE, "}", iteral{}, line));
			break;
		}
		case ',':
		{
			this->tokens.emplace_back(Token(COMMA, ",", iteral{}, line));
			break;
		}
		case '.':
		{
			this->tokens.emplace_back(Token(DOT, ".", iteral{}, line));
			break;
		}
		case '-':
		{
			this->tokens.emplace_back(Token(MINUS, "-", iteral{}, line));
			break;
		}
		case '+':
		{
			this->tokens.emplace_back(Token(PLUS, "+", iteral{}, line));
			break;
		}
		case ';':
		{
			this->tokens.emplace_back(Token(SEMICOLON, ";", iteral{}, line));
			break;
		}
		case '*':
		{
			this->tokens.emplace_back(Token(STAR, "*", iteral{}, line));
			break;
		}

		case '!':
		{
            if(match('='))
            {
                TokenType t = BANG_EQUAL;
                this->tokens.emplace_back(Token(t, "!=", iteral{}, line));
            }
            else
            {
                TokenType t = BANG;
                this->tokens.emplace_back(Token(t, "!", iteral{}, line));
            }
			break;
		}
		case '=':
		{
            if(match('='))
            {
                TokenType t = EQUAL_EQUAL;
                this->tokens.emplace_back(Token(t, "==", iteral{}, line));
            }
            else
            {
                TokenType t = EQUAL;
                this->tokens.emplace_back(Token(t, "=", iteral{}, line));
            }
			break;
		}
		case '<':
		{
            if(match('='))
            {
                TokenType t = LESS_EQUAL;
                this->tokens.emplace_back(Token(t, "<=", iteral{}, line));
            }
            else
            {
                TokenType t = LESS;
                this->tokens.emplace_back(Token(t, "<", iteral{}, line));
            }
			break;
		}
		case '>':
		{
            if(match('='))
            {
                TokenType t = GREATER_EQUAL;
                this->tokens.emplace_back(Token(t, ">=", iteral{}, line));
            }
            else
            {
                TokenType t = GREATER;
                this->tokens.emplace_back(Token(t, ">", iteral{}, line));
            }
			break;
		}

		case '/':
		{
			if (match('/'))
			{
				while (this->peek() != '\n' && !this->is_end())
					this->current++;
			}
			else
			{
				this->tokens.emplace_back(Token(SLASH, "/", iteral{}, line));
			}

			break;
		}

		case ' ':
		case '\r':
		case '\t':
			break;

		case '\n':
		{
			this->line++;
			break;
		}

		case '"':
		{
			this->handle_string();
			break;
		}
			

		default:
		{
			
			if (is_digit(c))
			{
				handle_number();
				break;
			}
			else if (is_alpha(c))
			{
				handle_identifier();
				break;
			}
			cout << code[current-1] << ":" << c << endl;
			cout << "error!" << endl;
			break;
		}
	}
}

char scanner::eat()
{
	
	return this->code[this->current++];
}

char scanner::peek()
{
	if (this->current > this->code.length())
		return '\0';

	return this->code[this->current];
}

char scanner::peek_next()
{
	if (current + 1 >= this->code.length())
		return  '\0';
	return this->code[current + 1];
}

bool scanner::match(char c)
{
	if (is_end())
		return false;
	if (this->code[this->current] != c)
		return false;

	this->current++;
	return true;
}

void scanner::handle_string()
{
	while (this->peek() != '"' && !this->is_end())
	{
		if (this->peek() == '\n')
			this->line++;
		this->current++;
	}

	if (this->is_end())
	{
		cout << "Unterminated string.";
		return;
	}

	iteral it;
    it.str = this->code.substr(this->start + 1, this->current - this->start - 1);

	this->tokens.emplace_back(Token(STRING,
		"\"" + it.str + "\"",
		it, this->line));

	this->eat();
}

void scanner::handle_number()
{
	while (is_digit(peek()) && !is_end())
	{
		this->current++;
	}

	if (peek() == '.' && is_digit(peek_next()))
	{
		this->eat();
		while (is_digit(peek()) && !is_end())
			this->current++;
	}

	string num_s = this->code.substr(this->start, this->current - this->start);
	double val = stod(num_s);
	iteral it;
	it.val = val;
	
	this->tokens.emplace_back(Token(NUMBER, num_s, it, line));
}

void scanner::handle_identifier()
{
	while (!is_end() && is_aldigit(peek()))
	{
		this->current++;
	}

	string tmp = this->code.substr(this->start, this->current - this->start);
	
	auto iter = this->keyword_table.find(tmp);
	if (iter != this->keyword_table.end())
	{
		iter->second.update_line(this->line);
		
		this->tokens.emplace_back(iter->second);
	}
	else
	{
		this->tokens.emplace_back(Token(IDENTIFIER, tmp, iteral{}, line));
	}
}

scanner::scanner(string& code):code(code), start(0), current(0), line(1)
{
	this->end = code.length();
	
	this->keyword_table.insert(make_pair("and", Token(AND, "and", iteral{}, 0)));
	this->keyword_table.insert(make_pair("class", Token(CLASS, "class", iteral{}, 0)));
	this->keyword_table.insert(make_pair("else", Token(ELSE, "else", iteral{}, 0)));

	iteral it{};
	it.boolean = false;
	this->keyword_table.insert(make_pair("false", Token(FALSE, "false", it, 0)));
	
	this->keyword_table.insert(make_pair("fun", Token(FUN, "fun", iteral{}, 0)));
	this->keyword_table.insert(make_pair("for", Token(FOR, "for", iteral{}, 0)));
	this->keyword_table.insert(make_pair("if", Token(IF, "if", iteral{}, 0)));
	this->keyword_table.insert(make_pair("nil", Token(NIL, "nil", iteral{}, 0)));
	this->keyword_table.insert(make_pair("or", Token(OR, "or", iteral{}, 0)));
	this->keyword_table.insert(make_pair("print", Token(PRINT, "print", iteral{}, 0)));
	this->keyword_table.insert(make_pair("return", Token(RETURN, "return", iteral{}, 0)));
	this->keyword_table.insert(make_pair("super", Token(SUPER, "super", iteral{}, 0)));
	this->keyword_table.insert(make_pair("this", Token(THIS, "this", iteral{}, 0)));

	it.boolean = true;
	this->keyword_table.insert(make_pair("true", Token(TRUE, "true", it, 0)));

	this->keyword_table.insert(make_pair("var", Token(VAR, "var", iteral{}, 0)));
	this->keyword_table.insert(make_pair("while", Token(WHILE, "while", iteral{}, 0)));

}

vector<Token> scanner::scan_Tokens()
{
	while (!is_end())
	{
		this->start = this->current;
		this->scan_Token();
	}

	this->tokens.emplace_back(Token(ENDOFFILE, "", iteral{}, this->line));
	
	return this->tokens;
}



