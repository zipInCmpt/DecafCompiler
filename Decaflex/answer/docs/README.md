
Decaf Compiler Specifications
===================
Jiaqi Li (301295755) <br> Jingmin Zhu (301295748)

-------------------

Reference: The following rules for Decaf Language is based on the specifications by Anoop Sarker. 
The code is implemented by Jiaqi Li and Jingmin Zhu with collaboration on different parts of the tokens. 
The following are what we have implemented. 
Note that the Regular Expressions in this document must present in the correct order to perform the functions. See the source code for more details.  

## Lexical Analyzer ##
### Supported Keywords ###
      bool - T_BOOLTYPE
      break - T_BREAK 
      continue - T_CONTINUE
      else - T_ELSE
      extern - T_EXTERN 
      false - T_FALSE
      for - T_FOR     
      func - T_FUNC  
      if - T_IF   
      int - T_INTTYPE   
      null - T_NULL    
      package - T_PACKAGE 
      return - T_RETURN  
      string - T_STRINGTYPE   
      true - T_TRUE
      var - T_VAR    
      void - T_VOID    
      while - T_WHILE 
### Supported Operators ###
      { - T_LCB
      } - T_RCB
      [ - T_LSB
      ] - T_RSB
      , - T_COMMA
      ; - T_SEMICOLON
      ( - T_LPAREN
      ) - T_RPAREN
      = - T_ASSIGN
      \- - T_MINUS
      \! - T_NOT
      \+ - T_PLUS 
      \* - T_MINUS
      \/ - T_DIV 
      << - T_LEFTSHIFT
      >> - T_RIGHTSHIFT
      < - T_LT
      \> - T_GT
      % - T_MOD
      <= - T_LEQ
      \>= - T_GEQ
      == - T_EQ
      != - T_NEQ
      && - T_AND
      || - T_OR
      . - T_DOT
### Literals ###
* <strong> Integers - T_INTTYPE </strong>
    + Decimal Int
    + Hex Int
* <strong> Char - T_CHARCONTANT</strong>
    + <code>(\'[^\\\']\'|\'[\\][abtnvfr\\\'\"]\')</code>
    + Char Literals                 
    + Escaped Chars
* <strong> String - T_STRINGCONTANT</strong>
    + <code>(\"[^\n]*([\\][abtnvfr\\\'\"])+[^\n]*[\"]|\"[^\n\"]*[^\n\"]\"|\"\")</code>
    + String Literals               
    + Empty String
    + String with escaped Chars
    
### Other Characters ###
* <strong> Whitespace - T_WHITESPACE </strong>
* <strong> New line - T_WHITESPACE \n </strong>
    + Continuous new line will be like: T_WHITESPACE \n\n\n...
    
### Comments ###
* <strong> Single line comment </strong>
    + Detection of "\n" after a comment
    
### Error Reporting ###
These are some errors that the compiler could generate when compiling the source code. Also, it could report the location of the error. 
<br>Here are the list of errors that you may see when compiling. 
#### Lexical Errors ####
    
     Error: unknown escape sequence in string constant      (\"[^\n]*([\\][\\])+[\\][^abtnvfr\\\'\"][^\n]*\"|\"[^\n]*[\\][^abtnvfr\\\'\"][^\n]*\")
     Error: newline in string constant                      (\"[\n]\")
     Error: string constant is missing closing delimiter    (\"[^\"\n]*[\n]|\"[\\]\"|\"([\\][\\])+[\\]\")
     Error: char constant length is greater than one        (\'[^\n\'][^\n\']+\')
     Error: unterminated char constant                      (\'[^\n\']*[\\\']\')
     Error: char constant has zero width                    (\'\')                       
     Error: unexpected character in input                   (\'[\\][^abtnvfr\\\'\"]\')
