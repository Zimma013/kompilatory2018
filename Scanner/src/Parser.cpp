/*
 * Parser.cpp
 *
 *  Created on: 14 cze 2018
 *      Author: Micha³ Kupiec
 */

#include "Parser.h"

Parser::Parser() {
	path="E:\\Eclipse-CPP\\workspace\\Scanner\\src\\samplePasacal.pas";
	tokenList = scanner.scan(path.c_str());
	//std::cout<<"init iterator"<<std::endl;
	it = tokenList.begin();
}

void Parser::error_msg(std::string location) {
	throw "Parser Exception - Found in " + location;
}

tokenVar Parser::consume_token(){//std::list<tokenVar> &tokenList //move iterator?
	tokenVar token;	token.code=""; token.value="";
	/*tstd::list<tokenVar>::iterator it = tokenList.begin();
	peek().code = it->code;
	peek().value = it->value;
	tokenList.pop_front();	//wszystko powyzej mozna zakomentowac i zwracac void
	return token;*/
	next_token();
	return token;
}

void Parser::next_token() {
	//std::cout<<"move iterator"<<std::endl;
	it++;
}

tokenVar Parser::peek() {
	tokenVar token;
	//std::list<tokenVar>::iterator it = tokenList.begin();
	token.code = it->code;
	token.value = it->value;
	return token;
}

