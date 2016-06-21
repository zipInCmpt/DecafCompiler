
#include "decafast-defs.h"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafast.tab.h"
#endif

using namespace std;

/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
};

string getString(decafAST *d) {
	if (d != NULL) {
		return d->str();
	} else {
		return string("None");
	}
}

template <class T>
string commaList(list<T> vec) {
    string s("");
    for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
        s = s + (s.empty() ? string("") : string(",")) + (*i)->str(); 
    }   
    if (s.empty()) {
        s = string("None");
    }   
    return s;
}

/// decafStmtList - List of Decaf statements
class decafStmtList : public decafAST {
	list<decafAST *> stmts;
public:
	decafStmtList() {}
	~decafStmtList() {
		for (list<decafAST *>::iterator i = stmts.begin(); i != stmts.end(); i++) { 
			delete *i;
		}
	}
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	string pop_front() { string value = stmts.back()->str(); stmts.pop_back(); return value; }
	string str() { return commaList<class decafAST *>(stmts); }
};

// Package
class PackageAST : public decafAST {
	string Name;
	decafStmtList *FieldDeclList;
	decafStmtList *MethodDeclList;
public:
	PackageAST(string name, decafStmtList *fieldlist, decafStmtList *methodlist) 
		: Name(name), FieldDeclList(fieldlist), MethodDeclList(methodlist) {}
	~PackageAST() { 
		//if (FieldDeclList != NULL) { delete FieldDeclList; }
		//if (MethodDeclList != NULL) { delete MethodDeclList; }
	}
	string str() { 
		return string("Package") + "(" + Name + "," + getString(FieldDeclList) + "," + getString(MethodDeclList) + ")";
	}
};

// Expr
class ExprAST : public decafAST {
	decafAST *decafASTNode;
public:
	ExprAST (decafAST *node) { decafASTNode = node; }
	~ExprAST() { delete decafASTNode; }
	string str() { return getString(decafASTNode); }
};

/// ProgramAST - the decaf program
class ProgramAST : public decafAST {
	decafStmtList *ExternList;
	PackageAST *PackageDef;
public:
	ProgramAST(decafStmtList *externs, PackageAST *c) : ExternList(externs), PackageDef(c) {}
	~ProgramAST() { 
		if (ExternList != NULL) { delete ExternList; } 
		if (PackageDef != NULL) { delete PackageDef; }
	}
	string str() { return string("Program") + "(" + getString(ExternList) + "," + getString(PackageDef) + ")"; }
};

class BoolConstantAST : public decafAST {
	bool value;
public:
	BoolConstantAST(bool type) { value = type; };
	~BoolConstantAST() { }
	string str() { if(value) return string("True"); else return string("False"); }
};

class rvalueAST : public decafAST {
	string idName;
	bool isArray;
	decafAST *arrayIndex;
public:
	rvalueAST(string ID, bool arraytype = false) { idName = ID; isArray = arraytype; arrayIndex = NULL; }
	rvalueAST(string ID, bool arraytype, decafAST *index) { idName = ID; isArray = arraytype; arrayIndex = index;}
	~rvalueAST() { }
	string str() {
		if(isArray) {
			return string("VariableExpr") + "(" + idName + ")";
		} else {
			/// TODO: Double check this statement
			return string("ArrayLocExpr") + "(" + idName + "," + getString(arrayIndex) + ")";
		}
	}
};

class NumberExprAST : public decafAST {
	int integerValue;
public:
	NumberExprAST(int value) { integerValue = value; }
	~NumberExprAST();
	string str() {
		/// TODO: Double check this statement
		return string("NumberExpr") + "(" + std::to_string(integerValue) + ")";
	}
};

class BoolExprAST : public decafAST {
	decafAST *boolASTNode;
public:
	BoolExprAST(decafAST *boolConstant) { boolASTNode = boolConstant; }
	~BoolExprAST() { delete boolASTNode; }
	string str() {
		return string("BoolExpr(") + getString(boolASTNode) + ")";
	}
};

