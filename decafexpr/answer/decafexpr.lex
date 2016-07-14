
%{
#include "decafexpr-defs.h"
#include "decafexpr.tab.h"
#include <iostream>
#include <cstdlib>
#define DEFAULTLINE 1
#define DEFAULTOKEN 0

using namespace std;

int lineno = 1;
int tokenpos = 1;

%}

%%
  /*
    Pattern definitions for all tokens 
  */
func                       { tokenpos += 4; return T_FUNC; }
int                        { tokenpos += 3; return T_INTTYPE; }
package					   { tokenpos += 7; return T_PACKAGE; }
bool                       { tokenpos += 4; return T_BOOLTYPE; }
break                      { tokenpos += 5; return T_BREAK; }
continue                   { tokenpos += 8; return T_CONTINUE; }
else                       { tokenpos += 4; return T_ELSE; }
extern                     { tokenpos += 6; return T_EXTERN; }
false                      { tokenpos += 5; yylval.boolValue = true; return T_FALSE; }
for                        { tokenpos += 3; return T_FOR; }
if                         { tokenpos += 2; return T_IF; }
null                       { tokenpos += 4; return T_NULL; }
return                     { tokenpos += 6; return T_RETURN; }
string                     { tokenpos += 6; return T_STRINGTYPE; }
true                       { tokenpos += 4; yylval.boolValue = true; return T_TRUE; }
var                        { tokenpos += 3; return T_VAR; }
void                       { tokenpos += 4; return T_VOID; }
while                      { tokenpos += 5; return T_WHILE; }
\'[^\\\']\'|\'[\\][abtnvfr\\\'\"]\' {
    if(yytext[1] == '\\') {
        switch(yytext[2]) {
            case 'a': yylval.numericalValue = '\a'; break;
            case 'b': yylval.numericalValue = '\b'; break;
            case 't': yylval.numericalValue = '\t'; break;
            case 'n': yylval.numericalValue = '\n'; break;
            case 'v': yylval.numericalValue = '\v'; break;
            case 'f': yylval.numericalValue = '\f'; break;
            case 'r': yylval.numericalValue = '\r'; break;
            case '\\': yylval.numericalValue = '\\'; break;
            case '\'': yylval.numericalValue = '\''; break;
        }
    } else {
        yylval.numericalValue = (int)yytext[1];
    }

    tokenpos += 3;
    return T_CHARCONSTANT;
}  // T_CHARCONSTNT
\'\'                       { cerr << lineno << " : Error at " << tokenpos << ". Char of zero length." << endl; return -1; } // char zero length
\'[\\][^abtnvfr\\\'\"]\'   { cerr << lineno << " : Error at " << tokenpos << ". Unexpected character." << endl; return -1; } // char unexpected character
\'[^\n\']*[\\\']\'         { cerr << lineno << " : Error at " << tokenpos << ". Unterminated character." << endl; return -1; } // char unterminated
\'[^\n\'][^\n\']+\'        { cerr << lineno << " : Error at " << tokenpos << ". Char has length greater than 1." << endl; return -1; } // char length greater than 1
\"[\n]\"                   { cerr << lineno << " : Error at " << tokenpos << ". String with new line. " << endl; return -1; } // string new line
\"[^\"\n]*[\n]|\"[\\]\"|\"([\\][\\])+[\\]\"   { cerr << lineno << " : Error at " << tokenpos << ". Unterminated string." << endl; return -1; } // string unterminated
\"[^\n]*([\\][\\])+[\\][^abtnvfr\\\'\"][^\n]*\"  { cerr << lineno << " : Error at " << tokenpos << ". String with unknown escape sequence." << endl; return -1; } // string unknown escape sequence
\"[^\n]*([\\][abtnvfr\\\'\"])+[^\n]*[\"] { tokenpos += strlen(yytext); yylval.sval = new string(yytext); return T_STRINGCONSTANT; }
\"[^\n]*[\\][^abtnvfr\\\'\"][^\n]*\"  { cerr << lineno << " : Error at " << tokenpos << ". String with unknown escape sequence." << endl; return -1; } // string unknown escape sequence
\"[^\n\"]*[^\n\"]\"|\"\"   { tokenpos += strlen(yytext); yylval.sval = new string(yytext); return T_STRINGCONSTANT; }  // T_STRINGCONTANT
~                          { cerr << "Error: unexpected character in input" << endl; return -1; }
\/\/[ ]*[^\n]*[\n]*        {

                   for(int i = 0; i < strlen(yytext); i++) {
                        if(yytext[i] == '\n') lineno++;
                   }

 }
