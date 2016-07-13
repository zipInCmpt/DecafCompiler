
#include "decafexpr-defs.h"
#include <list>
#include <stack>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafexpr.tab.h"
#endif

using namespace std;

extern llvm::Function *gen_main_def();

class descriptor;

typedef map<string, descriptor* > DecafSymbolTable;
typedef list<DecafSymbolTable* > DecafSymbolTableList;

//DecafSymbolTable GlobalCurrentST;
DecafSymbolTableList SymbolTableList;

/// decafAST - Base class for all abstract syntax tree nodes.
/// TODO:Done

bool isDebugging = false;

class descriptor {
	string identifierName;
	int type;
	int lineNumber;
	llvm::Value *Alloca;

public:
	descriptor(string idName, int targetType, int lineNo, llvm::Value *allocai) {
		identifierName = idName;
		type = targetType;
		lineNumber = lineNo;
		Alloca = allocai;
		//cout << "Defined variable in line " << lineNumber << " : " << identifierName << endl;
	}
	~descriptor() { }
	void debug() {
		cout << "Defind variable in line " << lineNumber << " : " << identifierName << endl;
	}
	llvm::Type *getType() {

		if(type == 17) return Builder.getInt32Ty();
		if(type == 18) return Builder.getInt1Ty();
		if(type == 19) return Builder.getVoidTy();
		if(type == 20) return Builder.getInt8PtrTy();
		else return Alloca->getType();
		//return Alloca->getType();
	}
	llvm::Value *getAlloca() {
		return Alloca;
	}

	void setAlloca(llvm::Value *allocai) {
		Alloca = allocai;
	}
};

descriptor *getSymbolTable(string idName) {

	DecafSymbolTable::iterator fetchedObject;
	for(DecafSymbolTableList::iterator i = SymbolTableList.begin(); i != SymbolTableList.end(); i++) {
		DecafSymbolTable::iterator fetchedObject;
		if((fetchedObject = (*i)->find(idName)) != (*i)->end()) {
			return fetchedObject->second;
		}
	}
	return NULL;

}

void checkTable(DecafSymbolTable *table) {
	for(DecafSymbolTable::iterator i = table->begin(); i != table->end(); i++) {
		(*i).second->debug();
	}
}

class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
	virtual llvm::Value *Codegen() = 0;
	virtual void insertSymbolIntoSymbolTable() = 0;
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

template <class T>
llvm::Value *listCodegen(list<T> vec) {
	llvm::Value *val = NULL;
	for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) {
		llvm::Value *j = (*i)->Codegen();
		if (j != NULL) { val = j; }
	}
	return val;
}

/// TODO:Done
/// decafStmtList - List of Decaf statements
class decafStmtList : public decafAST {
public: 
	list<decafAST *> stmts;
	//DecafSymbolTable *currentST;
//public:
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
	llvm::Value *Codegen() {
		return listCodegen<decafAST *>(stmts);
	}
	void insertSymbolIntoSymbolTable() {
		for (list<decafAST *>::iterator i = stmts.begin(); i != stmts.end(); i++) {
			(*i)->insertSymbolIntoSymbolTable();
		}
	}
};

/// TODO:Done
// Package
class PackageAST : public decafAST {
	string Name;
	decafStmtList *FieldDeclList;
	decafStmtList *MethodDeclList;
	DecafSymbolTable *currentST;
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
	llvm::Value *Codegen() {
		SymbolTableList.push_front(currentST);
		//checkTable(currentST);
		llvm::Value *val = NULL;
		TheModule->setModuleIdentifier(llvm::StringRef(Name));
		if (NULL != FieldDeclList) {
			if(isDebugging) printf("Debug message: Generating FieldDecls...\n");
			val = FieldDeclList->Codegen();
		}
		if (NULL != MethodDeclList) {
			//printf("Debug message: Generating MethodDecls...\n");
			val = MethodDeclList->Codegen();
		}
		// Q: should we enter the class name into the symbol table?
		SymbolTableList.pop_front();
		return val;
	}
	void insertSymbolIntoSymbolTable() {
		this->currentST = new DecafSymbolTable;
		SymbolTableList.push_front(currentST);

		FieldDeclList->insertSymbolIntoSymbolTable();
		MethodDeclList->insertSymbolIntoSymbolTable();

		SymbolTableList.pop_front();
	}
};

/// TODO: Done
// Expr
class ExprAST : public decafAST {
	decafAST *decafASTNode;
public:
	ExprAST (decafAST *node) { decafASTNode = node; }
	~ExprAST() { delete decafASTNode; }
	string str() { return getString(decafASTNode); }
	llvm::Value *Codegen() {
		return decafASTNode->Codegen();
	}
	void insertSymbolIntoSymbolTable() {
		decafASTNode->insertSymbolIntoSymbolTable();
	}
};

