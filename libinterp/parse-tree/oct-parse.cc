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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         octave_parse
#define yypush_parse    octave_push_parse
#define yypull_parse    octave_pull_parse
#define yypstate_new    octave_pstate_new
#define yypstate_delete octave_pstate_delete
#define yypstate        octave_pstate
#define yylex           octave_lex
#define yyerror         octave_error
#define yylval          octave_lval
#define yychar          octave_char
#define yydebug         octave_debug
#define yynerrs         octave_nerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 29 "oct-parse.yy"

#define YYDEBUG 1

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cassert>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <map>
#include <sstream>

#include "Cell.h"
#include "Matrix.h"
#include "cmd-edit.h"
#include "cmd-hist.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-env.h"
#include "oct-time.h"
#include "quit.h"

#include "comment-list.h"
#include "defaults.h"
#include "defun.h"
#include "dirfns.h"
#include "dynamic-ld.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "load-path.h"
#include "oct-hist.h"
#include "oct-map.h"
#include "ov-fcn-handle.h"
#include "ov-usr-fcn.h"
#include "ov-null-mat.h"
#include "toplev.h"
#include "pager.h"
#include "parse.h"
#include "pt-all.h"
#include "pt-eval.h"
#include "symtab.h"
#include "token.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

// oct-parse.h must be included after pt-all.h
#include <oct-parse.h>

extern int octave_lex (YYSTYPE *, void *);

// Global access to currently active lexer.
// FIXME -- to be removed after more parser+lexer refactoring.
octave_base_lexer *LEXER = 0;

#if defined (GNULIB_NAMESPACE)
// Calls to the following functions appear in the generated output from
// Bison without the namespace tag.  Redefine them so we will use them
// via the gnulib namespace.
#define fclose GNULIB_NAMESPACE::fclose
#define fprintf GNULIB_NAMESPACE::fprintf
#define malloc GNULIB_NAMESPACE::malloc
#endif

// TRUE means we printed messages about reading startup files.
bool reading_startup_message_printed = false;

// List of autoloads (function -> file mapping).
static std::map<std::string, std::string> autoload_map;

// Forward declarations for some functions defined at the bottom of
// the file.

static void yyerror (octave_base_parser& parser, const char *s);

// Finish building a statement.
template <class T>
static tree_statement *
make_statement (T *arg)
{
  octave_comment_list *comment = octave_comment_buffer::get_comment ();

  return new tree_statement (arg, comment);
}

#define ABORT_PARSE \
  do \
    { \
      yyerrok; \
      if ((interactive || forced_interactive) \
          && ! lexer.input_from_eval_string ()) \
        YYACCEPT; \
      else \
        YYABORT; \
    } \
  while (0)

#define lexer parser.lexer
#define scanner lexer.scanner



/* Line 268 of yacc.c  */
#line 191 "parse-tree/oct-parse.cc"

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
     ADD_EQ = 258,
     SUB_EQ = 259,
     MUL_EQ = 260,
     DIV_EQ = 261,
     LEFTDIV_EQ = 262,
     POW_EQ = 263,
     EMUL_EQ = 264,
     EDIV_EQ = 265,
     ELEFTDIV_EQ = 266,
     EPOW_EQ = 267,
     AND_EQ = 268,
     OR_EQ = 269,
     LSHIFT_EQ = 270,
     RSHIFT_EQ = 271,
     LSHIFT = 272,
     RSHIFT = 273,
     EXPR_AND_AND = 274,
     EXPR_OR_OR = 275,
     EXPR_AND = 276,
     EXPR_OR = 277,
     EXPR_NOT = 278,
     EXPR_LT = 279,
     EXPR_LE = 280,
     EXPR_EQ = 281,
     EXPR_NE = 282,
     EXPR_GE = 283,
     EXPR_GT = 284,
     LEFTDIV = 285,
     EMUL = 286,
     EDIV = 287,
     ELEFTDIV = 288,
     EPLUS = 289,
     EMINUS = 290,
     HERMITIAN = 291,
     TRANSPOSE = 292,
     PLUS_PLUS = 293,
     MINUS_MINUS = 294,
     POW = 295,
     EPOW = 296,
     NUM = 297,
     IMAG_NUM = 298,
     STRUCT_ELT = 299,
     NAME = 300,
     END = 301,
     DQ_STRING = 302,
     SQ_STRING = 303,
     FOR = 304,
     PARFOR = 305,
     WHILE = 306,
     DO = 307,
     UNTIL = 308,
     IF = 309,
     ELSEIF = 310,
     ELSE = 311,
     SWITCH = 312,
     CASE = 313,
     OTHERWISE = 314,
     BREAK = 315,
     CONTINUE = 316,
     FUNC_RET = 317,
     UNWIND = 318,
     CLEANUP = 319,
     TRY = 320,
     CATCH = 321,
     GLOBAL = 322,
     PERSISTENT = 323,
     FCN_HANDLE = 324,
     PROPERTIES = 325,
     METHODS = 326,
     EVENTS = 327,
     ENUMERATION = 328,
     METAQUERY = 329,
     SUPERCLASSREF = 330,
     GET = 331,
     SET = 332,
     FCN = 333,
     END_OF_INPUT = 334,
     LEXICAL_ERROR = 335,
     INPUT_FILE = 336,
     CLASSDEF = 337,
     UNARY = 338
   };
#endif
/* Tokens.  */
#define ADD_EQ 258
#define SUB_EQ 259
#define MUL_EQ 260
#define DIV_EQ 261
#define LEFTDIV_EQ 262
#define POW_EQ 263
#define EMUL_EQ 264
#define EDIV_EQ 265
#define ELEFTDIV_EQ 266
#define EPOW_EQ 267
#define AND_EQ 268
#define OR_EQ 269
#define LSHIFT_EQ 270
#define RSHIFT_EQ 271
#define LSHIFT 272
#define RSHIFT 273
#define EXPR_AND_AND 274
#define EXPR_OR_OR 275
#define EXPR_AND 276
#define EXPR_OR 277
#define EXPR_NOT 278
#define EXPR_LT 279
#define EXPR_LE 280
#define EXPR_EQ 281
#define EXPR_NE 282
#define EXPR_GE 283
#define EXPR_GT 284
#define LEFTDIV 285
#define EMUL 286
#define EDIV 287
#define ELEFTDIV 288
#define EPLUS 289
#define EMINUS 290
#define HERMITIAN 291
#define TRANSPOSE 292
#define PLUS_PLUS 293
#define MINUS_MINUS 294
#define POW 295
#define EPOW 296
#define NUM 297
#define IMAG_NUM 298
#define STRUCT_ELT 299
#define NAME 300
#define END 301
#define DQ_STRING 302
#define SQ_STRING 303
#define FOR 304
#define PARFOR 305
#define WHILE 306
#define DO 307
#define UNTIL 308
#define IF 309
#define ELSEIF 310
#define ELSE 311
#define SWITCH 312
#define CASE 313
#define OTHERWISE 314
#define BREAK 315
#define CONTINUE 316
#define FUNC_RET 317
#define UNWIND 318
#define CLEANUP 319
#define TRY 320
#define CATCH 321
#define GLOBAL 322
#define PERSISTENT 323
#define FCN_HANDLE 324
#define PROPERTIES 325
#define METHODS 326
#define EVENTS 327
#define ENUMERATION 328
#define METAQUERY 329
#define SUPERCLASSREF 330
#define GET 331
#define SET 332
#define FCN 333
#define END_OF_INPUT 334
#define LEXICAL_ERROR 335
#define INPUT_FILE 336
#define CLASSDEF 337
#define UNARY 338




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 157 "oct-parse.yy"

  // The type of the basic tokens returned by the lexer.
  token *tok_val;

  // Comment strings that we need to deal with mid-rule.
  octave_comment_list *comment_type;

  // Types for the nonterminals we generate.
  char sep_type;
  tree *tree_type;
  tree_matrix *tree_matrix_type;
  tree_cell *tree_cell_type;
  tree_expression *tree_expression_type;
  tree_constant *tree_constant_type;
  tree_fcn_handle *tree_fcn_handle_type;
  tree_anon_fcn_handle *tree_anon_fcn_handle_type;
  tree_identifier *tree_identifier_type;
  tree_index_expression *tree_index_expression_type;
  tree_colon_expression *tree_colon_expression_type;
  tree_argument_list *tree_argument_list_type;
  tree_parameter_list *tree_parameter_list_type;
  tree_command *tree_command_type;
  tree_if_command *tree_if_command_type;
  tree_if_clause *tree_if_clause_type;
  tree_if_command_list *tree_if_command_list_type;
  tree_switch_command *tree_switch_command_type;
  tree_switch_case *tree_switch_case_type;
  tree_switch_case_list *tree_switch_case_list_type;
  tree_decl_elt *tree_decl_elt_type;
  tree_decl_init_list *tree_decl_init_list_type;
  tree_decl_command *tree_decl_command_type;
  tree_statement *tree_statement_type;
  tree_statement_list *tree_statement_list_type;
  octave_user_function *octave_user_function_type;
  void *dummy_type;



/* Line 293 of yacc.c  */
#line 432 "parse-tree/oct-parse.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#ifndef YYPUSH_DECLS
#  define YYPUSH_DECLS
struct yypstate;
typedef struct yypstate yypstate;
enum { YYPUSH_MORE = 4 };

