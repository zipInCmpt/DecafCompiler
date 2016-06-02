
%{

#include <iostream>
#include <cstdlib>
#define DEFAULTLINE 0
#define DEFAULTOKEN 0

using namespace std;

%}

%%
  /*
    Pattern definitions for all tokens 
  */
func                       { return 1; }
int                        { return 2; }
package					   { return 3; }
bool                       { return 13; }
break                      { return 14; }
continue                   { return 16; }
else                       { return 19; }
extern                     { return 21; }
false                      { return 22; }
for                        { return 23; }
if                         { return 26; }
null                       { return 36; }
return                     { return 39; }
string                     { return 43; }
true                       { return 44; }
var                        { return 45; }
void                       { return 46; }
while                      { return 47; }
\'[^\\\']\'|\'[\\][abtnvfr\\\'\"]\'  { return 48; }  // T_CHARCONSTNT
\'\'|\'[\\][^abtnvfr\\\'\"]\'   { cerr << "Error: unexpected character in input" << endl; return -1; }
\'[^\n\']*[\\\']\'         { cerr << "Error: unexpected character in input" << endl; return -1; }
\'[^\n\'][^\n\']+\'        { cerr << "Error: unexpected character in input" << endl; return -1; }
\"[\"\n]\"                 { cerr << "Error: unexpected character in input" << endl; return -1; }
\"[^\"\n]*[\n]               { cerr << "Error: unexpected character in input" << endl; return -1; }
\"[^\n]*([\\][abtnvfr\\\'\"])+[^\n]*\" { return 51; }
\"[\\][^abtnvfr\\\'\"]*\"  { cerr << "Error: unexpected character in input" << endl; return -1; }
\"[^\n\"]*[^\n\"]\"|\"\"   { return 51; }  // T_STRINGCONTANT
~                          { cerr << "Error: unexpected character in input" << endl; return -1; }
\/\/[ ]*[^\n]*[\n]*        { return 49; }  // T_COMMENT
[0-9]+|0[x|X][0-9a-fA-F]+  { return 50; }  // T_INTCONSTANT
[a-zA-Z\_][a-zA-Z\_0-9]*   { return 8; }   // T_ID
\{                         { return 4; }
\}                         { return 5; }
\(                         { return 6; }
\)                         { return 7; }
\&\&                       { return 11; }
\=                         { return 12; }
\,                         { return 15; }
\/                         { return 17; }
\.                         { return 18; }
\=\=                       { return 20; }
\>\=                       { return 24; }
\>                         { return 25; }
\<\<                       { return 27; }
\<\=                       { return 28; }
\[                         { return 29; }
\<                         { return 30; }
\-                         { return 31; }
\%                         { return 32; }
\*                         { return 33; }
\!\=                       { return 34; }
\!                         { return 35; }
\|\|                       { return 37; }
\+                         { return 38; }
\>\>                       { return 40; }
\]                         { return 41; }
\;                         { return 42; }
[\r\t\v\f ]*\n[\n\t\f\r\a\v\b ]* { return 10; }
[\n]+                      { return 10; }
[\t\r\a\v\b ]+             { return 9; }   // T_WHITESPACE


%%

