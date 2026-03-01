#include<iostream>
#include<fstream>
#include"Token.h"
#include"PrintToken.h"
using namespace std;
using enum Token;

int main() {
	Token token = Token::START;
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

	//char c = file.get();
	char c;

	while (true) {
		switch (token) {
			case START:
				// Get the next non-whitespace character
				while (c == ' ') file.get(c);

				if (c == '\n') {
					line++;
					col = 1;
				}
				else {
					// token = lookup(c);
					tkn_line = line;
					tkn_col = col;
				}

				file.get(c);
				break;

			case IDENT:

		}
	}

	return 0;
}