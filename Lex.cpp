#include"Lex.h"
using enum Lex::Token;
using enum Lex::ErrorToken;

// The supported operators, delimiters, and keywords
unordered_set<char> Lex::operators = { '+', '-', '*', '%', '=', '!', '<', '>', '&', '|' };
unordered_set<char> Lex::delimiters = { ';', ',', '(', ')', '{', '}', '[', ']', ':' };
unordered_set<string> Lex::keywords = { "if", "else", "while", "for", "return", "int",
										"float", "string", "bool", "true", "false" };

// Returns the token of a char. Used by START only
Lex::Token Lex::lookup(char c, ifstream& file) {
	if (file.eof()) return EOFILE;
	else if (isalpha(c) || c == '_') return IDENT;
	else if (isdigit(c)) return INT_LIT;
	else if (c == '.') return FLOAT_LIT;
	else if (c == '"') return STR_LIT;
	else if (c == '/') return SNGL_CMT;
	else if (operators.contains(c)) return OPERATOR;
	else if (delimiters.contains(c)) return DELIM;
	else return ERROR;
}

// Distinguishes between IDENT and KEYWORD using the final lexeme
bool Lex::isKeyword(string lexeme) {
	if (keywords.contains(lexeme)) return true;
	else return false;
}

// Outputs final token and lexeme
void Lex::printToken(int line, int col, Token token, string lexeme) {
	string tkn_str = "";
	float f = 0; // Holds the actual value of a FLOAT_LIT

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

	// Output token
	cout << left;
	if (token == INT_LIT) {
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << setw(12) << lexeme << "[" + lexeme + "]" << endl;
	}
	else if (token == FLOAT_LIT) {
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << setw(12) << lexeme << "[" << f << "]" << endl;
	}
	else if (token == EOFILE) {
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << endl;
	}
	else if (token == MULT_CMT) {
		printMULT_CMT(line, col, false, lexeme);
	}
	else {
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn_str << lexeme << endl;
	}
}

// Outputs Error tokens 
void Lex::printError(int line, int col, ErrorToken errToken, string lexeme) {
	string err_str = ""; // Error message

	// Assign the corresponding string for error type
	switch (errToken) {
		case FLOAT_LIT_ERR: err_str = "Malformed float literal"; break;
		case STR_LIT_ERR: err_str = "Unterminated string literal"; break;
		case MULT_CMT_ERR:
			printMULT_CMT(line, col, true, lexeme);
			return;
			break;
		case CHAR_ERR: err_str = "Invalid character"; break;
	}

	// Output error token
	cout << left;
	cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
		<< setw(12) << "ERROR" << setw(30) << err_str + " " << setw(12) << lexeme << endl;
}

/* Outputs MULT_CMT tokens and MULT_CMT error tokens.
A special function is needed to add indentation after any new lines in the comment */
void Lex::printMULT_CMT(int line, int col, bool isError, string lexeme) {
	string indent = ""; // The string to indent each new line with

	// Set indentation amount
	if (isError) indent = string(54, ' ');
	else indent = string(24, ' ');

	int pos = lexeme.find('\n');
	
	// Add indentation after each new line
	while (pos != string::npos) {
		lexeme.insert(pos + 1, indent);
		pos = lexeme.find('\n', pos + 1);
	}

	cout << left;

	if (isError) { // Error token output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << "ERROR" << setw(30) << "Unterminated comment " << setw(12) << lexeme << endl;
	}
	else { // Regular token output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << "MULT_CMT" << lexeme << endl;
	}
}

// Helper function to add the current char to the lexeme and get the next one
void Lex::addChar(char& c, string& lexeme, ifstream& file, int& col) {
	lexeme.push_back(c);
	file.get(c);
	col++;
}