class BinaryExprAST : public decafAST {
	string binaryOperator;
	decafAST *leftValueNode;
	decafAST *rightValueNode;
public:
	BinaryExprAST(string binaryOp, decafAST *left, decafAST *right) {
		binaryOperator = binaryOp;
		leftValueNode = left;
		rightValueNode = right;
	}
	~BinaryExprAST() {
		binaryOperator = "";
		delete leftValueNode;
		delete  rightValueNode;
	}
	string str() {
		return string("BinaryExpr(") + binaryOperator + "," + getString(leftValueNode) + "," + getString(rightValueNode) + ")";
	}
};

class UnaryExprAST : public decafAST {
	string unaryOperator;
	decafAST *opNumber;
public:
	UnaryExprAST(string unaryOp, decafAST *exp) {
		unaryOperator = unaryOp;
		opNumber = exp;
	}
	~UnaryExprAST() {
		unaryOperator = "";
		delete opNumber;
	}
	string str() {
		return string("UnaryExpr(") + unaryOperator + "," + getString(opNumber) + ")";
	}
};

// Method_Call
class MethodCallAST : public decafAST {
	string identifierName;
	decafStmtList *argumentList;
public:
	MethodCallAST(string idName, decafStmtList *args) { identifierName = idName; argumentList = args; }
	~MethodCallAST() { identifierName = ""; delete argumentList; }
	string str() { return string("MethodCall(") + identifierName + "," + argumentList->str() + ")"; }
};



// Get Binary Operator
string getBinaryOp (int opId) {
	switch(opId) {
		case 0: return string("Plus"); break;
		case 1: return string("Minus"); break;
		case 2: return string("Mult"); break;
		case 3: return string("Div"); break;
		case 4: return string("Leftshift"); break;
		case 5: return string("Rightshift"); break;
		case 6: return string("Mod"); break;
		case 7: return string("Lt"); break;
		case 8: return string("Gt"); break;
		case 9: return string("Leq"); break;
		case 10: return string("Geq"); break;
		case 11: return string("Eq"); break;
		case 12: return string("Neq"); break;
		case 13: return string("And"); break;
		case 14: return string("Or"); break;
		default: return string(""); break;
	}
}

// DecafType
string getDecafType (int typeIndex) {
	switch (typeIndex) {
		case 17: return string("IntType"); break;
		case 18: return string("BoolType"); break;
		default: return string(""); break;
	}
}

// Method Type
string getMethodType (int typeIndex) {
	switch (typeIndex) {
		case 17: return getDecafType(typeIndex); break;
		case 18: return getDecafType(typeIndex); break;
		case 19: return string("VoidType"); break;
		default: return string(""); break;
	}
}

string getExternType (int typeIndex) {
	if(typeIndex == 17 || typeIndex == 18 || typeIndex == 19) {
		return getMethodType(typeIndex);
	} else {
		return string("StringType");
	}
}

// Get Unary Operator
string getUnaryOp (int opId) {
	switch(opId) {
		case 15: return string("UnaryMinus"); break;
		case 16: return string("Not"); break;
		default: return string(""); break;
	}
}

// Method Argument
class MethodArgumentAST : public decafAST {
	decafAST *decafASTNode;
public:
	MethodArgumentAST(decafAST *node) {
		decafASTNode = node;
	}
	~MethodArgumentAST() { delete decafASTNode; }
	string str() { return getString(decafASTNode); }
};

// String
class StringAST : public decafAST {
	string decafASTString;
public:
	StringAST(string value) { decafASTString = value; }
	~StringAST() { }
	string str() { return string("StringConstant") + "(" + decafASTString + ")"; }
	//string rawStr() { return decafASTString; }
};

class IDTypeStringAST : public decafAST {
	string decafASTString;
	int methodType;
public:
	IDTypeStringAST(string value, int typeId) { decafASTString = value; methodType = typeId; }
	~IDTypeStringAST() { }
	string str() { return decafASTString + "," + getMethodType(methodType); }
	//string rawStr() { return decafASTString; }
};

