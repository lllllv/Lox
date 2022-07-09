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
			this->tokens.emplace_back(Token(LEFT_PAREN, "(", literal{}, line));
			break;
		}
		case ')':
		{
			this->tokens.emplace_back(Token(RIGHT_PAREN, ")", literal{}, line));
			break;
		}
		case '{':
		{
			this->tokens.emplace_back(Token(LEFT_BRACE, "{", literal{}, line));
			break;
		}
		case '}':
		{
			this->tokens.emplace_back(Token(RIGHT_BRACE, "}", literal{}, line));
			break;
		}
		case ',':
		{
			this->tokens.emplace_back(Token(COMMA, ",", literal{}, line));
			break;
		}
		case '.':
		{
			this->tokens.emplace_back(Token(DOT, ".", literal{}, line));
			break;
		}
		case '-':
		{
			this->tokens.emplace_back(Token(MINUS, "-", literal{}, line));
			break;
		}
		case '+':
		{
			this->tokens.emplace_back(Token(PLUS, "+", literal{}, line));
			break;
		}
		case ';':
		{
			this->tokens.emplace_back(Token(SEMICOLON, ";", literal{}, line));
			break;
		}
		case '*':
		{
			this->tokens.emplace_back(Token(STAR, "*", literal{}, line));
			break;
		}

		case '!':
		{
            if(match('='))
            {
                TokenType t = BANG_EQUAL;
                this->tokens.emplace_back(Token(t, "!=", literal{}, line));
            }
            else
            {
                TokenType t = BANG;
                this->tokens.emplace_back(Token(t, "!", literal{}, line));
            }
			break;
		}
		case '=':
		{
            if(match('='))
            {
                TokenType t = EQUAL_EQUAL;
                this->tokens.emplace_back(Token(t, "==", literal{}, line));
            }
            else
            {
                TokenType t = EQUAL;
                this->tokens.emplace_back(Token(t, "=", literal{}, line));
            }
			break;
		}
		case '<':
		{
            if(match('='))
            {
                TokenType t = LESS_EQUAL;
                this->tokens.emplace_back(Token(t, "<=", literal{}, line));
            }
            else
            {
                TokenType t = LESS;
                this->tokens.emplace_back(Token(t, "<", literal{}, line));
            }
			break;
		}
		case '>':
		{
            if(match('='))
            {
                TokenType t = GREATER_EQUAL;
                this->tokens.emplace_back(Token(t, ">=", literal{}, line));
            }
            else
            {
                TokenType t = GREATER;
                this->tokens.emplace_back(Token(t, ">", literal{}, line));
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
				this->tokens.emplace_back(Token(SLASH, "/", literal{}, line));
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

	literal it;
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
	literal it;
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
		this->tokens.emplace_back(Token(IDENTIFIER, tmp, literal{}, line));
	}
}

scanner::scanner(string& code):code(code), start(0), current(0), line(1)
{
	this->end = code.length();
	
	this->keyword_table.insert(make_pair("and", Token(AND, "and", literal{}, 0)));
	this->keyword_table.insert(make_pair("class", Token(CLASS, "class", literal{}, 0)));
	this->keyword_table.insert(make_pair("else", Token(ELSE, "else", literal{}, 0)));

	literal it{};
	it.boolean = false;
	this->keyword_table.insert(make_pair("false", Token(FALSE, "false", it, 0)));
	
	this->keyword_table.insert(make_pair("fun", Token(FUN, "fun", literal{}, 0)));
	this->keyword_table.insert(make_pair("for", Token(FOR, "for", literal{}, 0)));
	this->keyword_table.insert(make_pair("if", Token(IF, "if", literal{}, 0)));
	this->keyword_table.insert(make_pair("nil", Token(NIL, "nil", literal{}, 0)));
	this->keyword_table.insert(make_pair("or", Token(OR, "or", literal{}, 0)));
	this->keyword_table.insert(make_pair("print", Token(PRINT, "_print_lox_object", literal{}, 0)));
	this->keyword_table.insert(make_pair("return", Token(RETURN, "return", literal{}, 0)));
	this->keyword_table.insert(make_pair("super", Token(SUPER, "super", literal{}, 0)));
	this->keyword_table.insert(make_pair("this", Token(THIS, "this", literal{}, 0)));

	it.boolean = true;
	this->keyword_table.insert(make_pair("true", Token(TRUE, "true", it, 0)));

	this->keyword_table.insert(make_pair("var", Token(VAR, "var", literal{}, 0)));
	this->keyword_table.insert(make_pair("while", Token(WHILE, "while", literal{}, 0)));

}

vector<Token> scanner::scan_Tokens()
{
	while (!is_end())
	{
		this->start = this->current;
		this->scan_Token();
	}

	this->tokens.emplace_back(Token(ENDOFFILE, "", literal{}, this->line));
	
	return this->tokens;
}



