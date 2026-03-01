#include"Lex.h"
using enum Lex::Token;

void Lex::printToken(int line, int col, Token token, string lexeme) {
	string tkn = "";

	// Determine if we should output values
	bool isInt = false;
	bool isFloat = false;
	float f = 0;

	// Assign the corresponding string for each token
	switch (token) {
	case IDENT: tkn = "IDENT"; break;
	case KEYWORD: tkn = "KEYWORD"; break;

	case INT_LIT:
		tkn = "INT_LIT";
		isInt = true;
		break;

	case FLOAT_LIT:
		tkn = "FLOAT_LIT";
		isFloat = true;
		f = stof(lexeme); // Convert to float to ensure proper formating (i.e. "2." -> 2.0)
		break;

	case STR_LIT: tkn = "STR_LIT"; break;
	case OPERATOR: tkn = "OPERATOR"; break;
	case DELIM: tkn = "DELIM"; break;
	case SNGL_CMT: tkn = "SNGL_CMT"; break;
	case MULT_CMT: tkn = "MULT_CMT"; break;
	case EOFILE: tkn = "EOF"; break;
	case ERROR: tkn = "ERROR"; break;
	}

	cout << left;

	// Output
	if (isInt) { // Int output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn << setw(12) << lexeme << "[" + lexeme + "]" << endl;
	}
	else if (isFloat) { // Float output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn << setw(12) << lexeme << "[" << f << "]" << endl;
	}
	else { // Regular output
		cout << setw(12) << "(" + to_string(line) + ":" + to_string(col) + ")"
			<< setw(12) << tkn << lexeme << endl;
	}
}