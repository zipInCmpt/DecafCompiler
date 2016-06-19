
%{
#include "default-defs.h"
#include "decafast.tab.h"
#include <iostream>
#include <cstdlib>
#define DEFAULTLINE 1
#define DEFAULTOKEN 0

using namespace std;

%}

%%
  /*
    Pattern definitions for all tokens 
  */
func                       { return T_FUNC; }
int                        { return T_INTTYPE; }
package					   { return T_PACKAGE; }
bool                       { return T_BOOLTYPE; }
break                      { return T_BREAK; }
continue                   { return T_CONTINUE; }
else                       { return T_ELSE; }
extern                     { return T_EXTERN; }
false                      { yylval.boolValue = true; return T_FALSE; }
for                        { return T_FOR; }
if                         { return T_IF; }
null                       { return T_NULL; }
return                     { return T_RETURN; }
string                     { return T_STRINGTYPE; }
true                       { yylval.boolValue = true; return T_TRUE; }
var                        { return T_VAR; }
void                       { return T_VOID; }
while                      { return T_WHILE; }
\'[^\\\']\'|\'[\\][abtnvfr\\\'\"]\'  { return T_CHARCONSTANT; }  // T_CHARCONSTNT
\'\'                       { return 101; } // char zero length
\'[\\][^abtnvfr\\\'\"]\'   { return 102; } // char unexpected character
\'[^\n\']*[\\\']\'         { return 103; } // char unterminated
\'[^\n\'][^\n\']+\'        { return 104; } // char length greater than 1
\"[\n]\"                   { return 105; } // string new line
\"[^\"\n]*[\n]|\"[\\]\"|\"([\\][\\])+[\\]\"   { return 106; } // string unterminated
\"[^\n]*([\\][\\])+[\\][^abtnvfr\\\'\"][^\n]*\"  { return 107; } // string unknown escape sequence
\"[^\n]*([\\][abtnvfr\\\'\"])+[^\n]*[\"] { return T_STRINGCONSTANT; }
\"[^\n]*[\\][^abtnvfr\\\'\"][^\n]*\"  { return 107; } // string unknown escape sequence
\"[^\n\"]*[^\n\"]\"|\"\"   { return T_STRINGCONSTANT; }  // T_STRINGCONTANT
~                          { cerr << "Error: unexpected character in input" << endl; return -1; }
\/\/[ ]*[^\n]*[\n]*        { return T_COMMENT; }  // T_COMMENT
[0-9]+|0[x|X][0-9a-fA-F]+  { yylval.numericalValue = atoi(yytext); return T_INTCONSTANT; }  // T_INTCONSTANT
[a-zA-Z\_][a-zA-Z\_0-9]*   { yylval.sval = new string(yytext); return T_ID; }   // T_ID
\{                         { return T_LCB; }
\}                         { return T_RCB; }
\(                         { return T_LPAREN; }
\)                         { return T_RPAREN; }
\&\&                       { return T_AND; }
\=                         { return T_ASSIGN; }
\,                         { return T_COMMA; }
\/                         { return T_DIV; }
\.                         { return T_DOT; }
\=\=                       { return T_EQ; }
\>\=                       { return T_GEQ; }
\>                         { return T_GT; }
\<\<                       { return T_LEFTSHIFT; }
\<\=                       { return T_LEQ; }
\[                         { return T_LSB; }
\<                         { return T_LT; }
\-                         { return T_MINUS; }
\%                         { return T_MOD; }
\*                         { return T_MULT; }
\!\=                       { return T_NEQ; }
\!                         { return T_NOT; }
\|\|                       { return T_OR; }
\+                         { return T_PLUS; }
\>\>                       { return T_RIGHTSHIFT; }
\]                         { return T_RSB; }
\;                         { return T_SEMICOLON; }
[\r\t\v\f ]*\n[\n\t\f\r\a\v\b ]* ;
[\n]+                      ;
[\t\r\a\v\b ]+             ;   // T_WHITESPACE


%%

