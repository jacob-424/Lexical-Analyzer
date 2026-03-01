#pragma once
#include"Token.h"
#include<string>
#include<iostream>
#include<iomanip>
using namespace std;
using enum Token;

void printToken(int line, int col, Token token, string lexeme);