/// TODO:Done
/// ProgramAST - the decaf program
class ProgramAST : public decafAST {
	decafStmtList *ExternList;
	PackageAST *PackageDef;
	DecafSymbolTable *currentST;
public:
	ProgramAST(decafStmtList *externs, PackageAST *c) : ExternList(externs), PackageDef(c) {}
	~ProgramAST() { 
		if (ExternList != NULL) { delete ExternList; } 
		if (PackageDef != NULL) { delete PackageDef; }
	}
	string str() { return string("Program") + "(" + getString(ExternList) + "," + getString(PackageDef) + ")"; }
	llvm::Value *Codegen() {
		if(isDebugging) printf("Debug message: Generating program...\n");
		llvm::Value *val = NULL;
		SymbolTableList.push_front(currentST);
		//checkTable(currentST);

		/*if (NULL != ExternList) {
			if(isDebugging) printf("Debug message: Generating Extern List...\n");
			val = ExternList->Codegen();
		}*/
		if (NULL != PackageDef) {
			if(isDebugging) printf("Debug message: Generating package...\n");
			val = PackageDef->Codegen();
		} else {
			throw runtime_error("no package definition in decaf program");
		}
		SymbolTableList.pop_front();
		return val;
	}
	void insertSymbolIntoSymbolTable() {
		this->currentST = new DecafSymbolTable;
		SymbolTableList.push_front(this->currentST);
		if(ExternList != NULL) ExternList->insertSymbolIntoSymbolTable();
		if(PackageDef != NULL) PackageDef->insertSymbolIntoSymbolTable();
		SymbolTableList.pop_front();
	}
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
		default: throw runtime_error("Operator not defined.");
	}
}

