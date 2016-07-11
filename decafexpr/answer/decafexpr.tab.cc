/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_PACKAGE = 258,
     T_LCB = 259,
     T_RCB = 260,
     T_ID = 261,
     T_AND = 262,
     T_ASSIGN = 263,
     T_BOOLTYPE = 264,
     T_BREAK = 265,
     T_CHARCONSTANT = 266,
     T_COMMA = 267,
     T_CONTINUE = 268,
     T_DIV = 269,
     T_DOT = 270,
     T_ELSE = 271,
     T_EQ = 272,
     T_EXTERN = 273,
     T_FALSE = 274,
     T_FOR = 275,
     T_FUNC = 276,
     T_GEQ = 277,
     T_GT = 278,
     T_IF = 279,
     T_INTCONSTANT = 280,
     T_INTTYPE = 281,
     T_LEFTSHIFT = 282,
     T_LEQ = 283,
     T_LPAREN = 284,
     T_LSB = 285,
     T_LT = 286,
     T_MINUS = 287,
     T_MOD = 288,
     T_MULT = 289,
     T_NEQ = 290,
     T_NOT = 291,
     T_NULL = 292,
     T_OR = 293,
     T_PLUS = 294,
     T_RETURN = 295,
     T_RIGHTSHIFT = 296,
     T_RPAREN = 297,
     T_RSB = 298,
     T_SEMICOLON = 299,
     T_STRINGCONSTANT = 300,
     T_STRINGTYPE = 301,
     T_TRUE = 302,
     T_VAR = 303,
     T_VOID = 304,
     T_WHILE = 305,
     T_WHITESPACE = 306,
     T_UMINUS = 307
   };
#endif
/* Tokens.  */
#define T_PACKAGE 258
#define T_LCB 259
#define T_RCB 260
#define T_ID 261
#define T_AND 262
#define T_ASSIGN 263
#define T_BOOLTYPE 264
#define T_BREAK 265
#define T_CHARCONSTANT 266
#define T_COMMA 267
#define T_CONTINUE 268
#define T_DIV 269
#define T_DOT 270
#define T_ELSE 271
#define T_EQ 272
#define T_EXTERN 273
#define T_FALSE 274
#define T_FOR 275
#define T_FUNC 276
#define T_GEQ 277
#define T_GT 278
#define T_IF 279
#define T_INTCONSTANT 280
#define T_INTTYPE 281
#define T_LEFTSHIFT 282
#define T_LEQ 283
#define T_LPAREN 284
#define T_LSB 285
#define T_LT 286
#define T_MINUS 287
#define T_MOD 288
#define T_MULT 289
#define T_NEQ 290
#define T_NOT 291
#define T_NULL 292
#define T_OR 293
#define T_PLUS 294
#define T_RETURN 295
#define T_RIGHTSHIFT 296
#define T_RPAREN 297
#define T_RSB 298
#define T_SEMICOLON 299
#define T_STRINGCONSTANT 300
#define T_STRINGTYPE 301
#define T_TRUE 302
#define T_VAR 303
#define T_VOID 304
#define T_WHILE 305
#define T_WHITESPACE 306
#define T_UMINUS 307




/* Copy the first part of user declarations.  */
#line 1 "decafexpr.y"

#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <list>
#include <map>
#include "decafexpr-defs.h"


using namespace std;

int yylex(void);
int yyerror(char *); 

// print AST?
bool printAST = false;

// this global variable contains all the generated code
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::IRBuilder<> Builder(llvm::getGlobalContext());
// the calls to getGlobalContext() in the init above and in the
// following code ensures that we are incrementally generating
// instructions in the right order

// dummy main function
// WARNING: this is not how you should implement code generation
// for the main function!
// You should write the codegen for the main method as
// part of the codegen for method declarations (MethodDecl)
static llvm::Function *TheFunction = 0;

// we have to create a main function
llvm::Function *gen_main_def() {
    // create the top-level definition for main
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::IntegerType::get(llvm::getGlobalContext(), 32), false);
    llvm::Function *TheFunction = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", TheModule);
    if (TheFunction == 0) {
        throw runtime_error("empty function block");
    }
    // Create a new basic block which contains a sequence of LLVM instructions
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", TheFunction);
    // All subsequent calls to IRBuilder will place instructions in this location
    Builder.SetInsertPoint(BB);
    return TheFunction;
}

#include "decafexpr.cc"



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 54 "decafexpr.y"
{
    class decafAST *ast;
    std::string *sval;
    int numericalValue;
    bool boolValue;
    class decafStmtList *list;
    class IDTypeList *IDList;
    class IDTypeStringSpecialAST *IDType;
    //char* sval;
 }
