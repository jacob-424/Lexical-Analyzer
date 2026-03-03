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
		START,
		IDENT,
		KEYWORD,
		INT_LIT,
		FLOAT_LIT,
		STR_LIT,
		OPERATOR,
		DELIM,
		SNGL_CMT,
		MULT_CMT,
		ERROR,
		EOFILE,
	};

	enum class ErrorToken {
		FLOAT_LIT_ERR,
		STR_LIT_ERR,
		MULT_CMT_ERR,
		CHAR_ERR
	};

	static Token lookup(char c, ifstream& file); // Returns the token of a char. Used by START only
	static bool isKeyword(string lexeme); // Distinguishes between IDENT and KEYWORD using the final lexeme
	static void printToken(int line, int col, Token token, string lexeme); // Outputs final token and lexeme
	static void printError(int line, int col, ErrorToken errToken, string lexeme); // Outputs Error tokens 
	
	/* Outputs MULT_CMT tokens and MULT_CMT error tokens.
	A special function is needed to handle any new lines in the MULT_CMT*/
	static void printMULT_CMT(int line, int col, bool isError, string lexeme);

	// Helper function to add char's to the lexeme and get the next Char
	static void addChar(char& c, string& lexeme, ifstream& file, int& col);

private:
	// The supported operators, delimiters, and keywords
	static unordered_set<char> operators;
	static unordered_set<char> delimiters;
	static unordered_set<string> keywords;
};