class IDTypeStringSpecialAST : public decafAST {
	decafAST *strs;
public:
	IDTypeStringSpecialAST(decafAST *node) { strs = node; }
	~IDTypeStringSpecialAST() { delete strs; }
	string str() { return string("VarDef(") + getString(strs) + ")"; }
};

class RawStringAST : public decafAST {
	string decafASTString;
public:
	RawStringAST(string value) { decafASTString = value; }
	~RawStringAST() { }
	string str() { return decafASTString; }
	//string rawStr() { return decafASTString; }
};

// Assign
class AssignAST : public decafAST {
	string identifierName;
	ExprAST *value;
	ExprAST *index;
	bool isArray;
public:
	AssignAST(string idName, ExprAST *assignedValue) { identifierName = idName; value = assignedValue; index = NULL; isArray = false; }
	AssignAST(string idName, ExprAST *dstIndex, ExprAST *assignedValue) { identifierName = idName; index = dstIndex; value = assignedValue; isArray = true; }
	~AssignAST() { identifierName = ""; delete value; if(isArray) delete index;}
	string str() {
		if(isArray) {
			return string("AssignArrayLoc(") + identifierName + "," + getString(index) + "," + getString(value) + ")";
		} else {
			return string("AssignArrayLoc(") + identifierName + "," + getString(value) + ")";
		}
	}
};



// Extern Type
class ExternType : public decafAST {
	int externType;
public:
	ExternType(int typeIndex) { externType = typeIndex; }
	~ExternType() { }
	string str() {
		return string("VarDef(") + getExternType(externType) + ")";
	}
};

// Extern
class ExternAST : public decafAST {
	string identifierName;
	int methodTypeId;
	decafStmtList *typeList;
public:
	ExternAST(string IdName, int typeId, decafStmtList *list) {
		identifierName = IdName;
		methodTypeId = typeId;
		typeList = list;
	}
	~ExternAST() {
		identifierName = "";
		delete typeList;
	}
	string str() {
		return string("ExternFunction(") + identifierName + "," + getMethodType(methodTypeId) + "," + typeList->str() + ")";
	}
};

// field size
/// TODO: Debug issue here. return "Scalar" or scalar value
class FieldSizeAST : public decafAST {
	int size;
	bool isArray;
public:
	FieldSizeAST(int sizeValue, bool array) { if(array) { size = sizeValue; isArray = array; } else { size = -1; isArray = array; } }
	~FieldSizeAST() { }
	string str() {
		if(isArray) {
			return string("Array(") + std::to_string(size) + ")";
		} else {
			return string("Scalar");
		}
	}
};

// Field_decl
class FieldDeclAST : public decafAST {
	string identifierName;
	int decafTypeId;
	bool isGlobal;
	decafAST *expr;
public:
	FieldDeclAST(string idName, int typeId, decafAST *exprNode, bool global) { identifierName = idName; decafTypeId = typeId; isGlobal = global; expr = exprNode; }
	~FieldDeclAST() { }
	string str() {
		if(isGlobal)
			return string("AssignGlobalVar(") + identifierName + "," + getDecafType(decafTypeId) + "," + getString(expr) + ")";
		else
			if (decafTypeId != -1) return string("FieldDecl(") + identifierName + "," + getDecafType(decafTypeId) + "," + getString(expr) + ")";
			else return string("FieldDecl(") + identifierName + "," + getString(expr) + ")";
	}
};

// typed symbol
class TypedSymbol : public decafAST {
	string identifierName;
	int decafTypeId;
public:
	TypedSymbol(string idName, int typeId) {
		identifierName = idName;
		decafTypeId = typeId;
	}
	~TypedSymbol() { }
	string str() {
		return string("VarDef(") + identifierName + "," + getDecafType(decafTypeId) + ")";
	}
};

