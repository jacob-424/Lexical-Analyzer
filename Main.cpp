#include<iostream>
#include<fstream>
#include"Lex.h"
using namespace std;
using enum Lex::Token;

int main() {
	Lex::Token token = START;
	int line = 1;
	int col = 1;
	int tkn_line = 0;
	int tkn_col = 0;
	string lexeme = "";
	ifstream file("input.txt");


	// Check if the input file was found
	if (!file) {
		cout << "Could not find the input file \"input.txt\"" << endl;
	}

	char c = file.get();

	while (true) {
		switch (token) {
			case START:
				// Get the next non-whitespace character
				while (c == ' ') {
					file.get(c);
					col++;
				}

				if (c == '\n') { // New line found
					line++;
					col = 1;
				}
				else { // Token found
					// token = lookup(c);

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
				if (isalnum(static_cast<unsigned char>(c)) || c == '_') {
					lexeme.push_back(c);
					file.get(c);
					col++;
				}
				else {
					// token = getToken(); // Check if IDENT or KEYWORD
					Lex::printToken(tkn_line, tkn_col, token, lexeme);
					token = START;
				}
		}
	}

	return 0;
}