#if defined __STDC__ || defined __cplusplus
int yyparse (octave_base_parser& parser);
#else
int yyparse ();
#endif
#if defined __STDC__ || defined __cplusplus
int yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, octave_base_parser& parser);
#else
int yypush_parse ();
#endif
#if defined __STDC__ || defined __cplusplus
int yypull_parse (yypstate *yyps, octave_base_parser& parser);
#else
int yypull_parse ();
#endif
#if defined __STDC__ || defined __cplusplus
yypstate * yypstate_new (void);
#else
yypstate * yypstate_new ();
#endif
#if defined __STDC__ || defined __cplusplus
void yypstate_delete (yypstate *yyps);
#else
void yypstate_delete ();
#endif
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 477 "parse-tree/oct-parse.cc"

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
#define YYFINAL  122
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1290

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  104
/* YYNRULES -- Number of rules.  */
#define YYNRULES  268
/* YYNRULES -- Number of states.  */
#define YYNSTATES  490

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      93,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      90,   100,     7,     6,    97,     5,    91,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    96,
       2,     3,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    98,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    19,
      22,    25,    27,    31,    32,    34,    37,    39,    43,    45,
      47,    49,    52,    54,    57,    59,    61,    63,    65,    67,
      69,    71,    73,    76,    80,    84,    88,    90,    93,    95,
      99,   102,   106,   110,   112,   115,   117,   121,   123,   126,
     129,   133,   135,   137,   139,   141,   143,   145,   147,   151,
     153,   155,   157,   159,   161,   165,   169,   173,   175,   177,
     180,   183,   187,   192,   196,   201,   204,   207,   211,   217,
     220,   223,   226,   229,   232,   236,   240,   244,   248,   252,
     256,   260,   264,   268,   272,   276,   280,   282,   284,   288,
     290,   294,   298,   302,   306,   310,   314,   318,   322,   326,
     330,   334,   338,   340,   344,   348,   352,   356,   360,   364,
     368,   372,   376,   380,   384,   388,   392,   396,   400,   402,
     404,   406,   408,   410,   412,   414,   416,   418,   420,   422,
     425,   428,   430,   433,   434,   436,   441,   443,   445,   447,
     452,   454,   457,   461,   464,   471,   476,   483,   484,   486,
     488,   491,   493,   496,   503,   508,   515,   522,   531,   542,
     551,   564,   566,   568,   570,   580,   590,   596,   597,   599,
     601,   605,   608,   609,   611,   613,   617,   620,   622,   626,
     628,   632,   637,   640,   644,   650,   652,   656,   660,   663,
     668,   672,   674,   676,   679,   681,   686,   693,   694,   698,
     700,   704,   706,   711,   714,   715,   717,   722,   725,   731,
     735,   737,   739,   741,   743,   747,   751,   755,   759,   762,
     769,   771,   775,   777,   783,   786,   793,   795,   799,   802,
     809,   811,   815,   817,   820,   827,   829,   833,   838,   839,
     841,   843,   845,   847,   850,   853,   854,   856,   857,   859,
     861,   864,   866,   868,   870,   873,   876,   879,   880
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     102,     0,    -1,   103,    -1,   104,   198,    -1,   198,    -1,
      93,    -1,    85,    -1,   104,    -1,   104,    93,    -1,   104,
      85,    -1,   105,   200,    -1,   109,    -1,   105,   199,   109,
      -1,    -1,   107,    -1,   108,   204,    -1,   109,    -1,   108,
     203,   109,    -1,   137,    -1,   138,    -1,   110,    -1,   112,
     111,    -1,   115,    -1,   111,   115,    -1,    51,    -1,    81,
      -1,    80,    -1,    53,    -1,    54,    -1,    48,    -1,    49,
      -1,   115,    -1,    94,    95,    -1,    94,    96,    95,    -1,
      94,    97,    95,    -1,    94,   118,    95,    -1,   119,    -1,
     119,    96,    -1,   123,    -1,   119,    96,   123,    -1,    92,
      98,    -1,    92,    96,    98,    -1,    92,   121,    98,    -1,
     122,    -1,   122,    96,    -1,   123,    -1,   122,    96,   123,
      -1,   129,    -1,   129,    97,    -1,    99,    75,    -1,    99,
     160,   109,    -1,   112,    -1,   116,    -1,   124,    -1,   117,
      -1,   120,    -1,   114,    -1,   113,    -1,    90,   137,   100,
      -1,     4,    -1,    29,    -1,   137,    -1,   127,    -1,   128,
      -1,   129,    97,   127,    -1,   129,    97,   128,    -1,   129,
      97,   137,    -1,    91,    -1,   126,    -1,   131,    44,    -1,
     131,    45,    -1,   131,    90,   100,    -1,   131,    90,   129,
     100,    -1,   131,    92,    98,    -1,   131,    92,   129,    98,
      -1,   131,    42,    -1,   131,    43,    -1,   131,   130,    50,
      -1,   131,   130,    90,   137,   100,    -1,    44,   131,    -1,
      45,   131,    -1,    29,   131,    -1,     6,   131,    -1,     5,
     131,    -1,   131,    46,   131,    -1,   131,    47,   131,    -1,
     131,     6,   131,    -1,   131,     5,   131,    -1,   131,     7,
     131,    -1,   131,     8,   131,    -1,   131,    40,   131,    -1,
     131,    41,   131,    -1,   131,    37,   131,    -1,   131,    38,
     131,    -1,   131,    36,   131,    -1,   131,    39,   131,    -1,
     133,    -1,   131,    -1,   133,     4,   131,    -1,   132,    -1,
     134,    23,   134,    -1,   134,    24,   134,    -1,   134,    30,
     134,    -1,   134,    31,   134,    -1,   134,    32,   134,    -1,
     134,    34,   134,    -1,   134,    35,   134,    -1,   134,    33,
     134,    -1,   134,    27,   134,    -1,   134,    28,   134,    -1,
     134,    25,   134,    -1,   134,    26,   134,    -1,   134,    -1,
     135,     3,   137,    -1,   135,     9,   137,    -1,   135,    10,
     137,    -1,   135,    11,   137,    -1,   135,    12,   137,    -1,
     135,    13,   137,    -1,   135,    14,   137,    -1,   135,    21,
     137,    -1,   135,    22,   137,    -1,   135,    15,   137,    -1,
     135,    16,   137,    -1,   135,    17,   137,    -1,   135,    18,
     137,    -1,   135,    19,   137,    -1,   135,    20,   137,    -1,
     134,    -1,   136,    -1,   125,    -1,   139,    -1,   143,    -1,
     154,    -1,   155,    -1,   156,    -1,   167,    -1,   165,    -1,
     175,    -1,    73,   140,    -1,    74,   140,    -1,   142,    -1,
     140,   142,    -1,    -1,   112,    -1,   112,     3,   141,   137,
      -1,   128,    -1,   144,    -1,   149,    -1,    60,   197,   145,
      52,    -1,   146,    -1,   146,   148,    -1,   137,   204,   106,
      -1,   146,   147,    -1,    61,   197,   204,   137,   204,   106,
      -1,    62,   197,   204,   106,    -1,    63,   197,   137,   204,
     150,    52,    -1,    -1,   153,    -1,   151,    -1,   151,   153,
      -1,   152,    -1,   151,   152,    -1,    64,   197,   204,   137,
     204,   106,    -1,    65,   197,   204,   106,    -1,    57,   197,
     137,   204,   106,    52,    -1,    58,   197,   204,   106,    59,
     137,    -1,    55,   197,   135,     3,   137,   204,   106,    52,
      -1,    55,   197,    90,   135,     3,   137,   100,   204,   106,
      52,    -1,    56,   197,   135,     3,   137,   204,   106,    52,
      -1,    56,   197,    90,   135,     3,   137,    97,   137,   100,
     204,   106,    52,    -1,    66,    -1,    67,    -1,    68,    -1,
      69,   197,   204,   106,    70,   197,   204,   106,    52,    -1,
      71,   197,   204,   106,    72,   197,   204,   106,    52,    -1,
      71,   197,   204,   106,    52,    -1,    -1,    90,    -1,   100,
      -1,   158,   161,   159,    -1,   158,     1,    -1,    -1,   162,
      -1,   142,    -1,   162,    97,   142,    -1,    94,    95,    -1,
     164,    -1,    94,   164,    95,    -1,   112,    -1,   164,    97,
     112,    -1,    87,   201,   106,    85,    -1,   157,    84,    -1,
     166,   197,   169,    -1,   166,   197,   163,     3,   169,    -1,
     112,    -1,    82,    91,   112,    -1,    83,    91,   112,    -1,
     168,   170,    -1,   160,   204,   106,   171,    -1,   204,   106,
     171,    -1,    52,    -1,    85,    -1,    88,   197,    -1,    52,
      -1,   172,   176,   112,   179,    -1,   174,   204,   181,   204,
     197,   173,    -1,    -1,    90,   177,   100,    -1,   178,    -1,
     177,    97,   178,    -1,   112,    -1,   112,     3,   141,   137,
      -1,    29,   112,    -1,    -1,   180,    -1,    30,   112,    91,
     112,    -1,    30,   112,    -1,   180,    27,   112,    91,   112,
      -1,   180,    27,   112,    -1,   183,    -1,   187,    -1,   190,
      -1,   194,    -1,   181,   204,   183,    -1,   181,   204,   187,
      -1,   181,   204,   190,    -1,   181,   204,   194,    -1,    76,
     197,    -1,   182,   176,   204,   184,   204,    52,    -1,   185,
      -1,   184,   204,   185,    -1,   112,    -1,   112,     3,   141,
     137,    96,    -1,    77,   197,    -1,   186,   176,   204,   188,
     204,    52,    -1,   167,    -1,   188,   204,   167,    -1,    78,
     197,    -1,   189,   176,   204,   191,   204,    52,    -1,   192,
      -1,   191,   204,   192,    -1,   112,    -1,    79,   197,    -1,
     193,   176,   204,   195,   204,    52,    -1,   196,    -1,   195,
     204,   196,    -1,   112,    90,   137,   100,    -1,    -1,    86,
      -1,     1,    -1,    97,    -1,    96,    -1,   199,    97,    -1,
     199,    96,    -1,    -1,   199,    -1,    -1,   202,    -1,    93,
      -1,   202,    93,    -1,    97,    -1,    96,    -1,    93,    -1,
     203,    97,    -1,   203,    96,    -1,   203,    93,    -1,    -1,
     203,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   310,   310,   315,   317,   321,   323,   328,   330,   332,
     336,   340,   342,   347,   348,   352,   356,   358,   362,   364,
     366,   378,   386,   388,   399,   407,   411,   415,   417,   421,
     423,   425,   429,   431,   433,   435,   439,   441,   445,   447,
     454,   456,   458,   462,   464,   468,   470,   478,   480,   484,
     491,   498,   500,   502,   504,   509,   511,   513,   515,   519,
     526,   532,   534,   536,   538,   543,   548,   555,   559,   561,
     563,   565,   571,   577,   583,   589,   591,   593,   595,   597,
     599,   601,   603,   605,   607,   609,   611,   613,   615,   617,
     619,   621,   623,   625,   627,   629,   633,   637,   639,   646,
     648,   650,   652,   654,   656,   658,   660,   662,   664,   666,
     668,   670,   674,   688,   690,   692,   694,   696,   698,   700,
     702,   704,   706,   708,   710,   712,   714,   716,   720,   735,
     737,   745,   747,   749,   751,   753,   755,   757,   759,   767,
     772,   779,   781,   789,   791,   793,   798,   808,   810,   818,
     825,   827,   834,   840,   847,   855,   863,   871,   872,   874,
     876,   883,   885,   892,   896,   906,   913,   918,   924,   930,
     936,   948,   953,   958,   969,   975,   981,   993,  1020,  1033,
    1040,  1047,  1056,  1057,  1070,  1072,  1083,  1088,  1096,  1106,
    1108,  1119,  1139,  1148,  1154,  1162,  1171,  1177,  1185,  1196,
    1198,  1202,  1211,  1251,  1258,  1270,  1274,  1279,  1280,  1284,
    1286,  1290,  1292,  1294,  1300,  1301,  1305,  1307,  1309,  1311,
    1315,  1317,  1319,  1321,  1323,  1325,  1327,  1329,  1333,  1338,
    1343,  1345,  1349,  1351,  1355,  1359,  1363,  1365,  1369,  1373,
    1377,  1379,  1383,  1387,  1391,  1395,  1397,  1401,  1410,  1413,
    1415,  1418,  1420,  1422,  1424,  1429,  1430,  1435,  1436,  1440,
    1442,  1446,  1448,  1450,  1452,  1454,  1456,  1461,  1462
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "':'", "'-'", "'+'", "'*'", "'/'",
  "ADD_EQ", "SUB_EQ", "MUL_EQ", "DIV_EQ", "LEFTDIV_EQ", "POW_EQ",
  "EMUL_EQ", "EDIV_EQ", "ELEFTDIV_EQ", "EPOW_EQ", "AND_EQ", "OR_EQ",
  "LSHIFT_EQ", "RSHIFT_EQ", "LSHIFT", "RSHIFT", "EXPR_AND_AND",
  "EXPR_OR_OR", "EXPR_AND", "EXPR_OR", "EXPR_NOT", "EXPR_LT", "EXPR_LE",
  "EXPR_EQ", "EXPR_NE", "EXPR_GE", "EXPR_GT", "LEFTDIV", "EMUL", "EDIV",
  "ELEFTDIV", "EPLUS", "EMINUS", "HERMITIAN", "TRANSPOSE", "PLUS_PLUS",
  "MINUS_MINUS", "POW", "EPOW", "NUM", "IMAG_NUM", "STRUCT_ELT", "NAME",
  "END", "DQ_STRING", "SQ_STRING", "FOR", "PARFOR", "WHILE", "DO", "UNTIL",
  "IF", "ELSEIF", "ELSE", "SWITCH", "CASE", "OTHERWISE", "BREAK",
  "CONTINUE", "FUNC_RET", "UNWIND", "CLEANUP", "TRY", "CATCH", "GLOBAL",
  "PERSISTENT", "FCN_HANDLE", "PROPERTIES", "METHODS", "EVENTS",
  "ENUMERATION", "METAQUERY", "SUPERCLASSREF", "GET", "SET", "FCN",
  "END_OF_INPUT", "LEXICAL_ERROR", "INPUT_FILE", "CLASSDEF", "UNARY",
  "'('", "'.'", "'{'", "'\\n'", "'['", "']'", "';'", "','", "'}'", "'@'",
  "')'", "$accept", "input", "input1", "simple_list", "simple_list1",
  "opt_list", "list", "list1", "statement", "word_list_cmd", "word_list",
  "identifier", "superclass_identifier", "meta_identifier", "string",
  "constant", "matrix", "matrix_rows", "matrix_rows1", "cell", "cell_rows",
  "cell_rows1", "cell_or_matrix_row", "fcn_handle", "anon_fcn_handle",
  "primary_expr", "magic_colon", "magic_tilde", "arg_list",
  "indirect_ref_op", "oper_expr", "colon_expr", "colon_expr1",
  "simple_expr", "assign_lhs", "assign_expr", "expression", "command",
  "declaration", "decl1", "decl_param_init", "decl2", "select_command",
  "if_command", "if_cmd_list", "if_cmd_list1", "elseif_clause",
  "else_clause", "switch_command", "case_list", "case_list1",
  "switch_case", "default_case", "loop_command", "jump_command",
  "except_command", "push_fcn_symtab", "param_list_beg", "param_list_end",
  "param_list", "param_list1", "param_list2", "return_list",
  "return_list1", "file", "function_beg", "function", "fcn_name",
  "function1", "function2", "function_end", "classdef_beg", "classdef_end",
  "classdef1", "classdef", "opt_attr_list", "attr_list", "attr",
  "opt_superclasses", "superclasses", "class_body", "properties_beg",
  "properties_block", "properties_list", "class_property", "methods_beg",
  "methods_block", "methods_list", "events_beg", "events_block",
  "events_list", "class_event", "enum_beg", "enum_block", "enum_list",
  "class_enum", "stash_comment", "parse_error", "sep_no_nl",
  "opt_sep_no_nl", "opt_nl", "nl", "sep", "opt_sep", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,    58,    45,    43,    42,    47,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
      40,    46,   123,    10,    91,    93,    59,    44,   125,    64,
      41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   103,   103,   103,   103,   103,
     104,   105,   105,   106,   106,   107,   108,   108,   109,   109,
     109,   110,   111,   111,   112,   113,   114,   115,   115,   116,
     116,   116,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   120,   121,   121,   122,   122,   123,   123,   124,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     128,   129,   129,   129,   129,   129,   129,   130,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   132,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   135,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   137,   137,
     137,   138,   138,   138,   138,   138,   138,   138,   138,   139,
     139,   140,   140,   141,   142,   142,   142,   143,   143,   144,
     145,   145,   146,   146,   147,   148,   149,   150,   150,   150,
     150,   151,   151,   152,   153,   154,   154,   154,   154,   154,
     154,   155,   155,   155,   156,   156,   156,   157,   158,   159,
     160,   160,   161,   161,   162,   162,   163,   163,   163,   164,
     164,   165,   166,   167,   167,   168,   168,   168,   169,   170,
     170,   171,   171,   172,   173,   174,   175,   176,   176,   177,
     177,   178,   178,   178,   179,   179,   180,   180,   180,   180,
     181,   181,   181,   181,   181,   181,   181,   181,   182,   183,
     184,   184,   185,   185,   186,   187,   188,   188,   189,   190,
     191,   191,   192,   193,   194,   195,   195,   196,   197,   198,
     198,   199,   199,   199,   199,   200,   200,   201,   201,   202,
     202,   203,   203,   203,   203,   203,   203,   204,   204
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       2,     1,     3,     0,     1,     2,     1,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     3,     3,     1,     2,     1,     3,
       2,     3,     3,     1,     2,     1,     3,     1,     2,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     1,     2,
       2,     3,     4,     3,     4,     2,     2,     3,     5,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     0,     1,     4,     1,     1,     1,     4,
       1,     2,     3,     2,     6,     4,     6,     0,     1,     1,
       2,     1,     2,     6,     4,     6,     6,     8,    10,     8,
      12,     1,     1,     1,     9,     9,     5,     0,     1,     1,
       3,     2,     0,     1,     1,     3,     2,     1,     3,     1,
       3,     4,     2,     3,     5,     1,     3,     3,     2,     4,
       3,     1,     1,     2,     1,     4,     6,     0,     3,     1,
       3,     1,     4,     2,     0,     1,     4,     2,     5,     3,
       1,     1,     1,     1,     3,     3,     3,     3,     2,     6,
       1,     3,     1,     5,     2,     6,     1,     3,     2,     6,
       1,     3,     1,     2,     6,     1,     3,     4,     0,     1,
       1,     1,     1,     2,     2,     0,     1,     0,     1,     1,
       2,     1,     1,     1,     2,     2,     2,     0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   250,     0,     0,     0,     0,     0,    29,    30,    24,
      27,    28,   248,   248,   248,   248,   248,   248,   171,   172,
     173,   248,   248,     0,     0,    26,    25,     6,   249,   257,
     248,     0,     0,     5,     0,     0,     0,     2,     0,   255,
      11,    20,    51,    57,    56,    31,    52,    54,    55,    53,
     130,    68,    97,    99,    96,   128,     0,   129,    18,    19,
     131,   132,   147,   148,   133,   134,   135,     0,   137,   248,
     136,   207,   267,   138,     4,     0,    51,    83,    82,    81,
      79,    80,     0,     0,     0,   267,     0,     0,   267,   267,
      60,   144,   146,   139,   141,   140,   259,    13,   258,   203,
       0,    59,    60,     0,    40,     0,    43,    45,    62,    63,
      47,    61,    32,     0,     0,     0,    36,    38,    49,   178,
       0,   177,     1,     9,     8,     3,   252,   251,   256,    10,
      21,    22,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,    76,    69,    70,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     192,     0,     0,     0,   263,   262,   261,   268,     0,     0,
     112,     0,     0,     0,   267,    13,   267,     0,   150,   267,
      13,    13,   143,   142,     0,    14,   267,    16,   260,    58,
      41,    42,    44,    48,    33,    34,    35,    37,   181,   184,
       0,   183,    50,   254,   253,    12,    23,    87,    86,    88,
      89,    94,    92,    93,    95,    90,    91,    84,    85,    71,
       0,    73,     0,    77,     0,    98,   100,   101,   110,   111,
     108,   109,   102,   103,   104,   107,   105,   106,   113,   114,
     115,   116,   117,   118,   119,   122,   123,   124,   125,   126,
     127,   120,   121,     0,     0,     0,   195,     0,   187,   267,
     193,     0,   211,     0,   209,   214,   266,   265,   264,   248,
     248,   248,   248,   267,   207,   220,   207,   221,   207,   222,
     207,   223,     0,     0,     0,     0,    13,     0,    13,   149,
     248,   248,   153,   151,   157,     0,     0,     0,   191,   268,
      15,    46,    64,    65,    66,    39,   179,   180,     0,     0,
      72,    74,     0,     0,     0,   186,   189,     0,     0,     0,
     267,   198,    13,   213,   143,     0,   208,     0,   205,   215,
     228,   234,   238,   243,   248,   267,   267,   267,   267,     0,
     267,     0,   267,     0,     0,   152,   267,   267,   248,   248,
       0,   159,   161,   158,   248,   176,   248,   145,    17,   185,
      78,   196,   197,   188,   195,   194,   190,    13,     0,     0,
     210,   217,     0,   224,   225,   226,   227,     0,     0,   177,
       0,     0,     0,    13,   113,    13,   165,   166,     0,    13,
     267,   267,   156,   162,   160,   267,   267,     0,   201,   202,
     200,   212,     0,   219,   204,   206,   232,   267,   230,   236,
     267,   242,   267,   240,     0,   267,   245,   267,     0,     0,
       0,   267,   155,     0,    13,    13,    13,   199,   216,     0,
     143,     0,   177,     0,     0,     0,    13,   167,     0,   169,
      13,   267,   164,     0,     0,   218,     0,   229,   231,   235,
     237,   239,   241,     0,   244,   246,     0,   267,   154,    13,
     174,   175,     0,   247,   168,    13,   163,   233,     0,   170
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    36,    37,    38,    39,   204,   205,   206,   207,    41,
     130,    76,    43,    44,    45,    46,    47,   115,   116,    48,
     105,   106,   107,    49,    50,    51,   108,    92,   110,   151,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    93,
     317,    94,    61,    62,   197,   198,   312,   313,    63,   370,
     371,   372,   373,    64,    65,    66,    67,   120,   327,   121,
     220,   221,   277,   278,    68,    69,    70,   279,   280,   341,
     420,    71,   425,    72,    73,   183,   283,   284,   348,   349,
     293,   294,   295,   427,   428,   296,   297,   430,   298,   299,
     432,   433,   300,   301,   435,   436,    82,    74,   128,   129,
      97,    98,   187,   188
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -384
static const yytype_int16 yypact[] =
{
     512,  -384,  1016,  1016,  1016,  1016,  1016,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,     8,     8,  -384,  -384,  -384,  -384,   -72,
    -384,  1033,   661,  -384,   604,   -56,    58,  -384,    14,    21,
    -384,  -384,   104,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  1131,  -384,    29,  1215,   791,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,   -14,  -384,  -384,
    -384,   -12,   -61,  -384,  -384,    19,  -384,    42,    42,    42,
      42,    42,  1050,  1106,  1033,   -61,  1033,  1033,   -61,   -61,
    -384,    93,  -384,     8,  -384,     8,  -384,   904,    -1,  -384,
       5,  -384,  1016,    37,  -384,    45,    31,  -384,  -384,  -384,
      15,  -384,  -384,    50,    52,    56,    82,  -384,  -384,  -384,
      16,   960,  -384,  -384,  -384,  -384,  -384,  -384,   848,  -384,
     104,  -384,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  -384,  -384,  -384,  -384,  1016,  1016,   583,  -384,
     682,   -39,  1016,  1016,  1016,  1016,  1016,  1016,  1016,  1016,
    1016,  1016,  1016,  1016,  1016,  1033,  1033,  1033,  1033,  1033,
    1033,  1033,  1033,  1033,  1033,  1033,  1033,  1033,  1033,  1033,
    -384,    20,    17,   108,  -384,  -384,  -384,   -49,    63,  1033,
     501,   177,  1033,   193,   -61,   904,   -61,   147,   115,   -61,
     904,   904,  -384,  -384,   122,  -384,   -61,  -384,  -384,  -384,
    -384,  -384,   739,   739,  -384,  -384,  -384,   739,  -384,  -384,
     111,   120,  -384,  -384,  -384,  -384,  -384,    18,    18,    42,
      42,    42,    42,    42,    42,    18,    18,    46,    46,  -384,
       1,  -384,    89,  -384,  1033,  1131,  -384,  -384,   238,   197,
     225,   590,   179,   179,   179,   179,   179,   179,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,   135,   150,   -29,     7,   235,   145,    33,
    -384,   108,   240,    55,  -384,   214,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,   -61,   -12,  -384,   -12,  -384,   -12,  -384,
     -12,  -384,  1248,  1033,  1268,  1033,   904,   187,   904,  -384,
    -384,  -384,  -384,  -384,   140,   180,   -23,  1033,  -384,   792,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,     8,   739,
    -384,  -384,   154,   108,   108,  -384,  -384,   -45,   -10,   108,
     -61,  -384,   904,  -384,  -384,    17,  -384,   108,  -384,   237,
    -384,  -384,  -384,  -384,    63,   -61,   -61,   -61,   -61,  1033,
     -61,  1033,   -61,   222,  1033,  -384,   -61,   -61,  -384,  -384,
     224,   140,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,  -384,  -384,  -384,  -384,  -384,   904,   -32,  1033,
    -384,   186,   108,  -384,  -384,  -384,  -384,   226,   108,  -384,
     108,   108,   182,   904,   188,   904,  -384,  -384,  1033,   904,
     -61,   -61,  -384,  -384,  -384,   -61,   -61,   -32,  -384,  -384,
    -384,  -384,   108,   189,  -384,  -384,   276,   -61,  -384,  -384,
     -61,  -384,   -61,  -384,   194,   -61,  -384,   -61,   231,  1033,
     236,   -61,  -384,  1033,   904,   904,   904,  -384,  -384,   108,
    -384,   163,   239,   183,  1033,   185,   904,  -384,   190,  -384,
     904,   -61,  -384,   241,   243,  -384,  1033,  -384,  -384,  -384,
    -384,  -384,  -384,   196,  -384,  -384,   245,   -61,  -384,   904,
    -384,  -384,   191,  -384,  -384,   904,  -384,  -384,   246,  -384
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -384,  -384,  -384,  -384,  -384,  -193,  -384,  -384,     3,  -384,
    -384,     0,  -384,  -384,   -24,  -384,  -384,  -384,  -384,  -384,
    -384,  -384,   -33,  -384,  -384,  -384,  -204,     6,   -74,  -384,
     369,  -384,  -384,   335,   -70,  -384,    -4,  -384,  -384,   265,
    -339,   -89,  -384,  -384,  -384,  -384,  -384,  -384,  -384,  -384,
    -384,   -71,   -69,  -384,  -384,  -384,  -384,  -384,  -384,    24,
    -384,  -384,  -384,    30,  -384,  -384,  -383,  -384,   -34,  -384,
    -110,  -384,  -384,  -384,  -384,  -219,  -384,   -30,  -384,  -384,
    -384,  -384,   -37,  -384,  -133,  -384,   -31,  -384,  -384,   -28,
    -384,  -129,  -384,   -27,  -384,  -126,   176,   292,  -384,  -384,
    -384,  -384,   125,   -46
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -190
static const yytype_int16 yytable[] =
{
      42,   117,   307,    40,   203,   389,   203,   315,   316,   322,
    -189,   243,   191,   193,    -7,     1,   429,   218,   131,   118,
     418,    96,     9,    91,    91,   134,   135,   100,   111,   375,
     111,   219,   184,   152,   119,   185,   186,    90,   109,   195,
     109,     9,   200,   201,   286,    90,   281,   287,   288,   376,
     383,   244,   339,   419,   136,   137,   138,   139,   122,     9,
     142,   143,   144,   145,   146,   147,   335,     9,     9,   470,
     180,     9,   273,   274,   240,   355,   242,   356,   182,   357,
     194,   358,   196,   199,   142,   143,   144,   145,   146,   147,
     144,   145,   208,    91,   118,    91,   202,    42,   329,   123,
      28,   330,   273,   274,  -189,   209,   226,   124,   148,   149,
     150,   466,   213,   363,   275,   365,  -182,   126,   127,   302,
      91,    42,   304,   119,   222,   322,   184,   212,    42,   185,
     186,   225,   148,   149,   150,   210,   148,   149,   150,   289,
     290,   291,   292,   211,   111,   214,   111,   215,   306,   388,
     308,   216,   345,   314,   109,   346,   109,    10,    11,     9,
     320,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   310,   311,   217,   321,
     303,   276,   282,   285,   325,   100,   329,   331,   100,    83,
      84,    85,    86,    87,   417,    42,   305,    88,    89,   309,
      42,    42,   153,   154,   368,   369,    99,   318,   111,   324,
     438,   326,   440,   111,     9,   467,   442,   328,   109,   323,
     153,   154,   155,   109,   157,   158,   333,   159,   160,   161,
     162,   163,   164,   342,     9,   471,     9,   474,   338,   379,
     332,   334,   339,   344,   347,   181,   364,   354,   153,   154,
     374,   462,   463,   464,   380,   159,   160,   161,   162,   163,
     164,   153,   154,   476,   392,   157,   158,   478,   159,   160,
     161,   162,   163,   164,   406,   336,   412,   422,   424,   450,
     449,   343,   437,   457,   454,   439,   486,   487,   459,    95,
     477,   469,   488,   480,   387,   481,   483,   484,   489,   360,
     413,   362,   414,   340,   385,   337,    42,   447,    42,   398,
     399,   400,   401,   377,   403,   390,   405,   393,   468,    42,
     408,   409,   378,   394,   472,   324,   395,   396,    91,   475,
     125,   319,     0,   381,   382,   323,     0,     0,   384,   386,
       0,     0,    42,     0,     0,   282,     0,   391,     0,     0,
       0,     0,     0,     0,     0,   402,     0,   404,     0,     0,
     407,     0,     0,     0,   443,   444,     0,     0,     0,   445,
     446,    77,    78,    79,    80,    81,     0,     0,     0,     0,
       0,   451,     0,     0,   452,   421,   453,    42,     0,   455,
       0,   456,   423,     0,     0,   460,     0,     0,   426,     0,
     431,   434,     0,    42,   441,    42,     0,     0,     0,    42,
       0,     0,     0,     0,     0,   479,     0,   190,   190,     0,
       0,     0,   448,     0,     0,     0,     0,     0,     0,     0,
       0,   485,     0,     0,     0,   458,     0,     0,     0,   461,
       0,     0,     0,     0,    42,    42,    42,     0,     0,   465,
     473,   426,     0,   431,     0,   434,    42,     0,     0,     0,
      42,     0,   482,     0,     0,   350,   351,   352,   353,     0,
       0,    79,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,    42,   366,   367,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
       0,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,     0,     0,     1,     0,   237,   238,     2,     3,     0,
       0,   245,     0,     0,   153,   154,   155,   156,   157,   158,
     397,   159,   160,   161,   162,   163,   164,     0,     0,     0,
       0,     4,     0,     0,   410,   411,     0,     0,     0,     0,
     415,     0,   416,     0,     0,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,    10,    11,    12,    13,    14,
      15,     0,    16,     0,     0,    17,     0,     0,    18,    19,
      20,    21,     0,    22,     0,    23,    24,   101,     2,     3,
       0,     0,    25,    26,     0,     0,  -177,    27,    28,    29,
      30,     0,    31,     0,    32,    33,    34,     0,   101,     2,
       3,    35,   102,   153,   154,     0,     0,   157,     0,     0,
     159,   160,   161,   162,   163,   164,     0,     5,     6,     0,
       0,     7,     8,   102,     9,     0,    10,    11,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       0,     0,     7,     8,     0,     9,     0,    10,    11,     0,
       0,     0,     0,    25,    26,   101,     2,     3,     0,     0,
       0,     0,     0,    31,     0,    32,     0,    34,     0,     0,
       0,     0,    35,   239,    25,    26,   101,     2,     3,     0,
     102,     0,     0,     0,    31,     0,    32,     0,    34,   112,
     113,   114,     0,    35,     0,     5,     6,     0,     0,     7,
       8,   102,     9,     0,    10,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     0,     0,
       7,     8,     0,     9,     0,    10,    11,     0,     0,     0,
       0,    25,    26,   101,     2,     3,     0,     0,     0,     0,
       0,    31,     0,    32,     0,    34,     0,   103,     0,   104,
      35,     0,    25,    26,     0,     0,     0,     0,   102,     0,
       0,     0,    31,     0,    32,     0,    34,     0,     0,     0,
     241,    35,     0,     5,     6,     0,     0,     7,     8,     0,
       9,     0,    10,    11,   165,     0,     0,     2,     3,     0,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,     0,     0,     0,     0,     0,    25,
      26,     4,     0,     0,     0,     0,     0,     0,     0,    31,
       0,    32,     0,    34,     0,     0,     5,     6,    35,     0,
       7,     8,     0,     9,     0,    10,    11,    12,    13,    14,
      15,     0,    16,     2,     3,    17,     0,     0,    18,    19,
      20,    21,     0,    22,     0,    23,    24,     0,     0,     0,
       0,     0,    25,    26,     0,     0,  -177,     4,     0,    29,
      30,     0,    31,     0,    32,   286,    34,     0,   287,   288,
       0,    35,     5,     6,     0,     0,     7,     8,     0,     9,
       0,    10,    11,    12,    13,    14,    15,     0,    16,     2,
       3,    17,     0,     0,    18,    19,    20,    21,     0,    22,
       0,    23,    24,     0,     0,     0,     0,     0,    25,    26,
       0,     0,  -177,     4,     0,    29,    30,     0,    31,     0,
      32,     0,    34,     0,   223,   224,     0,    35,     5,     6,
       0,     0,     7,     8,     0,     9,     0,    10,    11,    12,
      13,    14,    15,     0,    16,     2,     3,    17,     0,     0,
      18,    19,    20,    21,     0,    22,     0,    23,    24,     0,
       0,     0,     0,     0,    25,    26,     0,     0,  -177,     4,
       0,    29,    30,     0,    31,     0,    32,     0,    34,     0,
       0,     0,     0,    35,     5,     6,     0,     0,     7,     8,
       0,     9,     0,    10,    11,    12,    13,    14,    15,     0,
      16,     2,     3,    17,     0,     0,    18,    19,    20,    21,
       0,    22,     0,    23,    24,     0,     0,     0,     2,     3,
      25,    26,     0,     0,     0,     4,     0,    29,    30,     0,
      31,     0,    32,     0,    34,     2,     3,     0,     0,    35,
       5,     6,     4,     0,     7,     8,     0,     9,     0,    10,
      11,     0,     0,     0,     0,     0,     0,     5,     6,     4,
       0,     7,     8,     0,     9,     0,    10,    11,     0,     0,
       0,     0,     0,     0,     5,     6,    25,    26,     7,     8,
       0,     9,     0,    10,    11,     0,    31,     0,    32,     0,
      34,     2,     3,    25,    26,    75,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    32,     0,    34,     0,     0,
      25,    26,    35,     0,     0,     4,   132,   133,   134,   135,
     189,     0,    32,     0,    34,     0,     0,     0,     0,    75,
       5,     6,     0,     0,     7,     8,     0,     9,     0,    10,
      11,     0,     0,     0,     0,     0,     0,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,     0,
       0,     0,     0,     0,     0,     0,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,   192,     0,    32,     0,
      34,     0,     0,     0,     0,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -112,     0,
       0,   148,   149,   150,  -112,  -112,  -112,  -112,  -112,  -112,
    -112,  -112,  -112,  -112,  -112,  -112,  -112,  -112,   153,   154,
     155,   156,   157,   158,     0,   159,   160,   161,   162,   163,
     164,   359,     0,     0,     0,     0,     0,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   361,     0,     0,     0,     0,     0,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-384))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,    34,   195,     0,    93,   344,    95,   200,   201,   213,
       3,    50,    82,    83,     0,     1,   399,     1,    42,    75,
      52,    93,    51,    23,    24,     7,     8,    31,    32,    52,
      34,   120,    93,     4,    90,    96,    97,    29,    32,    85,
      34,    51,    88,    89,    93,    29,    29,    96,    97,    72,
      95,    90,    97,    85,    36,    37,    38,    39,     0,    51,
      42,    43,    44,    45,    46,    47,    95,    51,    51,   452,
      84,    51,    82,    83,   148,   294,   150,   296,    90,   298,
      84,   300,    86,    87,    42,    43,    44,    45,    46,    47,
      44,    45,    93,    93,    75,    95,     3,    97,    97,    85,
      86,   100,    82,    83,    97,   100,   130,    93,    90,    91,
      92,   450,    97,   306,    94,   308,   100,    96,    97,   189,
     120,   121,   192,    90,   121,   329,    93,    96,   128,    96,
      97,   128,    90,    91,    92,    98,    90,    91,    92,    76,
      77,    78,    79,    98,   148,    95,   150,    95,   194,   342,
     196,    95,    97,   199,   148,   100,   150,    53,    54,    51,
     206,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,    61,    62,    96,   212,
       3,   181,   182,   183,   217,   189,    97,    98,   192,    13,
      14,    15,    16,    17,   387,   195,     3,    21,    22,    52,
     200,   201,    23,    24,    64,    65,    30,    85,   212,   213,
     403,   100,   405,   217,    51,    52,   409,    97,   212,   213,
      23,    24,    25,   217,    27,    28,    91,    30,    31,    32,
      33,    34,    35,   279,    51,    52,    51,    52,     3,   328,
     244,    91,    97,     3,    30,    69,    59,   293,    23,    24,
      70,   444,   445,   446,   100,    30,    31,    32,    33,    34,
      35,    23,    24,   456,    27,    27,    28,   460,    30,    31,
      32,    33,    34,    35,    52,   275,    52,    91,    52,     3,
      91,   281,   100,    52,    90,    97,   479,    96,    52,    24,
     100,    52,   485,    52,   340,    52,   100,    52,    52,   303,
     371,   305,   371,   279,   338,   275,   306,   417,   308,   355,
     356,   357,   358,   317,   360,   345,   362,   354,   451,   319,
     366,   367,   319,   354,   453,   329,   354,   354,   328,   455,
      38,   206,    -1,   333,   334,   329,    -1,    -1,   338,   339,
      -1,    -1,   342,    -1,    -1,   345,    -1,   347,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   359,    -1,   361,    -1,    -1,
     364,    -1,    -1,    -1,   410,   411,    -1,    -1,    -1,   415,
     416,     2,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,   427,    -1,    -1,   430,   389,   432,   387,    -1,   435,
      -1,   437,   392,    -1,    -1,   441,    -1,    -1,   398,    -1,
     400,   401,    -1,   403,   408,   405,    -1,    -1,    -1,   409,
      -1,    -1,    -1,    -1,    -1,   461,    -1,    82,    83,    -1,
      -1,    -1,   422,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   477,    -1,    -1,    -1,   439,    -1,    -1,    -1,   443,
      -1,    -1,    -1,    -1,   444,   445,   446,    -1,    -1,   449,
     454,   451,    -1,   453,    -1,   455,   456,    -1,    -1,    -1,
     460,    -1,   466,    -1,    -1,   289,   290,   291,   292,    -1,
      -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   479,
      -1,    -1,    -1,    -1,    -1,   485,   310,   311,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
      -1,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,    -1,    -1,     1,    -1,   146,   147,     5,     6,    -1,
      -1,   152,    -1,    -1,    23,    24,    25,    26,    27,    28,
     354,    30,    31,    32,    33,    34,    35,    -1,    -1,    -1,
      -1,    29,    -1,    -1,   368,   369,    -1,    -1,    -1,    -1,
     374,    -1,   376,    -1,    -1,    -1,    44,    45,    -1,    -1,
      48,    49,    -1,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      68,    69,    -1,    71,    -1,    73,    74,     4,     5,     6,
      -1,    -1,    80,    81,    -1,    -1,    84,    85,    86,    87,
      88,    -1,    90,    -1,    92,    93,    94,    -1,     4,     5,
       6,    99,    29,    23,    24,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    44,    45,    -1,
      -1,    48,    49,    29,    51,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,    -1,
      -1,    -1,    -1,    80,    81,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,
      -1,    -1,    99,   100,    80,    81,     4,     5,     6,    -1,
      29,    -1,    -1,    -1,    90,    -1,    92,    -1,    94,    95,
      96,    97,    -1,    99,    -1,    44,    45,    -1,    -1,    48,
      49,    29,    51,    -1,    53,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,    -1,
      -1,    80,    81,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    92,    -1,    94,    -1,    96,    -1,    98,
      99,    -1,    80,    81,    -1,    -1,    -1,    -1,    29,    -1,
      -1,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,    -1,
      98,    99,    -1,    44,    45,    -1,    -1,    48,    49,    -1,
      51,    -1,    53,    54,     3,    -1,    -1,     5,     6,    -1,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    80,
      81,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    92,    -1,    94,    -1,    -1,    44,    45,    99,    -1,
      48,    49,    -1,    51,    -1,    53,    54,    55,    56,    57,
      58,    -1,    60,     5,     6,    63,    -1,    -1,    66,    67,
      68,    69,    -1,    71,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    80,    81,    -1,    -1,    84,    29,    -1,    87,
      88,    -1,    90,    -1,    92,    93,    94,    -1,    96,    97,
      -1,    99,    44,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    53,    54,    55,    56,    57,    58,    -1,    60,     5,
       6,    63,    -1,    -1,    66,    67,    68,    69,    -1,    71,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    80,    81,
      -1,    -1,    84,    29,    -1,    87,    88,    -1,    90,    -1,
      92,    -1,    94,    -1,    96,    97,    -1,    99,    44,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,    55,
      56,    57,    58,    -1,    60,     5,     6,    63,    -1,    -1,
      66,    67,    68,    69,    -1,    71,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    84,    29,
      -1,    87,    88,    -1,    90,    -1,    92,    -1,    94,    -1,
      -1,    -1,    -1,    99,    44,    45,    -1,    -1,    48,    49,
      -1,    51,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,     5,     6,    63,    -1,    -1,    66,    67,    68,    69,
      -1,    71,    -1,    73,    74,    -1,    -1,    -1,     5,     6,
      80,    81,    -1,    -1,    -1,    29,    -1,    87,    88,    -1,
      90,    -1,    92,    -1,    94,     5,     6,    -1,    -1,    99,
      44,    45,    29,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    29,
      -1,    48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    80,    81,    48,    49,
      -1,    51,    -1,    53,    54,    -1,    90,    -1,    92,    -1,
      94,     5,     6,    80,    81,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,
      80,    81,    99,    -1,    -1,    29,     5,     6,     7,     8,
      90,    -1,    92,    -1,    94,    -1,    -1,    -1,    -1,    99,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    92,    -1,
      94,    -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    90,    91,    92,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,     3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    29,    44,    45,    48,    49,    51,
      53,    54,    55,    56,    57,    58,    60,    63,    66,    67,
      68,    69,    71,    73,    74,    80,    81,    85,    86,    87,
      88,    90,    92,    93,    94,    99,   102,   103,   104,   105,
     109,   110,   112,   113,   114,   115,   116,   117,   120,   124,
     125,   126,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   143,   144,   149,   154,   155,   156,   157,   165,   166,
     167,   172,   174,   175,   198,    99,   112,   131,   131,   131,
     131,   131,   197,   197,   197,   197,   197,   197,   197,   197,
      29,   112,   128,   140,   142,   140,    93,   201,   202,   197,
     137,     4,    29,    96,    98,   121,   122,   123,   127,   128,
     129,   137,    95,    96,    97,   118,   119,   123,    75,    90,
     158,   160,     0,    85,    93,   198,    96,    97,   199,   200,
     111,   115,     5,     6,     7,     8,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    90,    91,
      92,   130,     4,    23,    24,    25,    26,    27,    28,    30,
      31,    32,    33,    34,    35,     3,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      84,   197,    90,   176,    93,    96,    97,   203,   204,    90,
     134,   135,    90,   135,   137,   204,   137,   145,   146,   137,
     204,   204,     3,   142,   106,   107,   108,   109,    93,   100,
      98,    98,    96,    97,    95,    95,    95,    96,     1,   142,
     161,   162,   109,    96,    97,   109,   115,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   100,
     129,    98,   129,    50,    90,   131,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,    82,    83,    94,   112,   163,   164,   168,
     169,    29,   112,   177,   178,   112,    93,    96,    97,    76,
      77,    78,    79,   181,   182,   183,   186,   187,   189,   190,
     193,   194,   135,     3,   135,     3,   204,   106,   204,    52,
      61,    62,   147,   148,   204,   106,   106,   141,    85,   203,
     204,   123,   127,   128,   137,   123,   100,   159,    97,    97,
     100,    98,   137,    91,    91,    95,   112,   164,     3,    97,
     160,   170,   204,   112,     3,    97,   100,    30,   179,   180,
     197,   197,   197,   197,   204,   176,   176,   176,   176,     3,
     137,     3,   137,   106,    59,   106,   197,   197,    64,    65,
     150,   151,   152,   153,    70,    52,    72,   137,   109,   142,
     100,   112,   112,    95,   112,   169,   112,   204,   106,   141,
     178,   112,    27,   183,   187,   190,   194,   197,   204,   204,
     204,   204,   137,   204,   137,   204,    52,   137,   204,   204,
     197,   197,    52,   152,   153,   197,   197,   106,    52,    85,
     171,   137,    91,   112,    52,   173,   112,   184,   185,   167,
     188,   112,   191,   192,   112,   195,   196,   100,   106,    97,
     106,   137,   106,   204,   204,   204,   204,   171,   112,    91,
       3,   204,   204,   204,    90,   204,   204,    52,   137,    52,
     204,   137,   106,   106,   106,   112,   141,    52,   185,    52,
     167,    52,   192,   137,    52,   196,   106,   100,   106,   204,
      52,    52,   137,   100,    52,   204,   106,    96,   106,    52
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
      yyerror (parser, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, scanner)
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
		  Type, Value, parser); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, octave_base_parser& parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    octave_base_parser& parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parser);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, octave_base_parser& parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    octave_base_parser& parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, octave_base_parser& parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    octave_base_parser& parser;
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
		       		       , parser);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, octave_base_parser& parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    octave_base_parser& parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