[0-9]+|0[x|X][0-9a-fA-F]+
{
    if(strlen(yytext) > 1) {
        if(yytext[1] == 'x' | yytext[1] == 'X') {
            int temp = 0;
            for(int i = strlen(yytext)-1, j = 1; i > 1; i--, j++) {
                switch(yytext[i]) {
                    case '0': temp += 0*j; break;
                    case '1': temp += 1*j; break;
                    case '2': temp += 2*j; break;
                    case '3': temp += 3*j; break;
                    case '4': temp += 4*j; break;
                    case '5': temp += 5*j; break;
                    case '6': temp += 6*j; break;
                    case '7': temp += 7*j; break;
                    case '8': temp += 8*j; break;
                    case '9': temp += 9*j; break;
                    case 'a': temp += 10*j; break;
                    case 'b': temp += 11*j; break;
                    case 'c': temp += 12*j; break;
                    case 'd': temp += 13*j; break;
                    case 'e': temp += 14*j; break;
                    case 'f': temp += 15*j; break;
                }
            }
            yylval.numericalValue = temp;
            return T_INTCONSTANT;
        } else {
            yylval.numericalValue = atoi(yytext); return T_INTCONSTANT;
        }
    }
    yylval.numericalValue = atoi(yytext); return T_INTCONSTANT;
}  // T_INTCONSTANT
[a-zA-Z\_][a-zA-Z\_0-9]*   { yylval.sval = new string(yytext); return T_ID; }   // T_ID
\{                         { tokenpos += 1; return T_LCB; }
\}                         { tokenpos += 1; return T_RCB; }
\(                         { tokenpos += 1; return T_LPAREN; }
\)                         { tokenpos += 1; return T_RPAREN; }
\&\&                       { tokenpos += 2; return T_AND; }
\=                         { tokenpos += 1; return T_ASSIGN; }
\,                         { tokenpos += 1; return T_COMMA; }
\/                         { tokenpos += 1; return T_DIV; }
\.                         { tokenpos += 1; return T_DOT; }
\=\=                       { tokenpos += 2; return T_EQ; }
\>\=                       { tokenpos += 2; return T_GEQ; }
\>                         { tokenpos += 1; return T_GT; }
\<\<                       { tokenpos += 2; return T_LEFTSHIFT; }
\<\=                       { tokenpos += 2; return T_LEQ; }
\[                         { tokenpos += 1; return T_LSB; }
\<                         { tokenpos += 1; return T_LT; }
\-                         { tokenpos += 1; return T_MINUS; }
\%                         { tokenpos += 1; return T_MOD; }
\*                         { tokenpos += 1; return T_MULT; }
\!\=                       { tokenpos += 2; return T_NEQ; }
\!                         { tokenpos += 1; return T_NOT; }
\|\|                       { tokenpos += 2; return T_OR; }
\+                         { tokenpos += 1; return T_PLUS; }
\>\>                       { tokenpos += 2; return T_RIGHTSHIFT; }
\]                         { tokenpos += 1; return T_RSB; }
\;                         { tokenpos += 1; return T_SEMICOLON; }
[\r\t\v\f ]*\n[\n\t\f\r\a\v\b ]* ; {

                   for(int i = 0; i < strlen(yytext); i++) {
                        if(yytext[i] == '\n') lineno++;
                   }

 }
[\n]+  {

                          for(int i = 0; i < strlen(yytext); i++) {
                               if(yytext[i] == '\n') lineno++;
                          }

        }
[\t\r\a\v\b ]+             ;   // T_WHITESPACE

%%

int yyerror(const char *s) {
  cerr << lineno << ": " << s << " at char " << tokenpos << endl;
  return 1;
}