/* Line 193 of yacc.c.  */
#line 264 "decafexpr.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 277 "decafexpr.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   406

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  106
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    13,    16,    18,
      19,    24,    31,    33,    36,    45,    50,    54,    62,    68,
      71,    73,    74,    77,    84,    90,    93,    95,    96,   100,
     102,   104,   107,   111,   113,   114,   116,   118,   120,   124,
     126,   127,   129,   131,   133,   135,   137,   139,   141,   143,
     148,   151,   153,   154,   159,   162,   165,   168,   170,   180,
     186,   188,   191,   193,   196,   199,   201,   202,   208,   213,
     216,   224,   230,   234,   241,   245,   247,   249,   251,   255,
     257,   262,   266,   268,   270,   272,   274,   276,   280,   285,
     289,   293,   297,   301,   305,   309,   313,   316,   320,   324,
     328,   332,   336,   339,   342,   346,   350
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    57,    -1,     4,    -1,     5,    -1,    58,
      59,    -1,    -1,    60,    58,    -1,    60,    -1,    -1,     3,
       6,    55,    56,    -1,     3,     6,    55,    62,    65,    56,
      -1,     3,    -1,     3,     6,    -1,    18,    21,     6,    29,
      72,    42,    73,    44,    -1,    48,    66,    74,    44,    -1,
      48,    68,    44,    -1,    48,    66,    30,    25,    43,    74,
      44,    -1,    48,    68,     8,    76,    44,    -1,    61,    62,
      -1,    61,    -1,    -1,    64,    70,    -1,    21,     6,    29,
      69,    42,    73,    -1,    21,     6,    29,    42,    73,    -1,
      63,    65,    -1,    63,    -1,    -1,    67,    12,    66,    -1,
      67,    -1,     6,    -1,     6,    74,    -1,    68,    12,    69,
      -1,    68,    -1,    -1,    79,    -1,    46,    -1,    74,    -1,
      71,    12,    72,    -1,    71,    -1,    -1,    49,    -1,    74,
      -1,    26,    -1,     9,    -1,    47,    -1,    19,    -1,    25,
      -1,    11,    -1,    48,    66,    74,    44,    -1,    77,    78,
      -1,    77,    -1,    -1,    55,    78,    81,    56,    -1,    55,
      56,    -1,    10,    44,    -1,    13,    44,    -1,    82,    -1,
      20,    29,    85,    44,    89,    44,    85,    42,    79,    -1,
      50,    29,    89,    42,    79,    -1,    83,    -1,    84,    44,
      -1,    79,    -1,    88,    44,    -1,    80,    81,    -1,    80,
      -1,    -1,    40,    29,    89,    42,    44,    -1,    40,    29,
      42,    44,    -1,    40,    44,    -1,    24,    29,    89,    42,
      79,    16,    79,    -1,    24,    29,    89,    42,    79,    -1,
      67,     8,    89,    -1,    67,    30,    89,    43,     8,    89,
      -1,    84,    12,    85,    -1,    84,    -1,    89,    -1,    45,
      -1,    86,    12,    87,    -1,    86,    -1,     6,    29,    87,
      42,    -1,     6,    29,    42,    -1,     6,    -1,    88,    -1,
      76,    -1,    75,    -1,    90,    -1,    29,    89,    42,    -1,
       6,    30,    89,    43,    -1,    89,    39,    89,    -1,    89,
      32,    89,    -1,    89,    34,    89,    -1,    89,    14,    89,
      -1,    89,    27,    89,    -1,    89,    41,    89,    -1,    89,
      33,    89,    -1,    32,    89,    -1,    89,    17,    89,    -1,
      89,    35,    89,    -1,    89,    31,    89,    -1,    89,    23,
      89,    -1,    89,    28,    89,    -1,    32,    89,    -1,    36,
      89,    -1,    89,    22,    89,    -1,    89,     7,    89,    -1,
      89,    38,    89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   132,   132,   134,   138,   144,   161,   167,   172,   180,
     184,   186,   188,   189,   194,   202,   220,   234,   251,   265,
     270,   277,   285,   292,   302,   314,   319,   326,   333,   340,
     350,   352,   361,   367,   375,   380,   388,   389,   393,   398,
     406,   412,   413,   417,   418,   422,   423,   427,   432,   440,
     459,   464,   471,   477,   482,   491,   497,   503,   507,   513,
     519,   524,   529,   533,   540,   545,   552,   558,   564,   570,
     578,   583,   592,   597,   605,   610,   620,   626,   636,   642,
     652,   658,   667,   673,   678,   683,   688,   692,   693,   701,
     706,   711,   716,   721,   726,   731,   736,   741,   746,   751,
     756,   761,   766,   771,   776,   781,   786
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_PACKAGE", "T_LCB", "T_RCB", "T_ID",
  "T_AND", "T_ASSIGN", "T_BOOLTYPE", "T_BREAK", "T_CHARCONSTANT",
  "T_COMMA", "T_CONTINUE", "T_DIV", "T_DOT", "T_ELSE", "T_EQ", "T_EXTERN",
  "T_FALSE", "T_FOR", "T_FUNC", "T_GEQ", "T_GT", "T_IF", "T_INTCONSTANT",
  "T_INTTYPE", "T_LEFTSHIFT", "T_LEQ", "T_LPAREN", "T_LSB", "T_LT",
  "T_MINUS", "T_MOD", "T_MULT", "T_NEQ", "T_NOT", "T_NULL", "T_OR",
  "T_PLUS", "T_RETURN", "T_RIGHTSHIFT", "T_RPAREN", "T_RSB", "T_SEMICOLON",
  "T_STRINGCONSTANT", "T_STRINGTYPE", "T_TRUE", "T_VAR", "T_VOID",
  "T_WHILE", "T_WHITESPACE", "T_UMINUS", "$accept", "start", "stbegin",
  "stend", "program", "extern_list", "decafpackage", "ExternDefn",
  "FieldDecl", "FieldDecls", "MethodDecl", "MethodDeclHead", "MethodDecls",
  "Identifiers", "Identifier", "IdentifierType", "IdentifierTypes",
  "MethodBlock", "ExternType", "ExternTypes", "MethodType", "Type",
  "BoolConstant", "Constant", "VarDecl", "VarDecls", "Block", "statement",
  "statements", "Return", "If", "Assign", "Assigns", "MethodArg",
  "MethodArgs", "MethodCall", "Expr", "Binarys", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    56,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    60,    61,    61,    61,    61,    62,
      62,    62,    63,    64,    64,    65,    65,    65,    66,    66,
      67,    68,    69,    69,    69,    70,    71,    71,    72,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      78,    78,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    81,    81,    81,    82,    82,    82,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     0,     2,     1,     0,
       4,     6,     1,     2,     8,     4,     3,     7,     5,     2,
       1,     0,     2,     6,     5,     2,     1,     0,     3,     1,
       1,     2,     3,     1,     0,     1,     1,     1,     3,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       2,     1,     0,     4,     2,     2,     2,     1,     9,     5,
       1,     2,     1,     2,     2,     1,     0,     5,     4,     2,
       7,     5,     3,     6,     3,     1,     1,     1,     3,     1,
       4,     3,     1,     1,     1,     1,     1,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     2,     2,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     2,     0,     8,     0,     1,    12,     5,
       7,     0,    13,    40,     3,    21,    44,    43,    36,    39,
       0,    37,     4,     0,    10,    20,    27,    40,     0,    30,
       0,    29,     0,    19,     0,    26,     0,     0,    38,    41,
       0,    42,    31,     0,     0,     0,     0,    16,     0,    25,
      52,    22,    35,    11,    14,     0,    15,    30,    28,    48,
      47,     0,     0,     0,    54,    51,    66,     0,    18,     0,
       0,    33,     0,     0,    50,    30,     0,     0,     0,     0,
       0,     0,     0,    62,    65,     0,    57,    60,     0,     0,
       0,    24,    34,     0,     0,     0,    55,    56,     0,     0,
       0,    69,     0,     0,     0,    64,    53,    61,    63,    17,
      32,    23,    49,    82,    46,     0,     0,     0,    81,    77,
      45,    85,    84,    79,     0,    83,    76,    86,    75,     0,
       0,     0,     0,     0,    72,     0,     0,     0,    96,   103,
       0,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,    87,    78,   105,    92,    97,
     104,   100,    93,   101,    99,    90,    95,    91,    98,   106,
      89,    94,    74,     0,    71,    67,    59,     0,    88,     0,
       0,    73,     0,    70,     0,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    50,    24,     3,     4,     9,     5,    25,    26,
      35,    36,    37,    30,    82,    71,    72,    51,    19,    20,
      40,    41,   121,   122,    65,    66,    83,    84,    85,    86,
      87,   128,   129,   123,   124,   125,   126,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -150
