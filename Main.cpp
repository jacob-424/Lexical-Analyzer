#include<iostream>
#include<fstream>
#include"Lex.h"
using namespace std;
using enum Lex::Token;
using enum Lex::ErrorToken;

int main() {
	Lex::Token token = START;
	Lex::ErrorToken errToken = CHAR_ERR;
	int line = 1;
	int col = 1;
	int tkn_line = 0;
	int tkn_col = 0;
	string lexeme = "";
	ifstream file("input.txt");
	bool escaped = false;

	// Check if the input file was found
	if (!file) {
		cout << "Could not find the input file \"input.txt\"" << endl;
	}

	char c = file.get();

	while (true) {
		switch (token) {
			/* START is not a real token. It handles whitespace, new lines, 
			EOF, and creates new tokens */
			case START:
				// Handle whitespace by getting the next non-whitespace character
				while (c == ' ' && !file.eof()) {
					file.get(c);
					col++;
				}

				// Handle new line
				if (c == '\n' && !file.eof()) { // New line found
					line++;
					col = 1;
				}
				else { // Create new token
					token = Lex::lookup(c, file);
					if (token == ERROR) errToken = CHAR_ERR;

					lexeme.clear();
					lexeme.push_back(c);

					// Save the line and column of the token
					tkn_line = line;
					tkn_col = col;

					col++;
				}

				file.get(c);
				break;

			case IDENT:
				// Add any more letters, digits, or underscores
				if ((isalnum(static_cast<unsigned char>(c)) || c == '_') && !file.eof()) {
					Lex::addChar(c, lexeme, file, col);
				}
				else { // End of token
					if (Lex::isKeyword(lexeme)) token = KEYWORD; // Check if IDENT or KEYWORD
					Lex::printToken(tkn_line, tkn_col, token, lexeme);
					token = START;
				}
				break;

			case INT_LIT:
				// Add any more digits
				if (isdigit(c) && !file.eof()) {
					Lex::addChar(c, lexeme, file, col);
				}
				else if (c == '.') { // Switch to FLOAT_LIT if we find a period
					Lex::addChar(c, lexeme, file, col);
					token = FLOAT_LIT;
				}
				else { // End of token
					Lex::printToken(tkn_line, tkn_col, token, lexeme);
					token = START;
				}
				break;

			case FLOAT_LIT:
				// Add any more digits
				if (isdigit(c) && !file.eof()) {
					Lex::addChar(c, lexeme, file, col);
				}
				else if (c == '.') { // Check if malformed number
					token = ERROR;
					errToken = FLOAT_LIT_ERR;
				}
				else if (lexeme == ".") { // Check if malformed number
					token = ERROR;
					errToken = CHAR_ERR;
				}
				else { // End of Token
					Lex::printToken(tkn_line, tkn_col, token, lexeme);
					token = START;
				}
				break;

			case STR_LIT:
				if (c == '\n' || file.eof()) { // Error token if string is unterminated
					token = ERROR;
					errToken = STR_LIT_ERR;
					escaped = false;
				}
				else if (c == '"' && !escaped) { // End of token
					Lex::addChar(c, lexeme, file, col);
					Lex::printToken(tkn_line, tkn_col, token, lexeme);
					token = START;
				}
				else if (c == '\\' && escaped) { // Allow \ to be escaped
					escaped = false;
					Lex::addChar(c, lexeme, file, col);
				}
				else { // Add any more char's
					if (c == '\\') escaped = true;
					else if (escaped) escaped = false;

					Lex::addChar(c, lexeme, file, col);
				}
				break;
				
			case OPERATOR:
				// Check if it's one of these operators: ==, !=, <=, >=, &&, ||
				if (c == '=' || c == '&' || c == '|') {
					Lex::addChar(c, lexeme, file, col);
				}

				Lex::printToken(tkn_line, tkn_col, token, lexeme);
				token = START;
				break;

			case DELIM:
				Lex::printToken(tkn_line, tkn_col, token, lexeme);
				token = START;
				break;

			case SNGL_CMT:
				// Check if token is actually a MULT_CMT or OPERATOR
				if (c != '/') {
					// Reroute to correct token
					if (c == '*') token = MULT_CMT;
					else token = OPERATOR;
					break;
				}

				// Add all characters until EOL is reached
				while (c != '\n' && !file.eof()) {
					Lex::addChar(c, lexeme, file, col);
				}
				
				Lex::printToken(tkn_line, tkn_col, token, lexeme);
				token = START;
				break;

			case ERROR:
				if (errToken == FLOAT_LIT_ERR) {
					// Collect the rest of the malformed number
					while ((c == '.' || isdigit(c)) && !file.eof()) {
						Lex::addChar(c, lexeme, file, col);
					}
				}

				Lex::printError(tkn_line, tkn_col, errToken, lexeme);
				token = START;
				break;

			case EOFILE:
				Lex::printToken(tkn_line, tkn_col, token, lexeme);
				return 0;
				break;
		}
	}

	return 0;
}