struct yypstate
  {
    /* Number of syntax errors so far.  */
    int yynerrs;

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
    /* Used to determine if this is the first time this instance has
       been used.  */
    int yynew;
  };

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (octave_base_parser& parser)
#else
int
yyparse (parser)
    octave_base_parser& parser;
#endif
{
  return yypull_parse (0, parser);
}

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yypull_parse (yypstate *yyps, octave_base_parser& parser)
#else
int
yypull_parse (yyps, parser)
    yypstate *yyps;
    octave_base_parser& parser;
#endif
{
  int yystatus;
  yypstate *yyps_local;
  int yychar;
  YYSTYPE yylval;
  if (yyps == 0)
    {
      yyps_local = yypstate_new ();
      if (!yyps_local)
        {
          yyerror (parser, YY_("memory exhausted"));
          return 2;
        }
    }
  else
    yyps_local = yyps;
  do {
    yychar = YYLEX;
    yystatus =
      yypush_parse (yyps_local, yychar, &yylval, parser);
  } while (yystatus == YYPUSH_MORE);
  if (yyps == 0)
    yypstate_delete (yyps_local);
  return yystatus;
}

/* Initialize the parser data structure.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
yypstate *
yypstate_new (void)
#else
yypstate *
yypstate_new ()

#endif
{
  yypstate *yyps;
  yyps = (yypstate *) malloc (sizeof *yyps);
  if (!yyps)
    return 0;
  yyps->yynew = 1;
  return yyps;
}

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void
yypstate_delete (yypstate *yyps)
#else
void
yypstate_delete (yyps)
    yypstate *yyps;
#endif
{
#ifndef yyoverflow
  /* If the stack was reallocated but the parse did not complete, then the
     stack still needs to be freed.  */
  if (!yyps->yynew && yyps->yyss != yyps->yyssa)
    YYSTACK_FREE (yyps->yyss);
