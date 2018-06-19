

#include <wchar.h>
#include <iostream>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::Pascal() {
		std::cout<<"pascalMain"<<std::endl;
		Expect(11 /* "program" */);
		Expect(_ident);
		if (la->kind == 12 /* "(" */) {
			Get();
			IdentList();
			Expect(13 /* ")" */);
		}
		Expect(_semicol);
		Block();
		Expect(14 /* "." */);
}

void Parser::IdentList() {
		Expect(_ident);
		while (la->kind == 16 /* "," */) {
			Get();
			Expect(_ident);
		}
}

void Parser::Block() {
	std::cout<<"blockMain if 1"<<std::endl;
		if (la->kind == 15 /* "label" */) {
			Get();
			Label();
			while (la->kind == 16 /* "," */) {
				Get();
				Label();
			}
			Expect(_semicol);
		}std::cout<<"blockMain if 2"<<std::endl;
		if (la->kind == 17 /* "const" */) {
			Get();
			ConstDecl();
			while (la->kind == _ident) {
				ConstDecl();
			}
		}std::cout<<"blockMain if 3"<<std::endl;
		if (la->kind == 18 /* "type" */) {
			Get();
			TypeDecl();
			while (la->kind == _ident) {
				TypeDecl();
			}
		}std::cout<<"blockMain if 4"<<std::endl;
		if (la->kind == 19 /* "var" */) {
			Get();
			std::cout<<"blockMain if 4.1"<<std::endl;
			VarDecl();
			//std::cout<<"blockMain if 4.2"<<std::endl;
			while (la->kind == _ident) {
				//std::cout<<"blockMain if 4.4"<<std::endl;
				VarDecl();
			}
		}std::cout<<"blockMain if 5"<<std::endl;
		while (la->kind == 20 /* "procedure" */ || la->kind == 21 /* "function" */) {
			if (la->kind == 20 /* "procedure" */) {
				Get();
				Expect(_ident);
				if (la->kind == 12 /* "(" */) {
					FormParList();
				}
				Expect(_semicol);
				if (StartOf(1)) {
					Block();
				} else if (la->kind == _ident) {
					Directive();
				} else SynErr(62);
				Expect(_semicol);
			} else {
				Get();
				Expect(_ident);
				if (la->kind == 12 /* "(" */) {
					FormParList();
				}
				if (la->kind == 22 /* ":" */) {
					Get();
					Expect(_ident);
				}
				Expect(_semicol);
				if (StartOf(1)) {
					Block();
				} else if (la->kind == _ident) {
					Directive();
				} else SynErr(63);
				Expect(_semicol);
			}
		}
		Expect(23 /* "begin" */);
		StatementSeq();
		Expect(_end);
}

void Parser::Label() {
		Expect(_intcon);
}

void Parser::ConstDecl() {
		Expect(_ident);
		Expect(24 /* "=" */);
		Constant();
		Expect(_semicol);
}

void Parser::TypeDecl() {
		Expect(_ident);
		Expect(24 /* "=" */);
		Type();
		Expect(_semicol);
}

void Parser::VarDecl() {
	std::cout<<"blockMain if 4.d"<<std::endl;
		IdentList();
		std::cout<<"blockMain if 4.l"<<std::endl;
		Expect(22 /* ":" */);
		std::cout<<"blockMain if 4.t"<<std::endl;
		Type();
		std::cout<<"blockMain if 4.e"<<std::endl;
		Expect(_semicol);
}

void Parser::FormParList() {
		Expect(12 /* "(" */);
		FormParSect();
		while (la->kind == _semicol) {
			Get();
			FormParSect();
		}
		Expect(13 /* ")" */);
}

void Parser::Directive() {
		Expect(_ident);
}

void Parser::StatementSeq() {
		Statement();
		while (la->kind == _semicol) {
			Get();
			Statement();
		}
}

void Parser::Constant() {
		if (StartOf(2)) {
			if (la->kind == _plus || la->kind == _minus) {
				if (la->kind == _plus) {
					Get();
				} else {
					Get();
				}
			}
			if (la->kind == _ident) {
				Get();
			} else if (la->kind == _intcon) {
				Get();
			} else if (la->kind == _realcon) {
				Get();
			} else SynErr(64);
		} else if (la->kind == _string) {
			Get();
		} else SynErr(65);
}

