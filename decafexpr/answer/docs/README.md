
Decaf Compiler Specifications
===================
Jiaqi Li (301295755) <br> Jingmin Zhu (301295748)

-------------------

###Description
* This is a compiler for the Decaf programming language.
  The compiler now deals with all situations in HW3: Variable Decl, Method Decl, Extern Method, Method Call, Assign, Arithmetic calculation and so on.
     
* The first step is to deal with named symbols. The symbol table list is kept as a global variable and each node with a block (like BlockAST, MethodDeclAST) contains the symbol table
of its block. The Symbol table of Method Decl also contains the Var Decls in the "()" before the block begins. When doing CodeGen, if the node is a Block or MethodDecl, its symbol table
 will be pushed to the global list and do code generation. Then, it is poped. This is the way I managed to keep the variables. 
 
* About CodeGen, it is not very complicated. But the C++ hashed map provides a sorted order to keep the keys (ID names of the variable) so when doing Method Call we need to check the order
of arguments carefully.

###Reference
* The rules for Decaf Language is based on the specifications by Anoop Sarker. 
The code is implemented by Jiaqi Li and Jingmin Zhu with collaboration on different parts of the grammar.
* The code is based on the HW1 and HW2 we have built on our own. Note that the lexical analyzer and the parser are both modified. Lex analyzer is modified for deal with Hex numbers 
 and Parser was modified a little bit for Symbol table and Code gen (just add some function calls to the rules).
 