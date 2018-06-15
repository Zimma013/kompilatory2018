/*
 * Parser.h
 *
 *  Created on: 14 cze 2018
 *      Author: Micha³ Kupiec
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Scanner.h"

class Parser {
public:
	Scanner scanner;

	Parser();
private:
	std::list<tokenVar> tokenList;
	tokenVar nextToken();//std::list<tokenVar> &tokenList
	tokenVar peek();
	void parse();
	void program_heading();
	void block();
	void program_block();
	void declaration_block();
	void expect_integer();
	void expect_real();
	void expect_bool();
	void expect_char();
	void parameter();
	void type();
	void array_declaration();

	void error_msg(tokenVar token, std::string);
};

#endif /* PARSER_H_ */