class MethodBlockAST : public decafAST {
	decafAST *block;
public:
	MethodBlockAST(decafAST *node) { block = node; }
	~MethodBlockAST() { delete block; }
	string str() {
		return string("Method") + getString(block);
	}
};


// Block
class BlockAST : public decafAST {
	decafStmtList *varDeclList;
	decafStmtList *statementList;
	bool isMethod;
public:
	BlockAST(decafStmtList *varDecl, decafStmtList *stmt) {
		varDeclList = varDecl;
		statementList = stmt;
	}
	~BlockAST() { delete varDeclList; delete statementList; };
	void turnToMethod() { isMethod = true; }
	string str() {
		if(!isMethod) return string("Block(") + varDeclList->str() + "," + statementList->str() + ")";
		else return string("MethodBlock(") + varDeclList->str() + "," + statementList->str() + ")";
	}
};

// Method Decl
class MethodDeclAST : public decafAST {
	string identifierName;
	int methodTypeId;
	decafStmtList *paramList;
	decafAST *block;
public:
	MethodDeclAST(string idName, int methodType, decafStmtList *params, decafAST *blockMethod) {
		identifierName = idName;
		methodTypeId = methodType;
		paramList = params;
		block = blockMethod;
	}
	~MethodDeclAST() {
		delete paramList;
		delete block;
	}
	string str() {
		return string("Method(") + identifierName + "," + getMethodType(methodTypeId) + "," + paramList->str() + "," + block->str() + ")";
	}
};

// Break, Continue
class SimpleStatement : public decafAST {
	int typeId;
public:
	SimpleStatement(int type) {
		typeId = type;
	}
	~SimpleStatement() { }
	string str() {
		if(typeId == 20) return string("BreakStmt");
		else if(typeId == 21) return string("ContinueStmt");
		else return string("");
	}
};

class IfStmtAST : public decafAST {
	decafAST *condition;
	decafAST *ifBlock;
	decafAST *ElseBlock;
public:
	IfStmtAST(decafAST *cond, decafAST *ifBlockStmt, decafAST *elseBlockStmt) {
		condition = cond;
		ifBlock = ifBlockStmt;
		ElseBlock = elseBlockStmt;
	}
	~IfStmtAST() {
		delete ifBlock;
		delete ElseBlock;
	}
	string str() {
		return string("IfStmt(") + getString(condition) + "," + getString(ifBlock) + "," + getString(ElseBlock) + ")";
	}
};

class WhileStmt : public decafAST {
	decafAST *condition;
	decafAST *whileBlock;
public:
	WhileStmt(decafAST *cond, decafAST *whileStmt) {
		condition = cond;
		whileBlock = whileStmt;
	}
	~WhileStmt() {
		delete condition;
		delete whileBlock;
	}
	string str() {
		return string("WhileStmt(") + getString(condition) + "," + getString(whileBlock) + ")";
	}
};

class ForStmtAST : public decafAST {
	decafStmtList *preAssignList;
	decafStmtList *loopAssignList;
	decafAST *condition;
public:
	ForStmtAST(decafStmtList *pre, decafAST *cond, decafStmtList *loop) {
		preAssignList = pre;
		condition = cond;
		loopAssignList = loop;
	}
	~ForStmtAST() {
		delete preAssignList;
		delete loopAssignList;
		delete condition;
	}
	string str() {
		return string("ForStmt(") + preAssignList->str() + "," + getString(condition) + "," +loopAssignList->str() + ")";
	}
};

class ReturnStmtAST : public decafAST {
	decafAST *returnValue;
public:
	ReturnStmtAST(decafAST *returnVal) {
		returnValue = returnVal;
	}
	~ReturnStmtAST() {
		delete returnValue;
	}
	string str() {
		return string("ReturnStmt(") + getString(returnValue) + ")";
	}
};

class StatementAST : public decafAST {
	decafAST *stmtASTNode;
public:
	StatementAST(decafAST *node) { stmtASTNode = node; }

	~StatementAST() { delete stmtASTNode; }
	string str() { return getString(stmtASTNode); }
};
