#include"Lex.h"
using enum Lex::Token;
using enum Lex::ErrorToken;

unordered_set<char> Lex::operators = { '+', '-', '*', '%', '=', '!', '<', '>', '&', '|' };
unordered_set<char> Lex::delimiters = { ';', ',', '(', ')', '{', '}', '[', ']', ':' };
unordered_set<string> Lex::keywords = { "if", "else", "while", "for", "return", "int",
										"float", "string", "bool", "true", "false" };

Lex::Token Lex::lookup(char c, ifstream& file) {
	if (file.eof()) return EOFILE;
	else if (isalpha(c) || c == '_') return IDENT;
	else if (isdigit(c)) return INT_LIT;
	else if (c == '.') return FLOAT_LIT;
	else if (c == '"') return STR_LIT;
	else if (c == '/') {
		Token tkn;
		file.get(c); // A single '/' is ambiguous by itself, so get the next char

		// Check if single line comment, multi line comment, or operator
		if (c == '/') tkn = SNGL_CMT;
		else if (c == '*') tkn = MULT_CMT;
		else tkn = OPERATOR;

		file.seekg(-1, ios::cur); // Go back one char in the file
		return tkn;
	}
	else if (operators.contains(c)) return OPERATOR;
	else if (delimiters.contains(c)) return DELIM;
	else return ERROR;
}

bool Lex::isKeyword(string lexeme) {
	if (keywords.contains(lexeme)) return true;
	else return false;
}

void Lex::printToken(int line, int col, Token token, string lexeme) {
	string tkn_str = "";
	float f = 0;

	// Assign the corresponding string for each token
	switch (token) {
	case IDENT: tkn_str = "IDENT"; break;
	case KEYWORD: tkn_str = "KEYWORD"; break;
	case INT_LIT: tkn_str = "INT_LIT"; break;
	case FLOAT_LIT:
		tkn_str = "FLOAT_LIT";
		f = stof(lexeme); // Convert to float to ensure proper formating (i.e. "2." -> 2.0)
		break;

	case STR_LIT: tkn_str = "STR_LIT"; break;
	case OPERATOR: tkn_str = "OPERATOR"; break;
	case DELIM: tkn_str = "DELIM"; break;
	case SNGL_CMT: tkn_str = "SNGL_CMT"; break;
	case MULT_CMT: tkn_str = "MULT_CMT"; break;
	case EOFILE: tkn_str = "EOF"; break;
	case ERROR: tkn_str = "ERROR"; break;
	}

	// Output
	cout << left;
	if (token == INT_LIT) { // Int output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << setw(12) << lexeme << "[" + lexeme + "]" << endl;
	}
	else if (token == FLOAT_LIT) { // Float output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << setw(12) << lexeme << "[" << f << "]" << endl;
	}
	else if (token == EOFILE) {
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << endl;
	}
	else { // Regular output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << lexeme << endl;
	}
}

void Lex::printError(int line, int col, ErrorToken errToken, string lexeme) {
	string err_str = "";

	switch (errToken) {
		case FLOAT_LIT_ERR: err_str = "Malformed float literal"; break;
		case STR_LIT_ERR: err_str = "Unterminated string literal"; break;
		case MULT_CMT_ERR: err_str = "Unterminated comment"; break;
		case CHAR_ERR: err_str = "Invalid character"; break;
	}

	cout << left;
	cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
		<< setw(12) << "ERROR" << setw(30) << err_str + " " << setw(12) << lexeme << endl;
}

void Lex::addChar(char& c, string& lexeme, ifstream& file, int& col) {
	lexeme.push_back(c);
	file.get(c);
	col++;
}