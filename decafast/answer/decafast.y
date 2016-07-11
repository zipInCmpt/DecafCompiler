%{
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <list>
#include "decafast-defs.h"

int yylex(void);
int yyerror(char *); 

// print AST?
bool printAST = true;

#include "decafast.cc"

using namespace std;

%}

%union{
    class decafAST *ast;
    std::string *sval;
    int numericalValue;
    bool boolValue;
    class decafStmtList *list;
    class IDTypeList *IDList;
    class IDTypeStringSpecialAST *IDType;
    //char* sval;
 }

%token T_PACKAGE
%token T_LCB
%token T_RCB
%token <sval> T_ID
%token T_AND
%token T_ASSIGN
%token T_BOOLTYPE
%token T_BREAK
%token <numericalValue> T_CHARCONSTANT
%token T_COMMA
%token T_CONTINUE
%token T_DIV
%token T_DOT
%token T_ELSE
%token T_EQ
%token T_EXTERN
%token T_FALSE
%token T_FOR
%token T_FUNC
%token T_GEQ
%token T_GT
%token T_IF
%token <numericalValue> T_INTCONSTANT
%token T_INTTYPE
%token T_LEFTSHIFT
%token T_LEQ
%token T_LPAREN
%token T_LSB
%token T_LT
%token T_MINUS
%token T_MOD
%token T_MULT
%token T_NEQ
%token T_NOT
%token T_NULL
%token T_OR
%token T_PLUS
%token T_RETURN
%token T_RIGHTSHIFT
%token T_RPAREN
%token T_RSB
%token T_SEMICOLON
%token <sval> T_STRINGCONSTANT
%token T_STRINGTYPE
%token T_TRUE
%token T_VAR
%token T_VOID
%token T_WHILE
%token T_WHITESPACE

%right T_ASSIGN
%left T_OR
%left T_AND
%left T_EQ T_NEQ T_LT T_GT T_LEQ T_GEQ
%left T_PLUS T_MINUS
%left T_MULT T_DIV T_MOD T_LEFTSHIFT T_RIGHTSHIFT
%left T_NOT
%left T_UMINUS

%type <ast> Binarys Constant Assign decafpackage ExternDefn statement MethodCall MethodArg Expr BoolConstant If Block Return ExternType MethodDecl MethodDeclHead MethodBlock
%type <numericalValue> Type MethodType
%type <list> MethodArgs ExternTypes Assigns VarDecl VarDecls statements FieldDecls extern_list FieldDecl Identifiers MethodDecls
%type <sval> Identifier
%type <IDList> IdentifierTypes
%type <IDType> IdentifierType
%%
/// TODO: Finished
start: program

/// TODO: Finished
program: extern_list decafpackage
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
		if (printAST) {
			cout << getString(prog) << endl;
		}
        delete prog;
    }
    |
{
    exit(EXIT_FAILURE);
}
    ;

/// TODO: Finished
extern_list:  ExternDefn extern_list
        {
            $2->push_front($1);
            $$ = $2;
        }
           |  ExternDefn
        {
            decafStmtList *externList = new decafStmtList();
            externList->push_front($1);
            $$ = externList;
        }
           |

        { decafStmtList *slist = new decafStmtList(); $$ = slist; }
    ;

/// TODO: Finished
decafpackage: T_PACKAGE T_ID T_LCB T_RCB
    { $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList());  delete $2; }
            | T_PACKAGE T_ID T_LCB FieldDecls MethodDecls T_RCB
        { $$ = new PackageAST(*$2, $4, $5);  delete $2; }
    | T_PACKAGE { exit(EXIT_FAILURE); }
    | T_PACKAGE T_ID { exit(EXIT_FAILURE); }

    ;

/// TODO: Finished
ExternDefn: T_EXTERN T_FUNC T_ID T_LPAREN ExternTypes T_RPAREN MethodType T_SEMICOLON
            {
                ExternAST *node = new ExternAST(*$3, $7, $5);
                $$ = node;
            }
          ;


