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
			this->tokens.emplace_back(Token(LEFT_PAREN, "", iteral{},  line));
			break;
		}
		case ')':
		{
			this->tokens.emplace_back(Token(RIGHT_PAREN, "", iteral{}, line));
			break;
		}
		case '{':
		{
			this->tokens.emplace_back(Token(LEFT_BRACE, "", iteral{}, line));
			break;
		}
		case '}':
		{
			this->tokens.emplace_back(Token(RIGHT_BRACE, "", iteral{}, line));
			break;
		}
		case ',':
		{
			this->tokens.emplace_back(Token(COMMA, "", iteral{}, line));
			break;
		}
		case '.':
		{
			this->tokens.emplace_back(Token(DOT, "", iteral{}, line));
			break;
		}
		case '-':
		{
			this->tokens.emplace_back(Token(MINUS, "", iteral{}, line));
			break;
		}
		case '+':
		{
			this->tokens.emplace_back(Token(PLUS, "", iteral{}, line));
			break;
		}
		case ';':
		{
			this->tokens.emplace_back(Token(SEMICOLON, "", iteral{}, line));
			break;
		}
		case '*':
		{
			this->tokens.emplace_back(Token(STAR, "", iteral{}, line));
			break;
		}

		case '!':
		{
			TokenType t = match('=') ? BANG_EQUAL : BANG;
			this->tokens.emplace_back(Token(t, "", iteral{}, line));
			break;
		}
		case '=':
		{
			TokenType t = match('=') ? EQUAL_EQUAL : EQUAL;
			this->tokens.emplace_back(Token(t, "", iteral{}, line));
			break;
		}
		case '<':
		{
			TokenType t = match('=') ? LESS_EQUAL : LESS;
			this->tokens.emplace_back(Token(t, "", iteral{}, line));
			break;
		}
		case '>':
		{
			TokenType t = match('=') ? GREATER_EQUAL : GREATER;
			this->tokens.emplace_back(Token(t, "", iteral{}, line));
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
				this->tokens.emplace_back(Token(SLASH, "", iteral{}, line));
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

	

	this->tokens.emplace_back(Token(STRING,
		this->code.substr(this->start + 1, this->current - this->start - 1),
		iteral{}, this->line));

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
	
	this->keyword_table.insert(make_pair("and", Token(AND, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("class", Token(CLASS, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("else", Token(ELSE, "", iteral{}, 0)));

	iteral it;
	it.boolean = false;
	this->keyword_table.insert(make_pair("false", Token(FALSE, "", it, 0)));
	
	this->keyword_table.insert(make_pair("fun", Token(FUN, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("for", Token(FOR, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("if", Token(IF, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("nil", Token(NIL, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("or", Token(OR, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("print", Token(PRINT, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("return", Token(RETURN, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("super", Token(SUPER, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("this", Token(THIS, "", iteral{}, 0)));

	it.boolean = true;
	this->keyword_table.insert(make_pair("true", Token(TRUE, "", it, 0)));

	this->keyword_table.insert(make_pair("var", Token(VAR, "", iteral{}, 0)));
	this->keyword_table.insert(make_pair("while", Token(WHILE, "", iteral{}, 0)));

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

Token::Token(TokenType type, string lexeme,iteral it, int line):type(type), lexeme(lexeme), it(it), line(line)
{

}

string Token::to_string()
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
		s += "\titeral:";
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
		s = "CLASS";
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
	}
	stringstream ss;
	ss << this->line;
	string line;
	ss >> line;
	s += "\tline: ";
	s += line;
	return s;
}

void Token::update_line(int line)
{
	this->line = line;
}