bool Parser::unsigned_integer_value() {
	if(peek().code=="UNSIGNED_INTEGER_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::signed_integer_value() {
	if(peek().code=="SIGNED_INTEGER_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::signed_real_value() {
	if(peek().code=="SIGNED_REAL_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::unsigned_real_value() {
	if(peek().code=="UNSIGNED_REAL_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::boolean_value() {
	if((peek().code=="TRUE_T")||(peek().code=="FALSE_T")) {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::char_value() {
	if(peek().code=="SINGLE_QUOTE_T") {
		consume_token();
		if ((peek().code=="IDENTIFIER_T")&&(peek().value.length()==1)) {
			consume_token();
			if (peek().code=="SINGLE_QUOTE_T") {
				consume_token();
				return true;
			} else {

				return false;
			}
		} else {

			return false;
		}
	} else {

		return false;
	}
}

bool Parser::integer_type(){
	if (peek().code=="INTEGER_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}



bool Parser::real_type() {
	if(peek().code=="REAL_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::boolean_type() {
	if(peek().code=="BOOLEAN_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::char_type() {
	if(peek().code=="CHAR_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::begin_element() {
	if(peek().code=="BEGIN_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::end_element() {
	if(peek().code=="END_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::and_element() {
	if(peek().code=="AND_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::or_element() {
	if(peek().code=="OR_T") {
		return true;
	} else {

		return false;
	}
}

bool Parser::not_element() {
	if(peek().code=="NOT_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::case_element() {
	if(peek().code=="CASE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::div_element() {
	if(peek().code=="DIV_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::mod_element() {
	if(peek().code=="MOD_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::xor_element() {//TODO::DADWDASDAW
	if(peek().code=="XOR_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::shr_element() {
	if(peek().code=="SHR_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::shl_element() {
	if(peek().code=="SHL_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::to_element() {
	if(peek().code=="TO_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::downto_element() {
	if(peek().code=="DOWNTO_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::from_element() {
	if(peek().code=="FROM_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::while_element() {

	if(peek().code=="WHILE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::repeat_element() {

	if(peek().code=="REPEAT_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::until_element() {

	if(peek().code=="UNTIL_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::array_element() {

	if(peek().code=="ARRAY_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::type_element() {

	if(peek().code=="TYPE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::record_element() {

	if(peek().code=="RECORD_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::nil_element() {

	if(peek().code=="NIL_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::if_element() {

	if(peek().code=="IF_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::else_element() {

	if(peek().code=="ELSE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::then_element() {

	if(peek().code=="THEN_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::const_element() {

	if(peek().code=="CONST_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::program_element() {
	if(peek().code=="PROGRAM_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::return_element() {

	if(peek().code=="RETURN_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::var_element() {

	if(peek().code=="VAR_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::function_element() {

	if(peek().code=="FUNCTION_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::procedure_element() {

	if(peek().code=="PROCEDURE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::of_element() {

	if(peek().code=="OF_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::for_element() {

	if(peek().code=="FOR_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::break_element() {

	if(peek().code=="BREAK_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::true_value() {

	if(peek().code=="TRUE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::false_value() {

	if(peek().code=="FALSE_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::identifier_element() {

	if(peek().code=="IDENTIFIER_T") {
		consume_token();
		return true;
	} else {

		return false;
	}
}

bool Parser::double_quote_element() {
	if(peek().code=="DOUBLE_QUOTE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::ampersant_element() {
	if(peek().code=="AMPERSANT_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::single_quote_element() {
	if(peek().code=="SINGLE_QUOTE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::left_parenthesis_element() {
	if(peek().code=="LEFT_PARENTHESIS_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::right_parenthesis_element() {
	if(peek().code=="RIGHT_PARENTHESIS?T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::left_square_element() {
	if(peek().code=="LEFT_SQUARE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::right_square_element() {
	if(peek().code=="RIGHT_SQUARE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::left_bracket_element() {
	if(peek().code=="LEFT_BRACKET_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::right_bracket_element() {
	if(peek().code=="RIGHT_BRACKET_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::multiply_element() {
	if(peek().code=="MULTIPLY_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::plus_element() {
	if(peek().code=="PLUS_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::minus_element() {
	if(peek().code=="MINUS_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::comma_element() {
	if(peek().code=="COMMA_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::dot_element() {
	if(peek().code=="DOT_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::dotdot_element() {
	if(peek().code=="DOTDOT_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::divide_element() {
	if(peek().code=="DIVIDE_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::colon_element() {
	if(peek().code=="COLON_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::assign_element() {
	if(peek().code=="ASSIGN_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::semicolon_element() {
	if(peek().code=="SEMICOLON_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::le_element() {
	if(peek().code=="LESS_THAN_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::lq_element() {
	if(peek().code=="LESS_OR_EQUAL_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::eq_element() {
	if(peek().code=="EQUAL_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::ge_element() {
	if(peek().code=="GREATER_THAN_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::gq_element() {
	if(peek().code=="GREATER_OR_EQUAL_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::neq_element() {
	if(peek().code=="NOT_EQUAL_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::at_element() {
	if(peek().code=="AT_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

bool Parser::up_arrow_element() {
	if(peek().code=="UP_ARROW_T") {
		consume_token();
		return true;
	} else {
		return false;
	}
}

void Parser::parse() {
	program();
}

void Parser::program() {
	program_header();
	declaration_block();
	compound_statement();
	if(dot_element()) {
		return;
	} else {
		error_msg("end of program");
	}
}



void Parser::program_header() {
	if(program_element()) {
		if(identifier_element()) {
			if(semicolon_element()) {
				return;
			} else {
				//error_msg("program declaration");
				std::cout<<"program declaration ;"<<std::endl;
			}
		} else {
			//error_msg("program declaration");
			std::cout<<"program declaration ident"<<std::endl;
		}
	} else {
		//error_msg("program declaration");
		std::cout<<"program declaration program"<<std::endl;
	}
}

void Parser::declaration_block() {
	if (var_element()) {
		var_declaration();
	} else if (procedure_element()) {
		procedure_declaration();
	} else if (function_element()) {
		function_declaration();
	}
	//compound_statement(); //as in main program body
}

bool Parser::simple_type() {
	return (integer_type() || real_type() || boolean_type() || char_type());
}

void Parser::type() {
	if (simple_type()) {
		if(semicolon_element()) {
			return;
		}
	} else if (array_element()) {
		array_declaration();
	}
}

bool Parser::range() {
	return left_square_element()			// [
			&&unsigned_integer_value()		// int
			&&dotdot_element()				// ..
			&&unsigned_integer_value()		// int
			&&right_square_element();		// ]
}

void Parser::array_declaration() {
	if (range()) {
		if (of_element()) {
			type();
		}
	}
}

void Parser::var_declaration() {
	if(identifier_element()) {
		if(colon_element()) {
			if(type()) {
				declaration_block();
			}
		}
	}
}

void Parser::return_type() {
	if(simple_type()) {
		return;
	} else if (array_element()) {
		if (of_element()) {
			return_type();
		}
	}
}

void Parser::procedure_declaration() {
	if (semicolon_element()) {
		compound_statement();
	} else if (left_parenthesis_element()) {
		parameter_list();
		compound_statement();
	}
}

void Parser::function_declaration() {
	if (colon_element()) {
		return_type();
		compound_statement();
	} else if (left_parenthesis_element()) {
		parameter_list();
		if (colon_element()) {
			return_type();
			compound_statement();
		}
	}
}

void Parser::formal_parameter_list() {
	formal_parameter();
}

void Parser::parameter_list() {
	parameter();
}

void Parser::formal_parameter() {
	if(identifier_element()) {
		if(colon_element()) {
			type();
			if(right_parenthesis_element()) {
				return;
			} else if (semicolon_element()){
				parameter();
			} else {
				error_msg("parameter list");
			}
		} else {
			error_msg("parameter list");
		}
	} else {
		error_msg("parameter list");
	}
}

void Parser::parameter() {
	if (identifier_element()) {
		if(comma_element()) {
			parameter();
			return;
		}
	} else if (value()) {
		if(comma_element()) {
			parameter();
			return;
		}
	} else if (right_parenthesis_element) {
		return;
	} else {
		error_msg("parameter list");
	}
}

void Parser::compound_statement() {
	if(begin_element()) {
		statements();
		if(end_element()) {
			return;
		}
	}
}

void Parser::statements() {
	statement();
	if(semicolon_element()) {
		statements();
	}
}

void Parser::statement() {
	if(identifier_element()) {
		if(assign_element()) {
			if(value()) {
				return;
			} else if (identifier_element()) {
				if (left_parenthesis_element()) {
					parameter_list();
				} else {
					return;
				}
			}
		} else if (left_parenthesis_element()) { //procedure or function

		}
	} else if (for_element()) {

	}
}

bool Parser::value() {
	return (unsigned_integer_value() || signed_integer_value() ||
			unsigned_real_value() || signed_real_value() ||
			boolean_value() || char_value());
}








int main() {
	Parser p;
	p.parse();
	/*for(p.it = p.tokenList.begin(); p.it!=p.tokenList.end();) {
		std::cout<<p.it->code<<std::endl;
		p.next_token();
	}*/
}