#endif
  free (yyps);
}

#define octave_nerrs yyps->octave_nerrs
#define yystate yyps->yystate
#define yyerrstatus yyps->yyerrstatus
#define yyssa yyps->yyssa
#define yyss yyps->yyss
#define yyssp yyps->yyssp
#define yyvsa yyps->yyvsa
#define yyvs yyps->yyvs
#define yyvsp yyps->yyvsp
#define yystacksize yyps->yystacksize


/*---------------.
| yypush_parse.  |
`---------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yypush_parse (yypstate *yyps, int yypushed_char, YYSTYPE const *yypushed_val, octave_base_parser& parser)
#else
int
yypush_parse (yyps, yypushed_char, yypushed_val, parser)
    yypstate *yyps;
    int yypushed_char;
    YYSTYPE const *yypushed_val;
    octave_base_parser& parser;
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

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

  if (!yyps->yynew)
    {
      yyn = yypact[yystate];
      goto yyread_pushed_token;
    }

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
      if (!yyps->yynew)
        {
          YYDPRINTF ((stderr, "Return for a new token:\n"));
          yyresult = YYPUSH_MORE;
          goto yypushreturn;
        }
      yyps->yynew = 0;
yyread_pushed_token:
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yypushed_char;
      if (yypushed_val)
        yylval = *yypushed_val;
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
#line 311 "oct-parse.yy"
    {
                    parser.stmt_list = (yyvsp[(1) - (1)].tree_statement_list_type);
                    YYACCEPT;
                  }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 316 "oct-parse.yy"
    { ABORT_PARSE; }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 318 "oct-parse.yy"
    { ABORT_PARSE; }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 322 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = 0; }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 324 "oct-parse.yy"
    {
                    lexer.end_of_input = true;
                    (yyval.tree_statement_list_type) = 0;
                  }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 329 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (1)].tree_statement_list_type); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 331 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (2)].tree_statement_list_type); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 333 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (2)].tree_statement_list_type); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 337 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), false); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 341 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 343 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), false); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 347 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = new tree_statement_list (); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 349 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (1)].tree_statement_list_type); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 353 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), true); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 357 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 359 "oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), true); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 363 "oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 365 "oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_command_type)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 367 "oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_index_expression_type)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 379 "oct-parse.yy"
    {
                    (yyval.tree_index_expression_type) = parser.make_index_expression ((yyvsp[(1) - (2)].tree_identifier_type), (yyvsp[(2) - (2)].tree_argument_list_type), '(');
                    if (! (yyval.tree_index_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 387 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 389 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_argument_list_type)->append ((yyvsp[(2) - (2)].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type);
                  }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 400 "oct-parse.yy"
    {
                    symbol_table::symbol_record *sr = (yyvsp[(1) - (1)].tok_val)->sym_rec ();
                    (yyval.tree_identifier_type) = new tree_identifier (*sr, (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                  }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 408 "oct-parse.yy"
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ()); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 412 "oct-parse.yy"
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ()); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 416 "oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (DQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 418 "oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (SQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 422 "oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 424 "oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (IMAG_NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 426 "oct-parse.yy"
    { (yyval.tree_constant_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 430 "oct-parse.yy"
    { (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 432 "oct-parse.yy"
    { (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 434 "oct-parse.yy"
    { (yyval.tree_expression_type) = new tree_constant (octave_null_matrix::instance); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 436 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_matrix ((yyvsp[(2) - (3)].tree_matrix_type)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 440 "oct-parse.yy"
    { (yyval.tree_matrix_type) = (yyvsp[(1) - (1)].tree_matrix_type); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 442 "oct-parse.yy"
    { (yyval.tree_matrix_type) = (yyvsp[(1) - (2)].tree_matrix_type); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 446 "oct-parse.yy"
    { (yyval.tree_matrix_type) = new tree_matrix ((yyvsp[(1) - (1)].tree_argument_list_type)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 448 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_matrix_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));
                    (yyval.tree_matrix_type) = (yyvsp[(1) - (3)].tree_matrix_type);
                  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 455 "oct-parse.yy"
    { (yyval.tree_expression_type) = new tree_constant (octave_value (Cell ())); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 457 "oct-parse.yy"
    { (yyval.tree_expression_type) = new tree_constant (octave_value (Cell ())); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 459 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_cell ((yyvsp[(2) - (3)].tree_cell_type)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 463 "oct-parse.yy"
    { (yyval.tree_cell_type) = (yyvsp[(1) - (1)].tree_cell_type); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 465 "oct-parse.yy"
    { (yyval.tree_cell_type) = (yyvsp[(1) - (2)].tree_cell_type); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 469 "oct-parse.yy"
    { (yyval.tree_cell_type) = new tree_cell ((yyvsp[(1) - (1)].tree_argument_list_type)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 471 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_cell_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));
                    (yyval.tree_cell_type) = (yyvsp[(1) - (3)].tree_cell_type);
                  }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 479 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (1)].tree_argument_list_type); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 481 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 485 "oct-parse.yy"
    {
                    (yyval.tree_fcn_handle_type) = parser.make_fcn_handle ((yyvsp[(2) - (2)].tok_val));
                    lexer.looking_at_function_handle--;
                  }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 492 "oct-parse.yy"
    {
                    (yyval.tree_anon_fcn_handle_type) = parser.make_anon_fcn_handle ((yyvsp[(2) - (3)].tree_parameter_list_type), (yyvsp[(3) - (3)].tree_statement_type));
                    lexer.nesting_level.remove ();
                  }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 499 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 501 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 503 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_fcn_handle_type); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 505 "oct-parse.yy"
    {
                    lexer.looking_at_matrix_or_assign_lhs = false;
                    (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type);
                  }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 510 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 512 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 514 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 516 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(2) - (3)].tree_expression_type)->mark_in_parens (); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 520 "oct-parse.yy"
    {
                    octave_value tmp (octave_value::magic_colon_t);
                    (yyval.tree_constant_type) = new tree_constant (tmp);
                  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 527 "oct-parse.yy"
    {
                    (yyval.tree_identifier_type) = new tree_black_hole ();
                  }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 533 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 535 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 537 "oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 539 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 544 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_identifier_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 549 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_expression_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 556 "oct-parse.yy"
    { lexer.looking_at_indirect_ref = true; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 560 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 562 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (PLUS_PLUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 564 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (MINUS_MINUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 566 "oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '(');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 572 "oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '(');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 578 "oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '{');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 584 "oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '{');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 590 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (HERMITIAN, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 592 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (TRANSPOSE, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 594 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(3) - (3)].tok_val)->text ()); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 596 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[(1) - (5)].tree_expression_type), (yyvsp[(4) - (5)].tree_expression_type)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 598 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (PLUS_PLUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 600 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (MINUS_MINUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 602 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (EXPR_NOT, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 604 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op ('+', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 606 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op ('-', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 608 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (POW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 610 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EPOW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 612 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 614 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 616 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('*', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 618 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('/', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 620 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 622 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 624 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EMUL, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 626 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 628 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (LEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 630 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (ELEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 634 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_colon_expression ((yyvsp[(1) - (1)].tree_colon_expression_type)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 638 "oct-parse.yy"
    { (yyval.tree_colon_expression_type) = new tree_colon_expression ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 640 "oct-parse.yy"
    {
                    if (! ((yyval.tree_colon_expression_type) = (yyvsp[(1) - (3)].tree_colon_expression_type)->append ((yyvsp[(3) - (3)].tree_expression_type))))
                      ABORT_PARSE;
                  }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 647 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 649 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (LSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 651 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (RSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 653 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 655 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 657 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_EQ, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 659 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 661 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 663 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_NE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 665 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 667 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 669 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_AND_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 671 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_OR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 675 "oct-parse.yy"
    {
                    (yyval.tree_argument_list_type) = parser.validate_matrix_for_assignment ((yyvsp[(1) - (1)].tree_expression_type));

                    if ((yyval.tree_argument_list_type))
                      { lexer.looking_at_matrix_or_assign_lhs = false; }
                    else
                      {
                        // validate_matrix_for_assignment deleted $1.
                        ABORT_PARSE;
                      }
                  }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 689 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op ('=', (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 691 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (ADD_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 693 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (SUB_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 695 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (MUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 697 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (DIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 699 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (LEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 701 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (POW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 703 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (LSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 705 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (RSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 707 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EMUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 709 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 711 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (ELEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 713 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EPOW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 715 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (AND_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 717 "oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (OR_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 721 "oct-parse.yy"
    {
                    if ((yyvsp[(1) - (1)].tree_expression_type) && ((yyvsp[(1) - (1)].tree_expression_type)->is_matrix () || (yyvsp[(1) - (1)].tree_expression_type)->is_cell ()))
                      {
                        if (parser.validate_array_list ((yyvsp[(1) - (1)].tree_expression_type)))
                          (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type);
                        else
                          {
                            delete (yyvsp[(1) - (1)].tree_expression_type);
                            ABORT_PARSE;
                          }
                      }
                    else
                      (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type);
                  }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 736 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 738 "oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_anon_fcn_handle_type); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 746 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_decl_command_type); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 748 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 750 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 752 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 754 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 756 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 758 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 760 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 768 "oct-parse.yy"
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (GLOBAL, (yyvsp[(1) - (2)].tok_val), (yyvsp[(2) - (2)].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 773 "oct-parse.yy"
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (PERSISTENT, (yyvsp[(1) - (2)].tok_val), (yyvsp[(2) - (2)].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 780 "oct-parse.yy"
    { (yyval.tree_decl_init_list_type) = new tree_decl_init_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 782 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_decl_init_list_type)->append ((yyvsp[(2) - (2)].tree_decl_elt_type));
                    (yyval.tree_decl_init_list_type) = (yyvsp[(1) - (2)].tree_decl_init_list_type);
                  }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 789 "oct-parse.yy"
    { lexer.looking_at_initializer_expression = true; }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 792 "oct-parse.yy"
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 794 "oct-parse.yy"
    {
                    lexer.looking_at_initializer_expression = false;
                    (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (4)].tree_identifier_type), (yyvsp[(4) - (4)].tree_expression_type));
                  }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 799 "oct-parse.yy"
    {
                    (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type));
                  }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 809 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_if_command_type); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 811 "oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_switch_command_type); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 819 "oct-parse.yy"
    {
                    if (! ((yyval.tree_if_command_type) = parser.finish_if_command ((yyvsp[(1) - (4)].tok_val), (yyvsp[(3) - (4)].tree_if_command_list_type), (yyvsp[(4) - (4)].tok_val), (yyvsp[(2) - (4)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 826 "oct-parse.yy"
    { (yyval.tree_if_command_list_type) = (yyvsp[(1) - (1)].tree_if_command_list_type); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 828 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
                  }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 835 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_command_list_type) = parser.start_if_command ((yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(3) - (3)].tree_statement_list_type));
                  }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 841 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
                  }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 848 "oct-parse.yy"
    {
                    (yyvsp[(4) - (6)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_clause_type) = parser.make_elseif_clause ((yyvsp[(1) - (6)].tok_val), (yyvsp[(4) - (6)].tree_expression_type), (yyvsp[(6) - (6)].tree_statement_list_type), (yyvsp[(2) - (6)].comment_type));
                  }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 856 "oct-parse.yy"
    { (yyval.tree_if_clause_type) = new tree_if_clause ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 864 "oct-parse.yy"
    {
                    if (! ((yyval.tree_switch_command_type) = parser.finish_switch_command ((yyvsp[(1) - (6)].tok_val), (yyvsp[(3) - (6)].tree_expression_type), (yyvsp[(5) - (6)].tree_switch_case_list_type), (yyvsp[(6) - (6)].tok_val), (yyvsp[(2) - (6)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 871 "oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list (); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 873 "oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[(1) - (1)].tree_switch_case_type)); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 875 "oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (1)].tree_switch_case_list_type); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 877 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
                  }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 884 "oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[(1) - (1)].tree_switch_case_type)); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 886 "oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
                  }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 893 "oct-parse.yy"
    { (yyval.tree_switch_case_type) = parser.make_switch_case ((yyvsp[(1) - (6)].tok_val), (yyvsp[(4) - (6)].tree_expression_type), (yyvsp[(6) - (6)].tree_statement_list_type), (yyvsp[(2) - (6)].comment_type)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 897 "oct-parse.yy"
    {
                    (yyval.tree_switch_case_type) = new tree_switch_case ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type));
                  }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 907 "oct-parse.yy"
    {
                    (yyvsp[(3) - (6)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    if (! ((yyval.tree_command_type) = parser.make_while_command ((yyvsp[(1) - (6)].tok_val), (yyvsp[(3) - (6)].tree_expression_type), (yyvsp[(5) - (6)].tree_statement_list_type), (yyvsp[(6) - (6)].tok_val), (yyvsp[(2) - (6)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 914 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_do_until_command ((yyvsp[(5) - (6)].tok_val), (yyvsp[(4) - (6)].tree_statement_list_type), (yyvsp[(6) - (6)].tree_expression_type), (yyvsp[(2) - (6)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 919 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[(1) - (8)].tok_val), (yyvsp[(3) - (8)].tree_argument_list_type), (yyvsp[(5) - (8)].tree_expression_type), 0,
                                                  (yyvsp[(7) - (8)].tree_statement_list_type), (yyvsp[(8) - (8)].tok_val), (yyvsp[(2) - (8)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 925 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[(1) - (10)].tok_val), (yyvsp[(4) - (10)].tree_argument_list_type), (yyvsp[(6) - (10)].tree_expression_type), 0,
                                                  (yyvsp[(9) - (10)].tree_statement_list_type), (yyvsp[(10) - (10)].tok_val), (yyvsp[(2) - (10)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 931 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[(1) - (8)].tok_val), (yyvsp[(3) - (8)].tree_argument_list_type), (yyvsp[(5) - (8)].tree_expression_type),
                                                  0, (yyvsp[(7) - (8)].tree_statement_list_type), (yyvsp[(8) - (8)].tok_val), (yyvsp[(2) - (8)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 937 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[(1) - (12)].tok_val), (yyvsp[(4) - (12)].tree_argument_list_type), (yyvsp[(6) - (12)].tree_expression_type),
                                                  (yyvsp[(8) - (12)].tree_expression_type), (yyvsp[(11) - (12)].tree_statement_list_type), (yyvsp[(12) - (12)].tok_val), (yyvsp[(2) - (12)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 949 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_break_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 954 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_continue_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 959 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_return_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 971 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_unwind_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 977 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 982 "oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[(1) - (5)].tok_val), (yyvsp[(4) - (5)].tree_statement_list_type), 0, (yyvsp[(5) - (5)].tok_val), (yyvsp[(2) - (5)].comment_type), 0)))
                      ABORT_PARSE;
                  }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 993 "oct-parse.yy"
    {
                    parser.curr_fcn_depth++;

                    if (parser.max_fcn_depth < parser.curr_fcn_depth)
                      parser.max_fcn_depth = parser.curr_fcn_depth;

                    lexer.symtab_context.push (symbol_table::alloc_scope ());

                    parser.function_scopes.push_back
                     (lexer.symtab_context.curr_scope ());

                    if (! lexer.reading_script_file
                        && parser.curr_fcn_depth == 1
                        && ! parser.parsing_subfunctions)
                      parser.primary_fcn_scope
                        = lexer.symtab_context.curr_scope ();

                    if (lexer.reading_script_file
                        && parser.curr_fcn_depth > 1)
                      parser.bison_error ("nested functions not implemented in this context");
                  }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1021 "oct-parse.yy"
    {
                    lexer.looking_at_parameter_list = true;

                    if (lexer.looking_at_function_handle)
                      {
                        lexer.symtab_context.push (symbol_table::alloc_scope ());
                        lexer.looking_at_function_handle--;
                        lexer.looking_at_anon_fcn_args = true;
                      }
                  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1034 "oct-parse.yy"
    {
                    lexer.looking_at_parameter_list = false;
                    lexer.looking_for_object_index = false;
                  }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1041 "oct-parse.yy"
    {
                    if ((yyvsp[(2) - (3)].tree_parameter_list_type))
                      lexer.mark_as_variables ((yyvsp[(2) - (3)].tree_parameter_list_type)->variable_names ());

                    (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
                  }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1048 "oct-parse.yy"
    {
                    parser.bison_error ("invalid parameter list");
                    (yyval.tree_parameter_list_type) = 0;
                    ABORT_PARSE;
                  }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1056 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1058 "oct-parse.yy"
    {
                    (yyvsp[(1) - (1)].tree_parameter_list_type)->mark_as_formal_parameters ();
                    if ((yyvsp[(1) - (1)].tree_parameter_list_type)->validate (tree_parameter_list::in))
                      {
                        lexer.mark_as_variables ((yyvsp[(1) - (1)].tree_parameter_list_type)->variable_names ());
                        (yyval.tree_parameter_list_type) = (yyvsp[(1) - (1)].tree_parameter_list_type);
                      }
                    else
                      ABORT_PARSE;
                  }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1071 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1073 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_parameter_list_type)->append ((yyvsp[(3) - (3)].tree_decl_elt_type));
                    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
                  }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1084 "oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;
                    (yyval.tree_parameter_list_type) = new tree_parameter_list ();
                  }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1089 "oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;
                    if ((yyvsp[(1) - (1)].tree_parameter_list_type)->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = (yyvsp[(1) - (1)].tree_parameter_list_type);
                    else
                      ABORT_PARSE;
                  }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1097 "oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;
                    if ((yyvsp[(2) - (3)].tree_parameter_list_type)->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
                    else
                      ABORT_PARSE;
                  }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1107 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list (new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type))); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1109 "oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_parameter_list_type)->append (new tree_decl_elt ((yyvsp[(3) - (3)].tree_identifier_type)));
                    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
                  }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1120 "oct-parse.yy"
    {
                    if (! lexer.reading_fcn_file)
                      {
                        tree_statement *end_of_script
                          = parser.make_end ("endscript", true,
                                             lexer.input_line_number,
                                             lexer.current_input_column);

                        parser.make_script ((yyvsp[(3) - (4)].tree_statement_list_type), end_of_script);
                      }

                    (yyval.tree_command_type) = 0;
                  }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1140 "oct-parse.yy"
    {
                    (yyval.tok_val) = (yyvsp[(2) - (2)].tok_val);
                    if (lexer.reading_classdef_file
                        || lexer.parsing_classdef)
                      lexer.maybe_classdef_get_set_method = true;
                  }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1149 "oct-parse.yy"
    {
                    (yyval.tree_command_type) = parser.finish_function (0, (yyvsp[(3) - (3)].octave_user_function_type), (yyvsp[(2) - (3)].comment_type), (yyvsp[(1) - (3)].tok_val)->line (),
                                                 (yyvsp[(1) - (3)].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1155 "oct-parse.yy"
    {
                    (yyval.tree_command_type) = parser.finish_function ((yyvsp[(3) - (5)].tree_parameter_list_type), (yyvsp[(5) - (5)].octave_user_function_type), (yyvsp[(2) - (5)].comment_type), (yyvsp[(1) - (5)].tok_val)->line (),
                                                 (yyvsp[(1) - (5)].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1163 "oct-parse.yy"
    {
                    std::string id_name = (yyvsp[(1) - (1)].tree_identifier_type)->name ();

                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;

                    (yyval.tree_identifier_type) = (yyvsp[(1) - (1)].tree_identifier_type);
                  }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1172 "oct-parse.yy"
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[(3) - (3)].tree_identifier_type);
                  }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1178 "oct-parse.yy"
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[(3) - (3)].tree_identifier_type);
                  }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1186 "oct-parse.yy"
    {
                    std::string fname = (yyvsp[(1) - (2)].tree_identifier_type)->name ();

                    delete (yyvsp[(1) - (2)].tree_identifier_type);

                    if (! ((yyval.octave_user_function_type) = parser.frob_function (fname, (yyvsp[(2) - (2)].octave_user_function_type))))
                      ABORT_PARSE;
                  }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1197 "oct-parse.yy"
    { (yyval.octave_user_function_type) = parser.start_function ((yyvsp[(1) - (4)].tree_parameter_list_type), (yyvsp[(3) - (4)].tree_statement_list_type), (yyvsp[(4) - (4)].tree_statement_type)); }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1199 "oct-parse.yy"
    { (yyval.octave_user_function_type) = parser.start_function (0, (yyvsp[(2) - (3)].tree_statement_list_type), (yyvsp[(3) - (3)].tree_statement_type)); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1203 "oct-parse.yy"
    {
                    parser.endfunction_found = true;
                    if (parser.end_token_ok ((yyvsp[(1) - (1)].tok_val), token::function_end))
                      (yyval.tree_statement_type) = parser.make_end ("endfunction", false,
                                            (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1212 "oct-parse.yy"
    {
// A lot of tests are based on the assumption that this is OK
//                  if (lexer.reading_script_file)
//                    {
//                      parser.bison_error ("function body open at end of script");
//                      YYABORT;
//                    }

                    if (parser.endfunction_found)
                      {
                        parser.bison_error ("inconsistent function endings -- "
                                 "if one function is explicitly ended, "
                                 "so must all the others");
                        YYABORT;
                      }

                    if (! (lexer.reading_fcn_file || lexer.reading_script_file
                           || lexer.input_from_eval_string ()))
                      {
                        parser.bison_error ("function body open at end of input");
                        YYABORT;
                      }

                    if (lexer.reading_classdef_file)
                      {
                        parser.bison_error ("classdef body open at end of input");
                        YYABORT;
                      }

                    (yyval.tree_statement_type) = parser.make_end ("endfunction", true,
                                          lexer.input_line_number,
                                          lexer.current_input_column);
                  }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1252 "oct-parse.yy"
    {
                    (yyval.comment_type) = 0;
                    lexer.parsing_classdef = true;
                  }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1259 "oct-parse.yy"
    {
                    lexer.parsing_classdef = false;

                    if (parser.end_token_ok ((yyvsp[(1) - (1)].tok_val), token::classdef_end))
                      (yyval.tree_statement_type) = parser.make_end ("endclassdef", false,
                                            (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1271 "oct-parse.yy"
    { (yyval.octave_user_function_type) = 0; }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1275 "oct-parse.yy"
    { (yyval.tree_command_type) = 0; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1279 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1281 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1285 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1287 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1291 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1293 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1295 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1300 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1302 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1306 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1308 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1310 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1312 "oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1316 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1318 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1320 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1322 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1324 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1326 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1328 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1330 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1334 "oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1339 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1344 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1346 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1350 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1352 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1356 "oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1360 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1364 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1366 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1370 "oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1374 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1378 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1380 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1384 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1388 "oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1392 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1396 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1398 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1402 "oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1410 "oct-parse.yy"
    { (yyval.comment_type) = octave_comment_buffer::get_comment (); }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1414 "oct-parse.yy"
    { parser.bison_error ("parse error"); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1419 "oct-parse.yy"
    { (yyval.sep_type) = ','; }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1421 "oct-parse.yy"
    { (yyval.sep_type) = ';'; }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1423 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1425 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1429 "oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1431 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1435 "oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1437 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1441 "oct-parse.yy"
    { (yyval.sep_type) = '\n'; }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1443 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1447 "oct-parse.yy"
    { (yyval.sep_type) = ','; }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1449 "oct-parse.yy"
    { (yyval.sep_type) = ';'; }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1451 "oct-parse.yy"
    { (yyval.sep_type) = '\n'; }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1453 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1455 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1457 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1461 "oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1463 "oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;



/* Line 1806 of yacc.c  */
#line 4632 "parse-tree/oct-parse.cc"
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
      yyerror (parser, YY_("syntax error"));
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
        yyerror (parser, yymsgp);
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
		      yytoken, &yylval, parser);
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
		  yystos[yystate], yyvsp, parser);
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
  yyerror (parser, YY_("memory exhausted"));
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
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  yyps->yynew = 1;

