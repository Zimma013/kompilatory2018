//============================================================================
// Name        : Scanner.cpp
// Author      : Mikh
// Version     : 0.0
// Copyright   : NO_ONE_SHALL_USE_THIS ver. 3.33
// Description : Skaner koloruj¹cy sk³adnie. Na podstawie listy tokenów ma kolorowac
//				 s³owa - przetworzyc nowy tokenFile do kodu html.
//============================================================================


#include "Scanner.h"
using namespace std;

void Scanner::checkForKeywords(tokenVar &token) {
	if (token.value=="integer"){
		token.code="INTEGER_T";
	}
	if (token.value=="real") {
		token.code="REAL_T";
	}
	if (token.value=="boolean") {
		token.code="BOOLEAN_T";
	}
	if(token.value=="char") {
		token.code="CHAR_T";
	}
	if (token.value=="begin") {
		token.code="BEGIN_T";
	}
	if (token.value=="end") {
		token.code="END_T";
	}
	if (token.value=="and") {
		token.code="AND_T";
	}
	if (token.value=="or") {
		token.code="OR_T";
	}
	if (token.value=="not") {
		token.code="NOT_T";
	}
	if (token.value=="case") {
		token.code="CASE_T";
	}
	if (token.value=="div") {
		token.code="DIV_T";
	}
	if (token.value=="mod") {
		token.code="MOD_T";
	}
	if (token.value=="xor") {
		token.code="XOR_T";
	}
	if (token.value=="shr") {
		token.code="SHR_T";
	}
	if (token.value=="shl") {
		token.code="SHL_T";
	}
	if (token.value=="to") {
		token.code="TO_T";
	}
	if (token.value=="downto") {
		token.code="DOWNTO_T";
	}
	if (token.value=="from") {
		token.code="FORM_T";
	}
	if (token.value=="while") {
		token.code="WHILE_T";
	}
	if (token.value=="repeat") {
		token.code="REPEAT_T";
	}
	if (token.value=="until") {
		token.code="UNTIL_T";
	}
	if(token.value=="array") {
		token.code="ARRAY_T";
	}
	if (token.value=="type") {
		token.code="TYPE_T";
	}
	if (token.value=="record") {
		token.code="RECORD_T";
	}
	if (token.value=="nil") {
		token.code="NIL_T";
	}
	if (token.value=="if") {
		token.code="IF_T";
	}
	if (token.value=="else") {
		token.code="ELSE_T";
	}
	if (token.value=="then") {
		token.code="THEN_T";
	}
	if (token.value=="const") {
		token.code="CONST_T";
	}
	if (token.value=="program") {
		token.code="PROGRAM_T";
	}
	if (token.value=="return") {
		token.code="RETURN_T";
	}
	if (token.value=="returns") {
		token.code="RETURNS_T";
	}
	if (token.value=="var") {
		token.code="VAR_T";
	}
	if (token.value=="function") {
		token.code="FUNCTION_T";
	}
	if (token.value=="procedure") {
		token.code="PROCEDURE_T";
	}
	if (token.value=="of") {
		token.code="OF_T";
	}
	if (token.value=="for") {
		token.code="FOR_T";
	}
	if (token.value=="break") {
		token.code="BREAK_T";
	}
}

void Scanner::scanIdentToken(tokenVar &token, ifstream &source) {
	char ch;
	while(
			((source.peek()>=48)&&(source.peek()<=57))  // [0-9]
		  ||((source.peek()>=65)&&(source.peek()<=90))  // [A-Z]
		  ||((source.peek()>=97)&&(source.peek()<=122)) // [a-z]
		   ||(source.peek()==95)) {					    // '_'
		source.get(ch);
		if((ch>=65)&&(ch<=90)) {
			ch = ch+32;
		}
		token.value+=ch;
	}
	checkForKeywords(token);
}

void Scanner::scanUnsignedIntToken(tokenVar &token, ifstream &source) {
	char ch;
	while(((source.peek()>=48)&&(source.peek()<=57))) { // [0-9]
		source.get(ch);
		if(ch==46){ // '.'
			token.code="UNSIGNED_NUMBER_T";
		}
		token.value+=ch;
	}
}

void Scanner::scanWhitespaceToken(tokenVar &token, ifstream &source) {
	char ch;
	//(ch=='\t' || ch==' ' || ch=='\r' || ch=='\n'|| ch=='\u000C')
	while((source.peek()=='\t') || (source.peek()==' ') ||
			(source.peek()=='\r') || (source.peek()=='\n') || (source.peek()=='\u000C')) {
		source.get(ch);
		token.value+=ch;
	}
}

//TODO: Probably wrong
void Scanner::scanErrorToken(tokenVar &token, ifstream &source){
	char ch;
	while(!((source.peek()=='\t') || (source.peek()==' ') ||
			(source.peek()=='\r') || (source.peek()=='\n') || (source.peek()=='\u000C'))) {
		source.get(ch);
		token.value+=ch;
	}

}

