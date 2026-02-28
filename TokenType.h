#pragma once

enum class TokenType {
	IDENT,
	KEYWORD,
	INT_LIT,
	FLOAT_LIT,
	STR_LIT,
	OPERATOR,
	DELIM,
	SNGL_CMT,
	MULT_CMT,
	EOF,
	ERROR
};