yypushreturn:
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1466 "oct-parse.yy"


// Generic error messages.

#undef lexer

static void
yyerror (octave_base_parser& parser, const char *s)
{
  parser.bison_error (s);
}

octave_base_parser::~octave_base_parser (void)
{
  delete stmt_list;

  delete &lexer;
}

void octave_base_parser::init (void)
{
  LEXER = &lexer;
}

void
octave_base_parser::reset (void)
{
  endfunction_found = false;
  autoloading = false;
  fcn_file_from_relative_lookup = false;
  parsing_subfunctions = false;
  max_fcn_depth = 0;
  curr_fcn_depth = 0;
  primary_fcn_scope = -1;
  curr_class_name = "";
  function_scopes.clear ();
  primary_fcn_ptr  = 0;
  subfunction_names.clear ();

  delete stmt_list;
  stmt_list = 0;

  lexer.reset ();
}

// Error mesages for mismatched end tokens.

void
octave_base_parser::end_error (const char *type, token::end_tok_type ettype,
                               int l, int c)
{
  static const char *fmt
    = "'%s' command matched by '%s' near line %d column %d";

  switch (ettype)
    {
    case token::simple_end:
      error (fmt, type, "end", l, c);
      break;

    case token::for_end:
      error (fmt, type, "endfor", l, c);
      break;

    case token::function_end:
      error (fmt, type, "endfunction", l, c);
      break;

    case token::classdef_end:
      error (fmt, type, "endclassdef", l, c);
      break;

    case token::if_end:
      error (fmt, type, "endif", l, c);
      break;

    case token::switch_end:
      error (fmt, type, "endswitch", l, c);
      break;

    case token::while_end:
      error (fmt, type, "endwhile", l, c);
      break;

    case token::try_catch_end:
      error (fmt, type, "end_try_catch", l, c);
      break;

    case token::unwind_protect_end:
      error (fmt, type, "end_unwind_protect", l, c);
      break;

    default:
      panic_impossible ();
      break;
    }
}

// Check to see that end tokens are properly matched.

bool
octave_base_parser::end_token_ok (token *tok, token::end_tok_type expected)
{
  bool retval = true;

  token::end_tok_type ettype = tok->ettype ();

  if (ettype != expected && ettype != token::simple_end)
    {
      retval = false;

      bison_error ("parse error");

      int l = tok->line ();
      int c = tok->column ();

      switch (expected)
        {
        case token::classdef_end:
          end_error ("classdef", ettype, l, c);
          break;

        case token::for_end:
          end_error ("for", ettype, l, c);
          break;

        case token::enumeration_end:
          end_error ("enumeration", ettype, l, c);
          break;

        case token::function_end:
          end_error ("function", ettype, l, c);
          break;

        case token::if_end:
          end_error ("if", ettype, l, c);
          break;

        case token::parfor_end:
          end_error ("parfor", ettype, l, c);
          break;

        case token::try_catch_end:
          end_error ("try", ettype, l, c);
          break;

        case token::switch_end:
          end_error ("switch", ettype, l, c);
          break;

        case token::unwind_protect_end:
          end_error ("unwind_protect", ettype, l, c);
          break;

        case token::while_end:
          end_error ("while", ettype, l, c);
          break;

        default:
          panic_impossible ();
          break;
        }
    }

  return retval;
}

// Maybe print a warning if an assignment expression is used as the
// test in a logical expression.

void
octave_base_parser::maybe_warn_assign_as_truth_value (tree_expression *expr)
{
  if (expr->is_assignment_expression ()
      && expr->paren_count () < 2)
    {
      if (lexer.fcn_file_full_name.empty ())
        warning_with_id
          ("Octave:assign-as-truth-value",
           "suggest parenthesis around assignment used as truth value");
      else
        warning_with_id
          ("Octave:assign-as-truth-value",
           "suggest parenthesis around assignment used as truth value near line %d, column %d in file '%s'",
           expr->line (), expr->column (), lexer.fcn_file_full_name.c_str ());
    }
}

// Maybe print a warning about switch labels that aren't constants.

void
octave_base_parser::maybe_warn_variable_switch_label (tree_expression *expr)
{
  if (! expr->is_constant ())
    {
      if (lexer.fcn_file_full_name.empty ())
        warning_with_id ("Octave:variable-switch-label",
                         "variable switch label");
      else
        warning_with_id
          ("Octave:variable-switch-label",
           "variable switch label near line %d, column %d in file '%s'",
           expr->line (), expr->column (), lexer.fcn_file_full_name.c_str ());
    }
}

static tree_expression *
fold (tree_binary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op1 = e->lhs ();
  tree_expression *op2 = e->rhs ();

  if (op1->is_constant () && op2->is_constant ())
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, op1->line (), op1->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          e->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete e;

          retval = tc_retval;
        }
    }

  return retval;
}

static tree_expression *
fold (tree_unary_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *op = e->operand ();

  if (op->is_constant ())
    {
      octave_value tmp = e->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, op->line (), op->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          e->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete e;

          retval = tc_retval;
        }
    }

  return retval;
}

// Finish building a range.

tree_expression *
octave_base_parser::finish_colon_expression (tree_colon_expression *e)
{
  tree_expression *retval = e;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  tree_expression *base = e->base ();
  tree_expression *limit = e->limit ();
  tree_expression *incr = e->increment ();

  if (base)
    {
      if (limit)
        {
          if (base->is_constant () && limit->is_constant ()
              && (! incr || (incr && incr->is_constant ())))
            {
              octave_value tmp = e->rvalue1 ();

              if (! (error_state || warning_state))
                {
                  tree_constant *tc_retval
                    = new tree_constant (tmp, base->line (), base->column ());

                  std::ostringstream buf;

                  tree_print_code tpc (buf);

                  e->accept (tpc);

                  tc_retval->stash_original_text (buf.str ());

                  delete e;

                  retval = tc_retval;
                }
            }
        }
      else
        {
          e->preserve_base ();
          delete e;

          // FIXME -- need to attempt constant folding here
          // too (we need a generic way to do that).
          retval = base;
        }
    }

  return retval;
}

// Make a constant.