void Parser::Type() {
		if (StartOf(3)) {
			std::cout<<"blockMain if t.st"<<std::endl;
			SimpleType();
		} else if (la->kind == 45 /* "^" */) {
			Get();
			Expect(_ident);
		} else if (StartOf(4)) {
			if (la->kind == 29 /* "packed" */) {
				Get();
			}
			if (la->kind == 25 /* "array" */) {
				Get();
				Expect(26 /* "[" */);
				SimpleType();
				while (la->kind == 16 /* "," */) {
					Get();
					SimpleType();
				}
				Expect(27 /* "]" */);
				Expect(28 /* "of" */);
				Type();
			} else if (la->kind == 58 /* "record" */) {
				Get();
				if (la->kind == _ident || la->kind == _case) {
					FieldList();
				}
				Expect(_end);
			} else if (la->kind == 59 /* "set" */) {
				Get();
				Expect(28 /* "of" */);
				Type();
			} else if (la->kind == 60 /* "file" */) {
				Get();
				Expect(28 /* "of" */);
				Type();
			} else SynErr(66);
		} else SynErr(67);
}

void Parser::FormParSect() {
		if (la->kind == _ident || la->kind == 19 /* "var" */) {
			if (la->kind == 19 /* "var" */) {
				Get();
			}
			IdentList();
			Expect(22 /* ":" */);
			if (la->kind == _ident) {
				Get();
			} else if (la->kind == 25 /* "array" */ || la->kind == 29 /* "packed" */) {
				ConformantArray();
			} else SynErr(68);
		} else if (la->kind == 20 /* "procedure" */) {
			Get();
			Expect(_ident);
			if (la->kind == 12 /* "(" */) {
				FormParList();
			}
		} else if (la->kind == 21 /* "function" */) {
			Get();
			Expect(_ident);
			if (la->kind == 12 /* "(" */) {
				FormParList();
			}
			Expect(22 /* ":" */);
			Expect(_ident);
		} else SynErr(69);
}

void Parser::ConformantArray() {
		if (la->kind == 25 /* "array" */) {
			Get();
			Expect(26 /* "[" */);
			Bounds();
			while (la->kind == _semicol) {
				Get();
				Bounds();
			}
			Expect(27 /* "]" */);
			Expect(28 /* "of" */);
			if (la->kind == _ident) {
				Get();
			} else if (la->kind == 25 /* "array" */ || la->kind == 29 /* "packed" */) {
				ConformantArray();
			} else SynErr(70);
		} else if (la->kind == 29 /* "packed" */) {
			Get();
			Expect(25 /* "array" */);
			Expect(26 /* "[" */);
			Bounds();
			Expect(27 /* "]" */);
			Expect(28 /* "of" */);
			Expect(_ident);
		} else SynErr(71);
}

void Parser::Bounds() {
		Expect(_ident);
		Expect(_dotdot);
		Expect(_ident);
		Expect(22 /* ":" */);
		Expect(_ident);
}

void Parser::Statement() {
		if (la->kind == _intcon) {
			Label();
			Expect(22 /* ":" */);
		}
		if (StartOf(5)) {
			switch (la->kind) {
			case _ident: {
				Designator();
				if (la->kind == 30 /* ":=" */) {
					Get();
					Expr();
				} else if (StartOf(6)) {
					if (la->kind == 12 /* "(" */) {
						ActParList();
					}
				} else SynErr(72);
				break;
			}
			case 31 /* "goto" */: {
				Get();
				Label();
				break;
			}
			case 23 /* "begin" */: {
				Get();
				StatementSeq();
				Expect(_end);
				break;
			}
			case 32 /* "while" */: {
				Get();
				Expr();
				Expect(33 /* "do" */);
				Statement();
				break;
			}
			case 34 /* "repeat" */: {
				Get();
				StatementSeq();
				Expect(35 /* "until" */);
				Expr();
				break;
			}
			case 36 /* "for" */: {
				Get();
				Expect(_ident);
				Expect(30 /* ":=" */);
				Expr();
				if (la->kind == 37 /* "to" */) {
					Get();
				} else if (la->kind == 38 /* "downto" */) {
					Get();
				} else SynErr(73);
				Expr();
				Expect(33 /* "do" */);
				Statement();
				break;
			}
			case 39 /* "if" */: {
				Get();
				Expr();
				Expect(40 /* "then" */);
				Statement();
				if (la->kind == 41 /* "else" */) {
					Get();
					Statement();
				}
				break;
			}
			case _case: {
				Get();
				Expr();
				Expect(28 /* "of" */);
				Case();
				while (la->kind == _semicol && Peek()->kind != _end) { //la.kind
					Expect(_semicol);
					Case();
				}
				if (la->kind == _semicol) {
					Get();
				}
				Expect(_end);
				break;
			}
			case 42 /* "with" */: {
				Get();
				Designator();
				while (la->kind == 16 /* "," */) {
					Get();
					Designator();
				}
				Expect(33 /* "do" */);
				Statement();
				break;
			}
			}
		}
}

