/*
 * Parser.cpp
 *
 *  Created on: 14 cze 2018
 *      Author: Micha³ Kupiec
 */

#include "Parser.h"

tokenVar nextToken(){

}

int main() {
	Scanner s;
	std::list<tokenVar> tokenList;

	//tokenList = s.scan();

	std::string path = "F:\\Eclipse-CPP\\workspace\\Scanner\\src\\samplePasacal.pas";
	tokenList = s.scan(path);
}

