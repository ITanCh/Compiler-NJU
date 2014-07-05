/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "la.y"

	#include"node.h"
	#include"lex.yy.c"
	#include"table.h"
	Node* root;


/* Line 268 of yacc.c  */
#line 79 "la.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     TYPE = 261,
     SEMI = 262,
     COMMA = 263,
     ASSIGNOP = 264,
     RELOP = 265,
     PLUS = 266,
     MINUS = 267,
     STAR = 268,
     DIV = 269,
     AND = 270,
     OR = 271,
     DOT = 272,
     NOT = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THAN_ELSE = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 9 "la.y"

	int type_int;              /* Constant integer value */
	float type_float;               /* Constant floating point value */
	char *type_str;              /* Ptr to constant string (strings are malloc'd) */
	Node* node;
    


/* Line 293 of yacc.c  */
#line 154 "la.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 166 "la.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  121

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    16,    20,    24,
      27,    29,    33,    35,    37,    43,    46,    48,    49,    51,
      53,    58,    63,    67,    70,    74,    76,    79,    84,    87,
      90,    91,    94,    96,   100,   106,   114,   120,   123,   126,
     129,   130,   134,   136,   140,   142,   146,   150,   154,   158,
     162,   166,   170,   174,   178,   182,   185,   188,   193,   197,
     202,   206,   208,   210,   212,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    34,    33,    -1,    -1,    36,
      35,     7,    -1,    36,     7,    -1,    36,    41,     7,    -1,
      36,    41,    44,    -1,     1,     7,    -1,    40,    -1,    40,
       8,    35,    -1,     6,    -1,    37,    -1,    25,    38,    23,
      47,    24,    -1,    25,    39,    -1,     5,    -1,    -1,     5,
      -1,     5,    -1,    40,    21,     3,    22,    -1,     5,    19,
      42,    20,    -1,     5,    19,    20,    -1,     1,    20,    -1,
      43,     8,    42,    -1,    43,    -1,    36,    40,    -1,    23,
      47,    45,    24,    -1,     1,    24,    -1,    46,    45,    -1,
      -1,    51,     7,    -1,    44,    -1,    26,    51,     7,    -1,
      27,    19,    51,    20,    46,    -1,    27,    19,    51,    20,
      46,    28,    46,    -1,    29,    19,    51,    20,    46,    -1,
       1,    20,    -1,     1,     7,    -1,    48,    47,    -1,    -1,
      36,    49,     7,    -1,    50,    -1,    50,     8,    49,    -1,
      40,    -1,    40,     9,    51,    -1,    51,     9,    51,    -1,
      51,    15,    51,    -1,    51,    16,    51,    -1,    51,    10,
      51,    -1,    51,    11,    51,    -1,    51,    12,    51,    -1,
      51,    13,    51,    -1,    51,    14,    51,    -1,    19,    51,
      20,    -1,    12,    51,    -1,    18,    51,    -1,     5,    19,
      52,    20,    -1,     5,    19,    20,    -1,    51,    21,    51,
      22,    -1,    51,    17,     5,    -1,     5,    -1,     3,    -1,
       4,    -1,    51,     8,    52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    43,    43,    45,    46,    48,    49,    50,    51,    52,
      54,    55,    59,    60,    62,    63,    65,    66,    68,    71,
      72,    74,    75,    76,    78,    79,    81,    86,    87,    89,
      90,    92,    93,    94,    95,    96,    97,    98,    99,   102,
     103,   106,   109,   110,   112,   113,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   138,   139
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE", "SEMI",
  "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND",
  "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
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
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      35,    35,    36,    36,    37,    37,    38,    38,    39,    40,
      40,    41,    41,    41,    42,    42,    43,    44,    44,    45,
      45,    46,    46,    46,    46,    46,    46,    46,    46,    47,
      47,    48,    49,    49,    50,    50,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     1,     0,     1,     1,
       4,     4,     3,     2,     3,     1,     2,     4,     2,     2,
       0,     2,     1,     3,     5,     7,     5,     2,     2,     2,
       0,     3,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     4,     3,     4,
       3,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    17,     0,     2,     0,     0,    13,     9,
      18,     0,    15,     1,     3,     0,    19,     6,     0,    10,
       0,    40,    23,     0,     5,     0,     0,     0,     7,    40,
       8,     0,     0,    40,    22,     0,     0,    25,    19,    11,
       0,    28,     0,    44,     0,    42,    14,    39,    26,    21,
       0,    20,     0,    62,    63,    61,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,    41,     0,    24,
      38,    37,     0,    55,    56,     0,     0,     0,     0,    27,
      29,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    43,    58,    65,     0,    54,    33,     0,
       0,    46,    49,    50,    51,    52,    53,    47,    48,    60,
       0,     0,    57,     0,     0,    59,    64,    34,    36,     0,
      35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    31,     8,    11,    12,    19,
      20,    36,    37,    62,    63,    64,    32,    33,    44,    45,
      65,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
      12,     2,   -67,    10,     7,   -67,    12,    72,   -67,   -67,
      49,    51,   -67,   -67,   -67,     3,    35,   -67,    68,    38,
      13,     0,   -67,    -1,   -67,    71,    77,    62,   -67,     0,
     -67,    71,    63,     0,   -67,    71,    74,    80,   -67,   -67,
      69,   -67,    39,    29,    95,    99,   -67,   -67,    89,   -67,
       0,   -67,    32,   -67,   -67,    93,    96,    96,    96,    96,
      98,   108,   -67,    87,    39,   109,    96,   -67,    71,   -67,
     -67,   -67,    78,    28,    28,   163,   122,    96,    96,   -67,
     -67,   -67,    96,    96,    96,    96,    96,    96,    96,    96,
     123,    96,   202,   -67,   -67,   136,   120,   -67,   -67,   176,
     189,   202,    92,    28,    28,    28,    28,    92,    92,   -67,
     149,    96,   -67,    66,    66,   -67,   -67,   113,   -67,    66,
     -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   148,   -67,   117,    11,   -67,   -67,   -67,   -27,
     -67,   105,   -67,   147,   104,   -66,    31,   -67,    88,   -67,
     -56,    58
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -31
static const yytype_int8 yytable[] =
{
      73,    74,    75,    76,    43,     2,     2,    13,    48,     9,
      92,     7,    -4,     1,    27,    10,    95,     7,     2,    34,
      28,    99,   100,    22,     3,     3,   101,   102,   103,   104,
     105,   106,   107,   108,    35,   110,    29,     3,    66,    70,
      52,    43,    53,    54,    55,    90,    25,   117,   118,    91,
      26,    56,    71,   120,    23,    95,    41,    57,    58,    26,
      42,    35,    29,   -30,    47,    59,    60,    52,    61,    53,
      54,    55,   -16,    15,    21,    24,    38,    16,    56,    17,
      40,    53,    54,    55,    57,    58,    41,    46,    50,    29,
      56,    51,    59,    60,    49,    61,    57,    58,    94,    53,
      54,    55,    67,    84,    85,    86,    87,    68,    56,    90,
      26,    79,    72,    91,    57,    58,    81,    77,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    78,   109,    98,
      91,    82,    83,    84,    85,    86,    87,    88,    89,    90,
     112,   119,    39,    91,   111,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    14,    69,    93,    91,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    30,    80,   116,
      91,   115,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,     0,    97,    91,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,     0,   113,    91,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,     0,   114,
      91,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,     0,     0,    91
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-67))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      56,    57,    58,    59,    31,     6,     6,     0,    35,     7,
      66,     0,     0,     1,     1,     5,    72,     6,     6,    20,
       7,    77,    78,    20,    25,    25,    82,    83,    84,    85,
      86,    87,    88,    89,    23,    91,    23,    25,     9,     7,
       1,    68,     3,     4,     5,    17,     8,   113,   114,    21,
      21,    12,    20,   119,    19,   111,    24,    18,    19,    21,
      29,    50,    23,    24,    33,    26,    27,     1,    29,     3,
       4,     5,    23,     1,    23,     7,     5,     5,    12,     7,
       3,     3,     4,     5,    18,    19,    24,    24,     8,    23,
      12,    22,    26,    27,    20,    29,    18,    19,    20,     3,
       4,     5,     7,    11,    12,    13,    14,     8,    12,    17,
      21,    24,    19,    21,    18,    19,     7,    19,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,     5,     7,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      20,    28,    25,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     6,    50,    68,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    20,    64,   111,
      21,    22,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,    21,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    20,    21,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    20,
      21,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    25,    32,    33,    34,    36,    37,     7,
       5,    38,    39,     0,    33,     1,     5,     7,    35,    40,
      41,    23,    20,    19,     7,     8,    21,     1,     7,    23,
      44,    36,    47,    48,    20,    36,    42,    43,     5,    35,
       3,    24,    47,    40,    49,    50,    24,    47,    40,    20,
       8,    22,     1,     3,     4,     5,    12,    18,    19,    26,
      27,    29,    44,    45,    46,    51,     9,     7,     8,    42,
       7,    20,    19,    51,    51,    51,    51,    19,    19,    24,
      45,     7,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    21,    51,    49,    20,    51,    52,    20,     7,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,     5,
      51,     8,    20,    20,    20,    22,    52,    46,    46,    28,
      46
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

