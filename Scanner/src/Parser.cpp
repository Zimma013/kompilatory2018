/*
 * Parser.cpp
 *
 *  Created on: 14 cze 2018
 *      Author: Micha³ Kupiec
 */

#include "Parser.h"

void Parser::error_msg(tokenVar token, std::string location) {
	throw "Parser Exception: " + token.value + " found in " + location;
}

tokenVar Parser::nextToken(){//std::list<tokenVar> &tokenList
	tokenVar token;
	std::list<tokenVar>::iterator it = tokenList.begin();
	token.code = it->code;
	token.value = it->value;
	tokenList.pop_front();
	return token;
}

tokenVar Parser::peek() {
	tokenVar token;
	std::list<tokenVar>::iterator it = tokenList.begin();
	token.code = it->code;
	token.value = it->value;
	return token;
}

void Parser::expect_integer(){
	tokenVar token = nextToken();
	if(token.code=="UNSIGNED_INTEGER_T") {
		token = nextToken();
		if(token.code=="SEMICOLON_T"){
			;;
		} else {
			error_msg(token,"assigning");
		}
	}
}

void Parser::expect_real(){
	tokenVar token = nextToken();
	if(token.code=="UNSIGNED_REAL_T") {
		token = nextToken();
		if(token.code=="SEMICOLON_T"){
			;;
		} else {
			error_msg(token,"assigning");
		}
	}
}

void Parser::expect_bool(){
	tokenVar token = nextToken();
	if((token.code=="TRUE_T")||(token.code=="FALSE_T")) {
		token = nextToken();
		if(token.code=="SEMICOLON_T"){
			;;
		} else {
			error_msg(token,"assigning");
		}
	}
}

void Parser::expect_char(){
	tokenVar token = nextToken();
	if(token.code=="SINGLE_QUOTE_T") {
		token = nextToken();
		if ((token.code=="IDENTIFIER_T")&&(token.value.length()==1)) {
			token = nextToken();
			if (token.code=="SINGLE_QUOTE_T") {
				token = nextToken();
				if(token.code=="SEMICOLON_T") {
					;;
				} else {
					error_msg(token,"assigning");
				}
			} else {
				error_msg(token,"assigning");
			}
		} else {
			error_msg(token,"assigning");
		}
	} else {
		error_msg(token,"assigning");
	}
}

void Parser::parameter() {
	tokenVar token = nextToken();
	if (token.code=="IDENTIFIER_T") {
		token = nextToken();
		if (token.code=="COLON_T") {
			type();
		}  else {
			error_msg(token,"declaration block");
		}
	} else {
		error_msg(token,"declaration block");
	}
}

void Parser::array_declaration();

void Parser::type() {
	tokenVar token = nextToken();
	if (token.code=="INTEGER_T") { //TODO: Type Integer
		token = nextToken();
		if(token.code=="SEMICOLON_T") {
			if (peek().code=="BEGIN_T") {
				;;//TODO: Parsing continues in program_block()
				program_block();
			} else {
				declaration_block();
			}
		} else if (token.code=="ASSIGN_T") {
			expect_integer();
		}
	} else if(token.code=="REAL_T") {//TODO: Type Real
		token = nextToken();
		if(token.code=="SEMICOLON_T") {
			if (peek().code=="BEGIN_T") {
				;;//TODO: Parsing continues in program_block()
				program_block();
			} else {
				declaration_block();
			}
		} else if (token.code=="ASSIGN_T") {
			expect_real();
		}
	} else if(token.code=="BOOLEAN_T") {//TODO: Type Boolean
		token = nextToken();
		if(token.code=="SEMICOLON_T") {
			if (peek().code=="BEGIN_T") {
				;;//TODO: Parsing continues in program_block()
				program_block();
			} else {
				declaration_block();
			}
		} else if (token.code=="ASSIGN_T") {
			expect_bool();
		}
	} else if(token.code=="CHAR_T") {//TODO: Type Char
		token = nextToken();
		if(token.code=="SEMICOLON_T") {
			if (peek().code=="BEGIN_T") {
				;;//TODO: Parsing continues in program_block()
				program_block();
			} else {
				declaration_block();
			}
		} else if (token.code=="ASSIGN_T") {
			expect_char();
		}
	} else if(token.code=="ARRAY_T") {
		array_declaration();
	}
}

void Parser::declaration_block() {
	tokenVar token = nextToken();
	if(token.code=="VAR_T") { //TODO: start reworking from here
		token = nextToken();
		parameter();
	} else {
		error_msg(token,"declaration block");
	}
}

void Parser::program_heading() {
	tokenVar token = nextToken();
	if (token.code=="PROGRAM_T") {
		token = nextToken();
		if (token.code=="IDENTIFIER_T") {
			token = nextToken();
			if (token.code=="SEMICOLON_T"){
				;; //TODO: Parsing continues
			} else {
				error_msg(token,"program heading");
			}
		} else {
			error_msg(token,"program heading");
		}
	} else {
		error_msg(token,"program heading");
	}

}

void Parser::program_block() {
	tokenVar token = nextToken();
	if(token.code=="BEGIN_T") {
		tokenVar token = nextToken();
		//
	}
}

void Parser::block(){
	tokenVar token = nextToken();
	if(peek().code=="VAR_T") {
		declaration_block();
	} else if (peek().code=="BEGIN_T") {
		program_block();
	}
}

void Parser::parse() {
		program_heading();
		block();
}

Parser::Parser(){
	Scanner s;
	std::string path = "F:\\Eclipse-CPP\\workspace\\Scanner\\src\\samplePasacal.pas";
	tokenList=s.scan(path);
}

int main() {
	//Scanner s;
	std::list<tokenVar> tokenList;
	tokenVar t1, t2;

	//tokenList = s.scan();

	std::string path = "F:\\Eclipse-CPP\\workspace\\Scanner\\src\\samplePasacal.pas";
	//Parser::tokenList = s.scan(path);
	/*t1 = nextToken(tokenList);
	t2 = nextToken(tokenList);

	std::cout<<t1.code<<" "<<t1.value<<std::endl<<t2.code<<" "<<t2.value<<std::endl;*/
}