void Parser::Designator() {
		Expect(_ident);
		while (la->kind == 14 /* "." */ || la->kind == 26 /* "[" */ || la->kind == 45 /* "^" */) {
			if (la->kind == 26 /* "[" */) {
				Get();
				Expr();
				while (la->kind == 16 /* "," */) {
					Get();
					Expr();
				}
				Expect(27 /* "]" */);
			} else if (la->kind == 14 /* "." */) {
				Get();
				Expect(_ident);
			} else {
				Get();
			}
		}
}

void Parser::Expr() {
		SimExpr();
		if (StartOf(7)) {
			RelOp();
			SimExpr();
		}
}

void Parser::ActParList() {
		Expect(12 /* "(" */);
		ActPar();
		while (la->kind == 16 /* "," */) {
			Get();
			ActPar();
		}
		Expect(13 /* ")" */);
}

void Parser::Case() {
		Constant();
		while (la->kind == 16 /* "," */) {
			Get();
			Constant();
		}
		Expect(22 /* ":" */);
		Statement();
}

void Parser::ActPar() {
		Expr();
		if (la->kind == 22 /* ":" */) {
			Get();
			Expr();
			if (la->kind == 22 /* ":" */) {
				Get();
				Expr();
			}
		}
}

void Parser::SimExpr() {
		if (la->kind == _plus || la->kind == _minus) {
			if (la->kind == _plus) {
				Get();
			} else {
				Get();
			}
		}
		Term();
		while (la->kind == _plus || la->kind == _minus || la->kind == 52 /* "or" */) {
			AddOp();
			Term();
		}
}

void Parser::RelOp() {
		switch (la->kind) {
		case 24 /* "=" */: {
			Get();
			break;
		}
		case 46 /* "<>" */: {
			Get();
			break;
		}
		case 47 /* "<" */: {
			Get();
			break;
		}
		case 48 /* "<=" */: {
			Get();
			break;
		}
		case 49 /* ">" */: {
			Get();
			break;
		}
		case 50 /* ">=" */: {
			Get();
			break;
		}
		case 51 /* "in" */: {
			Get();
			break;
		}
		default: SynErr(74); break;
		}
}

void Parser::Term() {
		Factor();
		while (StartOf(8)) {
			MultOp();
			Factor();
		}
}

void Parser::AddOp() {
		if (la->kind == _plus) {
			Get();
		} else if (la->kind == _minus) {
			Get();
		} else if (la->kind == 52 /* "or" */) {
			Get();
		} else SynErr(75);
}

void Parser::Factor() {
		switch (la->kind) {
		case _ident: {
			Designator();
			if (la->kind == 12 /* "(" */) {
				ActParList();
			}
			break;
		}
		case _intcon: {
			Get();
			break;
		}
		case _realcon: {
			Get();
			break;
		}
		case _string: {
			Get();
			break;
		}
		case 26 /* "[" */: {
			Set();
			break;
		}
		case 43 /* "nil" */: {
			Get();
			break;
		}
		case 12 /* "(" */: {
			Get();
			Expr();
			Expect(13 /* ")" */);
			break;
		}
		case 44 /* "not" */: {
			Get();
			Factor();
			break;
		}
		default: SynErr(76); break;
		}
}

void Parser::MultOp() {
		if (la->kind == 53 /* "*" */) {
			Get();
		} else if (la->kind == 54 /* "/" */) {
			Get();
		} else if (la->kind == 55 /* "div" */) {
			Get();
		} else if (la->kind == 56 /* "mod" */) {
			Get();
		} else if (la->kind == 57 /* "and" */) {
			Get();
		} else SynErr(77);
}

void Parser::Set() {
		Expect(26 /* "[" */);
		if (StartOf(9)) {
			Elem();
			while (la->kind == 16 /* "," */) {
				Get();
				Elem();
			}
		}
		Expect(27 /* "]" */);
}

