

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__



#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	Errors(int e);
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_ident=1,
		_string=2,
		_intcon=3,
		_realcon=4,
		_semicol=5,
		_dotdot=6,
		_plus=7,
		_minus=8,
		_case=9,
		_end=10
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

	bool FirstOfVariant() {
		int next = Peek()->kind;
		return next == _plus || next == _minus  || next == _ident || next == _string
		|| next == _intcon || next == _realcon;
	}

	Token* Peek() {
		scanner->ResetPeek();
		return scanner->Peek();
	}



	Parser(Scanner *scanner);
	Parser();
	~Parser();
	void SemErr(const wchar_t* msg);

	void parserInit(Scanner *scanner);

	void Pascal();
	void IdentList();
	void Block();
	void Label();
	void ConstDecl();
	void TypeDecl();
	void VarDecl();
	void FormParList();
	void Directive();
	void StatementSeq();
	void Constant();
	void Type();
	void FormParSect();
	void ConformantArray();
	void Bounds();
	void Statement();
	void Designator();
	void Expr();
	void ActParList();
	void Case();
	void ActPar();
	void SimExpr();
	void RelOp();
	void Term();
	void AddOp();
	void Factor();
	void MultOp();
	void Set();
	void Elem();
	void SimpleType();
	void FieldList();
	void FixedPart();
	void VariantPart();
	void FieldDecl();
	void Variant();

	void Parse();

}; // end Parser



#endif