/* Line 1806 of yacc.c  */
#line 43 "la.y"
    {(yyval.node)=initNode("Program","");addChild((yyval.node),(yyvsp[(1) - (1)].node));root=(yyval.node);}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 45 "la.y"
    {(yyval.node)=initNode("ExtDefList","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 46 "la.y"
    {(yyval.node)=initNode("ExtDefList","");}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 48 "la.y"
    {(yyval.node)=initNode("ExtDef","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 49 "la.y"
    {(yyval.node)=initNode("ExtDef","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 50 "la.y"
    {(yyval.node)=initNode("ExtDef","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 51 "la.y"
    {(yyval.node)=initNode("ExtDef","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 52 "la.y"
    {errorFlag=0;/*printf("%sExtDef:error SEMI\n",$$->value);i*/}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 54 "la.y"
    {(yyval.node)=initNode("ExtDecList","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 55 "la.y"
    {(yyval.node)=initNode("ExtDecList","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 59 "la.y"
    {(yyval.node)=initNode("Specifier","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 60 "la.y"
    {(yyval.node)=initNode("Specifier","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 62 "la.y"
    {(yyval.node)=initNode("StructSpecifier","");addChild((yyval.node),(yyvsp[(5) - (5)].node));addChild((yyval.node),(yyvsp[(4) - (5)].node));addChild((yyval.node),(yyvsp[(3) - (5)].node));addChild((yyval.node),(yyvsp[(2) - (5)].node));addChild((yyval.node),(yyvsp[(1) - (5)].node));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 63 "la.y"
    {(yyval.node)=initNode("StructSpecifier","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 65 "la.y"
    {(yyval.node)=initNode("OptTag","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 66 "la.y"
    {(yyval.node)=initNode("OptTag","");}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 68 "la.y"
    {(yyval.node)=initNode("Tag","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 71 "la.y"
    {(yyval.node)=initNode("VarDec","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 72 "la.y"
    {(yyval.node)=initNode("VarDec","");addChild((yyval.node),(yyvsp[(4) - (4)].node));addChild((yyval.node),(yyvsp[(3) - (4)].node));addChild((yyval.node),(yyvsp[(2) - (4)].node));addChild((yyval.node),(yyvsp[(1) - (4)].node));}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 74 "la.y"
    {(yyval.node)=initNode("FunDec","");addChild((yyval.node),(yyvsp[(4) - (4)].node));addChild((yyval.node),(yyvsp[(3) - (4)].node));addChild((yyval.node),(yyvsp[(2) - (4)].node));addChild((yyval.node),(yyvsp[(1) - (4)].node));}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 75 "la.y"
    {(yyval.node)=initNode("FunDec","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 76 "la.y"
    {errorFlag=0;/*printf("%sFunDec\n",$$->value);*/}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 78 "la.y"
    {(yyval.node)=initNode("VarList","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 79 "la.y"
    {(yyval.node)=initNode("VarList","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 81 "la.y"
    {(yyval.node)=initNode("ParamDec","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 86 "la.y"
    {(yyval.node)=initNode("CompSt","");addChild((yyval.node),(yyvsp[(4) - (4)].node));addChild((yyval.node),(yyvsp[(3) - (4)].node));addChild((yyval.node),(yyvsp[(2) - (4)].node));addChild((yyval.node),(yyvsp[(1) - (4)].node));}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 87 "la.y"
    {errorFlag=0;/*printf("%sCompSt RC\n",$$->value);*/}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 89 "la.y"
    {(yyval.node)=initNode("StmtList","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 90 "la.y"
    {(yyval.node)=initNode("StmtList","");}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 92 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 93 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 94 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 95 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(5) - (5)].node));addChild((yyval.node),(yyvsp[(4) - (5)].node));addChild((yyval.node),(yyvsp[(3) - (5)].node));addChild((yyval.node),(yyvsp[(2) - (5)].node));addChild((yyval.node),(yyvsp[(1) - (5)].node));}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 96 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(7) - (7)].node));addChild((yyval.node),(yyvsp[(6) - (7)].node));addChild((yyval.node),(yyvsp[(5) - (7)].node));addChild((yyval.node),(yyvsp[(4) - (7)].node));addChild((yyval.node),(yyvsp[(3) - (7)].node));addChild((yyval.node),(yyvsp[(2) - (7)].node));addChild((yyval.node),(yyvsp[(1) - (7)].node));}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 97 "la.y"
    {(yyval.node)=initNode("Stmt","");addChild((yyval.node),(yyvsp[(5) - (5)].node));addChild((yyval.node),(yyvsp[(4) - (5)].node));addChild((yyval.node),(yyvsp[(3) - (5)].node));addChild((yyval.node),(yyvsp[(2) - (5)].node));addChild((yyval.node),(yyvsp[(1) - (5)].node));}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 98 "la.y"
    {errorFlag=0;}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 99 "la.y"
    {errorFlag=0;/*printf("%sStmt SEMI\n",$$->value);*/}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 102 "la.y"
    {(yyval.node)=initNode("DefList","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 103 "la.y"
    {(yyval.node)=initNode("DefList","");}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 106 "la.y"
    {(yyval.node)=initNode("Def","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 109 "la.y"
    {(yyval.node)=initNode("DecList","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 110 "la.y"
    {(yyval.node)=initNode("DecList","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 112 "la.y"
    {(yyval.node)=initNode("Dec","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 113 "la.y"
    {(yyval.node)=initNode("Dec","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 116 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 117 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 118 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 119 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 120 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 121 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 122 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 123 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 124 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 125 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 126 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(2) - (2)].node));addChild((yyval.node),(yyvsp[(1) - (2)].node));}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 127 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(4) - (4)].node));addChild((yyval.node),(yyvsp[(3) - (4)].node));addChild((yyval.node),(yyvsp[(2) - (4)].node));addChild((yyval.node),(yyvsp[(1) - (4)].node));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 128 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 129 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(4) - (4)].node));addChild((yyval.node),(yyvsp[(3) - (4)].node));addChild((yyval.node),(yyvsp[(2) - (4)].node));addChild((yyval.node),(yyvsp[(1) - (4)].node));}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 130 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 131 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 132 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 133 "la.y"
    {(yyval.node)=initNode("Exp","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 138 "la.y"
    {(yyval.node)=initNode("Args","");addChild((yyval.node),(yyvsp[(3) - (3)].node));addChild((yyval.node),(yyvsp[(2) - (3)].node));addChild((yyval.node),(yyvsp[(1) - (3)].node));}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 139 "la.y"
    {(yyval.node)=initNode("Args","");addChild((yyval.node),(yyvsp[(1) - (1)].node));}
    break;



/* Line 1806 of yacc.c  */
#line 1963 "la.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 142 "la.y"


int main(int argc, char** argv)
{
 	if (argc <= 1) return 1;
	FILE* f = fopen(argv[1],"r");
	if (!f)
	{
		perror(argv[1]);
		return 1;
	}	
	root=NULL;
	yylineno=1;
	yyrestart(f);
	yyparse();
	if(errorFlag){
		//printTree(root,0);	
		initTable();
		Program(root);
	}
	return 0;
}

int yyerror(char* msg)
{
	printf("Error type B at line %d:%s===>unexpected near '%s'\n",yylineno,msg,yylval.node->value);
}