/// TODO: Finished
FieldDecl: T_VAR Identifiers Type T_SEMICOLON
         {
            decafStmtList *fieldDeclList = new decafStmtList();
            FieldSizeAST *size = new FieldSizeAST(-1, false);

            while($2->size() > 0) {
                   string name = $2->pop_front();
                   FieldDeclAST *fieldNode = new FieldDeclAST(name, $3, size, false);
                   fieldDeclList->push_front(fieldNode);
                   //cout << fieldNode->str() << endl;
                   //delete fieldNode;
            }
            //FieldDeclAST *node = new FieldDeclAST(*$2, $3, exprNode, false);
            $$ = fieldDeclList;
         }
        | T_VAR IdentifierType T_SEMICOLON
        {
                //cout << "hree" << endl;
                decafStmtList *fieldDeclList = new decafStmtList();
                FieldSizeAST *size = new FieldSizeAST(-1, false);

                FieldDeclAST *fieldNode = new FieldDeclAST($2->getName(), $2->getTypeId(), size, false);
                fieldDeclList->push_front(fieldNode);
                $$ = fieldDeclList;
        }
         | T_VAR Identifiers T_LSB T_INTCONSTANT T_RSB Type T_SEMICOLON
        {
            FieldSizeAST *size = new FieldSizeAST($4, true);
            decafStmtList *fieldDeclList = new decafStmtList();

            while($2->size() > 0) {
                string name = $2->pop_front();
                FieldDeclAST *fieldNode = new FieldDeclAST(name, $6, size, false);
                fieldDeclList->push_front(fieldNode);
            }

            $$ = fieldDeclList;
        }
        | T_VAR IdentifierType T_ASSIGN Constant T_SEMICOLON
        {
                decafStmtList *fieldDeclList = new decafStmtList();
                FieldDeclAST *node = new FieldDeclAST($2->getName(), $2->getTypeId(), $4, true);
                fieldDeclList->push_front(node);
                $$ = fieldDeclList;
        }
        ;

/// TODO: Finished
FieldDecls: FieldDecl FieldDecls
        {
                $2->push_front($1);
                $$ = $2;
        };
          | FieldDecl
{
    decafStmtList *list = new decafStmtList();
    list->push_front($1);
    $$ = list;
}
        |
{
    decafStmtList *list = new decafStmtList();
    $$ = list;
}
          ;

/// TODO: Finished
/// Modification: Testing
MethodDecl: MethodDeclHead MethodBlock
        {
            MethodDeclAST *node = new MethodDeclAST($1,$2);
            $$ = node;
        }
        ;

MethodDeclHead: T_FUNC T_ID T_LPAREN IdentifierTypes T_RPAREN MethodType
        {
            MethodDeclHeadAST *node=new MethodDeclHeadAST(*$2, $6, $4);
            $$ = node;
        }
        | T_FUNC T_ID T_LPAREN T_RPAREN MethodType
        {
            MethodDeclHeadAST *node=new MethodDeclHeadAST(*$2, $5, new IDTypeList());
            $$ = node;
        }
        ;

/// TODO: Finished
MethodDecls: MethodDecl MethodDecls
            {
                $2->push_front($1);
                $$ = $2;
            }
           | MethodDecl
            {
                decafStmtList *list = new decafStmtList();
                list->push_front($1);
                $$ = list;
            }
            |
            {
                decafStmtList *list = new decafStmtList();
                $$ = list;
            }
            ;

/// TODO: Finished
Identifiers: Identifier T_COMMA Identifiers
        {
            RawStringAST *str = new RawStringAST(*$1);
            //cout << "here " << str->str() << endl;
            $3->push_front(str);
            $$ = $3;
        }
| Identifier
        {
            decafStmtList *idList = new decafStmtList();
            RawStringAST *str = new RawStringAST(*$1);
            //cout << "here " << str->str() << endl;
            idList->push_front(str);
            $$ = idList;
        }
;

Identifier: T_ID { $$ = $1; };

IdentifierType: T_ID Type
{
    //cout << "Here" << endl;
    IDTypeStringAST *nnode = new IDTypeStringAST(*$1, $2);
    IDTypeStringSpecialAST *node = new IDTypeStringSpecialAST(nnode);
    $$ = node;
}
;

IdentifierTypes: IdentifierType T_COMMA IdentifierTypes
        {
                IDTypeStringSpecialAST *sss = new IDTypeStringSpecialAST(*$1);
                $3->push_front(sss);
                $$ = $3;
        }
        | IdentifierType
        {
            IDTypeList *list = new IDTypeList();
            IDTypeStringSpecialAST *sss = new IDTypeStringSpecialAST(*$1);
            list->push_front(sss);
            $$ = list;
        }
        |
        {
            $$ = new IDTypeList();
        }
        ;

MethodBlock: Block
        {
            MethodBlockAST *node = new MethodBlockAST($1);
            $$ = node;
        }
        ;

/// TODO: Finished
ExternType: T_STRINGTYPE { ExternType *type = new ExternType(0); $$ = type; }
| Type { ExternType *type = new ExternType($1); $$ = type; }
;

/// TODO: Finished
ExternTypes: ExternType T_COMMA ExternTypes
        {
            $3->push_front((decafAST *)$1);
            $$ = $3;
        }
| ExternType
        {
            decafStmtList *externTypeList = new decafStmtList();
            externTypeList->push_front((decafAST *) $1);
            $$ = externTypeList;
            //delete $1;
        }
|
{
    $$ = new decafStmtList();
}
;

/// TODO: Finished
MethodType: T_VOID { $$ = 19; }
| Type { $$ = $1; }
;