int main () {
  int token;
  string lexeme;
  int tokenNum = DEFAULTOKEN;
  int lineNum = DEFAULTLINE;
  while ((token = yylex())) {
    if (token > 0) {
      lexeme.assign(yytext);
	  switch(token) {
		case 1: cout << "T_FUNC " << lexeme << endl; tokenNum++; break;
		case 2: cout << "T_INTTYPE " << lexeme << endl; tokenNum++; break;
		case 3: cout << "T_PACKAGE " << lexeme << endl; tokenNum++; break;
		case 4: cout << "T_LCB " << lexeme << endl; tokenNum++; break;
		case 5: cout << "T_RCB " << lexeme << endl; tokenNum++; break;
		case 6: cout << "T_LPAREN " << lexeme << endl; tokenNum++; break;
		case 7: cout << "T_RPAREN " << lexeme << endl; tokenNum++; break;
		case 8: cout << "T_ID " << lexeme << endl; tokenNum++; break;
		case 9: cout << "T_WHITESPACE " << lexeme << endl; tokenNum++; break;
		case 56: cout << "T_WHITESPACE \\n" << endl; break;
		case 10: {
		             cout << "T_WHITESPACE ";
		             int flag = lexeme.find("\n");
		             while(flag != -1) {
		                cout << "\\n";
		                if(lexeme.length() > 1) {
		                   lexeme = lexeme.substr(flag+1, lexeme.length());
		                   flag = lexeme.find("\n");
		                } else {
		                    break;
		                }
		             }
		             cout << endl;

		             lineNum++;
		             tokenNum = DEFAULTOKEN;

		             break;
		         }
		case 11: cout << "T_AND " << lexeme << endl; tokenNum++; break;
		case 12: cout << "T_ASSIGN " << lexeme << endl; tokenNum++; break;
		case 13: cout << "T_BOOLTYPE " << lexeme << endl; tokenNum++; break;
		case 14: cout << "T_BREAK " << lexeme << endl; tokenNum++; break;
		case 15: cout << "T_COMMA " << lexeme << endl; tokenNum++; break;
		case 16: cout << "T_CONTINUE " << lexeme << endl; tokenNum++; break;
		case 17: cout << "T_DIV " << lexeme << endl; tokenNum++; break;
		case 18: cout << "T_DOT " << lexeme << endl; tokenNum++; break;
		case 19: cout << "T_ELSE " << lexeme << endl; tokenNum++; break;
		case 20: cout << "T_EQ " << lexeme << endl; tokenNum++; break;
		case 21: cout << "T_EXTERN " << lexeme << endl; tokenNum++; break;
		case 22: cout << "T_FALSE " << lexeme << endl; tokenNum++; break;
		case 23: cout << "T_FOR " << lexeme << endl; tokenNum++; break;
		case 24: cout << "T_GEQ " << lexeme << endl; tokenNum++; break;
		case 25: cout << "T_GT " << lexeme << endl; tokenNum++; break;
		case 26: cout << "T_IF " << lexeme << endl; tokenNum++; break;
		case 27: cout << "T_LEFTSHIFT " << lexeme << endl; tokenNum++; break;
		case 28: cout << "T_LEQ " << lexeme << endl; tokenNum++; break;
		case 29: cout << "T_LSB " << lexeme << endl; tokenNum++; break;
		case 30: cout << "T_LT " << lexeme << endl; tokenNum++; break;
		case 31: cout << "T_MINUS " << lexeme << endl; tokenNum++; break;
		case 32: cout << "T_MOD " << lexeme << endl; tokenNum++; break;
		case 33: cout << "T_MULT " << lexeme << endl; tokenNum++; break;
		case 34: cout << "T_NEQ " << lexeme << endl; tokenNum++; break;
		case 35: cout << "T_NOT " << lexeme << endl; tokenNum++; break;
		case 36: cout << "T_NULL " << lexeme << endl; tokenNum++; break;
		case 37: cout << "T_OR " << lexeme << endl; tokenNum++; break;
		case 38: cout << "T_PLUS " << lexeme << endl; tokenNum++; break;
		case 39: cout << "T_RETURN " << lexeme << endl; tokenNum++; break;
		case 40: cout << "T_RIGHTSHIFT " << lexeme << endl; tokenNum++; break;
		case 41: cout << "T_RSB " << lexeme << endl; tokenNum++; break;
		case 42: cout << "T_SEMICOLON " << lexeme << endl; tokenNum++; break;
		case 43: cout << "T_STRINGTYPE " << lexeme << endl; tokenNum++; break;
		case 44: cout << "T_TRUE " << lexeme << endl; tokenNum++; break;
		case 45: cout << "T_VAR " << lexeme << endl; tokenNum++; break;
		case 46: cout << "T_VOID " << lexeme << endl; tokenNum++; break;
		case 47: cout << "T_WHILE " << lexeme << endl; tokenNum++; break;
		case 48: cout << "T_CHARCONSTANT " << lexeme << endl; tokenNum++; break;
		case 49: {
		            int flag = lexeme.find("\n");
		            if(flag == -1) {
		                 cout << "T_COMMENT " << lexeme;
		            } else {
		                 cout << "T_COMMENT " << lexeme.substr(0, flag);
		                 lexeme = lexeme.substr(flag, lexeme.length());
		                 flag = lexeme.find("\n");
		                 while(flag != -1) {
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

		            lineNum++;
                    tokenNum = DEFAULTOKEN;

		            break;
		}
		case 50: cout << "T_INTCONSTANT " << lexeme << endl; tokenNum++; break;
		case 51: cout << "T_STRINGCONSTANT " << lexeme << endl; tokenNum++; break;
		case 52: cout << "T_WHITESPACE \\r" << endl; tokenNum++; break;
		case 53: cout << "T_WHITESPACE \\t" << endl; tokenNum++; break;
		case 54: cout << "T_WHITESPACE \\v" << endl; tokenNum++; break;
		case 55: cout << "T_WHITESPACE \\f" << endl; tokenNum++; break;
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

