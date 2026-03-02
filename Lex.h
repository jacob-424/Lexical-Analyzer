#pragma once
#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<unordered_set>
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

	static Token lookup(char c, ifstream& file);
	static bool isKeyword(string lexeme);
	static void printToken(int line, int col, Token token, string lexeme);

private:
	static unordered_set<char> operators;
	static unordered_set<char> delimiters;
	static unordered_set<string> keywords;
};