%{
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "default-defs.h"

int yylex(void);
int yyerror(char *); 

// print AST?
bool printAST = true;

#include "default.cc"

using namespace std;

%}

%union{
    class decafAST *ast;
    std::string *sval;
    //char* sval;
 }

%token T_PACKAGE
%token <sval>T_LCB
%token <sval>T_RCB
%token <sval> T_ID
%token T_AND
%token T_ASSIGN
%token T_BOOLTYPE
%token T_BREAK
%token T_CHARCONSTANT
%token T_COMMA
%token T_COMMENT
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
%token T_INTCONSTANT
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
%token T_STRINGCONSTANT
%token T_STRINGTYPE
%token T_TRUE
%token T_VAR
%token T_VOID
%token T_WHILE
%token T_WHITESPACE

%type <ast> extern_list decafpackage

%%

start: program

program: extern_list decafpackage
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
		if (printAST) {
			cout << getString(prog) << endl;
		}
        delete prog;
    }

extern_list: /* extern_list can be empty */
    { decafStmtList *slist = new decafStmtList(); $$ = slist; }
    ;

decafpackage: T_PACKAGE T_ID T_LCB T_RCB
    {  $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList());  delete $2; }
    ;

ExternDefn: T_EXTERN T_FUNC T_ID T_LPAREN ExternTypes T_RPAREN MethodType T_SEMICOLON
          | T_EXTERN T_FUNC T_ID T_LPAREN T_RPAREN MethodType T_SEMICOLON
          ;

statement: T_BREAK T_SEMICOLON { cout << "statement: T_BREAK"; }
         | T_CONTINUE T_SEMICOLON { cout << "statement: T_CONTINUE"; }
         | Return { cout << "statement: Return"; }
         | T_FOR T_LPAREN Assigns T_SEMICOLON Expr T_SEMICOLON Assigns T_RPAREN Block { cout << "statement: T_FOR"; }
         | T_WHILE T_LPAREN Expr T_RPAREN Block { cout << "statement: T_WHILE"; }
         | If { cout << "statement: If"; }
         | Assign T_SEMICOLON { cout << "statement: Assign"; }
         | Block { cout << "statement: Block"; }
         | MethodCall T_SEMICOLON { cout << "statement: methodcall"; }
         ;

statements: statement;

Expr: T_ID { cout << "Expr: T_ID" }
    | MethodCall { cout << "Expr: MethodCall" }
    | Constant { cout << "Expr: Constant" }
    | Expr BinaryOperator { cout << "Expr: Expr BinaryOperator"; }
    | UnaryOperator { cout << "Expr: Unary"; }
    | T_LPAREN Expr T_RPAREN { cout << "Expr: LPAREN RPAREN"; }
    | T_ID T_LSB Expr T_RSB { cout << "Expr: Array"; }
    ;

Return: T_RETURN T_LPAREN Expr T_RPAREN T_SEMICOLON { cout << "T_RETURN"; }
      | T_RETURN T_SEMICOLON { cout << "T_RETURN"; }
      ;

If: T_IF T_LPAREN Expr T_RPAREN Block T_ELSE Block { cout << "T_IF_ELSE"; }
  | T_IF T_LPAREN Expr T_RPAREN Block   { cout << "T_IF"; };
  ;

Assign: Lvalue "=" Expr { cout << "Assign"; }

Assigns: Assign T_COMMA
       | Assign
       ;

Lvalue: T_ID { cout << "LValue Not Array"; }
      | T_ID T_LSB Expr T_RSB { cout << "Lvalue Array"; }
      ;

UnaryOperator: T_NOT { cout << "Unary Not"; }
             | T_MINUS { cout << "Unary Minus"; }
             ;

ArithmeticOperator: T_PLUS { cout << "ArithOp - Plus"; }
                  | T_MINUS { cout << "ArithOp - Minus"; }
                  | T_MULT { cout << "ArithOp - Multiplication"; }
                  | T_DIV { cout << "ArithOp - Division"; }
                  | T_LEFTSHIFT { cout << "ArithOp - LSH "; }
                  | T_RIGHTSHIFT { cout << "ArithOp - RSH"; }
                  | T_MOD { cout << "ArithOp - Mod"; }
                  ;

BooleanOperator: T_EQ { cout << "BinaryOp - EQ"; }
               | T_NEQ { cout << "BinaryOp - NEQ"; }
               | T_LT { cout << "BinaryOp - LessThan"; }
               | T_GT { cout << "BinaryOp - Greater than"; }
               | T_LEQ { cout << "BinaryOp - Less or equal"; }
               | T_GEQ { cout << "BinaryOp - Greater or equal"; }
               | T_AND { cout << "BinaryOp - And"; }
               | T_OR { cout << "BinaryOp - Or"; }
               ;

BinaryOperator: BooleanOperator   { cout << "BinaryOp - Boolean"; }
              | ArithmeticOperator   { cout << "BinaryOp - Arith"; }
              ;

BoolConstant: T_TRUE { cout << "BoolConstant - True"; }
            | T_FALSE { cout << "BoolConstant - False"; }
            ;

Constant: T_INTCONSTANT { cout << "Int Constant"; }
        | T_CHARCONSTANT { cout << "Char Constant"; }
        | BoolConstant { cout << "Bool Constant"; }
        ;

Type: T_INTTYPE { cout << "Int type"; }
    | T_BOOLTYPE { cout << "Bool Type"; }
    ;

ArrayType: T_LSB T_INTCONSTANT T_RSB Type { cout << "Array Type"; }
         ;

MethodType: T_VOID { cout << "methodType - void"; }
          | Type { cout << "MethodType - Other"; }
          ;

ExternType: T_STRINGTYPE { cout << "ExternType - String"; }
          | MethodType { cout << "ExternType - Method"; }
          ;

ExternTypes: ExternType T_COMMA
           | ExternType
           ;

MethodArg: Expr { cout << "MethodArg - Expr"; }
         | T_STRINGCONSTANT { cout << "MethodArg - String"; }
         ;

MethodArgs: MethodArg T_COMMA { cout << "MethodArg - WithComma"; }
          | MethodArg { cout << "MethodArg - Ending"; }
          ;

MethodCall: T_ID T_LPAREN MethodArgs T_RPAREN { cout << "MethodCall - With Arg"; }
          | T_ID T_LPAREN T_RPAREN { cout << "MethodCall - Without Arg"; }

Identifiers: T_ID T_COMMA { cout << "Identifiers";}
           | T_ID  { cout << "Identifiers";}
           ;

VarDecl: T_VAR Identifiers Type T_SEMICOLON { cout << "Var Decl" };

VarDecls: VarDecl;

Block: T_LCB VarDecls statements T_RCB;

FieldDecl: T_VAR Identifiers Type T_SEMICOLON { cout << "Field Decl - NO Array" }
         | T_VAR Identifiers ArrayType T_SEMICOLON { cout << "Field Decl - Array" }
         | T_VAR T_ID Type "=" Constant T_SEMICOLON { cout << "Field Decl - Assign" }
         ;

FieldDecls: FieldDecl;

MethodDecl: T_FUNC T_ID T_LPAREN Identifiers T_RPAREN MethodType Block { cout<< "MethodDecl with IDs"; }
          | T_FUNC T_ID T_LPAREN T_RPAREN MethodType Block { cout<< "MethodDecl no IDs"; }
          ;

MethodDecls: MethodDecl;

%%

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