/// TODO: Finished
Type: T_INTTYPE { $$ = 17; }
| T_BOOLTYPE { $$ = 18; }
;

/// TODO: Finished
BoolConstant: T_TRUE { BoolConstantAST *node = new BoolConstantAST(true); $$ = node; }
| T_FALSE { BoolConstantAST *node = new BoolConstantAST(false); $$ = node; }
;

/// TODO: Finished
Constant: T_INTCONSTANT
{
    ConstantAST *node = new ConstantAST($1);
    $$ = node;
}
| T_CHARCONSTANT
{
    ConstantAST *node = new ConstantAST($1);
    $$ = node;
}
;

/// TODO: Finished
VarDecl: T_VAR Identifiers Type T_SEMICOLON
{
    decafStmtList *list = new decafStmtList();

    while($2->size() > 0) {
        string name = $2->pop_front();
        TypedSymbol *newNode = new TypedSymbol(name, $3);
        list->push_front(newNode);
    }

    $$ = list;

};

/// TODO: Finished
VarDecls: VarDecl VarDecls
{
    $2->push_front($1);
    $$ = $2;
}
| VarDecl
{
    decafStmtList *list = new decafStmtList();
    list->push_front($1);
    $$ = list;
}
|
{
    $$ = new decafStmtList();
}
;

/// TODO: Finished
Block: T_LCB VarDecls statements T_RCB
        {
                BlockAST *node = new BlockAST($2, $3);
                $$ = node;
        }
    | T_LCB T_RCB
        {
                BlockAST *node = new BlockAST(new decafStmtList(), new decafStmtList());
                $$ = node;
        }

     ;

/// TODO: Finished
statement: T_BREAK T_SEMICOLON
        {
                SimpleStatement *stmt = new SimpleStatement(20);
                StatementAST *node = new StatementAST(stmt);
                $$ = node;
        }
| T_CONTINUE T_SEMICOLON
        {
                SimpleStatement *stmt = new SimpleStatement(21);
                StatementAST *node = new StatementAST(stmt);
                $$ = node;
        }
| Return
        {
                StatementAST *node = new StatementAST($1); $$ = node;
        }
| T_FOR T_LPAREN Assigns T_SEMICOLON Expr T_SEMICOLON Assigns T_RPAREN Block
        {
                /// TODO: Finish after figure out the Block
                ForStmtAST *forStmt = new ForStmtAST($3, $5, $7, $9);
                $$ = forStmt;
        }
| T_WHILE T_LPAREN Expr T_RPAREN Block
        {
                WhileStmt *whileStmt = new WhileStmt($3, $5);
                StatementAST *node = new StatementAST(whileStmt);
                $$ = node;
        }
| If
        {
                StatementAST *node = new StatementAST($1);
                $$ = node;
        }
| Assign T_SEMICOLON
        {
                StatementAST *node = new StatementAST($1);
                $$ = node;
        }
| Block
        {
                StatementAST *node = new StatementAST($1); $$ = node;
        }
| MethodCall T_SEMICOLON
        {
                StatementAST *node = new StatementAST($1); $$ = node;
        }
;

/// TODO: Finish after Statement
statements: statement statements
{
    $2->push_front($1);
    $$ = $2;
}
          | statement
{
    decafStmtList *list = new decafStmtList();
    list->push_front($1);
    $$ = list;
}
|
{
    $$ = new decafStmtList();
}
;

/// TODO: Finished
Return: T_RETURN T_LPAREN Expr T_RPAREN T_SEMICOLON
      {
            ReturnStmtAST *node = new ReturnStmtAST($3);
            $$ = node;
            //cout << "T_RETURN";
      }
      | T_RETURN T_LPAREN T_RPAREN T_SEMICOLON
      {
            //decafAST *emptyNode = new decafAST();
            ReturnStmtAST *node = new ReturnStmtAST(NULL);
            $$ = node;
      }
      | T_RETURN T_SEMICOLON
        {
            ReturnStmtAST *node = new ReturnStmtAST(NULL);
            $$ = node;
        }
      ;

/// TODO: Check for ambiguity
If: T_IF T_LPAREN Expr T_RPAREN Block T_ELSE Block
      {
            IfStmtAST *node = new IfStmtAST($3, $5, $7);
            $$ = node;
      }
      | T_IF T_LPAREN Expr T_RPAREN Block
      {
            //decafStmtList *emptyNode = new decafStmtList();
            IfStmtAST *node = new IfStmtAST($3, $5, NULL);
            $$ = node;
      }
;

/// TODO: Finished - Double Check
Assign: Identifier T_ASSIGN Expr
        {
            AssignAST *node = new AssignAST(*$1, $3);
            $$ = node;
        }
|   Identifier T_LSB Expr T_RSB T_ASSIGN Expr
{
        AssignAST *node = new AssignAST(*$1, $3, $6);
        $$ = node;
}