int yyerror(const char *s) {
  int token;
  string lexeme;
  int tokenNum = DEFAULTOKEN;
  int lineNum = DEFAULTLINE;
  while ((token = yylex())) {
    if (token > 0) {
      lexeme.assign(yytext);
	  switch(token) {
		case 1: cout << "T_FUNC " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 2: cout << "T_INTTYPE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 3: cout << "T_PACKAGE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 4: cout << "T_LCB " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 5: cout << "T_RCB " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 6: cout << "T_LPAREN " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 7: cout << "T_RPAREN " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 8: cout << "T_ID " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 9: cout << "T_WHITESPACE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 56: cout << "T_WHITESPACE \\n" << endl; break;
		case 10: {
		             cout << "T_WHITESPACE ";
		             int flag = lexeme.find("\n");
		             while(flag != -1) {
		                lineNum++;
		                cout << "\\n";
		                if(lexeme.length() > 1) {
		                   lexeme = lexeme.substr(flag+1, lexeme.length());
		                   flag = lexeme.find("\n");
		                } else {
		                    break;
		                }
		             }
		             cout << endl;
		             tokenNum = DEFAULTOKEN + lexeme.length();

		             break;
		         }
		case 11: cout << "T_AND " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 12: cout << "T_ASSIGN " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 13: cout << "T_BOOLTYPE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 14: cout << "T_BREAK " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 15: cout << "T_COMMA " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 16: cout << "T_CONTINUE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 17: cout << "T_DIV " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 18: cout << "T_DOT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 19: cout << "T_ELSE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 20: cout << "T_EQ " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 21: cout << "T_EXTERN " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 22: cout << "T_FALSE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 23: cout << "T_FOR " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 24: cout << "T_GEQ " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 25: cout << "T_GT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 26: cout << "T_IF " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 27: cout << "T_LEFTSHIFT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 28: cout << "T_LEQ " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 29: cout << "T_LSB " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 30: cout << "T_LT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 31: cout << "T_MINUS " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 32: cout << "T_MOD " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 33: cout << "T_MULT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 34: cout << "T_NEQ " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 35: cout << "T_NOT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 36: cout << "T_NULL " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 37: cout << "T_OR " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 38: cout << "T_PLUS " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 39: cout << "T_RETURN " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 40: cout << "T_RIGHTSHIFT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 41: cout << "T_RSB " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 42: cout << "T_SEMICOLON " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 43: cout << "T_STRINGTYPE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 44: cout << "T_TRUE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 45: cout << "T_VAR " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 46: cout << "T_VOID " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 47: cout << "T_WHILE " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 48: cout << "T_CHARCONSTANT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 49: {
		            int flag = lexeme.find("\n");
		            if(flag == -1) {
		                 cout << "T_COMMENT " << lexeme;
		            } else {
		                 cout << "T_COMMENT " << lexeme.substr(0, flag);
		                 lexeme = lexeme.substr(flag, lexeme.length());
		                 flag = lexeme.find("\n");
		                 while(flag != -1) {
		                    lineNum++;
                            cout << "\\n";
                         	if(lexeme.length() > 1) {
                         		 lexeme = lexeme.substr(flag+1, lexeme.length());
                         		 flag = lexeme.find("\n");
                         	} else {
                         		 break;
                         	}
                         }
		            }
		            cout << endl;
                    tokenNum = DEFAULTOKEN;

		            break;
		}
		case 50: cout << "T_INTCONSTANT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 51: cout << "T_STRINGCONSTANT " << lexeme << endl; tokenNum+=lexeme.length(); break;
		case 52: cout << "T_WHITESPACE \\r" << endl; tokenNum+=lexeme.length(); break;
		case 53: cout << "T_WHITESPACE \\t" << endl; tokenNum+=lexeme.length(); break;
		case 54: cout << "T_WHITESPACE \\v" << endl; tokenNum+=lexeme.length(); break;
		case 55: cout << "T_WHITESPACE \\f" << endl; tokenNum+=lexeme.length(); break;
		case 101: {
		                cerr << "Error: char constant has zero width\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
		                exit(EXIT_FAILURE);
		                break;
		          }
        case 102: {
                  		cerr << "Error: unexpected character in input\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                  		exit(EXIT_FAILURE);
                  		break;
                  }
        case 103: {
                        cerr << "Error: unterminated char constant\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                        exit(EXIT_FAILURE);
                        break;
                  }
        case 104: {
                        cerr << "Error: char constant length is greater than one\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                        exit(EXIT_FAILURE);
                        break;
                  }
        case 105: {
                        cerr << "Error: newline in string constant\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                        exit(EXIT_FAILURE);
                        break;
                  }
        case 106: {
                        cerr << "Error: string constant is missing closing delimiter\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                        exit(EXIT_FAILURE);
                        break;
                  }
        case 107: {
                        cerr << "Error: unknown escape sequence in string constant\n" << "Lexical error: line "<< lineNum << ", position " << tokenNum+1 << endl;
                        exit(EXIT_FAILURE);
                        break;
                  }

		default: exit(EXIT_FAILURE);
	  }
    } else {
      if (token < 0) {
		exit(EXIT_FAILURE);
      }
    }
  }
  exit(EXIT_SUCCESS);
}