llvm::Value* BinaryOpExpr(int opId, llvm::Value *L, llvm::Value *R) {
	switch(opId) {
		case 0: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateAdd(L, R, "AddTmp");
		case 1: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateSub(L, R, "SubTmp");
		case 2: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateMul(L, R, "MulTmp");
		case 3: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateSDiv(L, R, "DivTmp");
		case 4: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateShl(L, R, "LShiftTmp");
		case 5: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateLShr(L, R, "RShitTmp");
		case 6: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateSRem(L, R, "RemainTmp");
		case 7: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpSLT(L, R, "LTTmp");
		case 8: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpSGT(L, R, "GTTmp");
		case 9: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpSLE(L, R, "LEQTmp");
		case 10: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpSGE(L, R, "GEQTmp");
		case 11: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpEQ(L, R, "EQTmp");
		case 12: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateICmpNE(L, R, "NEQTmp");
		case 13: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateAnd(L, R, "AndTmp");
		case 14: if(isDebugging) cout << "OpId " << opId << endl; return Builder.CreateOr(L, R, "OrTmp");
		default: if(isDebugging) cout << "OpId " << opId << endl; return NULL;
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

llvm::Value* UnaryOpExpr(int opId, llvm::Value *L) {
	switch(opId) {
		case 15: return Builder.CreateNeg(L, "NegTmp");
		case 16: return Builder.CreateNot(L, "NotTmp");
		default: return NULL;
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

llvm::Type* getLLVMType(int typeIndex) {
	switch (typeIndex) {
		case 17: return Builder.getInt32Ty();
		case 18: return Builder.getInt1Ty();
		case 19: return Builder.getVoidTy();
		case 20: return Builder.getInt8PtrTy();
		default: return NULL;
	}
}

/// TODO: Done
class BoolConstantAST : public decafAST {
	bool value;
public:
	BoolConstantAST(bool type) { value = type; };
	~BoolConstantAST() { }
	string str() { if(value) return string("BoolExpr(True)"); else return string("BoolExpr(False)"); }
	llvm::Value *Codegen() {
		if(value) return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(1, 1));
		else return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(1, 0));
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Not Done
class rvalueAST : public decafAST {
	string idName;
	bool isArray;
	decafAST *arrayIndex;
public:
	rvalueAST(string ID, bool arraytype = false) { idName = ID; isArray = arraytype; arrayIndex = NULL; }
	rvalueAST(string ID, bool arraytype, decafAST *index) { idName = ID; isArray = arraytype; arrayIndex = index;}
	~rvalueAST() { }
	string str() {
		if(!isArray) {
			return string("VariableExpr") + "(" + idName + ")";
		} else {
			return string("ArrayLocExpr") + "(" + idName + "," + getString(arrayIndex) + ")";
		}
	}
	llvm::Value *Codegen() {
		if(isDebugging) cout << "Codegen for RValue " << idName << endl;
		if(!isArray) {
			llvm::Value *fetchedVar = getSymbolTable(idName)->getAlloca();
			//if(fetchedVar) cout << "Success in RValue" << endl;
			//else cout << "Failure in RValue" << endl;
			return fetchedVar;
		} else {
			return NULL;
		};
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class NumberExprAST : public decafAST {
	int integerValue;
public:
	NumberExprAST(int value) { integerValue = value; }
	~NumberExprAST();
	string str() {
		return string("NumberExpr") + "(" + std::to_string(integerValue) + ")";
	}
	llvm::Value *Codegen() {
		return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, integerValue));
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class BoolExprAST : public decafAST {
	decafAST *boolASTNode;
public:
	BoolExprAST(decafAST *boolConstant) { boolASTNode = boolConstant; }
	~BoolExprAST() { delete boolASTNode; }
	string str() {
		return string("BoolExpr(") + getString(boolASTNode) + ")";
	}
	llvm::Value *Codegen() {
		return boolASTNode->Codegen();
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class BinaryExprAST : public decafAST {
	int binaryOperator;
	decafAST *leftValueNode;
	decafAST *rightValueNode;
public:
	BinaryExprAST(int binaryOp, decafAST *left, decafAST *right) {
		binaryOperator = binaryOp;
		leftValueNode = left;
		rightValueNode = right;
	}
	~BinaryExprAST() {
		delete leftValueNode;
		delete rightValueNode;
	}
	string str() {
		return string("BinaryExpr(") + getBinaryOp(binaryOperator) + "," + getString(leftValueNode) + "," + getString(rightValueNode) + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value *L = leftValueNode->Codegen();
		llvm::Value *R = rightValueNode->Codegen();
		if(L == 0 || R == 0) return 0;

		return BinaryOpExpr(binaryOperator, L, R);
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class UnaryExprAST : public decafAST {
	int unaryOperator;
	decafAST *opNumber;
public:
	UnaryExprAST(int unaryOp, decafAST *exp) {
		unaryOperator = unaryOp;
		opNumber = exp;
	}
	~UnaryExprAST() {
		delete opNumber;
	}
	string str() {
		return string("UnaryExpr(") + getUnaryOp(unaryOperator) + "," + getString(opNumber) + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value *opNum = opNumber->Codegen();
		if(opNum == NULL) return NULL;
		return UnaryOpExpr(unaryOperator, opNum);
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// Method_Call
/// TODO: Not Done
class MethodCallAST : public decafAST {
	string identifierName;
	decafStmtList *argumentList;
public:
	MethodCallAST(string idName, decafStmtList *args) { identifierName = idName; argumentList = args; }
	~MethodCallAST() { identifierName = ""; delete argumentList; }
	string str() { return string("MethodCall(") + identifierName + "," + argumentList->str() + ")"; }
	llvm::Value *Codegen() {
		if(isDebugging) {
			cout << "Debug message: Generating method call... Calling " << identifierName << endl;
		}

		llvm::Function *TheFunction = TheModule->getFunction(identifierName);
		//return NULL;
		if(TheFunction==NULL) {
			throw runtime_error("Undefined function is called.");
			// return NULL;
		} else {
			if(isDebugging) cout << "ArgumentListSize = " << argumentList->stmts.size() << endl;
			if(argumentList->stmts.size() != TheFunction->arg_size())
				throw runtime_error("Incorrect # arguments passed.");

			std::vector<llvm::Value *> args;
			//llvm::ArgumentListType* func_args=TheFunction->getArgumentList();
			for (list<decafAST *>::iterator i = argumentList->stmts.begin()/*,
				llvm::ArgumentListType::iterator j = func_args->begin()*/;
				i != argumentList->stmts.end()/*, j!=func_args->end()*/;
				++i/*, ++*/) {
				if(isDebugging) cout << "Argument Type: ";
				llvm::Value *tempCodeGen = (*i)->Codegen();
				if(isDebugging) cout << "(finishing codegen for this argument) ";
				if(isDebugging) {
					if(tempCodeGen->getType()==getLLVMType(17)) cout<< "int type" <<endl;//int
					else if(tempCodeGen->getType()==getLLVMType(18)) cout<< "bool type" <<endl;//bool
					else if(tempCodeGen->getType()==getLLVMType(19)) cout<< "void type" <<endl;//void
					else if(tempCodeGen->getType()==getLLVMType(20)) cout<< "string type" <<endl;//string
				}
				if(/*(*j)==getLLVMType(17) && */tempCodeGen->getType()==getLLVMType(18))
					tempCodeGen= Builder.CreateZExt(tempCodeGen, Builder.getInt32Ty(), "zexttmp");
				//if(tempCodeGen) cout << "Success in MethodCall?" << endl;
				//else cout << "Failure in MethodCall" << endl;
				//cout << "Matched Sequence: " << (*i)->str() << endl;
				if(tempCodeGen==NULL) {
					if(isDebugging) cout << "NULL return." << endl;
					return NULL;
				}
				else args.push_back(tempCodeGen);
				//cout << "Matched Sequence: " << (*i)->str() << endl;
			}


			bool isVoid = TheFunction->getReturnType()->isVoidTy();
			llvm::Value *val = Builder.CreateCall(
			    TheFunction,
			    args,
			    isVoid ? "" : "calltmp"
			);
			//cout << "here#" << argumentList->stmts.size() << endl;
			if(isDebugging) cout << "Method Call done..." << endl;
			return val;
		}
	}
	void insertSymbolIntoSymbolTable() {

	}
};

string getExternType (int typeIndex) {
	if(typeIndex == 17 || typeIndex == 18 || typeIndex == 19) {
		return getMethodType(typeIndex);
	} else {
		return string("StringType");
	}
}

// Method Argument
/// TODO: Not Done
class MethodArgumentAST : public decafAST {
	decafAST *decafASTNode;
public:
	MethodArgumentAST(decafAST *node) {
		decafASTNode = node;
	}
	~MethodArgumentAST() { delete decafASTNode; }
	string str() { return getString(decafASTNode); }
	llvm::Value *Codegen() {
		return decafASTNode->Codegen();
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// String
/// TODO: Done
class StringAST : public decafAST {
	string decafASTString;
public:
	StringAST(string value) { decafASTString = value; }
	~StringAST() { }
	string str() { return string("StringConstant") + "(" + decafASTString + ")"; }
	//string rawStr() { return decafASTString; }
	llvm::Value *Codegen() {
		llvm::GlobalVariable *GlobalString = Builder.CreateGlobalString(decafASTString, "globalstring");
		llvm::Value *stringConst = Builder.CreateConstGEP2_32(GlobalString->getValueType(), GlobalString, 0, 0, "cast");
		return stringConst;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class IDTypeStringAST : public decafAST {
	string decafASTString;
	int methodType;
	int linepos;
public:
	IDTypeStringAST(string value, int typeId, int pos) { decafASTString = value; methodType = typeId; linepos = pos; }
	~IDTypeStringAST() { }
	string str() { return decafASTString + "," + getMethodType(methodType); }
	string getName() { return decafASTString; }
	int getType() { return methodType; }
	//string rawStr() { return decafASTString; }
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {
		llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(methodType), nullptr, decafASTString);
		descriptor *newDecp = new descriptor(decafASTString, methodType, linepos, Alloca);
		SymbolTableList.front()->insert(std::pair<string, descriptor* >(decafASTString, newDecp));
	}
};

/// TODO: Done
class IDTypeStringSpecialAST : public decafAST {
	IDTypeStringAST *strs;
public:
	IDTypeStringSpecialAST(IDTypeStringAST *node) { strs = node; }
	~IDTypeStringSpecialAST() { delete strs; }
	string str() { return string("VarDef(") + getString(strs) + ")"; }
	string getName() { return strs->getName(); }
	int getTypeId() { return strs->getType(); }
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {
		strs->insertSymbolIntoSymbolTable();
	}
};

/// TODO: Done
class RawStringAST : public decafAST {
	string decafASTString;
public:
	RawStringAST(string value) { decafASTString = value; }
	~RawStringAST() { }
	string str() { return decafASTString; }
	//string rawStr() { return decafASTString; }
	llvm::Value *Codegen() {
		llvm::GlobalVariable *GlobalString = Builder.CreateGlobalString(decafASTString, "globalstring");
		llvm::Value *stringConst = Builder.CreateConstGEP2_32(GlobalString->getValueType(), GlobalString, 0, 0, "cast");
		return stringConst;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// Assign
/// TODO: Not Done
class AssignAST : public decafAST {
	string identifierName;
	decafAST *value;
	decafAST *index;
	bool isArray;
public:
	AssignAST(string idName, decafAST *assignedValue) { identifierName = idName; value = assignedValue; index = NULL; isArray = false; }
	AssignAST(string idName, decafAST *dstIndex, decafAST *assignedValue) { identifierName = idName; index = dstIndex; value = assignedValue; isArray = true; }
	~AssignAST() { delete value; if(isArray) delete index;}
	string str() {
		if(isArray) {
			return string("AssignArrayLoc(") + identifierName + "," + getString(index) + "," + getString(value) + ")";
		} else {
			return string("AssignVar(") + identifierName + "," + getString(value) + ")";
		}
	}
	llvm::Value *Codegen() {
		if(!isArray) {
			descriptor *fetchedVarDescriptor = getSymbolTable(identifierName);

			if(fetchedVarDescriptor) {
				if(isDebugging) fetchedVarDescriptor->debug();
				llvm::Type *AllocaType = fetchedVarDescriptor->getType();
				llvm::Value *temp = value->Codegen();
				const llvm::PointerType *ptrTy = temp->getType()->getPointerTo();

				if(ptrTy == AllocaType) {
					cout << "Codegen for Assign to " << identifierName << endl;
					llvm::Value *val = Builder.CreateStore(temp, (llvm::AllocaInst *)fetchedVarDescriptor->getAlloca());
					return val;
				} else {
					return NULL;
				}
			} else {
				return NULL;
			}
		} else
			return NULL;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// Extern Type
/// TODO: Done
class ExternType : public decafAST {
public:
	int externType;
//public:
	ExternType(int typeIndex) { externType = typeIndex; }
	~ExternType() { }
	string str() {
		return string("VarDef(") + getExternType(externType) + ")";
	}
	llvm::Value *Codegen() {
		//return getLLVMType(externType);
		return NULL;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// Extern
/// TODO: Not Done
class ExternAST : public decafAST {
	string identifierName;
	int methodTypeId;
	decafStmtList *typeList;
	int linepos;
public:
	ExternAST(string IdName, int typeId, decafStmtList *list, int pos) {
		identifierName = IdName;
		methodTypeId = typeId;
		typeList = list;
		linepos = pos;
	}
	~ExternAST() {
		identifierName = "";
		delete typeList;
	}
	string str() {
		return string("ExternFunction(") + identifierName + "," + getMethodType(methodTypeId) + "," + typeList->str() + ")";
	}
	llvm::Value *Codegen() {

		/*std::vector<llvm::Type*> args;
		printf("Debug message: Generating extern function...\n");
		for (list<decafAST *>::iterator i = typeList->stmts.begin(); i != typeList->stmts.end(); i++) {
			//printf("%d\n", ((ExternType *)(*i))->externType );
			printf("%d\n", ((ExternType *) (*i))->externType);
			args.push_back(getLLVMType(((ExternType *) (*i))->externType));
		}
		llvm::Type *returnTy=getLLVMType(methodTypeId);
		llvm::Function *func = llvm::Function::Create(
		    llvm::FunctionType::get(returnTy, args, false),
		    llvm::Function::ExternalLinkage,
		    identifierName,
		    TheModule
		);

		return func;*/
		return NULL;
	}
	void insertSymbolIntoSymbolTable() {

		std::vector<llvm::Type*> args;
		if(isDebugging) printf("Debug message: Generating extern function...\nArg Type: ");
		for (list<decafAST *>::iterator i = typeList->stmts.begin(); i != typeList->stmts.end(); i++) {
			//printf("%d\n", ((ExternType *)(*i))->externType );
			if(isDebugging) printf("%d ", ((ExternType *) (*i))->externType);
			args.push_back(getLLVMType(((ExternType *) (*i))->externType));
		}
		if(isDebugging) printf("\n");
		llvm::Type *returnTy=getLLVMType(methodTypeId);
		llvm::Function *func = llvm::Function::Create(
		    llvm::FunctionType::get(returnTy, args, false),
		    llvm::Function::ExternalLinkage,
		    identifierName,
		    TheModule
		);

		descriptor *newDescp = new descriptor(identifierName, methodTypeId, linepos, (llvm::Value *)func);
		SymbolTableList.front()->insert(std::pair<string, descriptor* >(identifierName, newDescp));
	}
};

// field size
/// TODO: Not Done
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
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

// Field_decl
/// TODO: Not Done
class FieldDeclAST : public decafAST {
	string identifierName;
	int decafTypeId;
	bool isGlobal;
	decafAST *expr;
	int linepos;
public:
	FieldDeclAST(string idName, int typeId, decafAST *exprNode, bool global, int pos) { identifierName = idName; decafTypeId = typeId; isGlobal = global; expr = exprNode; linepos = pos; }
	~FieldDeclAST() { }
	string str() {
		if(isGlobal)
			return string("AssignGlobalVar(") + identifierName + "," + getDecafType(decafTypeId) + "," + getString(expr) + ")";
		else
			if (decafTypeId != -1) return string("FieldDecl(") + identifierName + "," + getDecafType(decafTypeId) + "," + getString(expr) + ")";
			else return string("FieldDecl(") + identifierName + "," + getString(expr) + ")";
	}
	llvm::Value *Codegen() {
		if(isDebugging) cout << "FieldDecl Codegen In progress..." << endl;
		llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(decafTypeId), nullptr, identifierName);
		descriptor *temp = getSymbolTable(identifierName);
		temp->setAlloca(Alloca);
		if(isDebugging) cout << "Finish FieldDecl Codegen In progress..." << endl;
		return Alloca;
	}
	void insertSymbolIntoSymbolTable() {
		//llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(decafTypeId), nullptr, identifierName);
		descriptor *newDescp = new descriptor(identifierName, decafTypeId, linepos, NULL);
		//SymbolTableList.front()->insert(std::pair<string, descriptor* >(identifierName, newDescp));
		SymbolTableList.front()->insert(std::pair<string, descriptor* >(identifierName, newDescp));
	}
};

// typed symbol
/// TODO: Not Done
class TypedSymbol : public decafAST {
	string identifierName;
	int decafTypeId;
	int linepos;
public:
	TypedSymbol(string idName, int typeId, int pos) {
		identifierName = idName;
		decafTypeId = typeId;
		linepos = pos;
	}
	~TypedSymbol() { }
	string str() {
		return string("VarDef(") + identifierName + "," + getDecafType(decafTypeId) + ")";
	}
	llvm::Value *Codegen() {

		if(isDebugging) cout << "Codegen for Var definition(Typed Symbol)..." << endl;

		llvm::Value *val = NULL;
		//llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(decafTypeId), nullptr, identifierName);
		descriptor *temp = getSymbolTable(identifierName);
		//temp->setAlloca(Alloca);
		// Zero Initialization
		llvm::Value *tempV;
		if(decafTypeId == 17) tempV = Builder.getInt32(0);
		else if(decafTypeId == 19) tempV = Builder.getInt1(0);

		llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(decafTypeId), nullptr, identifierName);

		//val = Builder.CreateLoad(temp->getAlloca(), identifierName.c_str());
		temp->setAlloca(Alloca);

		val = Builder.CreateStore(tempV, (llvm::AllocaInst *)temp->getAlloca());

		if(isDebugging) cout << "Finish Codegen for Var definition(Typed Symbol)..." << endl;
		return val;

		//return Alloca;
	}
	void insertSymbolIntoSymbolTable() {
		//llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType(decafTypeId), nullptr, identifierName);
		descriptor *newDescp = new descriptor(identifierName, decafTypeId, linepos, NULL);
		SymbolTableList.front()->insert(std::pair<string, descriptor* >(identifierName, newDescp));
	}
};

/// TODO: Not Done
class MethodBlockAST : public decafAST {
	decafAST *block;
public:
	MethodBlockAST(decafAST *node) { block = node; }
	~MethodBlockAST() { delete block; }
	string str() {
		return string("Method") + getString(block);
	}
	llvm::Value *Codegen() {
		if(block != NULL) return block->Codegen();
		else return NULL;
	}
	void insertSymbolIntoSymbolTable() {
		if (block != NULL)
			block->insertSymbolIntoSymbolTable();
	}
};


// Block
/// TODO: Not Done
class BlockAST : public decafAST {
	decafStmtList *varDeclList;
	decafStmtList *statementList;
	DecafSymbolTable *currentST;
	bool isMethod;
public:
	BlockAST(decafStmtList *varDecl, decafStmtList *stmt) {
		varDeclList = varDecl;
		statementList = stmt;
		currentST = NULL;
		isMethod = false;
	}
	~BlockAST() { delete varDeclList; delete statementList; };
	void turnToMethod() { isMethod = true; }
	string str() {
		if(!isMethod) return string("Block(") + varDeclList->str() + "," + statementList->str() + ")";
		else return string("MethodBlock(") + varDeclList->str() + "," + statementList->str() + ")";
	}
	llvm::Value *Codegen() {

		if(isDebugging) cout << "Block CodeGen......" << endl;
		llvm::Value *val = NULL;

		if(!isMethod) {
			SymbolTableList.push_front(currentST);
			//if(!isMethod) checkTable(currentST);
			if(varDeclList != NULL) val = varDeclList->Codegen();
			if(statementList != NULL) val = statementList->Codegen();
			SymbolTableList.pop_front();
		} else {

			if(varDeclList != NULL) val = varDeclList->Codegen();
			if(statementList != NULL) val = statementList->Codegen();
		}

		if(isDebugging) cout << "Finished Block CodeGen......" << endl;

		return val;
	}

	void insertSymbolIntoSymbolTable() {
		if(isDebugging) printf("Inserting block into symbol table...\n");
		if(!isMethod) {
			this->currentST = new DecafSymbolTable;
			SymbolTableList.push_front(this->currentST);

			if(varDeclList != NULL) varDeclList->insertSymbolIntoSymbolTable();
			if(statementList != NULL) statementList->insertSymbolIntoSymbolTable();

			SymbolTableList.pop_front();
		} else {
			varDeclList->insertSymbolIntoSymbolTable();
			statementList->insertSymbolIntoSymbolTable();
		}
	}
};

// Break, Continue
/// TODO: Not Done - Not Needed
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
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done - Not Needed
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
	llvm::Value *Codegen() {
/*
		llvm::Value *ConditionCode = condition->Codegen();
		if(!ConditionCode)
			return NULL;

		ConditionCode = Builder.CreateFCmpONE(ConditionCode, llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat(0.0)), "IfCond");
		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

		llvm::BasicBlock *ThenBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "Then", TheFunction);
		llvm::BasicBlock *EBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "Else");
		llvm::BasicBlock *MergeBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "IfCont");
		Builder.CreateCondBr(ConditionCode, ThenBlock, EBlock);

		Builder.SetInsertPoint(ThenBlock);

		llvm::Value *ThenCode = ifBlock->Codegen();
		if(!ThenCode) return NULL;
		Builder.CreateBr(MergeBlock);
		ThenBlock = Builder.GetInsertBlock();
		TheFunction->getBasicBlockList().push_back(EBlock);
		Builder.SetInsertPoint(EBlock);

		llvm::Value *ElseCode = ElseBlock->Codegen();
		if(!ElseCode) return NULL;
		Builder.CreateBr(MergeBlock);
		EBlock = Builder.GetInsertBlock();
		TheFunction->getBasicBlockList().push_back(MergeBlock);
		Builder.SetInsertPoint(MergeBlock);

		llvm::PHINode *node = Builder.CreatePHI(llvm::Type::getDoubleTy(llvm::getGlobalContext()), 2, "IfTmp");
		node->addIncoming(ThenCode, ThenBlock);
		node->addIncoming(ElseCode, EBlock);

		return node;
		*/
		return NULL;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Not Done - Not Needed
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
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Not Done - Not Needed
class ForStmtAST : public decafAST {
	decafStmtList *preAssignList;
	decafStmtList *loopAssignList;
	decafAST *condition;
	decafAST *Block;
public:
	ForStmtAST(decafStmtList *pre, decafAST *cond, decafStmtList *loop, decafAST *blockNode) {
		preAssignList = pre;
		condition = cond;
		loopAssignList = loop;
		Block = blockNode;
	}
	~ForStmtAST() {
		delete preAssignList;
		delete loopAssignList;
		delete condition;
		delete Block;
	}
	string str() {
		return string("ForStmt(") + preAssignList->str() + "," + getString(condition) + "," +loopAssignList->str() + "," + getString(Block) + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Not Done Return
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
	llvm::Value *Codegen() {
		if(returnValue != NULL)
			return Builder.CreateRet(returnValue->Codegen());
		else return NULL;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Done
class ConstantAST : public decafAST {
	int constantValue;
public:
	ConstantAST(int value) { constantValue = value; }
	~ConstantAST() { }
	string str() { return string("NumberExpr(") + std::to_string(constantValue) + ")"; }
	llvm::Value *Codegen() {
		if(isDebugging) cout << "Starting NumberExpr Codegen" << endl;
		llvm::Value *codegen = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, constantValue));
		if(isDebugging) cout << "Finished NumberExpr Codegen" << endl;
		return codegen;
	}
	void insertSymbolIntoSymbolTable() {

	}
};

/// TODO: Not Done
class StatementAST : public decafAST {
	decafAST *stmtASTNode;
public:
	StatementAST(decafAST *node) { stmtASTNode = node; }

	~StatementAST() { delete stmtASTNode; }
	string str() { return getString(stmtASTNode); }
	llvm::Value *Codegen() {
		if(stmtASTNode != NULL) return stmtASTNode->Codegen();
		else return NULL;
	}
	void insertSymbolIntoSymbolTable() {
		stmtASTNode->insertSymbolIntoSymbolTable();
	}
};

/// TODO: Done
class IDTypeList : public decafAST {
	list<IDTypeStringSpecialAST* > stmts;
public:
	IDTypeList() {}
	~IDTypeList() {
		for (list<IDTypeStringSpecialAST* >::iterator i = stmts.begin(); i != stmts.end(); i++) {
			delete *i;
		}
	}
	int size() { return stmts.size(); }
	void push_front(IDTypeStringSpecialAST *e) { stmts.push_front(e); }
	void push_back(IDTypeStringSpecialAST *e) { stmts.push_back(e); }
	string pop_front() { string value = stmts.back()->str(); stmts.pop_back(); return value; }

	string str() { return commaList<class IDTypeStringSpecialAST *>(stmts); }

	vector<llvm::Type* > getTypeList() {

		vector<llvm::Type* > args;

		for (list<IDTypeStringSpecialAST* >::iterator i = stmts.begin(); i != stmts.end(); i++) {
			args.push_back(getLLVMType((*i)->getTypeId()));
		}
		return args;
	};

	llvm::Value *Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
	void insertSymbolIntoSymbolTable() {
		for (list<IDTypeStringSpecialAST* >::iterator i = stmts.begin(); i != stmts.end(); i++) {
			if((*i) != NULL) (*i)->insertSymbolIntoSymbolTable();
		}
	}
};

// Method Decl
/// TODO: Not Done

class MethodDeclHeadAST : public decafAST {
	string identifierName;
	int methodTypeId;
	IDTypeList *paramList;
	int startpos;
public:
	MethodDeclHeadAST(string idName, int methodType, IDTypeList *params, int linepos) {
		identifierName = idName;
		methodTypeId = methodType;
		paramList = params;
		startpos = linepos;
	}
	~MethodDeclHeadAST() {
		delete paramList;
	}
	string str() {
		return identifierName;
		//return string("Method(") + identifierName + "," + getMethodType(methodTypeId) + "," + paramList->str()+ "," ; //+ block->str() + ")";
	}
	llvm::Value *Codegen() {
		/*cout << "Generating MethodDecl Heads..." << identifierName << endl;
		llvm::Type *returnType = getLLVMType(methodTypeId);
		// get the types for every variables
		vector<llvm::Type *> args = paramList->getTypeList();

		llvm::Function *func = llvm::Function::Create(
				llvm::FunctionType::get(returnType, args, false),
				llvm::Function::ExternalLinkage,
				identifierName,
				TheModule
		);

		return func;*/
		return NULL;
	}
	void insertSymbolIntoSymbolTable() {
		// insert the argument list into the function symbol table
		paramList->insertSymbolIntoSymbolTable();
	}
	llvm::Function* insertMethodDeclIntoParentSymbolTable() {
		if(isDebugging) printf("Inserting method decl into symbol table...\n");

		llvm::Type *returnType = getLLVMType(methodTypeId);
		// get the types for every variables
		vector<llvm::Type *> args = paramList->getTypeList();

		llvm::Function *func = llvm::Function::Create(
				llvm::FunctionType::get(returnType, args, false),
				llvm::Function::ExternalLinkage,
				identifierName,
				TheModule
		);

		descriptor *newDesp = new descriptor(identifierName, methodTypeId, startpos, (llvm::Value *)func);
		SymbolTableList.front()->insert(std::pair<string, descriptor* >(identifierName, newDesp));
		return func;
	}

	int getType() {
		return methodTypeId;
	}
};

class MethodDeclAST : public decafAST {
	decafAST *head;
	decafAST *block;
	DecafSymbolTable *currentST;
	llvm::Function *func;
public:
	MethodDeclAST(decafAST *headMethod, decafAST *blockMethod) {
		head = headMethod;
		block = blockMethod;
	}
	~MethodDeclAST() {
		delete head;
		delete block;
	}
	string str() {
		return head->str() + block->str() + ")";
	}
	llvm::Value *Codegen() {
		SymbolTableList.push_front(currentST);

		//checkTable(currentST);
		if(isDebugging) printf("Debug message: Generating MethodDecl...\n");

		llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", func);
		// Symbol table
		Builder.SetInsertPoint(BB);

		if(block != NULL) {
			if(isDebugging) cout << "Method Block CodeGen..." << endl;
			block->Codegen();
			if(isDebugging) cout << "Finish Method Block CodeGen..." << endl;
		}

		MethodDeclHeadAST *tempHead = (MethodDeclHeadAST *)head;
		llvm::Value *typedefault;
		switch(tempHead->getType()) {
			case 17: Builder.CreateRet(llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, 0)));; break;
			//case 18: Builder.CreateRet(Builder.get()); break;
			case 19: Builder.CreateRet((llvm::Value *)Builder.getVoidTy()); break;
			//case 20: typedefault = Builder.getInt8PtrTy(); break;
		}

		//Builder.CreateRet(typedefault);

		SymbolTableList.pop_front();

		//verifyFunction(*func);

		if(isDebugging) cout << "Finish Method CodeGen..." << endl;

		return func;
	}
	void insertSymbolIntoSymbolTable() {

		MethodDeclHeadAST * headAST = ((MethodDeclHeadAST *)head);
		MethodBlockAST * blockAST = ((MethodBlockAST *)block);

		func = headAST->insertMethodDeclIntoParentSymbolTable();

		this->currentST = new DecafSymbolTable;
		SymbolTableList.push_front(this->currentST);

		headAST ->insertSymbolIntoSymbolTable();
		blockAST->insertSymbolIntoSymbolTable();

		SymbolTableList.pop_front();
		
	}
};

