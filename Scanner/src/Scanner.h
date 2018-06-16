/*
 * Scanner.h
 *
 *  Created on: 14 cze 2018
 *      Author: Micha³ Kupiec
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <fstream>
#include <list>

struct tokenVar {
	std::string code;
	std::string value;
};

class Scanner {
	public:
		std::list<tokenVar> scan(std::string path);
		//std::list<tokenVar> scan();
	private:
		std::list<tokenVar> fileToTokenScan(std::ifstream &source);
		std::list<tokenVar> ignoreWhitespaces(std::list<tokenVar> &list);
		tokenVar scanToken(std::ifstream &source);
		void scanWhitespaceToken(tokenVar &token, std::ifstream &source);
		void scanErrorToken(tokenVar &token, std::ifstream &source);
		void scanUnsignedIntToken(tokenVar &token, std::ifstream &source);
		void scanSignedIntToken(tokenVar &token, std::ifstream &source);
		void scanIdentToken(tokenVar &token, std::ifstream &source);
		void checkForKeywords(tokenVar &token);
};



#endif /* SCANNER_H_ */