tokenVar Scanner::scanToken(ifstream &source) {
	char ch;
	tokenVar t;
	t.code="";
	t.value="";
	source.get(ch);
	if (((ch>='A')&&(ch<='Z'))||((ch>='a')&&(ch<='z'))){ //TODO: IDENTIFIERS AND KEYWORDS
		t.code="IDENTIFIER_T";
		if((ch>=65)&&(ch<=90)) {
			ch = ch+32;
		}
		t.value+=ch;
		scanIdentToken(t,source);
		return t;
	} else if ((ch>='0')&&(ch<='9')) { //TODO: NUMBERS
		t.code="UNSIGNED_INTEGER_T";
		t.value+=ch;
		scanUnsignedIntToken(t,source);
		return t;
	} else if (ch==0x22) { //TODO: SYMBOLS
		t.code="DOUBLE_QUOTE_T";
		t.value+=ch;
		return t;
	} else if (ch=='&') {
		t.code="AMPERSANT_T";
		t.value+=ch;
		return t;
	} else if (ch=='\'') {
		t.code="SINGLE_QUOTE_T";
		t.value+=ch;
		return t;
	} else if (ch==40) {
		t.code="LEFT_PARENTHESIS_T";
		t.value+=ch;
		return t;
	} else if (ch==41) {
		t.code="RIGHT_PARENTHESIS_T";
		t.value+=ch;
		return t;
	} else if (ch==42) {
		t.code="MULTIPLY_T";
		t.value+=ch;
		return t;
	} else if (ch==43) {
		t.code="PLUS_T";
		t.value+=ch;
	} else if (ch==44) {
		t.code="COMMA_T";
		t.value+=ch;
		return t;
	} else if (ch==45) {
		t.code="MINUS_T";
		t.value+=ch;
		return t;
	} else if (ch==46) {
		t.code="PERIOD_T";
		t.value+=ch;
		if(source.peek()==46){
			t.code="DOTDOT_t";
			source.get(ch);
			t.value+=ch;
		}
		return t;
	} else if (ch==47) {
		t.code="DIVIDE_T";
		t.value+=ch;
		return t;
	} else if (ch==58) {
		t.code="COLON_T";
		t.value+=ch;
		if(source.peek()==61){
			t.code="ASSIGN_T";
			source.get(ch);
			t.value+=ch;
		}
		return t;
	} else if (ch==59) {
		t.code="SEMICOLON_T";
		t.value+=ch;
		return t;
	} else if (ch==60) {
		t.code="LESS_THAN_T";
		t.value+=ch;
		if(source.peek()==61) {
			t.code="LESS_OR_EQUAL_T";
			source.get(ch);
			t.value+=ch;
		} else if (ch==62) {
			t.code="NOT_EQUAL_T";
			source.get(ch);
			t.value+=ch;
		}
		return t;
	} else if (ch==61){
		t.code="EQUAL_T";
		t.value+=ch;
		return t;
	} else if (ch==62) {
		t.code="GREATER_THAN_T";
		t.value+=ch;
		if(source.peek()==61) {
			t.code="GREATER_OR_EQUAL_T";
			source.get(ch);
			t.value+=ch;
		}
		return t;
	} else if (ch==64) {
		t.code="AT_T";
		t.value+=ch;
		return t;
	} else if (ch==91) {
		t.code="LEFT_SQUARE_T";
		t.value+=ch;
		return t;
	} else if (ch==93) {
		t.code="RIGHT_SQUARE_T";
		t.value+=ch;
		return t;
	} else if (ch==94) {
		t.code="UPARROW_T";
		t.value+=ch;
		return t;
	} else if (ch==95) {
		t.code="UNDERLINE_T";
		t.value+=ch;
		return t;
	} else if (ch==123) {
		t.code="LEFT_BRACKET_T";
		t.value+=ch;
		return t;
	} else if (ch==125) {
		t.code="RIGHT_BRACKET_T";
		t.value+=ch;
		return t;
	} else if (ch=='\t' || ch==0x20 || ch=='\r' || ch=='\n'|| ch=='\u000C'){ //TODO: WHITESPACES
		t.code="WHITESPACE_T";
		t.value+=ch;
		scanWhitespaceToken(t,source);
		return t;
	}

	//TODO: ANYTHING ELSE
	t.code="ERROR";
	t.value+=ch;
	scanErrorToken(t,source);
	return t;
}

list<tokenVar> Scanner::ignoreWhitespaces(list<tokenVar> &list) {

	std::list<tokenVar> newList;
	tokenVar token;
	std::list<tokenVar>::iterator it = list.begin();
	while(it!=list.end()) {
		if(it->code!="WHITESPACE_T") {
			newList.push_back(*it);
		}
		it++;
	}
	return newList;
}

list<tokenVar> Scanner::fileToTokenScan(ifstream &source) {
	list<tokenVar>::iterator it;
	list<tokenVar> tokenList;
	tokenVar token;
	while(!source.eof()){
		token = scanToken(source);
		tokenList.push_back(token);
	}
	tokenList = ignoreWhitespaces(tokenList);
	return tokenList;
}

list<tokenVar> Scanner::scan() {
	ifstream sourceFile;
	list<tokenVar> tokenList;
	string path;

	cout << "Podaj scie¿kê do skanowanego pliku" << endl;
	cin >> path;
	sourceFile.open(path);
	tokenList = fileToTokenScan(sourceFile);
	sourceFile.close();

	return tokenList;
}

list<tokenVar> Scanner::scan(string path) {
	ifstream sourceFile;
	list<tokenVar> tokenList;

	sourceFile.open(path);
	tokenList = fileToTokenScan(sourceFile);
	sourceFile.close();

	return tokenList;
}

/*int main() {
	ifstream sourceFile;
	ofstream tokenFile;
	string path;

	string buffer;

	list<tokenVar> tokenList;
	list<tokenVar>::iterator it;


	//cout << "Podaj scie¿kê do skanowanego pliku" << endl;
	//cin >> path;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!WA¯NE!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//to jest to zmiany.
	sourceFile.open("F:\\Eclipse-CPP\\workspace\\Scanner\\src\\samplePasacal.pas");

	tokenList = Scanner::fileToTokenScan(sourceFile);

	tokenList = Scanner::scan();

	it = tokenList.begin();
	while (it != tokenList.end()) {
		//if(it->code!="WHITESPACE_T")
		cout << "Code: " << it->code << " Value: " << it->value << endl;
		it++;
	}

	sourceFile.close();
	return 0;
}*/
