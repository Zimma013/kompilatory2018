/*
 * Compiler.cpp
 *
 *  Created on: 19 cze 2018
 *      Author: Micha� Kupiec
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include "Parser.h"
#include "Scanner.h"
#include <sys/timeb.h>
#include <wchar.h>

#include "Compiler.h"
using namespace std;

int main(int argc, char *argv[]) {

	if (argc == 2) {
		cout<<argv[1]<<endl;
		FILE* stream;
		if ((stream = fopen(argv[1], "rb")) == NULL) {
				wprintf(L"--- Cannot open file %ls\n", argv[1]);
				exit(1);
		}
		//wchar_t* fileName = (wchar_t*) argv[2];
		//cout<<fileName<<endl;
	    //Scanner scanner = new Scanner(stream);
		//cout<<"scanner"<<endl;
	    Scanner scanner;
	    //cout<<"scannerInit"<<endl;
	    scanner.scannerInit(stream);
	    Parser parser;
	    //cout<<"parser"<<endl;
	    parser.parserInit(&scanner);
	    //cout<<"parserInit"<<endl;
	    parser.Parse();
	    //cout<<"end"<<endl;
	    if(parser.errors->count>0){
	    	cout<<parser.errors->count<<" : errors detected"<<endl;
	    }
		} else
			printf("-- No source file specified\n");

		return 0;
}

