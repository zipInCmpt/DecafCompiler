
%{
#include "decafcomp-defs.h"
#include "decafcomp.tab.h"
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
                        if(yytext[i] == '\n') {
                            lineno++;
                            tokenpos = 0;
                        }
                   }

 }
[0-9]+|0[x|X][0-9a-fA-F]+     {
    if(strlen(yytext) > 1) {
        if(yytext[1] == 'x' | yytext[1] == 'X') {
            int temp = 0;
            //cout << strlen(yytext) << endl;
            for(int i = 2; i < strlen(yytext); i++) {
                switch(yytext[i]) {
                    case '0': temp = temp*16 + 0; break;
                    case '1': temp = temp*16 + 1; break;
                    case '2': temp = temp*16 + 2; break;
                    case '3': temp = temp*16 + 3; break;
                    case '4': temp = temp*16 + 4; break;
                    case '5': temp = temp*16 + 5; break;
                    case '6': temp = temp*16 + 6; break;
                    case '7': temp = temp*16 + 7; break;
                    case '8': temp = temp*16 + 8; break;
                    case '9': temp = temp*16 + 9; break;
                    case 'a': temp = temp*16 + 10; break;
                    case 'b': temp = temp*16 + 11; break;
                    case 'c': temp = temp*16 + 12; break;
                    case 'd': temp = temp*16 + 13; break;
                    case 'e': temp = temp*16 + 14; break;
                    case 'f': temp = temp*16 + 15; break;
                    case 'A': temp = temp*16 + 10; break;
                    case 'B': temp = temp*16 + 11; break;
                    case 'C': temp = temp*16 + 12; break;
                    case 'D': temp = temp*16 + 13; break;
                    case 'E': temp = temp*16 + 14; break;
                    case 'F': temp = temp*16 + 15; break;
                }
            }
            yylval.numericalValue = temp;
            //cout << temp << endl;
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
                        if(yytext[i] == '\n') {
                            lineno++;
                            tokenpos = 0;
                        }
                   }

 }
[\n]+  {

                          for(int i = 0; i < strlen(yytext); i++) {
                               if(yytext[i] == '\n') {
                                     lineno++;
                                     tokenpos = 0;
                               }
                          }

        }
[\t\r\a\v\b ]+             ;   // T_WHITESPACE

%%

int yyerror(const char *s) {
  cout << "Syntax Error :" << " at line " << lineno << " char " << tokenpos << endl;
  return 1;
}

