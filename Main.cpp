#include<iostream>
#include<fstream>
#include"Token.h"
#include"PrintToken.h"
using namespace std;
using enum Token;

int main() {
	Token token = Token::START;
	int line = 0;
	int col = 0;
	string lexeme = "";
	ifstream file("input.txt");


	// Check if the input file was found
	if (!file) {
		cout << "Could not find the input file \"input.txt\"" << endl;
	}

	char c = file.get();

	//while (true) {
	//	switch (token) {
	//		default:
	//			// token = lookup(c)
	//	}
	//}

	printToken(1, 2, FLOAT_LIT, "1.5");

	return 0;
}