void Parser::Elem() {
		Expr();
		if (la->kind == _dotdot) {
			Get();
			Expr();
		}
}

void Parser::SimpleType() {
	std::cout<<"blockMain if st:"<<la->kind<<std::endl;
		if (la->kind == _ident && Peek()->kind != _dotdot) { //la.kind
			std::cout<<"blockMain if exp"<<std::endl;
			Expect(_ident);
		} else if (StartOf(10)) {
			std::cout<<"blockMain if exp1"<<std::endl;
			Constant();
			Expect(_dotdot);
			Constant();
		} else if (la->kind == 12 /* "(" */) {
			std::cout<<"blockMain if exp2"<<std::endl;
			Get();
			IdentList();
			Expect(13 /* ")" */);
		} else {std::cout<<"blockMain if expe"<<std::endl;SynErr(78);}
}

void Parser::FieldList() {
		if (la->kind == _ident) {
			FixedPart();
			if (la->kind == _semicol && Peek()->kind == _case) { //la.kind
				Expect(_semicol);
				VariantPart();
			}
		} else if (la->kind == _case) {
			VariantPart();
		} else SynErr(79);
		if (la->kind == _semicol) {
			Get();
		}
}

void Parser::FixedPart() {
		FieldDecl();
		while (la->kind == _semicol && Peek()->kind == _ident) { //la.kind
			Expect(_semicol);
			FieldDecl();
		}
}

void Parser::VariantPart() {
		Expect(_case);
		Expect(_ident);
		if (la->kind == 22 /* ":" */) {
			Get();
			Expect(_ident);
		}
		Expect(28 /* "of" */);
		Variant();
		while (la->kind == _semicol && FirstOfVariant()) { //la.kind
			Expect(_semicol);
			Variant();
		}
}

void Parser::FieldDecl() {
		IdentList();
		Expect(22 /* ":" */);
		Type();
}

