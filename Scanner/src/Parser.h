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
	Parser();
	void parse();

	std::list<tokenVar> tokenList;
	std::list<tokenVar>::iterator it;

	void next_token();

private:
	std::string path;
	Scanner scanner;

	tokenVar consume_token();//std::list<tokenVar> &tokenList



	tokenVar peek();

	bool unsigned_integer_value();
	bool signed_integer_value();
	bool signed_real_value();
	bool unsigned_real_value();
	bool boolean_value();
	bool char_value();
	bool integer_type();
	bool real_type();
	bool boolean_type();
	bool char_type();

	bool begin_element();
	bool end_element();
	bool and_element();
	bool or_element();
	bool not_element();
	bool case_element();
	bool div_element();
	bool mod_element();
	bool xor_element();
	bool shr_element();
	bool shl_element();
	bool to_element();
	bool downto_element();
	bool from_element();
	bool while_element();
	bool repeat_element();
	bool until_element();
	bool array_element();
	bool type_element();
	bool record_element();
	bool nil_element();
	bool if_element();
	bool else_element();
	bool then_element();
	bool const_element();
	bool program_element();
	bool return_element();
	bool var_element();
	bool function_element();
	bool procedure_element();
	bool of_element();
	bool for_element();
	bool break_element();
	bool true_value();
	bool false_value();
	bool identifier_element();
	bool double_quote_element();
	bool ampersant_element();
	bool single_quote_element();
	bool left_parenthesis_element();
	bool right_parenthesis_element();
	bool left_square_element();
	bool right_square_element();
	bool left_bracket_element();
	bool right_bracket_element();
	bool multiply_element();
	bool plus_element();
	bool minus_element();
	bool comma_element();
	bool dot_element();
	bool dotdot_element();
	bool divide_element();
	bool colon_element();
	bool assign_element();
	bool semicolon_element();
	bool le_element();
	bool lq_element();
	bool eq_element();
	bool ge_element();
	bool gq_element();
	bool neq_element();
	bool at_element();
	bool up_arrow_element();

	bool simple_type();
	bool range();
	bool value();

	void program();
	void program_header();
	void block();
	void declaration_block();
	void var_declaration();
	void procedure_declaration();
	void function_declaration();
	void expect_integer();
	void expect_real();
	void expect_bool();
	void expect_char();
	void variable_declaration();
	void type();
	void return_type();
	void array_declaration();
	void statements();
	void statement();
	void variable();
	void compound_statement();
	void block_declarations();
	void formal_parameter_list();
	void formal_parameter();
	void parameter_list();
	void parameter();
	void parameter_list();
	void parameter();

	void error_msg(std::string);
};



#endif /* PARSER_H_ */
