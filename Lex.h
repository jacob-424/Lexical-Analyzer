#pragma once
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;

class Lex {
public:
	enum class Token {
		IDENT,
		KEYWORD,
		INT_LIT,
		FLOAT_LIT,
		STR_LIT,
		OPERATOR,
		DELIM,
		SNGL_CMT,
		MULT_CMT,
		EOFILE,
		ERROR,
		START
	};

	static void printToken(int line, int col, Token token, string lexeme);
};