static const yytype_int16 yypact[] =
{
      72,   -11,    20,  -150,     9,    13,    31,  -150,    33,  -150,
    -150,    57,    37,   121,  -150,    11,  -150,  -150,  -150,    75,
      55,  -150,  -150,   101,  -150,    61,    96,   121,    67,    62,
       0,   103,    24,  -150,   115,    96,    37,   123,  -150,  -150,
      88,  -150,  -150,   109,    92,   131,    94,  -150,   110,  -150,
      17,  -150,  -150,  -150,  -150,    98,  -150,  -150,  -150,  -150,
    -150,    99,    27,   131,  -150,    97,    60,    62,  -150,    62,
      67,   132,   106,    62,  -150,   120,   107,   113,   124,   135,
      50,   137,    73,  -150,    60,   123,  -150,  -150,   116,   117,
     125,  -150,   144,    67,   129,    66,  -150,  -150,   131,    95,
      93,  -150,    95,    95,    95,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,    53,  -150,    95,    95,    95,  -150,  -150,
    -150,  -150,  -150,   156,   142,  -150,   309,  -150,   165,   146,
     217,   147,   240,   263,   309,   171,    95,   286,  -150,  -150,
     127,  -150,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,   131,    95,    37,
    -150,   151,    37,   188,   194,  -150,  -150,   355,  -150,   365,
     365,   365,  -150,   365,   365,     1,  -150,  -150,   365,   332,
       1,  -150,  -150,   148,   181,  -150,  -150,    95,  -150,   131,
      37,   309,   158,  -150,    37,  -150
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,   195,   -23,  -150,   208,  -150,  -150,  -150,   190,
    -150,  -150,   183,   -34,   -20,   196,   128,  -150,  -150,   203,
     -57,    -6,  -150,   177,  -150,   173,   -36,  -150,   152,  -150,
    -150,     8,  -149,  -150,   102,    12,   -98,  -150
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -10
static const yytype_int16 yytable[] =
{
      52,   130,   132,    31,   133,   134,   135,    21,   182,    16,
       6,    58,     8,    91,    53,   143,    22,   137,   138,   139,
       7,    21,    22,    42,    44,    31,    17,    64,   147,    73,
      43,     1,    46,    69,   151,   152,   111,    11,   164,    12,
     192,    14,   156,    31,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,    23,
     183,    90,   106,    42,    14,    63,    75,    94,    47,    70,
      76,    16,   113,    77,    88,    -9,    16,    59,    89,   100,
      78,   103,    95,   136,    79,   114,    13,    27,    17,   191,
       1,    60,    88,    17,   101,   115,    89,    28,   116,   113,
      80,   113,   117,   104,    59,    59,    59,    29,   118,    23,
      81,   119,   114,   120,   114,    45,    39,    34,    60,    60,
      60,    48,   115,   184,   115,   116,   186,   116,    22,   117,
      16,   117,    54,   113,    55,   131,    56,    57,    59,    62,
     120,    67,   120,    68,    92,    63,   114,    17,    93,    95,
      69,    96,    60,    98,   193,   142,   115,    97,   195,   116,
     107,   108,   143,   117,    99,   144,   102,    18,   140,   109,
     145,   146,   119,   112,   120,   147,   148,   157,   142,   149,
     150,   151,   152,   153,   141,   143,   154,   155,   144,   156,
     158,   160,   189,   145,   146,   185,   187,   190,   147,   148,
     194,   142,   149,   150,   151,   152,   153,    15,   143,   154,
     155,   144,   156,    10,   163,    33,   145,   146,    49,    32,
     110,   147,   148,    61,   142,   149,   150,   151,   152,   153,
      38,   143,   154,   155,   144,   156,   105,   188,    74,   145,
     146,     0,   166,     0,   147,   148,     0,   142,   149,   150,
     151,   152,   153,     0,   143,   154,   155,   144,   156,   159,
       0,     0,   145,   146,     0,     0,     0,   147,   148,     0,
     142,   149,   150,   151,   152,   153,     0,   143,   154,   155,
     144,   156,   161,     0,     0,   145,   146,     0,     0,     0,
     147,   148,     0,   142,   149,   150,   151,   152,   153,     0,
     143,   154,   155,   144,   156,   162,     0,     0,   145,   146,
       0,     0,     0,   147,   148,     0,   142,   149,   150,   151,
     152,   153,     0,   143,   154,   155,   144,   156,   165,     0,
       0,   145,   146,     0,     0,     0,   147,   148,     0,   142,
     149,   150,   151,   152,   153,     0,   143,   154,   155,   144,
     156,     0,     0,     0,   145,   146,     0,     0,     0,   147,
     148,     0,     0,   149,   150,   151,   152,   153,     0,   143,
       0,   155,   144,   156,     0,     0,     0,   145,   146,   143,
       0,     0,   147,   148,     0,     0,   149,   150,   151,   152,
     153,     0,   147,     0,   155,     0,   156,   150,   151,   152,
       0,     0,     0,     0,   155,     0,   156
};

static const yytype_int16 yycheck[] =
{
      36,    99,   100,    23,   102,   103,   104,    13,   157,     9,
      21,    45,     3,    70,    37,    14,     5,   115,   116,   117,
       0,    27,     5,    29,    30,    45,    26,    50,    27,    63,
      30,    18,     8,     6,    33,    34,    93,     6,   136,     6,
     189,     4,    41,    63,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,    48,
     158,    67,    85,    69,     4,    48,     6,    73,    44,    42,
      10,     9,     6,    13,    66,     3,     9,    11,    66,    29,
      20,     8,    29,    30,    24,    19,    29,    12,    26,   187,
      18,    25,    84,    26,    44,    29,    84,    42,    32,     6,
      40,     6,    36,    30,    11,    11,    11,     6,    42,    48,
      50,    45,    19,    47,    19,    12,    49,    21,    25,    25,
      25,     6,    29,   159,    29,    32,   162,    32,     5,    36,
       9,    36,    44,     6,    25,    42,    44,     6,    11,    29,
      47,    43,    47,    44,    12,    48,    19,    26,    42,    29,
       6,    44,    25,    29,   190,     7,    29,    44,   194,    32,
      44,    44,    14,    36,    29,    17,    29,    46,    12,    44,
      22,    23,    45,    44,    47,    27,    28,    12,     7,    31,
      32,    33,    34,    35,    42,    14,    38,    39,    17,    41,
      44,    44,    44,    22,    23,    44,     8,    16,    27,    28,
      42,     7,    31,    32,    33,    34,    35,    12,    14,    38,
      39,    17,    41,     5,    43,    25,    22,    23,    35,    23,
      92,    27,    28,    46,     7,    31,    32,    33,    34,    35,
      27,    14,    38,    39,    17,    41,    84,    43,    65,    22,
      23,    -1,   140,    -1,    27,    28,    -1,     7,    31,    32,
      33,    34,    35,    -1,    14,    38,    39,    17,    41,    42,
      -1,    -1,    22,    23,    -1,    -1,    -1,    27,    28,    -1,
       7,    31,    32,    33,    34,    35,    -1,    14,    38,    39,
      17,    41,    42,    -1,    -1,    22,    23,    -1,    -1,    -1,
      27,    28,    -1,     7,    31,    32,    33,    34,    35,    -1,
      14,    38,    39,    17,    41,    42,    -1,    -1,    22,    23,
      -1,    -1,    -1,    27,    28,    -1,     7,    31,    32,    33,
      34,    35,    -1,    14,    38,    39,    17,    41,    42,    -1,
      -1,    22,    23,    -1,    -1,    -1,    27,    28,    -1,     7,
      31,    32,    33,    34,    35,    -1,    14,    38,    39,    17,
      41,    -1,    -1,    -1,    22,    23,    -1,    -1,    -1,    27,
      28,    -1,    -1,    31,    32,    33,    34,    35,    -1,    14,
      -1,    39,    17,    41,    -1,    -1,    -1,    22,    23,    14,
      -1,    -1,    27,    28,    -1,    -1,    31,    32,    33,    34,
      35,    -1,    27,    -1,    39,    -1,    41,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    54,    57,    58,    60,    21,     0,     3,    59,
      58,     6,     6,    29,     4,    55,     9,    26,    46,    71,
      72,    74,     5,    48,    56,    61,    62,    12,    42,     6,
      66,    67,    68,    62,    21,    63,    64,    65,    72,    49,
      73,    74,    74,    30,    74,    12,     8,    44,     6,    65,
      55,    70,    79,    56,    44,    25,    44,     6,    66,    11,
      25,    76,    29,    48,    56,    77,    78,    43,    44,     6,
      42,    68,    69,    66,    78,     6,    10,    13,    20,    24,
      40,    50,    67,    79,    80,    81,    82,    83,    84,    88,
      74,    73,    12,    42,    74,    29,    44,    44,    29,    29,
      29,    44,    29,     8,    30,    81,    56,    44,    44,    44,
      69,    73,    44,     6,    19,    29,    32,    36,    42,    45,
      47,    75,    76,    86,    87,    88,    89,    90,    84,    85,
      89,    42,    89,    89,    89,    89,    30,    89,    89,    89,
      12,    42,     7,    14,    17,    22,    23,    27,    28,    31,
      32,    33,    34,    35,    38,    39,    41,    12,    44,    42,
      44,    42,    42,    43,    89,    42,    87,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    85,    89,    79,    44,    79,     8,    43,    44,
      16,    89,    85,    79,    42,    79
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 134 "decafexpr.y"
    {
        newSTNode();
;}
    break;

  case 4:
#line 138 "decafexpr.y"
    {
        currentST = SymbolTableList.front();
        SymbolTableList.pop_front();
;}
    break;

  case 5:
#line 145 "decafexpr.y"
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)(yyvsp[(1) - (2)].list), (PackageAST *)(yyvsp[(2) - (2)].ast)); 
		if (printAST) {
			cout << getString(prog) << endl;
		}
        try {
            prog->Codegen();
        }
        catch (std::runtime_error &e) {
            cout << "semantic error: " << e.what() << endl;
            //cout << prog->str() << endl;
            exit(EXIT_FAILURE);
        }
        delete prog;
    ;}
    break;

  case 6:
#line 161 "decafexpr.y"
    {
    exit(EXIT_FAILURE);
;}
    break;

  case 7:
#line 168 "decafexpr.y"
    {
            (yyvsp[(2) - (2)].list)->push_front((yyvsp[(1) - (2)].ast));
            (yyval.list) = (yyvsp[(2) - (2)].list);
        ;}
    break;

  case 8:
#line 173 "decafexpr.y"
    {
            decafStmtList *externList = new decafStmtList();
            externList->push_front((yyvsp[(1) - (1)].ast));
            (yyval.list) = externList;
        ;}
    break;

  case 9:
#line 180 "decafexpr.y"
    { decafStmtList *slist = new decafStmtList(); (yyval.list) = slist; ;}
    break;

  case 10:
#line 185 "decafexpr.y"
    { (yyval.ast) = new PackageAST(*(yyvsp[(2) - (4)].sval), new decafStmtList(), new decafStmtList());  delete (yyvsp[(2) - (4)].sval); ;}
    break;

  case 11:
#line 187 "decafexpr.y"
    { (yyval.ast) = new PackageAST(*(yyvsp[(2) - (6)].sval), (yyvsp[(4) - (6)].list), (yyvsp[(5) - (6)].list));  delete (yyvsp[(2) - (6)].sval); ;}
    break;

  case 12:
#line 188 "decafexpr.y"
    { exit(EXIT_FAILURE); ;}
    break;

  case 13:
#line 189 "decafexpr.y"
    { exit(EXIT_FAILURE); ;}
    break;

  case 14:
#line 195 "decafexpr.y"
    {
                ExternAST *node = new ExternAST(*(yyvsp[(3) - (8)].sval), (yyvsp[(7) - (8)].numericalValue), (yyvsp[(5) - (8)].list));
                (yyval.ast) = node;
            ;}
    break;

  case 15:
#line 203 "decafexpr.y"
    {
            decafStmtList *fieldDeclList = new decafStmtList();
            FieldSizeAST *size = new FieldSizeAST(-1, false);

            while((yyvsp[(2) - (4)].list)->size() > 0) {
                   string name = (yyvsp[(2) - (4)].list)->pop_front();
                   FieldDeclAST *fieldNode = new FieldDeclAST(name, (yyvsp[(3) - (4)].numericalValue), size, false);
                   fieldDeclList->push_front(fieldNode);
                   //cout << fieldNode->str() << endl;
                   //delete fieldNode;
                   llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(3) - (4)].numericalValue)), nullptr, name);
                   descriptor *newVariableDecpr = new descriptor(name, (yyvsp[(3) - (4)].numericalValue), lineno, Alloca);
                   currentST.insert(std::pair<string, descriptor* >(name, newVariableDecpr));
            }
            //FieldDeclAST *node = new FieldDeclAST(*$2, $3, exprNode, false);
            (yyval.list) = fieldDeclList;
         ;}
    break;

  case 16:
#line 221 "decafexpr.y"
    {
                //cout << "here" << endl;
                decafStmtList *fieldDeclList = new decafStmtList();
                FieldSizeAST *size = new FieldSizeAST(-1, false);

                FieldDeclAST *fieldNode = new FieldDeclAST((yyvsp[(2) - (3)].IDType)->getName(), (yyvsp[(2) - (3)].IDType)->getTypeId(), size, false);
                fieldDeclList->push_front(fieldNode);
                (yyval.list) = fieldDeclList;

                llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(2) - (3)].IDType)->getTypeId()), nullptr, (yyvsp[(2) - (3)].IDType)->getName());
                descriptor *newVariableDecpr = new descriptor((yyvsp[(2) - (3)].IDType)->getName(), (yyvsp[(2) - (3)].IDType)->getTypeId(), lineno, Alloca);
                currentST.insert(std::pair<string, descriptor* >((yyvsp[(2) - (3)].IDType)->getName(), newVariableDecpr));
        ;}
    break;

  case 17:
#line 235 "decafexpr.y"
    {
            FieldSizeAST *size = new FieldSizeAST((yyvsp[(4) - (7)].numericalValue), true);
            decafStmtList *fieldDeclList = new decafStmtList();

            while((yyvsp[(2) - (7)].list)->size() > 0) {
                string name = (yyvsp[(2) - (7)].list)->pop_front();
                FieldDeclAST *fieldNode = new FieldDeclAST(name, (yyvsp[(6) - (7)].numericalValue), size, false);
                fieldDeclList->push_front(fieldNode);

                llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(6) - (7)].numericalValue)), nullptr, name);
                descriptor *newVariableDecpr = new descriptor(name, (yyvsp[(6) - (7)].numericalValue), lineno, Alloca);
                currentST.insert(std::pair<string, descriptor* >(name, newVariableDecpr));
            }

            (yyval.list) = fieldDeclList;
        ;}
    break;

  case 18:
#line 252 "decafexpr.y"
    {
                decafStmtList *fieldDeclList = new decafStmtList();
                FieldDeclAST *node = new FieldDeclAST((yyvsp[(2) - (5)].IDType)->getName(), (yyvsp[(2) - (5)].IDType)->getTypeId(), (yyvsp[(4) - (5)].ast), true);
                fieldDeclList->push_front(node);
                (yyval.list) = fieldDeclList;

                llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(2) - (5)].IDType)->getTypeId()), nullptr, (yyvsp[(2) - (5)].IDType)->getName());
                descriptor *newVariableDecpr = new descriptor((yyvsp[(2) - (5)].IDType)->getName(), (yyvsp[(2) - (5)].IDType)->getTypeId(), lineno, Alloca);
                currentST.insert(std::pair<string, descriptor* >((yyvsp[(2) - (5)].IDType)->getName(), newVariableDecpr));
        ;}
    break;

  case 19:
#line 266 "decafexpr.y"
    {
                (yyvsp[(2) - (2)].list)->push_front((yyvsp[(1) - (2)].list));
                (yyval.list) = (yyvsp[(2) - (2)].list);
        ;}
    break;

  case 20:
#line 271 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();
    list->push_front((yyvsp[(1) - (1)].list));
    (yyval.list) = list;
;}
    break;

  case 21:
#line 277 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();
    (yyval.list) = list;
;}
    break;

  case 22:
#line 286 "decafexpr.y"
    {
            MethodDeclAST *node = new MethodDeclAST((yyvsp[(1) - (2)].ast),(yyvsp[(2) - (2)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 23:
#line 293 "decafexpr.y"
    {
            MethodDeclHeadAST *node=new MethodDeclHeadAST(*(yyvsp[(2) - (6)].sval), (yyvsp[(6) - (6)].numericalValue), (yyvsp[(4) - (6)].IDList));
            (yyval.ast) = node;

            llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(6) - (6)].numericalValue)), nullptr, *(yyvsp[(2) - (6)].sval));
            descriptor *newVariableDecpr = new descriptor(*(yyvsp[(2) - (6)].sval), (yyvsp[(6) - (6)].numericalValue), lineno, Alloca);
            currentST.insert(std::pair<string, descriptor* >(*(yyvsp[(2) - (6)].sval), newVariableDecpr));

        ;}
    break;

  case 24:
#line 303 "decafexpr.y"
    {
            MethodDeclHeadAST *node=new MethodDeclHeadAST(*(yyvsp[(2) - (5)].sval), (yyvsp[(5) - (5)].numericalValue), new IDTypeList());
            (yyval.ast) = node;

            llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(5) - (5)].numericalValue)), nullptr, *(yyvsp[(2) - (5)].sval));
            descriptor *newVariableDecpr = new descriptor(*(yyvsp[(2) - (5)].sval), (yyvsp[(5) - (5)].numericalValue), lineno, Alloca);
            currentST.insert(std::pair<string, descriptor* >(*(yyvsp[(2) - (5)].sval), newVariableDecpr));
        ;}
    break;

  case 25:
#line 315 "decafexpr.y"
    {
                (yyvsp[(2) - (2)].list)->push_front((yyvsp[(1) - (2)].ast));
                (yyval.list) = (yyvsp[(2) - (2)].list);
            ;}
    break;

  case 26:
#line 320 "decafexpr.y"
    {
                decafStmtList *list = new decafStmtList();
                list->push_front((yyvsp[(1) - (1)].ast));
                (yyval.list) = list;
            ;}
    break;

  case 27:
#line 326 "decafexpr.y"
    {
                decafStmtList *list = new decafStmtList();
                (yyval.list) = list;
            ;}
    break;

  case 28:
#line 334 "decafexpr.y"
    {
            RawStringAST *str = new RawStringAST(*(yyvsp[(1) - (3)].sval));
            //cout << "here " << str->str() << endl;
            (yyvsp[(3) - (3)].list)->push_front(str);
            (yyval.list) = (yyvsp[(3) - (3)].list);
        ;}
    break;

  case 29:
#line 341 "decafexpr.y"
    {
            decafStmtList *idList = new decafStmtList();
            RawStringAST *str = new RawStringAST(*(yyvsp[(1) - (1)].sval));
            //cout << "here " << str->str() << endl;
            idList->push_front(str);
            (yyval.list) = idList;
        ;}
    break;

  case 30:
#line 350 "decafexpr.y"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); ;}
    break;

  case 31:
#line 353 "decafexpr.y"
    {
    //cout << "Here" << endl;
    IDTypeStringAST *nnode = new IDTypeStringAST(*(yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].numericalValue));
    IDTypeStringSpecialAST *node = new IDTypeStringSpecialAST(nnode);
    (yyval.IDType) = node;
;}
    break;

  case 32:
#line 362 "decafexpr.y"
    {
                IDTypeStringSpecialAST *sss = new IDTypeStringSpecialAST(*(yyvsp[(1) - (3)].IDType));
                (yyvsp[(3) - (3)].IDList)->push_front(sss);
                (yyval.IDList) = (yyvsp[(3) - (3)].IDList);
        ;}
    break;

  case 33:
#line 368 "decafexpr.y"
    {
            IDTypeList *list = new IDTypeList();
            IDTypeStringSpecialAST *sss = new IDTypeStringSpecialAST(*(yyvsp[(1) - (1)].IDType));
            list->push_front(sss);
            (yyval.IDList) = list;
        ;}
    break;

  case 34:
#line 375 "decafexpr.y"
    {
            (yyval.IDList) = new IDTypeList();
        ;}
    break;

  case 35:
#line 381 "decafexpr.y"
    {
            MethodBlockAST *node = new MethodBlockAST((yyvsp[(1) - (1)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 36:
#line 388 "decafexpr.y"
    { ExternType *type = new ExternType(0); (yyval.ast) = type; ;}
    break;

  case 37:
#line 389 "decafexpr.y"
    { ExternType *type = new ExternType((yyvsp[(1) - (1)].numericalValue)); (yyval.ast) = type; ;}
    break;

  case 38:
#line 394 "decafexpr.y"
    {
            (yyvsp[(3) - (3)].list)->push_front((decafAST *)(yyvsp[(1) - (3)].ast));
            (yyval.list) = (yyvsp[(3) - (3)].list);
        ;}
    break;

  case 39:
#line 399 "decafexpr.y"
    {
            decafStmtList *externTypeList = new decafStmtList();
            externTypeList->push_front((decafAST *) (yyvsp[(1) - (1)].ast));
            (yyval.list) = externTypeList;
            //delete $1;
        ;}
    break;

  case 40:
#line 406 "decafexpr.y"
    {
    (yyval.list) = new decafStmtList();
;}
    break;

  case 41:
#line 412 "decafexpr.y"
    { (yyval.numericalValue) = 19; ;}
    break;

  case 42:
#line 413 "decafexpr.y"
    { (yyval.numericalValue) = (yyvsp[(1) - (1)].numericalValue); ;}
    break;

  case 43:
#line 417 "decafexpr.y"
    { (yyval.numericalValue) = 17; ;}
    break;

  case 44:
#line 418 "decafexpr.y"
    { (yyval.numericalValue) = 18; ;}
    break;

  case 45:
#line 422 "decafexpr.y"
    { BoolConstantAST *node = new BoolConstantAST(true); (yyval.ast) = node; ;}
    break;

  case 46:
#line 423 "decafexpr.y"
    { BoolConstantAST *node = new BoolConstantAST(false); (yyval.ast) = node; ;}
    break;

  case 47:
#line 428 "decafexpr.y"
    {
    ConstantAST *node = new ConstantAST((yyvsp[(1) - (1)].numericalValue));
    (yyval.ast) = node;
;}
    break;

  case 48:
#line 433 "decafexpr.y"
    {
    ConstantAST *node = new ConstantAST((yyvsp[(1) - (1)].numericalValue));
    (yyval.ast) = node;
;}
    break;

  case 49:
#line 441 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();

    while((yyvsp[(2) - (4)].list)->size() > 0) {
        string name = (yyvsp[(2) - (4)].list)->pop_front();
        TypedSymbol *newNode = new TypedSymbol(name, (yyvsp[(3) - (4)].numericalValue));
        list->push_front(newNode);

        llvm::AllocaInst *Alloca = Builder.CreateAlloca(getLLVMType((yyvsp[(3) - (4)].numericalValue)), nullptr, name);
        descriptor *newVariableDecpr = new descriptor(name, (yyvsp[(3) - (4)].numericalValue), lineno, Alloca);
        currentST.insert(std::pair<string, descriptor* >(name, newVariableDecpr));
    }

    (yyval.list) = list;

;}
    break;

  case 50:
#line 460 "decafexpr.y"
    {
    (yyvsp[(2) - (2)].list)->push_front((yyvsp[(1) - (2)].list));
    (yyval.list) = (yyvsp[(2) - (2)].list);
;}
    break;

  case 51:
#line 465 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();
    list->push_front((yyvsp[(1) - (1)].list));
    (yyval.list) = list;
;}
    break;

  case 52:
#line 471 "decafexpr.y"
    {
    (yyval.list) = new decafStmtList();
;}
    break;

  case 53:
#line 478 "decafexpr.y"
    {
                BlockAST *node = new BlockAST((yyvsp[(2) - (4)].list), (yyvsp[(3) - (4)].list));
                (yyval.ast) = node;
        ;}
    break;

  case 54:
#line 483 "decafexpr.y"
    {
                BlockAST *node = new BlockAST(new decafStmtList(), new decafStmtList());
                (yyval.ast) = node;
        ;}
    break;

  case 55:
#line 492 "decafexpr.y"
    {
                SimpleStatement *stmt = new SimpleStatement(20);
                StatementAST *node = new StatementAST(stmt);
                (yyval.ast) = node;
        ;}
    break;

  case 56:
#line 498 "decafexpr.y"
    {
                SimpleStatement *stmt = new SimpleStatement(21);
                StatementAST *node = new StatementAST(stmt);
                (yyval.ast) = node;
        ;}
    break;

  case 57:
#line 504 "decafexpr.y"
    {
                StatementAST *node = new StatementAST((yyvsp[(1) - (1)].ast)); (yyval.ast) = node;
        ;}
    break;

  case 58:
#line 508 "decafexpr.y"
    {
                /// TODO: Finish after figure out the Block
                ForStmtAST *forStmt = new ForStmtAST((yyvsp[(3) - (9)].list), (yyvsp[(5) - (9)].ast), (yyvsp[(7) - (9)].list), (yyvsp[(9) - (9)].ast));
                (yyval.ast) = forStmt;
        ;}
    break;

  case 59:
#line 514 "decafexpr.y"
    {
                WhileStmt *whileStmt = new WhileStmt((yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast));
                StatementAST *node = new StatementAST(whileStmt);
                (yyval.ast) = node;
        ;}
    break;

  case 60:
#line 520 "decafexpr.y"
    {
                StatementAST *node = new StatementAST((yyvsp[(1) - (1)].ast));
                (yyval.ast) = node;
        ;}
    break;

  case 61:
#line 525 "decafexpr.y"
    {
                StatementAST *node = new StatementAST((yyvsp[(1) - (2)].ast));
                (yyval.ast) = node;
        ;}
    break;

  case 62:
#line 530 "decafexpr.y"
    {
                StatementAST *node = new StatementAST((yyvsp[(1) - (1)].ast)); (yyval.ast) = node;
        ;}
    break;

  case 63:
#line 534 "decafexpr.y"
    {
                StatementAST *node = new StatementAST((yyvsp[(1) - (2)].ast)); (yyval.ast) = node;
        ;}
    break;

  case 64:
#line 541 "decafexpr.y"
    {
    (yyvsp[(2) - (2)].list)->push_front((yyvsp[(1) - (2)].ast));
    (yyval.list) = (yyvsp[(2) - (2)].list);
;}
    break;

  case 65:
#line 546 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();
    list->push_front((yyvsp[(1) - (1)].ast));
    (yyval.list) = list;
;}
    break;

  case 66:
#line 552 "decafexpr.y"
    {
    (yyval.list) = new decafStmtList();
;}
    break;

  case 67:
#line 559 "decafexpr.y"
    {
            ReturnStmtAST *node = new ReturnStmtAST((yyvsp[(3) - (5)].ast));
            (yyval.ast) = node;
            //cout << "T_RETURN";
      ;}
    break;

  case 68:
#line 565 "decafexpr.y"
    {
            //decafAST *emptyNode = new decafAST();
            ReturnStmtAST *node = new ReturnStmtAST(NULL);
            (yyval.ast) = node;
      ;}
    break;

  case 69:
#line 571 "decafexpr.y"
    {
            ReturnStmtAST *node = new ReturnStmtAST(NULL);
            (yyval.ast) = node;
        ;}
    break;

  case 70:
#line 579 "decafexpr.y"
    {
            IfStmtAST *node = new IfStmtAST((yyvsp[(3) - (7)].ast), (yyvsp[(5) - (7)].ast), (yyvsp[(7) - (7)].ast));
            (yyval.ast) = node;
      ;}
    break;

  case 71:
#line 584 "decafexpr.y"
    {
            //decafStmtList *emptyNode = new decafStmtList();
            IfStmtAST *node = new IfStmtAST((yyvsp[(3) - (5)].ast), (yyvsp[(5) - (5)].ast), NULL);
            (yyval.ast) = node;
      ;}
    break;

  case 72:
#line 593 "decafexpr.y"
    {
            AssignAST *node = new AssignAST(*(yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 73:
#line 598 "decafexpr.y"
    {
        // Array. Just ignore in HW3
        AssignAST *node = new AssignAST(*(yyvsp[(1) - (6)].sval), (yyvsp[(3) - (6)].ast), (yyvsp[(6) - (6)].ast));
        (yyval.ast) = node;
;}
    break;

  case 74:
#line 606 "decafexpr.y"
    {
               (yyvsp[(3) - (3)].list)->push_front((yyvsp[(1) - (3)].ast));
               (yyval.list) = (yyvsp[(3) - (3)].list);
        ;}
    break;

  case 75:
#line 611 "decafexpr.y"
    {
    decafStmtList *list = new decafStmtList();
    list->push_front((yyvsp[(1) - (1)].ast));
    (yyval.list) = list;
;}
    break;

  case 76:
#line 621 "decafexpr.y"
    {
            MethodArgumentAST *node = new MethodArgumentAST((yyvsp[(1) - (1)].ast));
            (yyval.ast) = node;
            //cout << "MethodArg - Expr";
        ;}
    break;

  case 77:
#line 627 "decafexpr.y"
    {
            StringAST *strnode = new StringAST(*(yyvsp[(1) - (1)].sval));
            MethodArgumentAST *node = new MethodArgumentAST(strnode);
            (yyval.ast) = node;
            //cout << "MethodArg - String";
        ;}
    break;

  case 78:
#line 637 "decafexpr.y"
    {
            (yyvsp[(3) - (3)].list)->push_front((yyvsp[(1) - (3)].ast));
            (yyval.list) = (yyvsp[(3) - (3)].list);
            //cout << "MethodArg - WithComma";
        ;}
    break;

  case 79:
#line 643 "decafexpr.y"
    {
            decafStmtList *list = new decafStmtList();
            list->push_front((yyvsp[(1) - (1)].ast));
            (yyval.list) = list;
            //cout << "MethodArg - Ending";
        ;}
    break;

  case 80:
#line 653 "decafexpr.y"
    {
            MethodCallAST *node = new MethodCallAST(*(yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].list));
            (yyval.ast) = node;
            //cout << "MethodCall - With Arg";
        ;}
    break;

  case 81:
#line 659 "decafexpr.y"
    {
            decafStmtList *args = new decafStmtList();
            MethodCallAST *node = new MethodCallAST(*(yyvsp[(1) - (3)].sval), args);
            (yyval.ast) = node;
            //cout << "MethodCall - Without Arg";
        ;}
    break;

  case 82:
#line 668 "decafexpr.y"
    {
            rvalueAST *rvalue = new rvalueAST(*(yyvsp[(1) - (1)].sval), false);
            ExprAST *node = new ExprAST(rvalue);
            (yyval.ast) = node;
        ;}
    break;

  case 83:
#line 674 "decafexpr.y"
    {
            ExprAST *node = new ExprAST((yyvsp[(1) - (1)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 84:
#line 679 "decafexpr.y"
    {
            ExprAST *node = new ExprAST((yyvsp[(1) - (1)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 85:
#line 684 "decafexpr.y"
    {
            ExprAST *node = new ExprAST((yyvsp[(1) - (1)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 86:
#line 689 "decafexpr.y"
    {
            (yyval.ast) = (yyvsp[(1) - (1)].ast);
        ;}
    break;

  case 87:
#line 692 "decafexpr.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 88:
#line 694 "decafexpr.y"
    {
            rvalueAST *rvalue = new rvalueAST(*(yyvsp[(1) - (4)].sval), true, (yyvsp[(3) - (4)].ast));
            ExprAST *node = new ExprAST(rvalue);
            (yyval.ast) = node;
        ;}
    break;

  case 89:
#line 702 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(0, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 90:
#line 707 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(1, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 91:
#line 712 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(2, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 92:
#line 717 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(3, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 93:
#line 722 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(4, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 94:
#line 727 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(5, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 95:
#line 732 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(6, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 96:
#line 737 "decafexpr.y"
    {
             UnaryExprAST *node = new UnaryExprAST(15, (yyvsp[(2) - (2)].ast));
             (yyval.ast) = node;
        ;}
    break;

  case 97:
#line 742 "decafexpr.y"
    {
    BinaryExprAST *node = new BinaryExprAST(11, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
    (yyval.ast) = node;
;}
    break;

  case 98:
#line 747 "decafexpr.y"
    {
    BinaryExprAST *node = new BinaryExprAST(12, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
    (yyval.ast) = node;
;}
    break;

  case 99:
#line 752 "decafexpr.y"
    {
    BinaryExprAST *node = new BinaryExprAST(7, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
    (yyval.ast) = node;
;}
    break;

  case 100:
#line 757 "decafexpr.y"
    {
    BinaryExprAST *node = new BinaryExprAST(8, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
    (yyval.ast) = node;
;}
    break;

  case 101:
#line 762 "decafexpr.y"
    {
    BinaryExprAST *node = new BinaryExprAST(9, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
    (yyval.ast) = node;
;}
    break;

  case 102:
#line 767 "decafexpr.y"
    {
                UnaryExprAST *node = new UnaryExprAST(15, (yyvsp[(2) - (2)].ast));
        (yyval.ast) = node;
        ;}
    break;

  case 103:
#line 772 "decafexpr.y"
    {
             UnaryExprAST *node = new UnaryExprAST(16, (yyvsp[(2) - (2)].ast));
             (yyval.ast) = node;
        ;}
    break;

  case 104:
#line 777 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(10, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 105:
#line 782 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(13, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;

  case 106:
#line 787 "decafexpr.y"
    {
            BinaryExprAST *node = new BinaryExprAST(14, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast));
            (yyval.ast) = node;
        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2584 "decafexpr.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 793 "decafexpr.y"


int main() {
    // initialize LLVM
    llvm::LLVMContext &Context = llvm::getGlobalContext();
    // Make the module, which holds all the code.
    TheModule = new llvm::Module("Test", Context);
    // set up symbol table
    // set up dummy main function
    TheFunction = gen_main_def();
    // parse the input and create the abstract syntax tree
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
    // remove symbol table
    // Finish off the main function. (see the WARNING above)
    // return 0 from main, which is EXIT_SUCCESS
    Builder.CreateRet(llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32, 0)));
    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);
    // Print out all of the generated code to stderr
    TheModule->dump();
    return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}