/// TODO: Finished
Assigns: Assign T_COMMA Assigns
        {
               $3->push_front($1);
               $$ = $3;
        };
| Assign
{
    decafStmtList *list = new decafStmtList();
    list->push_front($1);
    $$ = list;
}
;


/// TODO: Finished
MethodArg: Expr
        {
            MethodArgumentAST *node = new MethodArgumentAST($1);
            $$ = node;
            //cout << "MethodArg - Expr";
        }
| T_STRINGCONSTANT
        {
            StringAST *strnode = new StringAST(*$1);
            MethodArgumentAST *node = new MethodArgumentAST(strnode);
            $$ = node;
            //cout << "MethodArg - String";
        }
;

/// TODO: Check
MethodArgs: MethodArg T_COMMA MethodArgs
        {
            $3->push_front($1);
            $$ = $3;
            //cout << "MethodArg - WithComma";
        }
| MethodArg
        {
            decafStmtList *list = new decafStmtList();
            list->push_front($1);
            $$ = list;
            //cout << "MethodArg - Ending";
        }
;

/// TODO: Finished
MethodCall: T_ID T_LPAREN MethodArgs T_RPAREN
        {
            MethodCallAST *node = new MethodCallAST(*$1, $3);
            $$ = node;
            //cout << "MethodCall - With Arg";
        }
| T_ID T_LPAREN T_RPAREN
        {
            decafStmtList *args = new decafStmtList();
            MethodCallAST *node = new MethodCallAST(*$1, args);
            $$ = node;
            //cout << "MethodCall - Without Arg";
        }

/// TODO: Not Finished
Expr: T_ID
        {
            rvalueAST *rvalue = new rvalueAST(*$1, false);
            ExprAST *node = new ExprAST(rvalue);
            $$ = node;
        }
| MethodCall
        {
            ExprAST *node = new ExprAST($1);
            $$ = node;
        }
| Constant
        {
            ExprAST *node = new ExprAST($1);
            $$ = node;
        }
| BoolConstant
        {
            ExprAST *node = new ExprAST($1);
            $$ = node;
        }
| Binarys
        {
            $$ = $1;
        }
| T_LPAREN Expr T_RPAREN { $$ = $2; }
| T_ID T_LSB Expr T_RSB
        {
            rvalueAST *rvalue = new rvalueAST(*$1, true, $3);
            ExprAST *node = new ExprAST(rvalue);
            $$ = node;
        }
;
/// TODO: Split Binary Operators into an independent rule
Binarys: Expr T_PLUS Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(0), $1, $3);
            $$ = node;
        }
        | Expr T_MINUS Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(1), $1, $3);
            $$ = node;
        }
        | Expr T_MULT Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(2), $1, $3);
            $$ = node;
        }
        | Expr T_DIV Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(3), $1, $3);
            $$ = node;
        }
        | Expr T_LEFTSHIFT Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(4), $1, $3);
            $$ = node;
        }
        | Expr T_RIGHTSHIFT Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(5), $1, $3);
            $$ = node;
        }
        | Expr T_MOD Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(6), $1, $3);
            $$ = node;
        }
        | T_MINUS Expr %prec T_UMINUS
        {
             UnaryExprAST *node = new UnaryExprAST(getUnaryOp(15), $2);
             $$ = node;
        }
| Expr T_EQ Expr
{
    BinaryExprAST *node = new BinaryExprAST(getBinaryOp(11), $1, $3);
    $$ = node;
}
| Expr T_NEQ Expr
{
    BinaryExprAST *node = new BinaryExprAST(getBinaryOp(12), $1, $3);
    $$ = node;
}
| Expr T_LT Expr
{
    BinaryExprAST *node = new BinaryExprAST(getBinaryOp(7), $1, $3);
    $$ = node;
}
| Expr T_GT Expr
{
    BinaryExprAST *node = new BinaryExprAST(getBinaryOp(8), $1, $3);
    $$ = node;
}
| Expr T_LEQ Expr
{
    BinaryExprAST *node = new BinaryExprAST(getBinaryOp(9), $1, $3);
    $$ = node;
}
        | T_MINUS Expr %prec T_UMINUS
        {
                UnaryExprAST *node = new UnaryExprAST(getUnaryOp(15), $2);
        $$ = node;
        }
        | T_NOT Expr
        {
             UnaryExprAST *node = new UnaryExprAST(getUnaryOp(16), $2);
             $$ = node;
        }
        | Expr T_GEQ Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(10), $1, $3);
            $$ = node;
        }
        | Expr T_AND Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(13), $1, $3);
            $$ = node;
        }
        | Expr T_OR Expr
        {
            BinaryExprAST *node = new BinaryExprAST(getBinaryOp(14), $1, $3);
            $$ = node;
        }
        ;

%%

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
        //cout << retval << endl;
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