void Parser::Variant() {
		Constant();
		while (la->kind == 16 /* "," */) {
			Get();
			Constant();
		}
		Expect(22 /* ":" */);
		Expect(12 /* "(" */);
		if (la->kind == _ident || la->kind == _case) {
			FieldList();
		}
		Expect(13 /* ")" */);
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	std::cout<<"dummy"<<std::endl;
	la->val = coco_string_create(L"Dummy Token");
	std::cout<<"postDummy"<<std::endl;
	Get();
	std::cout<<"postGet"<<std::endl;
	Pascal();
	std::cout<<"postPascal"<<std::endl;
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 61;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

Parser::Parser() {

}

void Parser::parserInit(Scanner *scanner) {
	maxT = 61;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors(0);
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[11][63] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,T,T,T, T,T,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,T, T,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,x,x,T, T,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,x,x, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,x,x},
		{x,T,x,x, x,x,x,x, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,T, T,x,T,x, T,x,x,T, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,T,x,x, x,x,T,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, x,x,x,x, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, T,T,T,T, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,T,T,T, T,T,x,x, x,x,x},
		{x,T,T,T, T,x,x,T, T,x,x,x, T,x,x,x, x,x,x,x, x,x,x,x, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}
Errors::Errors(int e) {
	count=e;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"ident expected"); break;
			case 2: s = coco_string_create(L"string expected"); break;
			case 3: s = coco_string_create(L"intcon expected"); break;
			case 4: s = coco_string_create(L"realcon expected"); break;
			case 5: s = coco_string_create(L"semicol expected"); break;
			case 6: s = coco_string_create(L"dotdot expected"); break;
			case 7: s = coco_string_create(L"plus expected"); break;
			case 8: s = coco_string_create(L"minus expected"); break;
			case 9: s = coco_string_create(L"case expected"); break;
			case 10: s = coco_string_create(L"end expected"); break;
			case 11: s = coco_string_create(L"\"program\" expected"); break;
			case 12: s = coco_string_create(L"\"(\" expected"); break;
			case 13: s = coco_string_create(L"\")\" expected"); break;
			case 14: s = coco_string_create(L"\".\" expected"); break;
			case 15: s = coco_string_create(L"\"label\" expected"); break;
			case 16: s = coco_string_create(L"\",\" expected"); break;
			case 17: s = coco_string_create(L"\"const\" expected"); break;
			case 18: s = coco_string_create(L"\"type\" expected"); break;
			case 19: s = coco_string_create(L"\"var\" expected"); break;
			case 20: s = coco_string_create(L"\"procedure\" expected"); break;
			case 21: s = coco_string_create(L"\"function\" expected"); break;
			case 22: s = coco_string_create(L"\":\" expected"); break;
			case 23: s = coco_string_create(L"\"begin\" expected"); break;
			case 24: s = coco_string_create(L"\"=\" expected"); break;
			case 25: s = coco_string_create(L"\"array\" expected"); break;
			case 26: s = coco_string_create(L"\"[\" expected"); break;
			case 27: s = coco_string_create(L"\"]\" expected"); break;
			case 28: s = coco_string_create(L"\"of\" expected"); break;
			case 29: s = coco_string_create(L"\"packed\" expected"); break;
			case 30: s = coco_string_create(L"\":=\" expected"); break;
			case 31: s = coco_string_create(L"\"goto\" expected"); break;
			case 32: s = coco_string_create(L"\"while\" expected"); break;
			case 33: s = coco_string_create(L"\"do\" expected"); break;
			case 34: s = coco_string_create(L"\"repeat\" expected"); break;
			case 35: s = coco_string_create(L"\"until\" expected"); break;
			case 36: s = coco_string_create(L"\"for\" expected"); break;
			case 37: s = coco_string_create(L"\"to\" expected"); break;
			case 38: s = coco_string_create(L"\"downto\" expected"); break;
			case 39: s = coco_string_create(L"\"if\" expected"); break;
			case 40: s = coco_string_create(L"\"then\" expected"); break;
			case 41: s = coco_string_create(L"\"else\" expected"); break;
			case 42: s = coco_string_create(L"\"with\" expected"); break;
			case 43: s = coco_string_create(L"\"nil\" expected"); break;
			case 44: s = coco_string_create(L"\"not\" expected"); break;
			case 45: s = coco_string_create(L"\"^\" expected"); break;
			case 46: s = coco_string_create(L"\"<>\" expected"); break;
			case 47: s = coco_string_create(L"\"<\" expected"); break;
			case 48: s = coco_string_create(L"\"<=\" expected"); break;
			case 49: s = coco_string_create(L"\">\" expected"); break;
			case 50: s = coco_string_create(L"\">=\" expected"); break;
			case 51: s = coco_string_create(L"\"in\" expected"); break;
			case 52: s = coco_string_create(L"\"or\" expected"); break;
			case 53: s = coco_string_create(L"\"*\" expected"); break;
			case 54: s = coco_string_create(L"\"/\" expected"); break;
			case 55: s = coco_string_create(L"\"div\" expected"); break;
			case 56: s = coco_string_create(L"\"mod\" expected"); break;
			case 57: s = coco_string_create(L"\"and\" expected"); break;
			case 58: s = coco_string_create(L"\"record\" expected"); break;
			case 59: s = coco_string_create(L"\"set\" expected"); break;
			case 60: s = coco_string_create(L"\"file\" expected"); break;
			case 61: s = coco_string_create(L"??? expected"); break;
			case 62: s = coco_string_create(L"invalid Block"); break;
			case 63: s = coco_string_create(L"invalid Block"); break;
			case 64: s = coco_string_create(L"invalid Constant"); break;
			case 65: s = coco_string_create(L"invalid Constant"); break;
			case 66: s = coco_string_create(L"invalid Type"); break;
			case 67: s = coco_string_create(L"invalid Type"); break;
			case 68: s = coco_string_create(L"invalid FormParSect"); break;
			case 69: s = coco_string_create(L"invalid FormParSect"); break;
			case 70: s = coco_string_create(L"invalid ConformantArray"); break;
			case 71: s = coco_string_create(L"invalid ConformantArray"); break;
			case 72: s = coco_string_create(L"invalid Statement"); break;
			case 73: s = coco_string_create(L"invalid Statement"); break;
			case 74: s = coco_string_create(L"invalid RelOp"); break;
			case 75: s = coco_string_create(L"invalid AddOp"); break;
			case 76: s = coco_string_create(L"invalid Factor"); break;
			case 77: s = coco_string_create(L"invalid MultOp"); break;
			case 78: s = coco_string_create(L"invalid SimpleType"); break;
			case 79: s = coco_string_create(L"invalid FieldList"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}