tree_constant *
octave_base_parser::make_constant (int op, token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_constant *retval = 0;

  switch (op)
    {
    case NUM:
      {
        octave_value tmp (tok_val->number ());
        retval = new tree_constant (tmp, l, c);
        retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case IMAG_NUM:
      {
        octave_value tmp (Complex (0.0, tok_val->number ()));
        retval = new tree_constant (tmp, l, c);
        retval->stash_original_text (tok_val->text_rep ());
      }
      break;

    case DQ_STRING:
    case SQ_STRING:
      {
        std::string txt = tok_val->text ();

        char delim = op == DQ_STRING ? '"' : '\'';
        octave_value tmp (txt, delim);

        if (txt.empty ())
          {
            if (op == DQ_STRING)
              tmp = octave_null_str::instance;
            else
              tmp = octave_null_sq_str::instance;
          }

        retval = new tree_constant (tmp, l, c);

        if (op == DQ_STRING)
          txt = undo_string_escapes (txt);

        // FIXME -- maybe this should also be handled by
        // tok_val->text_rep () for character strings?
        retval->stash_original_text (delim + txt + delim);
      }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

// Make a function handle.

tree_fcn_handle *
octave_base_parser::make_fcn_handle (token *tok_val)
{
  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_fcn_handle *retval = new tree_fcn_handle (tok_val->text (), l, c);

  return retval;
}

// Make an anonymous function handle.

tree_anon_fcn_handle *
octave_base_parser::make_anon_fcn_handle (tree_parameter_list *param_list,
                                          tree_statement *stmt)
{
  // FIXME -- need to get these from the location of the @ symbol.
  int l = lexer.input_line_number;
  int c = lexer.current_input_column;

  tree_parameter_list *ret_list = 0;

  symbol_table::scope_id fcn_scope = lexer.symtab_context.curr_scope ();

  if (lexer.symtab_context.empty ())
    panic_impossible ();

  lexer.symtab_context.pop ();

  stmt->set_print_flag (false);

  tree_statement_list *body = new tree_statement_list (stmt);

  body->mark_as_anon_function_body ();

  tree_anon_fcn_handle *retval
    = new tree_anon_fcn_handle (param_list, ret_list, body, fcn_scope, l, c);
  // FIXME: Stash the filename.  This does not work and produces
  // errors when executed.
  //retval->stash_file_name (lexer.fcn_file_name);

  return retval;
}

// Build a binary expression.

tree_expression *
octave_base_parser::make_binary_op (int op, tree_expression *op1,
                                    token *tok_val, tree_expression *op2)
{
  octave_value::binary_op t = octave_value::unknown_binary_op;

  switch (op)
    {
    case POW:
      t = octave_value::op_pow;
      break;

    case EPOW:
      t = octave_value::op_el_pow;
      break;

    case '+':
      t = octave_value::op_add;
      break;

    case '-':
      t = octave_value::op_sub;
      break;

    case '*':
      t = octave_value::op_mul;
      break;

    case '/':
      t = octave_value::op_div;
      break;

    case EMUL:
      t = octave_value::op_el_mul;
      break;

    case EDIV:
      t = octave_value::op_el_div;
      break;

    case LEFTDIV:
      t = octave_value::op_ldiv;
      break;

    case ELEFTDIV:
      t = octave_value::op_el_ldiv;
      break;

    case LSHIFT:
      t = octave_value::op_lshift;
      break;

    case RSHIFT:
      t = octave_value::op_rshift;
      break;

    case EXPR_LT:
      t = octave_value::op_lt;
      break;

    case EXPR_LE:
      t = octave_value::op_le;
      break;

    case EXPR_EQ:
      t = octave_value::op_eq;
      break;

    case EXPR_GE:
      t = octave_value::op_ge;
      break;

    case EXPR_GT:
      t = octave_value::op_gt;
      break;

    case EXPR_NE:
      t = octave_value::op_ne;
      break;

    case EXPR_AND:
      t = octave_value::op_el_and;
      break;

    case EXPR_OR:
      t = octave_value::op_el_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_binary_expression *e
    = maybe_compound_binary_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a boolean expression.

tree_expression *
octave_base_parser::make_boolean_op (int op, tree_expression *op1,
                                     token *tok_val, tree_expression *op2)
{
  tree_boolean_expression::type t;

  switch (op)
    {
    case EXPR_AND_AND:
      t = tree_boolean_expression::bool_and;
      break;

    case EXPR_OR_OR:
      t = tree_boolean_expression::bool_or;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_boolean_expression *e
    = new tree_boolean_expression (op1, op2, l, c, t);

  return fold (e);
}

// Build a prefix expression.

tree_expression *
octave_base_parser::make_prefix_op (int op, tree_expression *op1,
                                    token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case EXPR_NOT:
      t = octave_value::op_not;
      break;

    case '+':
      t = octave_value::op_uplus;
      break;

    case '-':
      t = octave_value::op_uminus;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_prefix_expression *e
    = new tree_prefix_expression (op1, l, c, t);

  return fold (e);
}

// Build a postfix expression.

tree_expression *
octave_base_parser::make_postfix_op (int op, tree_expression *op1,
                                     token *tok_val)
{
  octave_value::unary_op t = octave_value::unknown_unary_op;

  switch (op)
    {
    case HERMITIAN:
      t = octave_value::op_hermitian;
      break;

    case TRANSPOSE:
      t = octave_value::op_transpose;
      break;

    case PLUS_PLUS:
      t = octave_value::op_incr;
      break;

    case MINUS_MINUS:
      t = octave_value::op_decr;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = tok_val->line ();
  int c = tok_val->column ();

  tree_postfix_expression *e
    = new tree_postfix_expression (op1, l, c, t);

  return fold (e);
}

// Build an unwind-protect command.

tree_command *
octave_base_parser::make_unwind_command (token *unwind_tok,
                                         tree_statement_list *body,
                                         tree_statement_list *cleanup_stmts,
                                         token *end_tok,
                                         octave_comment_list *lc,
                                         octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::unwind_protect_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = unwind_tok->line ();
      int c = unwind_tok->column ();

      retval = new tree_unwind_protect_command (body, cleanup_stmts,
                                                lc, mc, tc, l, c);
    }

  return retval;
}

// Build a try-catch command.

tree_command *
octave_base_parser::make_try_command (token *try_tok,
                                      tree_statement_list *body,
                                      tree_statement_list *cleanup_stmts,
                                      token *end_tok,
                                      octave_comment_list *lc,
                                      octave_comment_list *mc)
{
  tree_command *retval = 0;

  if (end_token_ok (end_tok, token::try_catch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = try_tok->line ();
      int c = try_tok->column ();

      retval = new tree_try_catch_command (body, cleanup_stmts,
                                           lc, mc, tc, l, c);
    }

  return retval;
}

// Build a while command.

tree_command *
octave_base_parser::make_while_command (token *while_tok,
                                        tree_expression *expr,
                                        tree_statement_list *body,
                                        token *end_tok,
                                        octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  if (end_token_ok (end_tok, token::while_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer.looping--;

      int l = while_tok->line ();
      int c = while_tok->column ();

      retval = new tree_while_command (expr, body, lc, tc, l, c);
    }

  return retval;
}

// Build a do-until command.

tree_command *
octave_base_parser::make_do_until_command (token *until_tok,
                                           tree_statement_list *body,
                                           tree_expression *expr,
                                           octave_comment_list *lc)
{
  tree_command *retval = 0;

  maybe_warn_assign_as_truth_value (expr);

  octave_comment_list *tc = octave_comment_buffer::get_comment ();

  lexer.looping--;

  int l = until_tok->line ();
  int c = until_tok->column ();

  retval = new tree_do_until_command (expr, body, lc, tc, l, c);

  return retval;
}

// Build a for command.

tree_command *
octave_base_parser::make_for_command (int tok_id, token *for_tok,
                                      tree_argument_list *lhs,
                                      tree_expression *expr,
                                      tree_expression *maxproc,
                                      tree_statement_list *body,
                                      token *end_tok,
                                      octave_comment_list *lc)
{
  tree_command *retval = 0;

  bool parfor = tok_id == PARFOR;

  if (end_token_ok (end_tok, parfor ? token::parfor_end : token::for_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      lexer.looping--;

      int l = for_tok->line ();
      int c = for_tok->column ();

      if (lhs->length () == 1)
        {
          tree_expression *tmp = lhs->remove_front ();

          retval = new tree_simple_for_command (parfor, tmp, expr, maxproc,
                                                body, lc, tc, l, c);

          delete lhs;
        }
      else
        {
          if (parfor)
            bison_error ("invalid syntax for parfor statement");
          else
            retval = new tree_complex_for_command (lhs, expr, body,
                                                   lc, tc, l, c);
        }
    }

  return retval;
}

// Build a break command.

tree_command *
octave_base_parser::make_break_command (token *break_tok)
{
  tree_command *retval = 0;

  int l = break_tok->line ();
  int c = break_tok->column ();

  retval = new tree_break_command (l, c);

  return retval;
}

// Build a continue command.

tree_command *
octave_base_parser::make_continue_command (token *continue_tok)
{
  tree_command *retval = 0;

  int l = continue_tok->line ();
  int c = continue_tok->column ();

  retval = new tree_continue_command (l, c);

  return retval;
}

// Build a return command.

tree_command *
octave_base_parser::make_return_command (token *return_tok)
{
  tree_command *retval = 0;

  int l = return_tok->line ();
  int c = return_tok->column ();

  retval = new tree_return_command (l, c);

  return retval;
}

// Start an if command.

tree_if_command_list *
octave_base_parser::start_if_command (tree_expression *expr,
                                      tree_statement_list *list)
{
  maybe_warn_assign_as_truth_value (expr);

  tree_if_clause *t = new tree_if_clause (expr, list);

  return new tree_if_command_list (t);
}

// Finish an if command.

tree_if_command *
octave_base_parser::finish_if_command (token *if_tok,
                                       tree_if_command_list *list,
                                       token *end_tok,
                                       octave_comment_list *lc)
{
  tree_if_command *retval = 0;

  if (end_token_ok (end_tok, token::if_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = if_tok->line ();
      int c = if_tok->column ();

      if (list && ! list->empty ())
        {
          tree_if_clause *elt = list->front ();

          if (elt)
            {
              elt->line (l);
              elt->column (c);
            }
        }

      retval = new tree_if_command (list, lc, tc, l, c);
    }

  return retval;
}

// Build an elseif clause.

tree_if_clause *
octave_base_parser::make_elseif_clause (token *elseif_tok,
                                        tree_expression *expr,
                                        tree_statement_list *list,
                                        octave_comment_list *lc)
{
  maybe_warn_assign_as_truth_value (expr);

  int l = elseif_tok->line ();
  int c = elseif_tok->column ();

  return new tree_if_clause (expr, list, lc, l, c);
}

// Finish a switch command.

tree_switch_command *
octave_base_parser::finish_switch_command (token *switch_tok,
                                           tree_expression *expr,
                                           tree_switch_case_list *list,
                                           token *end_tok,
                                           octave_comment_list *lc)
{
  tree_switch_command *retval = 0;

  if (end_token_ok (end_tok, token::switch_end))
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      int l = switch_tok->line ();
      int c = switch_tok->column ();

      if (list && ! list->empty ())
        {
          tree_switch_case *elt = list->front ();

          if (elt)
            {
              elt->line (l);
              elt->column (c);
            }
        }

      retval = new tree_switch_command (expr, list, lc, tc, l, c);
    }

  return retval;
}

// Build a switch case.

tree_switch_case *
octave_base_parser::make_switch_case (token *case_tok,
                                      tree_expression *expr,
                                      tree_statement_list *list,
                                      octave_comment_list *lc)
{
  maybe_warn_variable_switch_label (expr);

  int l = case_tok->line ();
  int c = case_tok->column ();

  return new tree_switch_case (expr, list, lc, l, c);
}

// Build an assignment to a variable.

tree_expression *
octave_base_parser::make_assign_op (int op, tree_argument_list *lhs,
                                    token *eq_tok, tree_expression *rhs)
{
  tree_expression *retval = 0;

  octave_value::assign_op t = octave_value::unknown_assign_op;

  switch (op)
    {
    case '=':
      t = octave_value::op_asn_eq;
      break;

    case ADD_EQ:
      t = octave_value::op_add_eq;
      break;

    case SUB_EQ:
      t = octave_value::op_sub_eq;
      break;

    case MUL_EQ:
      t = octave_value::op_mul_eq;
      break;

    case DIV_EQ:
      t = octave_value::op_div_eq;
      break;

    case LEFTDIV_EQ:
      t = octave_value::op_ldiv_eq;
      break;

    case POW_EQ:
      t = octave_value::op_pow_eq;
      break;

    case LSHIFT_EQ:
      t = octave_value::op_lshift_eq;
      break;

    case RSHIFT_EQ:
      t = octave_value::op_rshift_eq;
      break;

    case EMUL_EQ:
      t = octave_value::op_el_mul_eq;
      break;

    case EDIV_EQ:
      t = octave_value::op_el_div_eq;
      break;

    case ELEFTDIV_EQ:
      t = octave_value::op_el_ldiv_eq;
      break;

    case EPOW_EQ:
      t = octave_value::op_el_pow_eq;
      break;

    case AND_EQ:
      t = octave_value::op_el_and_eq;
      break;

    case OR_EQ:
      t = octave_value::op_el_or_eq;
      break;

    default:
      panic_impossible ();
      break;
    }

  int l = eq_tok->line ();
  int c = eq_tok->column ();

  if (lhs->is_simple_assign_lhs ())
    {
      tree_expression *tmp = lhs->remove_front ();

      retval = new tree_simple_assignment (tmp, rhs, false, l, c, t);

      delete lhs;
    }
  else if (t == octave_value::op_asn_eq)
    return new tree_multi_assignment (lhs, rhs, false, l, c);
  else
    bison_error ("computed multiple assignment not allowed");

  return retval;
}

// Define a script.

void
octave_base_parser::make_script (tree_statement_list *cmds,
                                 tree_statement *end_script)
{
  if (! cmds)
    cmds = new tree_statement_list ();

  cmds->append (end_script);

  octave_user_script *script
    = new octave_user_script (lexer.fcn_file_full_name,
                              lexer.fcn_file_name,
                              cmds, lexer.help_text);

  lexer.help_text = "";

  octave_time now;

  script->stash_fcn_file_time (now);

  primary_fcn_ptr = script;
}

// Begin defining a function.

octave_user_function *
octave_base_parser::start_function (tree_parameter_list *param_list,
                                    tree_statement_list *body,
                                    tree_statement *end_fcn_stmt)
{
  // We'll fill in the return list later.

  if (! body)
    body = new tree_statement_list ();

  body->append (end_fcn_stmt);

  octave_user_function *fcn
    = new octave_user_function (lexer.symtab_context.curr_scope (),
                                param_list, 0, body);

  if (fcn)
    {
      octave_comment_list *tc = octave_comment_buffer::get_comment ();

      fcn->stash_trailing_comment (tc);
      fcn->stash_fcn_end_location (end_fcn_stmt->line (),
                                   end_fcn_stmt->column ());
    }

  return fcn;
}

tree_statement *
octave_base_parser::make_end (const std::string& type, bool eof, int l, int c)
{
  return make_statement (new tree_no_op_command (type, eof, l, c));
}

// Do most of the work for defining a function.

octave_user_function *
octave_base_parser::frob_function (const std::string& fname,
                                   octave_user_function *fcn)
{
  std::string id_name = fname;

  // If input is coming from a file, issue a warning if the name of
  // the file does not match the name of the function stated in the
  // file.  Matlab doesn't provide a diagnostic (it ignores the stated
  // name).
  if (! autoloading && lexer.reading_fcn_file
      && curr_fcn_depth == 1 && ! parsing_subfunctions)
  {
    // FIXME -- should lexer.fcn_file_name already be
    // preprocessed when we get here?  It seems to only be a
    // problem with relative file names.

    std::string nm = lexer.fcn_file_name;

    size_t pos = nm.find_last_of (file_ops::dir_sep_chars ());

    if (pos != std::string::npos)
      nm = lexer.fcn_file_name.substr (pos+1);

    if (nm != id_name)
      {
        warning_with_id
          ("Octave:function-name-clash",
           "function name '%s' does not agree with function file name '%s'",
           id_name.c_str (), lexer.fcn_file_full_name.c_str ());

        id_name = nm;
      }
  }

  if (lexer.reading_fcn_file || lexer.reading_classdef_file || autoloading)
    {
      octave_time now;

      fcn->stash_fcn_file_name (lexer.fcn_file_full_name);
      fcn->stash_fcn_file_time (now);
      fcn->mark_as_system_fcn_file ();

      if (fcn_file_from_relative_lookup)
        fcn->mark_relative ();

      if (curr_fcn_depth > 1 || parsing_subfunctions)
        {
          fcn->stash_parent_fcn_name (lexer.fcn_file_name);

          if (curr_fcn_depth > 1)
            fcn->stash_parent_fcn_scope (function_scopes[function_scopes.size ()-2]);
          else
            fcn->stash_parent_fcn_scope (primary_fcn_scope);
        }

      if (lexer.parsing_class_method)
        {
          if (curr_class_name == id_name)
            fcn->mark_as_class_constructor ();
          else
            fcn->mark_as_class_method ();

          fcn->stash_dispatch_class (curr_class_name);
        }

      std::string nm = fcn->fcn_file_name ();

      file_stat fs (nm);

      if (fs && fs.is_newer (now))
        warning_with_id ("Octave:future-time-stamp",
                         "time stamp for '%s' is in the future", nm.c_str ());
    }
  else if (! input_from_tmp_history_file
           && ! lexer.force_script
           && lexer.reading_script_file
           && lexer.fcn_file_name == id_name)
    {
      warning ("function '%s' defined within script file '%s'",
               id_name.c_str (), lexer.fcn_file_full_name.c_str ());
    }

  fcn->stash_function_name (id_name);

  if (! lexer.help_text.empty () && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    {
      fcn->document (lexer.help_text);

      lexer.help_text = "";
    }

  if (lexer.reading_fcn_file && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    primary_fcn_ptr = fcn;

  return fcn;
}

tree_function_def *
octave_base_parser::finish_function (tree_parameter_list *ret_list,
                                     octave_user_function *fcn,
                                     octave_comment_list *lc,
                                     int l, int c)
{
  tree_function_def *retval = 0;

  if (ret_list)
    ret_list->mark_as_formal_parameters ();

  if (fcn)
    {
      std::string nm = fcn->name ();
      std::string file = fcn->fcn_file_name ();

      std::string tmp = nm;
      if (! file.empty ())
        tmp += ": " + file;

      symbol_table::cache_name (fcn->scope (), tmp);

      if (lc)
        fcn->stash_leading_comment (lc);

      fcn->define_ret_list (ret_list);

      if (curr_fcn_depth > 1 || parsing_subfunctions)
        {
          fcn->mark_as_subfunction ();
          fcn->stash_fcn_location (l, c);

          subfunction_names.push_back (nm);

          if (endfunction_found && function_scopes.size () > 1)
            {
              symbol_table::scope_id pscope
                = function_scopes[function_scopes.size ()-2];

              symbol_table::install_nestfunction (nm, octave_value (fcn),
                                                  pscope);
            }
          else
            symbol_table::install_subfunction (nm, octave_value (fcn),
                                               primary_fcn_scope);
        }

      if (curr_fcn_depth == 1 && fcn)
        symbol_table::update_nest (fcn->scope ());

      if (! lexer.reading_fcn_file && curr_fcn_depth == 1)
        {
          // We are either reading a script file or defining a function
          // at the command line, so this definition creates a
          // tree_function object that is placed in the parse tree.
          // Otherwise, it is just inserted in the symbol table,
          // either as a subfunction or nested function (see above),
          // or as the primary function for the file, via
          // primary_fcn_ptr (see also load_fcn_from_file,,
          // parse_fcn_file, and
          // symbol_table::fcn_info::fcn_info_rep::find_user_function).

          retval = new tree_function_def (fcn);
        }
    }

  return retval;
}

void
octave_base_parser::recover_from_parsing_function (void)
{
  if (lexer.symtab_context.empty ())
    panic_impossible ();

  lexer.symtab_context.pop ();

  if (lexer.reading_fcn_file && curr_fcn_depth == 1
      && ! parsing_subfunctions)
    parsing_subfunctions = true;

  curr_fcn_depth--;
  function_scopes.pop_back ();

  lexer.defining_func--;
  lexer.parsed_function_name.pop ();
  lexer.looking_at_return_list = false;
  lexer.looking_at_parameter_list = false;
}

// Make an index expression.

tree_index_expression *
octave_base_parser::make_index_expression (tree_expression *expr,
                                           tree_argument_list *args,
                                           char type)
{
  tree_index_expression *retval = 0;

  if (args && args->has_magic_tilde ())
    {
      bison_error ("invalid use of empty argument (~) in index expression");
      return retval;
    }

  int l = expr->line ();
  int c = expr->column ();

  expr->mark_postfix_indexed ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (args, type);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, args, l, c, type);

  return retval;
}

// Make an indirect reference expression.

tree_index_expression *
octave_base_parser::make_indirect_ref (tree_expression *expr,
                                       const std::string& elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer.looking_at_indirect_ref = false;

  return retval;
}

// Make an indirect reference expression with dynamic field name.

tree_index_expression *
octave_base_parser::make_indirect_ref (tree_expression *expr, tree_expression *elt)
{
  tree_index_expression *retval = 0;

  int l = expr->line ();
  int c = expr->column ();

  if (expr->is_index_expression ())
    {
      tree_index_expression *tmp = static_cast<tree_index_expression *> (expr);

      tmp->append (elt);

      retval = tmp;
    }
  else
    retval = new tree_index_expression (expr, elt, l, c);

  lexer.looking_at_indirect_ref = false;

  return retval;
}

// Make a declaration command.

tree_decl_command *
octave_base_parser::make_decl_command (int tok, token *tok_val,
                                       tree_decl_init_list *lst)
{
  tree_decl_command *retval = 0;

  int l = tok_val->line ();
  int c = tok_val->column ();

  switch (tok)
    {
    case GLOBAL:
      retval = new tree_global_command (lst, l, c);
      break;

    case PERSISTENT:
      if (curr_fcn_depth > 0)
        retval = new tree_persistent_command (lst, l, c);
      else
        {
          if (lexer.reading_script_file)
            warning ("ignoring persistent declaration near line %d of file '%s'",
                     l, lexer.fcn_file_full_name.c_str ());
          else
            warning ("ignoring persistent declaration near line %d", l);
        }
      break;

    default:
      panic_impossible ();
      break;
    }

  return retval;
}

bool
octave_base_parser::validate_array_list (tree_expression *e)
{
  bool retval = true;

  tree_array_list *al = dynamic_cast<tree_array_list *> (e);

  for (tree_array_list::iterator i = al->begin (); i != al->end (); i++)
    {
      tree_argument_list *row = *i;

      if (row && row->has_magic_tilde ())
        {
          retval = false;
          if (e->is_matrix ())
             bison_error ("invalid use of tilde (~) in matrix expression");
           else
             bison_error ("invalid use of tilde (~) in cell expression");
          break;
        }
    }

  return retval;
}

tree_argument_list *
octave_base_parser::validate_matrix_for_assignment (tree_expression *e)
{
  tree_argument_list *retval = 0;

  if (e->is_constant ())
    {
      octave_value ov = e->rvalue1 ();

      if (ov.is_empty ())
        bison_error ("invalid empty left hand side of assignment");
      else
        bison_error ("invalid constant left hand side of assignment");

      delete e;
    }
  else
    {
      bool is_simple_assign = true;

      tree_argument_list *tmp = 0;

      if (e->is_matrix ())
        {
          tree_matrix *mat = dynamic_cast<tree_matrix *> (e);

          if (mat && mat->size () == 1)
            {
              tmp = mat->front ();
              mat->pop_front ();
              delete e;
              is_simple_assign = false;
            }
        }
      else
        tmp = new tree_argument_list (e);

      if (tmp && tmp->is_valid_lvalue_list ())
        {
          lexer.mark_as_variables (tmp->variable_names ());
          retval = tmp;
        }
      else
        {
          bison_error ("invalid left hand side of assignment");
          delete tmp;
        }

      if (retval && is_simple_assign)
        retval->mark_as_simple_assign_lhs ();
    }

  return retval;
}

// Finish building an array_list.

tree_expression *
octave_base_parser::finish_array_list (tree_array_list *array_list)
{
  tree_expression *retval = array_list;

  unwind_protect frame;

  frame.protect_var (error_state);
  frame.protect_var (warning_state);

  frame.protect_var (discard_error_messages);
  frame.protect_var (discard_warning_messages);

  discard_error_messages = true;
  discard_warning_messages = true;

  if (array_list->all_elements_are_constant ())
    {
      octave_value tmp = array_list->rvalue1 ();

      if (! (error_state || warning_state))
        {
          tree_constant *tc_retval
            = new tree_constant (tmp, array_list->line (),
                                 array_list->column ());

          std::ostringstream buf;

          tree_print_code tpc (buf);

          array_list->accept (tpc);

          tc_retval->stash_original_text (buf.str ());

          delete array_list;

          retval = tc_retval;
        }
    }

  return retval;
}

// Finish building a matrix list.

tree_expression *
octave_base_parser::finish_matrix (tree_matrix *m)
{
  return finish_array_list (m);
}

// Finish building a cell list.

tree_expression *
octave_base_parser::finish_cell (tree_cell *c)
{
  return finish_array_list (c);
}

void
octave_base_parser::maybe_warn_missing_semi (tree_statement_list *t)
{
  if (curr_fcn_depth > 0)
    {
      tree_statement *tmp = t->back ();

      if (tmp->is_expression ())
        warning_with_id
          ("Octave:missing-semicolon",
           "missing semicolon near line %d, column %d in file '%s'",
            tmp->line (), tmp->column (), lexer.fcn_file_full_name.c_str ());
    }
}

tree_statement_list *
octave_base_parser::set_stmt_print_flag (tree_statement_list *list,
                                         char sep, bool warn_missing_semi)
{
  tree_statement *tmp = list->back ();

  switch (sep)
    {
    case ';':
      tmp->set_print_flag (false);
      break;

    case 0:
    case ',':
    case '\n':
      tmp->set_print_flag (true);
      if (warn_missing_semi)
        maybe_warn_missing_semi (list);
      break;

    default:
      warning ("unrecognized separator type!");
      break;
    }

  // Even if a statement is null, we add it to the list then remove it
  // here so that the print flag is applied to the correct statement.

  if (tmp->is_null_statement ())
    {
      list->pop_back ();
      delete tmp;
    }

  return list;
}

tree_statement_list *
octave_base_parser::make_statement_list (tree_statement *stmt)
{
  return new tree_statement_list (stmt);
}

tree_statement_list *
octave_base_parser::append_statement_list (tree_statement_list *list,
                                           char sep, tree_statement *stmt,
                                           bool warn_missing_semi)
{
  set_stmt_print_flag (list, sep, warn_missing_semi);

  list->append (stmt);

  return list;
}

void
octave_base_parser::bison_error (const char *s)
{
  int err_col = lexer.current_input_column - 1;

  std::ostringstream output_buf;

  if (lexer.reading_fcn_file || lexer.reading_script_file || lexer.reading_classdef_file)
    output_buf << "parse error near line " << lexer.input_line_number
               << " of file " << lexer.fcn_file_full_name;
  else
    output_buf << "parse error:";

  if (s && strcmp (s, "parse error") != 0)
    output_buf << "\n\n  " << s;

  output_buf << "\n\n";

  std::string curr_line = lexer.current_input_line;

  if (! curr_line.empty ())
    {
      size_t len = curr_line.length ();

      if (curr_line[len-1] == '\n')
        curr_line.resize (len-1);

      // Print the line, maybe with a pointer near the error token.

      output_buf << ">>> " << curr_line << "\n";

      if (err_col == 0)
        err_col = len;

      for (int i = 0; i < err_col + 3; i++)
        output_buf << " ";

      output_buf << "^";
    }

  output_buf << "\n";

  std::string msg = output_buf.str ();

  parse_error ("%s", msg.c_str ());
}

int
octave_parser::run (void)
{
  return octave_parse (*this);
}

octave_push_parser::~octave_push_parser (void)
{
  yypstate_delete (static_cast<yypstate *> (parser_state));
}

void
octave_push_parser::init (void)
{
  parser_state = yypstate_new ();

  octave_base_parser::init ();
}

// Parse input from INPUT.  Pass TRUE for EOF if the end of INPUT should
// finish the parse.

int
octave_push_parser::run (const std::string& input, bool eof)
{
  int status = -1;

  dynamic_cast<octave_push_lexer&> (lexer).append_input (input, eof);

  do
    {   
      YYSTYPE lval;

      int token = octave_lex (&lval, scanner);

      if (token < 0)
        {
          if (! eof && lexer.at_end_of_buffer ())
            {
              status = -1;
              break;
            }
        }

      yypstate *pstate = static_cast<yypstate *> (parser_state);

      status = octave_push_parse (pstate, token, &lval, *this);
    }
  while (status == YYPUSH_MORE);

  return status;
}

static void
safe_fclose (FILE *f)
{
  // FIXME -- comments at the end of an input file are
  // discarded (otherwise, they would be appended to the next
  // statement, possibly from the command line or another file, which
  // can be quite confusing).

  octave_comment_list *tc = octave_comment_buffer::get_comment ();

  delete tc;

  if (f)
    fclose (static_cast<FILE *> (f));
}

static octave_function *
parse_fcn_file (const std::string& full_file, const std::string& file,
                const std::string& dispatch_type,
                bool require_file, bool force_script, bool autoload,    
                bool relative_lookup, const std::string& warn_for)
{
  unwind_protect frame;

  octave_function *fcn_ptr = 0;

  // Open function file and parse.

  FILE *in_stream = command_editor::get_input_stream ();

  frame.add_fcn (command_editor::set_input_stream, in_stream);

  frame.add_fcn (command_history::ignore_entries,
                 command_history::ignoring_entries ());

  command_history::ignore_entries ();

  FILE *ffile = 0;

  if (! full_file.empty ())
    ffile = gnulib::fopen (full_file.c_str (), "rb");

  frame.add_fcn (safe_fclose, ffile);

  if (ffile)
    {
      // octave_base_parser constructor sets this for us.
      frame.protect_var (LEXER);

      octave_parser parser (ffile);

      parser.curr_class_name = dispatch_type;
      parser.autoloading = autoload;
      parser.fcn_file_from_relative_lookup = relative_lookup;

      parser.lexer.force_script = force_script;
      parser.lexer.prep_for_file ();
      parser.lexer.parsing_class_method = ! dispatch_type.empty ();

      parser.lexer.fcn_file_name = file;
      parser.lexer.fcn_file_full_name = full_file;

      int status = parser.run ();

      fcn_ptr = parser.primary_fcn_ptr;

      if (fcn_ptr)
        {
          fcn_ptr->maybe_relocate_end ();

          if (parser.parsing_subfunctions)
            {
              if (! parser.endfunction_found)
                parser.subfunction_names.reverse ();

              fcn_ptr->stash_subfunction_names (parser.subfunction_names);
            }
        }

      if (status != 0)
        error ("parse error while reading file %s", full_file.c_str ());
    }
  else if (require_file)
    error ("no such file, '%s'", full_file.c_str ());
  else if (! warn_for.empty ())
    error ("%s: unable to open file '%s'", warn_for.c_str (),
           full_file.c_str ());

  return fcn_ptr;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found,
                    std::string& full_file)
{
  std::string retval;

  full_file = fcn_file_in_path (nm);

  std::string file = full_file;

  size_t file_len = file.length ();

  if ((file_len > 4 && file.substr (file_len-4) == ".oct")
      || (file_len > 4 && file.substr (file_len-4) == ".mex")
      || (file_len > 2 && file.substr (file_len-2) == ".m"))
    {
      file = octave_env::base_pathname (file);
      file = file.substr (0, file.find_last_of ('.'));

      size_t pos = file.find_last_of (file_ops::dir_sep_str ());
      if (pos != std::string::npos)
        file = file.substr (pos+1);
    }

  if (! file.empty ())
    {
      symbol_found = true;

      octave_function *fcn
        = parse_fcn_file (full_file, file, "", true, false, false, false, "");

      if (fcn)
        {
          retval = fcn->doc_string ();

          delete fcn;
        }
    }

  return retval;
}

std::string
get_help_from_file (const std::string& nm, bool& symbol_found)
{
  std::string file;
  return get_help_from_file (nm, symbol_found, file);
}

std::string
lookup_autoload (const std::string& nm)
{
  std::string retval;

  typedef std::map<std::string, std::string>::const_iterator am_iter;

  am_iter p = autoload_map.find (nm);

  if (p != autoload_map.end ())
    retval = load_path::find_file (p->second);

  return retval;
}

string_vector
autoloaded_functions (void)
{
  string_vector names (autoload_map.size ());

  octave_idx_type i = 0;
  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    names[i++] = p->first;

  return names;
}

string_vector
reverse_lookup_autoload (const std::string& nm)
{
  string_vector names;

  typedef std::map<std::string, std::string>::const_iterator am_iter;
  for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
    if (nm == p->second)
      names.append (p->first);

  return names;
}

octave_function *
load_fcn_from_file (const std::string& file_name, const std::string& dir_name,
                    const std::string& dispatch_type,
                    const std::string& fcn_name, bool autoload)
{
  octave_function *retval = 0;

  unwind_protect frame;

  std::string nm = file_name;

  size_t nm_len = nm.length ();

  std::string file;

  bool relative_lookup = false;

  file = nm;

  if ((nm_len > 4 && nm.substr (nm_len-4) == ".oct")
      || (nm_len > 4 && nm.substr (nm_len-4) == ".mex")
      || (nm_len > 2 && nm.substr (nm_len-2) == ".m"))
    {
      nm = octave_env::base_pathname (file);
      nm = nm.substr (0, nm.find_last_of ('.'));

      size_t pos = nm.find_last_of (file_ops::dir_sep_str ());
      if (pos != std::string::npos)
        nm = nm.substr (pos+1);
    }

  relative_lookup = ! octave_env::absolute_pathname (file);

  file = octave_env::make_absolute (file);

  int len = file.length ();

  if (len > 4 && file.substr (len-4, len-1) == ".oct")
    {
      if (autoload && ! fcn_name.empty ())
        nm = fcn_name;

      retval = octave_dynamic_loader::load_oct (nm, file, relative_lookup);
    }
  else if (len > 4 && file.substr (len-4, len-1) == ".mex")
    {
      // Temporarily load m-file version of mex-file, if it exists,
      // to get the help-string to use.

      octave_function *tmpfcn = parse_fcn_file (file.substr (0, len - 2),
                                                nm, dispatch_type, false,
                                                autoload, autoload,
                                                relative_lookup, "");

      retval = octave_dynamic_loader::load_mex (nm, file, relative_lookup);

      if (tmpfcn)
        retval->document (tmpfcn->doc_string ());
      delete tmpfcn;
    }
  else if (len > 2)
    {
      retval = parse_fcn_file (file, nm, dispatch_type, true, autoload,
                               autoload, relative_lookup, "");
    }

  if (retval)
    {
      retval->stash_dir_name (dir_name);

      if (retval->is_user_function ())
        {
          symbol_table::scope_id id = retval->scope ();

          symbol_table::stash_dir_name_for_subfunctions (id, dir_name);
        }
    }

  return retval;
}

DEFUN (autoload, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} autoload (@var{function}, @var{file})\n\
Define @var{function} to autoload from @var{file}.\n\
\n\
The second argument, @var{file}, should be an absolute file name or\n\
a file name in the same directory as the function or script from which\n\
the autoload command was run.  @var{file} should not depend on the\n\
Octave load path.\n\
\n\
Normally, calls to @code{autoload} appear in PKG_ADD script files that\n\
are evaluated when a directory is added to the Octave's load path.  To\n\
avoid having to hardcode directory names in @var{file}, if @var{file}\n\
is in the same directory as the PKG_ADD script then\n\
\n\
@example\n\
autoload (\"foo\", \"bar.oct\");\n\
@end example\n\
\n\
@noindent\n\
will load the function @code{foo} from the file @code{bar.oct}.  The above\n\
when @code{bar.oct} is not in the same directory or uses like\n\
\n\
@example\n\
autoload (\"foo\", file_in_loadpath (\"bar.oct\"))\n\
@end example\n\
\n\
@noindent\n\
are strongly discouraged, as their behavior might be unpredictable.\n\
\n\
With no arguments, return a structure containing the current autoload map.\n\
@seealso{PKG_ADD}\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 0)
    {
      Cell func_names (dim_vector (autoload_map.size (), 1));
      Cell file_names (dim_vector (autoload_map.size (), 1));

      octave_idx_type i = 0;
      typedef std::map<std::string, std::string>::const_iterator am_iter;
      for (am_iter p = autoload_map.begin (); p != autoload_map.end (); p++)
        {
          func_names(i) = p->first;
          file_names(i) = p->second;

          i++;
        }

      octave_map m;

      m.assign ("function", func_names);
      m.assign ("file", file_names);

      retval = m;
    }
  else if (nargin == 2)
    {
      string_vector argv = args.make_argv ("autoload");

      if (! error_state)
        {
          std::string nm = argv[2];

          if (! octave_env::absolute_pathname (nm))
            {
              octave_user_code *fcn = octave_call_stack::caller_user_code ();

              bool found = false;

              if (fcn)
                {
                  std::string fname = fcn->fcn_file_name ();

                  if (! fname.empty ())
                    {
                      fname = octave_env::make_absolute (fname);
                      fname = fname.substr (0, fname.find_last_of (file_ops::dir_sep_str ()) + 1);

                      file_stat fs (fname + nm);

                      if (fs.exists ())
                        {
                          nm = fname + nm;
                          found = true;
                        }
                    }
                }
              if (! found)
                warning_with_id ("Octave:autoload-relative-file-name",
                                 "autoload: '%s' is not an absolute file name",
                                 nm.c_str ());
            }
          autoload_map[argv[1]] = nm;
        }
    }
  else
    print_usage ();

  return retval;
}

void
source_file (const std::string& file_name, const std::string& context,
             bool verbose, bool require_file, const std::string& warn_for)
{
  // Map from absolute name of script file to recursion level.  We
  // use a map instead of simply placing a limit on recursion in the
  // source_file function so that two mutually recursive scripts
  // written as
  //
  //   foo1.m:
  //   ------
  //   foo2
  //
  //   foo2.m:
  //   ------
  //   foo1
  //
  // and called with
  //
  //   foo1
  //
  // (for example) will behave the same if they are written as
  //
  //   foo1.m:
  //   ------
  //   source ("foo2.m")
  //
  //   foo2.m:
  //   ------
  //   source ("foo1.m")
  //
  // and called with
  //
  //   source ("foo1.m")
  //
  // (for example).

  static std::map<std::string, int> source_call_depth;

  std::string file_full_name = file_ops::tilde_expand (file_name);

  file_full_name = octave_env::make_absolute (file_full_name);

  unwind_protect frame;

  if (source_call_depth.find (file_full_name) == source_call_depth.end ())
    source_call_depth[file_full_name] = -1;

  frame.protect_var (source_call_depth[file_full_name]);

  source_call_depth[file_full_name]++;

  if (source_call_depth[file_full_name] >= Vmax_recursion_depth)
    {
      error ("max_recursion_depth exceeded");
      return;
    }

  if (! context.empty ())
    {
      if (context == "caller")
        octave_call_stack::goto_caller_frame ();
      else if (context == "base")
        octave_call_stack::goto_base_frame ();
      else
        error ("source: context must be \"caller\" or \"base\"");

      if (! error_state)
        frame.add_fcn (octave_call_stack::pop);
    }

  if (! error_state)
    {
      octave_function *fcn = parse_fcn_file (file_full_name, file_name,
                                             "", require_file, true,
                                             false, false, warn_for);

      if (! error_state)
        {
          if (fcn && fcn->is_user_script ())
            {
              octave_value_list args;

              if (verbose)
                {
                  std::cout << "executing commands from " << file_full_name << " ... ";
                  reading_startup_message_printed = true;
                  std::cout.flush ();
                }

              fcn->do_multi_index_op (0, args);

              if (verbose)
                std::cout << "done." << std::endl;

              delete fcn;
            }
        }
      else
        error ("source: error sourcing file '%s'",
               file_full_name.c_str ());
    }
}

DEFUN (mfilename, args, ,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} mfilename ()\n\
@deftypefnx {Built-in Function} {} mfilename (\"fullpath\")\n\
@deftypefnx {Built-in Function} {} mfilename (\"fullpathext\")\n\
Return the name of the currently executing file.  At the top-level,\n\
return the empty string.  Given the argument @code{\"fullpath\"},\n\
include the directory part of the file name, but not the extension.\n\
Given the argument @code{\"fullpathext\"}, include the directory part\n\
of the file name and the extension.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      print_usage ();
      return retval;
    }

  std::string arg;

  if (nargin == 1)
    {
      arg = args(0).string_value ();

      if (error_state)
        {
          error ("mfilename: expecting argument to be a character string");
          return retval;
        }
    }

  std::string fname;

  octave_user_code *fcn = octave_call_stack::caller_user_code ();

  if (fcn)
    {
      fname = fcn->fcn_file_name ();

      if (fname.empty ())
        fname = fcn->name ();
    }

  if (arg == "fullpathext")
    retval = fname;
  else
    {
      size_t dpos = fname.rfind (file_ops::dir_sep_char ());
      size_t epos = fname.rfind ('.');

      if (epos <= dpos)
        epos = std::string::npos;

      fname = (epos != std::string::npos) ? fname.substr (0, epos) : fname;

      if (arg == "fullpath")
        retval = fname;
      else
        retval = (dpos != std::string::npos) ? fname.substr (dpos+1) : fname;
    }

  return retval;
}


DEFUN (source, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} source (@var{file})\n\
Parse and execute the contents of @var{file}.  This is equivalent to\n\
executing commands from a script file, but without requiring the file to\n\
be named @file{@var{file}.m}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 1 || nargin == 2)
    {
      std::string file_name = args(0).string_value ();

      if (! error_state)
        {
          std::string context;

          if (nargin == 2)
            context = args(1).string_value ();

          if (! error_state)
            source_file (file_name, context);
          else
            error ("source: expecting context to be character string");
        }
      else
        error ("source: expecting file name as argument");
    }
  else
    print_usage ();

  return retval;
}

// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  NAME is the name of the function to
// call.  ARGS are the arguments to the function.  NARGOUT is the
// number of output arguments expected.

octave_value_list
feval (const std::string& name, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  octave_value fcn = symbol_table::find_function (name, args);

  if (fcn.is_defined ())
    retval = fcn.do_multi_index_op (nargout, args);
  else
    {
      maybe_missing_function_hook (name);
      if (! error_state)
        error ("feval: function '%s' not found", name.c_str ());
    }

  return retval;
}

octave_value_list
feval (octave_function *fcn, const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  if (fcn)
    retval = fcn->do_multi_index_op (nargout, args);

  return retval;
}

static octave_value_list
get_feval_args (const octave_value_list& args)
{
  return args.slice (1, args.length () - 1, true);
}


// Evaluate an Octave function (built-in or interpreted) and return
// the list of result values.  The first element of ARGS should be a
// string containing the name of the function to call, then the rest
// are the actual arguments to the function.  NARGOUT is the number of
// output arguments expected.

octave_value_list
feval (const octave_value_list& args, int nargout)
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      octave_value f_arg = args(0);

      if (f_arg.is_string ())
        {
          std::string name = f_arg.string_value ();

          if (! error_state)
            {
              octave_value_list tmp_args = get_feval_args (args);

              retval = feval (name, tmp_args, nargout);
            }
        }
      else if (f_arg.is_function_handle ()
               || f_arg.is_anonymous_function ()
               || f_arg.is_inline_function ())
        {
          const octave_value_list tmp_args = get_feval_args (args);

          retval = f_arg.do_multi_index_op (nargout, tmp_args);
        }
      else
        error ("feval: first argument must be a string, inline function or a function handle");
    }

  return retval;
}

DEFUN (feval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} feval (@var{name}, @dots{})\n\
Evaluate the function named @var{name}.  Any arguments after the first\n\
are passed on to the named function.  For example,\n\
\n\
@example\n\
@group\n\
feval (\"acos\", -1)\n\
     @result{} 3.1416\n\
@end group\n\
@end example\n\
\n\
@noindent\n\
calls the function @code{acos} with the argument @samp{-1}.\n\
\n\
The function @code{feval} can also be used with function handles of\n\
any sort (@pxref{Function Handles}).  Historically, @code{feval} was\n\
the only way to call user-supplied functions in strings, but\n\
function handles are now preferred due to the cleaner syntax they\n\
offer.  For example,\n\
\n\
@example\n\
@group\n\
@var{f} = @@exp;\n\
feval (@var{f}, 1)\n\
    @result{} 2.7183\n\
@var{f} (1)\n\
    @result{} 2.7183\n\
@end group\n\
@end example\n\
\n\
@noindent\n\
are equivalent ways to call the function referred to by @var{f}.  If it\n\
cannot be predicted beforehand that @var{f} is a function handle or the\n\
function name in a string, @code{feval} can be used instead.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    retval = feval (args, nargout);
  else
    print_usage ();

  return retval;
}

DEFUN (builtin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@dots{}]} builtin (@var{f}, @dots{})\n\
Call the base function @var{f} even if @var{f} is overloaded to\n\
another function for the given type signature.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      const std::string name (args(0).string_value ());

      if (! error_state)
        {
          octave_value fcn = symbol_table::builtin_find (name);

          if (fcn.is_defined ())
            retval = feval (fcn.function_value (), args.splice (0, 1),
                            nargout);
          else
            error ("builtin: lookup for symbol '%s' failed", name.c_str ());
        }
      else
        error ("builtin: function name (F) must be a string");
    }
  else
    print_usage ();

  return retval;
}

octave_value_list
eval_string (const std::string& eval_str, bool silent,
             int& parse_status, int nargout)
{
  octave_value_list retval;

  unwind_protect frame;

  // octave_base_parser constructor sets this for us.
  frame.protect_var (LEXER);

  octave_parser parser (eval_str);

  do
    {
      parser.reset ();

      parse_status = parser.run ();

      // Unmark forced variables.
      frame.run (1);

      if (parse_status == 0)
        {
          if (parser.stmt_list)
            {
              tree_statement *stmt = 0;

              if (parser.stmt_list->length () == 1
                  && (stmt = parser.stmt_list->front ())
                  && stmt->is_expression ())
                {
                  tree_expression *expr = stmt->expression ();

                  if (silent)
                    expr->set_print_flag (false);

                  bool do_bind_ans = false;

                  if (expr->is_identifier ())
                    {
                      tree_identifier *id
                        = dynamic_cast<tree_identifier *> (expr);

                      do_bind_ans = (! id->is_variable ());
                    }
                  else
                    do_bind_ans = (! expr->is_assignment_expression ());

                  retval = expr->rvalue (nargout);

                  if (do_bind_ans && ! (error_state || retval.empty ()))
                    bind_ans (retval(0), expr->print_result ());

                  if (nargout == 0)
                    retval = octave_value_list ();
                }
              else if (nargout == 0)
                parser.stmt_list->accept (*current_evaluator);
              else
                error ("eval: invalid use of statement list");

              if (error_state
                  || tree_return_command::returning
                  || tree_break_command::breaking
                  || tree_continue_command::continuing)
                break;
            }
          else if (parser.lexer.end_of_input)
            break;
        }
    }
  while (parse_status == 0);

  return retval;
}

octave_value
eval_string (const std::string& eval_str, bool silent, int& parse_status)
{
  octave_value retval;

  octave_value_list tmp = eval_string (eval_str, silent, parse_status, 1);

  if (! tmp.empty ())
    retval = tmp(0);

  return retval;
}

static octave_value_list
eval_string (const octave_value& arg, bool silent, int& parse_status,
             int nargout)
{
  std::string s = arg.string_value ();

  if (error_state)
    {
      error ("eval: expecting std::string argument");
      return octave_value (-1);
    }

  return eval_string (s, silent, parse_status, nargout);
}

void
cleanup_statement_list (tree_statement_list **lst)
{
  if (*lst)
    {
      delete *lst;
      *lst = 0;
    }
}

DEFUN (eval, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} eval (@var{try})\n\
@deftypefnx {Built-in Function} {} eval (@var{try}, @var{catch})\n\
Parse the string @var{try} and evaluate it as if it were an Octave\n\
program.  If that fails, evaluate the optional string @var{catch}.\n\
The string @var{try} is evaluated in the current context,\n\
so any results remain available after @code{eval} returns.\n\
\n\
The following example makes the variable @var{a} with the approximate\n\
value 3.1416 available.\n\
\n\
@example\n\
eval (\"a = acos(-1);\");\n\
@end example\n\
\n\
If an error occurs during the evaluation of @var{try} the @var{catch}\n\
string is evaluated, as the following example shows:\n\
\n\
@example\n\
@group\n\
eval ('error (\"This is a bad example\");',\n\
      'printf (\"This error occurred:\\n%s\\n\", lasterr ());');\n\
     @print{} This error occurred:\n\
        This is a bad example\n\
@end group\n\
@end example\n\
\n\
Consider using try/catch blocks instead if you are only using @code{eval}\n\
as an error-capturing mechanism rather than for the execution of arbitrary\n\
code strings.\n\
@seealso{evalin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 0)
    {
      unwind_protect frame;

      if (nargin > 1)
        {
          frame.protect_var (buffer_error_messages);
          buffer_error_messages++;
        }

      int parse_status = 0;

      octave_value_list tmp = eval_string (args(0), nargout > 0,
                                           parse_status, nargout);

      if (nargin > 1 && (parse_status != 0 || error_state))
        {
          error_state = 0;

          // Set up for letting the user print any messages from
          // errors that occurred in the first part of this eval().

          buffer_error_messages--;

          tmp = eval_string (args(1), nargout > 0, parse_status, nargout);

          if (nargout > 0)
            retval = tmp;
        }
      else if (nargout > 0)
        retval = tmp;
    }
  else
    print_usage ();

  return retval;
}

/*

%!shared x
%! x = 1;

%!assert (eval ("x"), 1)
%!assert (eval ("x;"))
%!assert (eval ("x;"), 1);

%!test
%! y = eval ("x");
%! assert (y, 1);

%!test
%! y = eval ("x;");
%! assert (y, 1);

%!test
%! eval ("x = 1;")
%! assert (x,1);

%!test
%! eval ("flipud = 2;");
%! assert (flipud, 2);

%!function y = __f ()
%!  eval ("flipud = 2;");
%!  y = flipud;
%!endfunction
%!assert (__f(), 2)

% bug #35645
%!test
%! [a,] = gcd (1,2);
%! [a,b,] = gcd (1, 2);

*/

DEFUN (assignin, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} assignin (@var{context}, @var{varname}, @var{value})\n\
Assign @var{value} to @var{varname} in context @var{context}, which\n\
may be either @code{\"base\"} or @code{\"caller\"}.\n\
@seealso{evalin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin == 3)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
          unwind_protect frame;

          if (context == "caller")
            octave_call_stack::goto_caller_frame ();
          else if (context == "base")
            octave_call_stack::goto_base_frame ();
          else
            error ("assignin: CONTEXT must be \"caller\" or \"base\"");

          if (! error_state)
            {
              frame.add_fcn (octave_call_stack::pop);

              std::string nm = args(1).string_value ();

              if (! error_state)
                {
                  if (valid_identifier (nm))
                    symbol_table::assign (nm, args(2));
                  else
                    error ("assignin: invalid variable name in argument VARNAME");
                }
              else
                error ("assignin: VARNAME must be a string");
            }
        }
      else
        error ("assignin: CONTEXT must be a string");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (evalin, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn  {Built-in Function} {} evalin (@var{context}, @var{try})\n\
@deftypefnx {Built-in Function} {} evalin (@var{context}, @var{try}, @var{catch})\n\
Like @code{eval}, except that the expressions are evaluated in the\n\
context @var{context}, which may be either @code{\"caller\"} or\n\
@code{\"base\"}.\n\
@seealso{eval, assignin}\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin > 1)
    {
      std::string context = args(0).string_value ();

      if (! error_state)
        {
          unwind_protect frame;

          if (context == "caller")
            octave_call_stack::goto_caller_frame ();
          else if (context == "base")
            octave_call_stack::goto_base_frame ();
          else
            error ("evalin: CONTEXT must be \"caller\" or \"base\"");

          if (! error_state)
            {
              frame.add_fcn (octave_call_stack::pop);

              if (nargin > 2)
                {
                  frame.protect_var (buffer_error_messages);
                  buffer_error_messages++;
                }

              int parse_status = 0;

              octave_value_list tmp = eval_string (args(1), nargout > 0,
                                                   parse_status, nargout);

              if (nargout > 0)
                retval = tmp;

              if (nargin > 2 && (parse_status != 0 || error_state))
                {
                  error_state = 0;

                  // Set up for letting the user print any messages from
                  // errors that occurred in the first part of this eval().

                  buffer_error_messages--;

                  tmp = eval_string (args(2), nargout > 0,
                                     parse_status, nargout);

                  retval = (nargout > 0) ? tmp : octave_value_list ();
                }
            }
        }
      else
        error ("evalin: CONTEXT must be a string");
    }
  else
    print_usage ();

  return retval;
}

DEFUN (__parser_debug_flag__, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{old_val} =} __parser_debug_flag__ (@var{new_val}))\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  bool debug_flag = octave_debug;

  retval = set_internal_variable (debug_flag, args, nargout,
                                  "__parser_debug_flag__");

  octave_debug = debug_flag;

  return retval;
}

