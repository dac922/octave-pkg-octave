/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 1

/* Pull parsers.  */
#define YYPULL 1


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
/* Line 371 of yacc.c  */
#line 29 "parse-tree/oct-parse.yy"

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


/* Line 371 of yacc.c  */
#line 186 "parse-tree/oct-parse.cc"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED
# define YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int octave_debug;
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
/* Line 387 of yacc.c  */
#line 157 "parse-tree/oct-parse.yy"

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


/* Line 387 of yacc.c  */
#line 433 "parse-tree/oct-parse.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


#ifndef YYPUSH_MORE_DEFINED
# define YYPUSH_MORE_DEFINED
enum { YYPUSH_MORE = 4 };
#endif

typedef struct octave_pstate octave_pstate;

#if defined __STDC__ || defined __cplusplus
int octave_parse (octave_base_parser& parser);
#else
int octave_parse ();
#endif
#if defined __STDC__ || defined __cplusplus
int octave_push_parse (octave_pstate *ps, int pushed_char, YYSTYPE const *pushed_val, octave_base_parser& parser);
#else
int octave_push_parse ();
#endif
#if defined __STDC__ || defined __cplusplus
int octave_pull_parse (octave_pstate *ps, octave_base_parser& parser);
#else
int octave_pull_parse ();
#endif
#if defined __STDC__ || defined __cplusplus
octave_pstate * octave_pstate_new (void);
#else
octave_pstate * octave_pstate_new ();
#endif
#if defined __STDC__ || defined __cplusplus
void octave_pstate_delete (octave_pstate *ps);
#else
void octave_pstate_delete ();
#endif

#endif /* !YY_OCTAVE_PARSE_TREE_OCT_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 479 "parse-tree/oct-parse.cc"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  115
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1223

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  261
/* YYNRULES -- Number of states.  */
#define YYNSTATES  488

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
      90,   100,     7,     6,    98,     5,    91,     8,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     4,    96,
       2,     3,     2,     2,    99,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    95,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,    97,     2,     2,     2,     2,
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
       0,     0,     3,     6,     9,    11,    13,    16,    18,    22,
      23,    25,    28,    30,    34,    36,    38,    40,    43,    45,
      48,    50,    52,    54,    56,    58,    60,    62,    64,    68,
      70,    74,    78,    80,    84,    85,    87,    89,    92,    95,
      99,   102,   107,   109,   111,   113,   115,   117,   119,   121,
     125,   127,   129,   131,   133,   135,   139,   143,   147,   149,
     151,   154,   157,   161,   166,   170,   175,   178,   181,   185,
     191,   194,   197,   200,   203,   206,   210,   214,   218,   222,
     226,   230,   234,   238,   242,   246,   250,   254,   256,   258,
     262,   264,   268,   272,   276,   280,   284,   288,   292,   296,
     300,   304,   308,   312,   314,   318,   322,   326,   330,   334,
     338,   342,   346,   350,   354,   358,   362,   366,   370,   374,
     376,   378,   380,   382,   384,   386,   388,   390,   392,   394,
     396,   399,   402,   404,   407,   408,   410,   415,   417,   419,
     424,   426,   429,   434,   437,   445,   450,   457,   458,   460,
     462,   465,   467,   470,   478,   483,   491,   498,   508,   519,
     529,   542,   544,   546,   548,   558,   568,   574,   575,   577,
     579,   583,   586,   587,   589,   591,   595,   597,   599,   602,
     604,   608,   610,   614,   619,   622,   626,   632,   634,   638,
     642,   645,   650,   654,   656,   658,   661,   663,   668,   675,
     676,   680,   682,   686,   688,   693,   696,   697,   699,   704,
     707,   713,   717,   719,   721,   723,   725,   729,   733,   737,
     741,   744,   751,   753,   757,   759,   765,   768,   775,   777,
     781,   784,   791,   793,   797,   799,   802,   809,   811,   815,
     820,   821,   822,   824,   826,   828,   830,   833,   836,   837,
     839,   840,   842,   844,   847,   849,   851,   853,   856,   859,
     862,   863
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     102,     0,    -1,   103,    93,    -1,   103,    85,    -1,   197,
      -1,   199,    -1,   104,   199,    -1,   108,    -1,   104,   198,
     108,    -1,    -1,   106,    -1,   107,   203,    -1,   108,    -1,
     107,   202,   108,    -1,   134,    -1,   135,    -1,   109,    -1,
     111,   110,    -1,   114,    -1,   110,   114,    -1,    51,    -1,
      81,    -1,    80,    -1,    53,    -1,    54,    -1,    48,    -1,
      49,    -1,   114,    -1,    94,   117,    95,    -1,   120,    -1,
     117,    96,   120,    -1,    92,   119,    97,    -1,   120,    -1,
     119,    96,   120,    -1,    -1,    98,    -1,   126,    -1,   126,
      98,    -1,    98,   126,    -1,    98,   126,    98,    -1,    99,
      75,    -1,    99,   157,   195,   108,    -1,   111,    -1,   115,
      -1,   121,    -1,   116,    -1,   118,    -1,   113,    -1,   112,
      -1,    90,   134,   100,    -1,     4,    -1,    29,    -1,   134,
      -1,   124,    -1,   125,    -1,   126,    98,   124,    -1,   126,
      98,   125,    -1,   126,    98,   134,    -1,    91,    -1,   123,
      -1,   128,    44,    -1,   128,    45,    -1,   128,    90,   100,
      -1,   128,    90,   126,   100,    -1,   128,    92,    97,    -1,
     128,    92,   126,    97,    -1,   128,    42,    -1,   128,    43,
      -1,   128,   127,    50,    -1,   128,   127,    90,   134,   100,
      -1,    44,   128,    -1,    45,   128,    -1,    29,   128,    -1,
       6,   128,    -1,     5,   128,    -1,   128,    46,   128,    -1,
     128,    47,   128,    -1,   128,     6,   128,    -1,   128,     5,
     128,    -1,   128,     7,   128,    -1,   128,     8,   128,    -1,
     128,    40,   128,    -1,   128,    41,   128,    -1,   128,    37,
     128,    -1,   128,    38,   128,    -1,   128,    36,   128,    -1,
     128,    39,   128,    -1,   130,    -1,   128,    -1,   130,     4,
     128,    -1,   129,    -1,   131,    23,   131,    -1,   131,    24,
     131,    -1,   131,    30,   131,    -1,   131,    31,   131,    -1,
     131,    32,   131,    -1,   131,    34,   131,    -1,   131,    35,
     131,    -1,   131,    33,   131,    -1,   131,    27,   131,    -1,
     131,    28,   131,    -1,   131,    25,   131,    -1,   131,    26,
     131,    -1,   131,    -1,   132,     3,   134,    -1,   132,     9,
     134,    -1,   132,    10,   134,    -1,   132,    11,   134,    -1,
     132,    12,   134,    -1,   132,    13,   134,    -1,   132,    14,
     134,    -1,   132,    21,   134,    -1,   132,    22,   134,    -1,
     132,    15,   134,    -1,   132,    16,   134,    -1,   132,    17,
     134,    -1,   132,    18,   134,    -1,   132,    19,   134,    -1,
     132,    20,   134,    -1,   131,    -1,   133,    -1,   122,    -1,
     136,    -1,   140,    -1,   151,    -1,   152,    -1,   153,    -1,
     165,    -1,   163,    -1,   173,    -1,    73,   137,    -1,    74,
     137,    -1,   139,    -1,   137,   139,    -1,    -1,   111,    -1,
     111,     3,   138,   134,    -1,   141,    -1,   146,    -1,    60,
     196,   142,    52,    -1,   143,    -1,   143,   145,    -1,   134,
     195,   203,   105,    -1,   143,   144,    -1,    61,   196,   203,
     134,   195,   203,   105,    -1,    62,   196,   203,   105,    -1,
      63,   196,   134,   203,   147,    52,    -1,    -1,   150,    -1,
     148,    -1,   148,   150,    -1,   149,    -1,   148,   149,    -1,
      64,   196,   203,   134,   195,   203,   105,    -1,    65,   196,
     203,   105,    -1,    57,   196,   134,   195,   203,   105,    52,
      -1,    58,   196,   203,   105,    59,   134,    -1,    55,   196,
     132,     3,   134,   195,   203,   105,    52,    -1,    55,   196,
      90,   132,     3,   134,   100,   203,   105,    52,    -1,    56,
     196,   132,     3,   134,   195,   203,   105,    52,    -1,    56,
     196,    90,   132,     3,   134,    98,   134,   100,   203,   105,
      52,    -1,    66,    -1,    67,    -1,    68,    -1,    69,   196,
     203,   105,    70,   196,   203,   105,    52,    -1,    71,   196,
     203,   105,    72,   196,   203,   105,    52,    -1,    71,   196,
     203,   105,    52,    -1,    -1,    90,    -1,   100,    -1,   155,
     158,   156,    -1,   155,     1,    -1,    -1,   159,    -1,   160,
      -1,   159,    98,   160,    -1,   139,    -1,   125,    -1,    94,
      95,    -1,   111,    -1,    94,   162,    95,    -1,   111,    -1,
     162,    98,   111,    -1,    87,   200,   105,    85,    -1,   154,
      84,    -1,   164,   196,   167,    -1,   164,   196,   161,     3,
     167,    -1,   111,    -1,    82,    91,   111,    -1,    83,    91,
     111,    -1,   166,   168,    -1,   157,   203,   105,   169,    -1,
     203,   105,   169,    -1,    52,    -1,    85,    -1,    88,   196,
      -1,    52,    -1,   170,   174,   111,   177,    -1,   172,   203,
     179,   203,   196,   171,    -1,    -1,    90,   175,   100,    -1,
     176,    -1,   175,    98,   176,    -1,   111,    -1,   111,     3,
     138,   134,    -1,    29,   111,    -1,    -1,   178,    -1,    30,
     111,    91,   111,    -1,    30,   111,    -1,   178,    27,   111,
      91,   111,    -1,   178,    27,   111,    -1,   181,    -1,   185,
      -1,   188,    -1,   192,    -1,   179,   203,   181,    -1,   179,
     203,   185,    -1,   179,   203,   188,    -1,   179,   203,   192,
      -1,    76,   196,    -1,   180,   174,   203,   182,   203,    52,
      -1,   183,    -1,   182,   203,   183,    -1,   111,    -1,   111,
       3,   138,   134,    96,    -1,    77,   196,    -1,   184,   174,
     203,   186,   203,    52,    -1,   165,    -1,   186,   203,   165,
      -1,    78,   196,    -1,   187,   174,   203,   189,   203,    52,
      -1,   190,    -1,   189,   203,   190,    -1,   111,    -1,    79,
     196,    -1,   191,   174,   203,   193,   203,    52,    -1,   194,
      -1,   193,   203,   194,    -1,   111,    90,   134,   100,    -1,
      -1,    -1,    86,    -1,     1,    -1,    98,    -1,    96,    -1,
     198,    98,    -1,   198,    96,    -1,    -1,   198,    -1,    -1,
     201,    -1,    93,    -1,   201,    93,    -1,    98,    -1,    96,
      -1,    93,    -1,   202,    98,    -1,   202,    96,    -1,   202,
      93,    -1,    -1,   202,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   310,   310,   315,   321,   325,   327,   331,   333,   338,
     339,   343,   347,   349,   353,   355,   357,   369,   377,   379,
     390,   398,   402,   406,   408,   412,   414,   416,   420,   424,
     426,   440,   444,   446,   465,   466,   468,   470,   472,   474,
     478,   485,   492,   494,   496,   498,   503,   505,   507,   509,
     513,   520,   526,   528,   530,   532,   537,   542,   549,   553,
     555,   557,   559,   565,   571,   577,   583,   585,   587,   589,
     591,   593,   595,   597,   599,   601,   603,   605,   607,   609,
     611,   613,   615,   617,   619,   621,   623,   627,   631,   633,
     640,   642,   644,   646,   648,   650,   652,   654,   656,   658,
     660,   662,   664,   668,   682,   684,   686,   688,   690,   692,
     694,   696,   698,   700,   702,   704,   706,   708,   710,   714,
     729,   731,   739,   741,   743,   745,   747,   749,   751,   753,
     761,   766,   773,   775,   783,   785,   787,   798,   800,   808,
     815,   817,   824,   830,   837,   845,   853,   861,   862,   864,
     866,   873,   875,   882,   886,   896,   903,   908,   914,   920,
     926,   938,   943,   948,   959,   965,   971,   983,  1010,  1023,
    1030,  1037,  1046,  1047,  1060,  1062,  1069,  1071,  1079,  1085,
    1100,  1114,  1116,  1127,  1147,  1156,  1162,  1170,  1179,  1185,
    1193,  1204,  1206,  1210,  1219,  1259,  1266,  1278,  1282,  1287,
    1288,  1292,  1294,  1298,  1300,  1302,  1308,  1309,  1313,  1315,
    1317,  1319,  1323,  1325,  1327,  1329,  1331,  1333,  1335,  1337,
    1341,  1346,  1351,  1353,  1357,  1359,  1363,  1367,  1371,  1373,
    1377,  1381,  1385,  1387,  1391,  1395,  1399,  1403,  1405,  1409,
    1418,  1422,  1425,  1427,  1430,  1432,  1434,  1436,  1441,  1442,
    1447,  1448,  1452,  1454,  1458,  1460,  1462,  1464,  1466,  1468,
    1473,  1474
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "'('", "'.'", "'{'", "'\\n'", "'['", "']'", "';'", "'}'", "','", "'@'",
  "')'", "$accept", "input", "simple_list", "simple_list1", "opt_list",
  "list", "list1", "statement", "word_list_cmd", "word_list", "identifier",
  "superclass_identifier", "meta_identifier", "string", "constant",
  "matrix", "matrix_rows", "cell", "cell_rows", "cell_or_matrix_row",
  "fcn_handle", "anon_fcn_handle", "primary_expr", "magic_colon",
  "magic_tilde", "arg_list", "indirect_ref_op", "oper_expr", "colon_expr",
  "colon_expr1", "simple_expr", "assign_lhs", "assign_expr", "expression",
  "command", "declaration", "decl1", "decl_param_init", "decl2",
  "select_command", "if_command", "if_cmd_list", "if_cmd_list1",
  "elseif_clause", "else_clause", "switch_command", "case_list",
  "case_list1", "switch_case", "default_case", "loop_command",
  "jump_command", "except_command", "push_fcn_symtab", "param_list_beg",
  "param_list_end", "param_list", "param_list1", "param_list2",
  "param_list_elt", "return_list", "return_list1", "file", "function_beg",
  "function", "fcn_name", "function1", "function2", "function_end",
  "classdef_beg", "classdef_end", "classdef1", "classdef", "opt_attr_list",
  "attr_list", "attr", "opt_superclasses", "superclasses", "class_body",
  "properties_beg", "properties_block", "properties_list",
  "class_property", "methods_beg", "methods_block", "methods_list",
  "events_beg", "events_block", "events_list", "class_event", "enum_beg",
  "enum_block", "enum_list", "class_enum", "stmt_begin", "stash_comment",
  "parse_error", "sep_no_nl", "opt_sep_no_nl", "opt_nl", "nl", "sep",
  "opt_sep", YY_NULL
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
      40,    46,   123,    10,    91,    93,    59,   125,    44,    64,
      41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   107,   108,   108,   108,   109,   110,   110,
     111,   112,   113,   114,   114,   115,   115,   115,   116,   117,
     117,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     121,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   125,   126,   126,   126,   126,   126,   126,   127,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   129,   130,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   132,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   135,   135,   135,   135,   135,   135,   135,   135,
     136,   136,   137,   137,   138,   139,   139,   140,   140,   141,
     142,   142,   143,   143,   144,   145,   146,   147,   147,   147,
     147,   148,   148,   149,   150,   151,   151,   151,   151,   151,
     151,   152,   152,   152,   153,   153,   153,   154,   155,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   161,   161,
     161,   162,   162,   163,   164,   165,   165,   166,   166,   166,
     167,   168,   168,   169,   169,   170,   171,   172,   173,   174,
     174,   175,   175,   176,   176,   176,   177,   177,   178,   178,
     178,   178,   179,   179,   179,   179,   179,   179,   179,   179,
     180,   181,   182,   182,   183,   183,   184,   185,   186,   186,
     187,   188,   189,   189,   190,   191,   192,   193,   193,   194,
     195,   196,   197,   197,   198,   198,   198,   198,   199,   199,
     200,   200,   201,   201,   202,   202,   202,   202,   202,   202,
     203,   203
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     2,     1,     3,     0,
       1,     2,     1,     3,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     1,     3,     0,     1,     1,     2,     2,     3,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       2,     2,     3,     4,     3,     4,     2,     2,     3,     5,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     0,     1,     4,     1,     1,     4,
       1,     2,     4,     2,     7,     4,     6,     0,     1,     1,
       2,     1,     2,     7,     4,     7,     6,     9,    10,     9,
      12,     1,     1,     1,     9,     9,     5,     0,     1,     1,
       3,     2,     0,     1,     1,     3,     1,     1,     2,     1,
       3,     1,     3,     4,     2,     3,     5,     1,     3,     3,
       2,     4,     3,     1,     1,     2,     1,     4,     6,     0,
       3,     1,     3,     1,     4,     2,     0,     1,     4,     2,
       5,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       2,     6,     1,     3,     1,     5,     2,     6,     1,     3,
       2,     6,     1,     3,     1,     2,     6,     1,     3,     4,
       0,     0,     1,     1,     1,     1,     2,     2,     0,     1,
       0,     1,     1,     2,     1,     1,     1,     2,     2,     2,
       0,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   243,     0,     0,     0,     0,     0,    25,    26,    20,
      23,    24,   241,   241,   241,   241,   241,   241,   161,   162,
     163,   241,   241,     0,     0,    22,    21,   242,   250,   241,
       0,    34,    34,   245,   244,     0,     0,     0,   248,     7,
      16,    42,    48,    47,    27,    43,    45,    46,    44,   121,
      59,    88,    90,    87,   119,     0,   120,    14,    15,   122,
     123,   137,   138,   124,   125,   126,     0,   128,   241,   127,
     199,   260,   129,     4,   249,     5,     0,    42,    74,    73,
      72,    70,    71,     0,     0,     0,   260,     0,     0,   260,
     260,   135,   130,   132,   131,   252,     9,   251,   195,     0,
      50,    51,    35,     0,    32,    53,    54,    36,    52,     0,
      29,    40,   168,     0,   240,     1,     3,     2,   249,     6,
      17,    18,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,    67,    60,    61,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,     0,     0,     0,   256,   255,   254,   261,     0,   247,
     246,     0,   103,     0,     0,     0,   240,     9,   240,     0,
     140,   260,     9,     9,   134,   133,     0,    10,   260,    12,
     253,    49,    38,    34,    31,    37,    28,    34,   171,    51,
     177,   176,     0,   173,   174,   167,     8,    19,    78,    77,
      79,    80,    85,    83,    84,    86,    81,    82,    75,    76,
      62,     0,    64,     0,    68,     0,    89,    91,    92,   101,
     102,    99,   100,    93,    94,    95,    98,    96,    97,   104,
     105,   106,   107,   108,   109,   110,   113,   114,   115,   116,
     117,   118,   111,   112,     0,     0,     0,   187,     0,   260,
     185,     0,   203,     0,   201,   206,   259,   258,   257,   241,
     241,   241,   241,   260,   199,   212,   199,   213,   199,   214,
     199,   215,     0,     0,     0,     0,   260,     0,   260,   139,
     241,   241,   143,   141,   147,     0,     0,     0,   183,   261,
      11,    39,    33,    55,    56,    57,    30,   169,   170,     0,
      41,     0,    63,    65,     0,     0,     0,   178,   181,     0,
       0,   260,   190,     9,   205,   134,     0,   200,     0,   197,
     207,   220,   226,   230,   235,   241,   260,   260,   260,   260,
       0,   240,     0,   240,     9,     0,     9,   260,   260,   241,
     241,     0,   149,   151,   148,   241,   166,   241,   136,    13,
     175,    69,   188,   189,   180,     0,   187,   186,     9,     0,
       0,   202,   209,     0,   216,   217,   218,   219,     0,     0,
     167,     0,     0,     0,   260,   104,   260,     0,   156,   142,
       0,     9,   260,   260,   146,   152,   150,   260,   260,   182,
       0,   193,   194,   192,   204,     0,   211,   196,   198,   224,
     260,   222,   228,   260,   234,   260,   232,     0,   260,   237,
     260,     9,     0,     9,   155,   240,   145,     0,     9,     9,
       9,   191,   208,     0,   134,     0,   167,     0,     0,     0,
       9,     0,     0,     0,   260,   240,   154,     0,     0,   210,
       0,   221,   223,   227,   229,   231,   233,     0,   236,   238,
       0,   157,   260,   159,     9,   260,   164,   165,     0,   239,
     158,     9,   144,     9,   225,     0,   153,   160
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    36,    37,    38,   196,   197,   198,   199,    40,   120,
      77,    42,    43,    44,    45,    46,   109,    47,   103,   104,
      48,    49,    50,   105,   106,   107,   141,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    92,   307,    93,    60,
      61,   189,   190,   302,   303,    62,   361,   362,   363,   364,
      63,    64,    65,    66,   113,   318,   114,   212,   213,   214,
     268,   329,    67,    68,    69,   269,   270,   332,   413,    70,
     418,    71,    72,   173,   273,   274,   339,   340,   283,   284,
     285,   420,   421,   286,   287,   423,   288,   289,   425,   426,
     290,   291,   428,   429,   215,    83,    73,    74,    75,    96,
      97,   177,   178
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -376
static const yytype_int16 yypact[] =
{
     496,  -376,   915,   915,   915,   915,   915,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,   -26,   -26,  -376,  -376,  -376,   -57,  -376,
     932,   567,   567,  -376,  -376,   -47,    29,    16,    27,  -376,
    -376,    28,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  1030,  -376,    41,  1114,  1147,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,    18,  -376,  -376,  -376,
       5,    54,  -376,  -376,    46,  -376,   -19,  -376,     7,     7,
       7,     7,     7,   949,  1005,   932,    54,   932,   932,    54,
      54,   113,   -26,  -376,   -26,  -376,   803,    33,  -376,    43,
    -376,   915,   635,    58,  -376,  -376,  -376,    48,  -376,    26,
    -376,  -376,  -376,    11,  -376,  -376,  -376,  -376,   747,  -376,
      28,  -376,   915,   915,   915,   915,   915,   915,   915,   915,
     915,   915,  -376,  -376,  -376,  -376,   915,   915,   155,  -376,
     601,   -32,   915,   915,   915,   915,   915,   915,   915,   915,
     915,   915,   915,   915,   915,   932,   932,   932,   932,   932,
     932,   932,   932,   932,   932,   932,   932,   932,   932,   932,
    -376,   -10,    13,   -26,  -376,  -376,  -376,    90,    -1,  -376,
    -376,   932,  1188,   148,   932,   167,  -376,   803,  -376,   130,
     101,    54,   803,   803,  -376,  -376,   105,  -376,    54,  -376,
    -376,  -376,   100,   567,  -376,   635,  -376,   567,  -376,  -376,
    -376,  -376,   110,   107,  -376,   859,  -376,  -376,   269,   269,
       7,     7,     7,     7,     7,     7,   269,   269,   -23,   -23,
    -376,    80,  -376,    97,  -376,   932,  1030,  -376,  -376,   316,
     257,   134,    56,   173,   173,   173,   173,   173,   173,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,   129,   132,   -34,   222,   224,    10,
    -376,   -26,   228,    91,  -376,   207,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,    54,     5,  -376,     5,  -376,     5,  -376,
       5,  -376,  1167,   932,  1187,   932,    54,   179,    54,  -376,
    -376,  -376,  -376,  -376,   137,   169,   -17,   932,  -376,   691,
    -376,   635,  -376,  -376,  -376,  -376,  -376,  -376,  -376,    15,
    -376,   635,  -376,  -376,   140,   -26,   -26,  -376,  -376,     9,
     -35,    54,  -376,   803,  -376,  -376,    13,  -376,   -26,  -376,
     214,  -376,  -376,  -376,  -376,    -1,    54,    54,    54,    54,
     932,  -376,   932,  -376,   803,   932,   803,    54,    54,  -376,
    -376,   190,   137,  -376,  -376,  -376,  -376,  -376,  -376,  -376,
    -376,  -376,  -376,  -376,  -376,   -26,  -376,  -376,   803,   -15,
     932,  -376,   152,   -26,  -376,  -376,  -376,  -376,   192,   -26,
    -376,   -26,   -26,   146,    54,   150,    54,   199,  -376,  -376,
     932,   803,    54,    54,  -376,  -376,  -376,    54,    54,  -376,
     -15,  -376,  -376,  -376,  -376,   -26,   161,  -376,  -376,   250,
      54,  -376,  -376,    54,  -376,    54,  -376,   166,    54,  -376,
      54,   803,   932,   803,  -376,  -376,  -376,   932,   803,   803,
     803,  -376,  -376,   -26,  -376,   162,   208,   178,   932,   182,
     803,   209,   159,   210,    54,  -376,  -376,   211,   212,  -376,
     932,  -376,  -376,  -376,  -376,  -376,  -376,   168,  -376,  -376,
     217,  -376,    54,  -376,   803,    54,  -376,  -376,   174,  -376,
    -376,   803,  -376,   803,  -376,   220,  -376,  -376
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -376,  -376,  -376,  -376,    25,  -376,  -376,     1,  -376,  -376,
       0,  -376,  -376,   -27,  -376,  -376,  -376,  -376,  -376,   -22,
    -376,  -376,  -376,  -197,  -100,   -75,  -376,   393,  -376,  -376,
     559,   -64,  -376,   -28,  -376,  -376,   249,  -329,   -87,  -376,
    -376,  -376,  -376,  -376,  -376,  -376,  -376,  -376,   -88,   -76,
    -376,  -376,  -376,  -376,  -376,  -376,     6,  -376,  -376,   -25,
    -376,  -376,  -376,  -376,  -375,  -376,   -30,  -376,  -115,  -376,
    -376,  -376,  -376,   -62,  -376,   -33,  -376,  -376,  -376,  -376,
     -44,  -376,  -143,  -376,   -41,  -376,  -376,   -24,  -376,  -127,
    -376,   -16,  -376,  -126,  -177,    17,  -376,   293,   294,  -376,
    -376,   136,    59
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -249
static const yytype_int16 yytable[] =
{
      41,    39,    99,   108,   108,   195,   380,   195,   313,   296,
     110,   298,   208,   210,   121,   422,     9,     9,   234,   183,
     185,   134,   135,    91,    91,     9,   211,   202,   111,   115,
      84,    85,    86,    87,    88,   366,    95,   411,    89,    90,
     209,     9,   271,   112,   209,   142,    98,   264,   265,   132,
     133,   134,   135,   136,   137,   367,   111,   186,   235,   188,
     191,   327,     9,   231,     9,   233,     9,   138,   139,   140,
     412,   464,   264,   265,   108,   279,   280,   281,   282,   143,
     144,    10,    11,   147,   266,   171,   149,   150,   151,   152,
     153,   154,    91,   217,    91,   172,    41,   138,   139,   140,
     112,   116,   170,   174,   374,   314,   175,   375,   176,   117,
     108,  -172,   108,    91,   313,   460,   194,   292,    41,   216,
     294,   206,   207,    33,   313,    34,   200,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   179,   201,   180,   187,   205,   174,   192,   193,
     175,   293,   176,    99,   203,   204,    99,   143,   144,   100,
       2,     3,   300,   301,   149,   150,   151,   152,   153,   154,
     295,   267,   272,   275,   394,   108,   396,   315,   321,   108,
     322,   312,   299,   276,   101,   316,   277,    41,   278,   336,
     308,   337,    41,    41,   323,   321,   143,   144,   311,     5,
       6,   359,   360,     7,     8,   319,     9,   324,    10,    11,
     317,   314,   297,     9,   461,    41,   320,   305,   306,   210,
     325,   314,   346,   326,   347,  -179,   348,   330,   349,     9,
     465,   335,   211,     9,   468,    25,    26,   338,   355,   365,
     371,   383,   404,   415,   417,    30,   430,    31,   432,    32,
     304,   434,   443,   444,    35,   230,   448,   310,   454,   472,
     463,   471,   473,   476,   477,   351,   328,   353,   479,   480,
     484,   334,   487,    94,   405,   331,   124,   125,   475,   368,
     143,   144,   145,   315,   147,   148,   406,   149,   150,   151,
     152,   153,   154,   315,   370,   441,   341,   342,   343,   344,
     377,   384,   462,   381,   385,   126,   127,   128,   129,    41,
     369,   132,   133,   134,   135,   136,   137,   357,   358,    91,
     466,   386,   393,   469,   395,   372,   373,   398,   333,   387,
     376,   118,   119,    41,   309,     0,   272,     0,   382,   143,
     144,     0,   345,   147,   148,     0,   149,   150,   151,   152,
     153,   154,   414,     0,    41,   354,    41,   356,   379,   138,
     139,   140,   388,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   435,     0,     0,   409,   402,   403,    41,   397,
       0,   399,   407,   416,   408,     0,     0,     0,     0,   419,
     378,   424,   427,     0,     0,    78,    79,    80,    81,    82,
       0,    41,     0,   410,   452,   389,   390,   391,   392,   455,
       0,     0,     0,     0,     0,   442,   400,   401,     0,     0,
     467,     0,     0,     0,     0,     0,   436,     0,     0,     0,
       0,    41,   478,    41,     0,     0,     0,     0,    41,    41,
      41,     0,     0,   459,     0,   419,     0,   424,     0,   427,
      41,     0,     0,   431,     0,   433,   451,     0,   453,     0,
       0,   437,   438,   456,   457,   458,   439,   440,     0,     0,
       0,     0,     0,     0,    41,   470,     0,     0,     0,   445,
       0,    41,   446,    41,   447,     0,     0,   449,     0,   450,
       0,     0,     0,     0,    80,     0,     0,     1,     0,   482,
       0,     2,     3,     0,     0,     0,   485,     0,   486,     0,
       0,     0,     0,   474,     0,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,     4,     0,     0,     0,   228,
     229,   481,     0,     0,   483,   236,     0,     0,     0,     0,
       5,     6,     0,     0,     7,     8,     0,     9,     0,    10,
      11,    12,    13,    14,    15,     0,    16,     0,     0,    17,
       0,     0,    18,    19,    20,    21,     0,    22,     0,    23,
      24,   100,     2,     3,     0,     0,    25,    26,     0,     0,
    -167,  -248,    27,    28,    29,     0,    30,     0,    31,  -248,
      32,     0,    33,     0,    34,    35,   101,     0,     0,     0,
       0,     0,     0,     0,     0,   100,     2,     3,     0,     0,
       0,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,   100,
       2,     3,   182,   182,     0,     5,     6,    25,    26,     7,
       8,     0,     9,     0,    10,    11,     0,    30,     0,    31,
       0,    32,     0,     0,   101,   102,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,    25,    26,     7,     8,     0,     9,     0,    10,    11,
       0,    30,     0,    31,     0,    32,     2,     3,   232,     0,
      35,     0,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,     0,    25,    26,     0,     0,     0,
       4,     0,     0,     0,     0,    30,     0,    31,     0,    32,
       0,     0,     0,     0,    35,     5,     6,     0,     0,     7,
       8,     0,     9,     0,    10,    11,    12,    13,    14,    15,
       0,    16,     2,     3,    17,     0,     0,    18,    19,    20,
      21,     0,    22,     0,    23,    24,     0,     0,     0,     0,
       0,    25,    26,     0,     0,  -167,     4,     0,    28,    29,
       0,    30,     0,    31,   276,    32,     0,   277,     0,   278,
      35,     5,     6,     0,     0,     7,     8,     0,     9,     0,
      10,    11,    12,    13,    14,    15,     0,    16,     2,     3,
      17,     0,     0,    18,    19,    20,    21,     0,    22,     0,
      23,    24,     0,     0,     0,     0,     0,    25,    26,     0,
       0,  -167,     4,     0,    28,    29,     0,    30,     0,    31,
       0,    32,     0,   179,     0,   180,    35,     5,     6,     0,
       0,     7,     8,     0,     9,     0,    10,    11,    12,    13,
      14,    15,     0,    16,     2,     3,    17,     0,     0,    18,
      19,    20,    21,     0,    22,     0,    23,    24,     0,     0,
       0,     0,     0,    25,    26,     0,     0,  -167,     4,     0,
      28,    29,     0,    30,     0,    31,     0,    32,     0,     0,
       0,     0,    35,     5,     6,     0,     0,     7,     8,     0,
       9,     0,    10,    11,    12,    13,    14,    15,     0,    16,
       2,     3,    17,     0,     0,    18,    19,    20,    21,     0,
      22,     0,    23,    24,     0,     0,     0,     2,     3,    25,
      26,     0,     0,     0,     4,     0,    28,    29,     0,    30,
       0,    31,     0,    32,     2,     3,     0,     0,    35,     5,
       6,     4,     0,     7,     8,     0,     9,     0,    10,    11,
       0,     0,     0,     0,     0,     0,     5,     6,     4,     0,
       7,     8,     0,     9,     0,    10,    11,     0,     0,     0,
       0,     0,     0,     5,     6,    25,    26,     7,     8,     0,
       9,     0,    10,    11,     0,    30,     0,    31,     0,    32,
       2,     3,    25,    26,    76,     0,     0,     0,     0,     0,
       0,     0,    30,     0,    31,     0,    32,     0,     0,    25,
      26,    35,     0,     0,     4,   122,   123,   124,   125,   181,
       0,    31,     0,    32,     0,     0,     0,     0,    76,     5,
       6,     0,     0,     7,     8,     0,     9,     0,    10,    11,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,     0,     0,
       0,     0,     0,     0,     0,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,   184,     0,    31,     0,    32,
       0,     0,     0,     0,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -103,     0,     0,
     138,   139,   140,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,   143,   144,   145,
     146,   147,   148,     0,   149,   150,   151,   152,   153,   154,
     155,     0,     0,     0,     0,     0,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     350,     0,     0,     0,     0,     0,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     352,     0,     0,     0,     0,     0,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
       0,   143,   144,   145,   146,   147,   148,     0,   149,   150,
     151,   152,   153,   154
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-376)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     0,    30,    31,    32,    92,   335,    94,   205,   186,
      32,   188,     1,   113,    41,   390,    51,    51,    50,    83,
      84,    44,    45,    23,    24,    51,   113,   102,    75,     0,
      13,    14,    15,    16,    17,    52,    93,    52,    21,    22,
      29,    51,    29,    90,    29,     4,    29,    82,    83,    42,
      43,    44,    45,    46,    47,    72,    75,    85,    90,    87,
      88,    95,    51,   138,    51,   140,    51,    90,    91,    92,
      85,   446,    82,    83,   102,    76,    77,    78,    79,    23,
      24,    53,    54,    27,    94,    68,    30,    31,    32,    33,
      34,    35,    92,   120,    94,    90,    96,    90,    91,    92,
      90,    85,    84,    93,    95,   205,    96,    98,    98,    93,
     138,   100,   140,   113,   311,   444,     3,   181,   118,   118,
     184,    95,    96,    96,   321,    98,    93,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,    96,   100,    98,    86,    98,    93,    89,    90,
      96,     3,    98,   181,    96,    97,   184,    23,    24,     4,
       5,     6,    61,    62,    30,    31,    32,    33,    34,    35,
       3,   171,   172,   173,   351,   203,   353,   205,    98,   207,
     100,   203,    52,    93,    29,   207,    96,   187,    98,    98,
      85,   100,   192,   193,    97,    98,    23,    24,    98,    44,
      45,    64,    65,    48,    49,    98,    51,   235,    53,    54,
     100,   311,   187,    51,    52,   215,   215,   192,   193,   319,
      91,   321,   284,    91,   286,     3,   288,     3,   290,    51,
      52,     3,   319,    51,    52,    80,    81,    30,    59,    70,
     100,    27,    52,    91,    52,    90,   100,    92,    98,    94,
     191,    52,    91,     3,    99,   100,    90,   198,   435,   100,
      52,    52,    52,    52,    52,   293,   266,   295,   100,    52,
      96,   271,    52,    24,   362,   269,     7,     8,   455,   307,
      23,    24,    25,   311,    27,    28,   362,    30,    31,    32,
      33,    34,    35,   321,   319,   410,   279,   280,   281,   282,
     330,   345,   445,   336,   345,    36,    37,    38,    39,   309,
     309,    42,    43,    44,    45,    46,    47,   300,   301,   319,
     447,   345,   350,   449,   352,   325,   326,   355,   269,   345,
     330,    38,    38,   333,   198,    -1,   336,    -1,   338,    23,
      24,    -1,   283,    27,    28,    -1,    30,    31,    32,    33,
      34,    35,   380,    -1,   354,   296,   356,   298,   333,    90,
      91,    92,   345,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   400,    -1,    -1,   375,   359,   360,   378,   354,
      -1,   356,   365,   383,   367,    -1,    -1,    -1,    -1,   389,
     331,   391,   392,    -1,    -1,     2,     3,     4,     5,     6,
      -1,   401,    -1,   378,   432,   346,   347,   348,   349,   437,
      -1,    -1,    -1,    -1,    -1,   415,   357,   358,    -1,    -1,
     448,    -1,    -1,    -1,    -1,    -1,   401,    -1,    -1,    -1,
      -1,   431,   460,   433,    -1,    -1,    -1,    -1,   438,   439,
     440,    -1,    -1,   443,    -1,   445,    -1,   447,    -1,   449,
     450,    -1,    -1,   394,    -1,   396,   431,    -1,   433,    -1,
      -1,   402,   403,   438,   439,   440,   407,   408,    -1,    -1,
      -1,    -1,    -1,    -1,   474,   450,    -1,    -1,    -1,   420,
      -1,   481,   423,   483,   425,    -1,    -1,   428,    -1,   430,
      -1,    -1,    -1,    -1,   101,    -1,    -1,     1,    -1,   474,
      -1,     5,     6,    -1,    -1,    -1,   481,    -1,   483,    -1,
      -1,    -1,    -1,   454,    -1,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,    29,    -1,    -1,    -1,   136,
     137,   472,    -1,    -1,   475,   142,    -1,    -1,    -1,    -1,
      44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,
      54,    55,    56,    57,    58,    -1,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    68,    69,    -1,    71,    -1,    73,
      74,     4,     5,     6,    -1,    -1,    80,    81,    -1,    -1,
      84,    85,    86,    87,    88,    -1,    90,    -1,    92,    93,
      94,    -1,    96,    -1,    98,    99,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,
      -1,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,    83,    84,    -1,    44,    45,    80,    81,    48,
      49,    -1,    51,    -1,    53,    54,    -1,    90,    -1,    92,
      -1,    94,    -1,    -1,    29,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    80,    81,    48,    49,    -1,    51,    -1,    53,    54,
      -1,    90,    -1,    92,    -1,    94,     5,     6,    97,    -1,
      99,    -1,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,    -1,    80,    81,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    -1,    90,    -1,    92,    -1,    94,
      -1,    -1,    -1,    -1,    99,    44,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,     5,     6,    63,    -1,    -1,    66,    67,    68,
      69,    -1,    71,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,    84,    29,    -1,    87,    88,
      -1,    90,    -1,    92,    93,    94,    -1,    96,    -1,    98,
      99,    44,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,     5,     6,
      63,    -1,    -1,    66,    67,    68,    69,    -1,    71,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,
      -1,    84,    29,    -1,    87,    88,    -1,    90,    -1,    92,
      -1,    94,    -1,    96,    -1,    98,    99,    44,    45,    -1,
      -1,    48,    49,    -1,    51,    -1,    53,    54,    55,    56,
      57,    58,    -1,    60,     5,     6,    63,    -1,    -1,    66,
      67,    68,    69,    -1,    71,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,    84,    29,    -1,
      87,    88,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,
      -1,    -1,    99,    44,    45,    -1,    -1,    48,    49,    -1,
      51,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
       5,     6,    63,    -1,    -1,    66,    67,    68,    69,    -1,
      71,    -1,    73,    74,    -1,    -1,    -1,     5,     6,    80,
      81,    -1,    -1,    -1,    29,    -1,    87,    88,    -1,    90,
      -1,    92,    -1,    94,     5,     6,    -1,    -1,    99,    44,
      45,    29,    -1,    48,    49,    -1,    51,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    29,    -1,
      48,    49,    -1,    51,    -1,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    80,    81,    48,    49,    -1,
      51,    -1,    53,    54,    -1,    90,    -1,    92,    -1,    94,
       5,     6,    80,    81,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    92,    -1,    94,    -1,    -1,    80,
      81,    99,    -1,    -1,    29,     5,     6,     7,     8,    90,
      -1,    92,    -1,    94,    -1,    -1,    -1,    -1,    99,    44,
      45,    -1,    -1,    48,    49,    -1,    51,    -1,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    92,    -1,    94,
      -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      90,    91,    92,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
       3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
       3,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    31,
      32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     5,     6,    29,    44,    45,    48,    49,    51,
      53,    54,    55,    56,    57,    58,    60,    63,    66,    67,
      68,    69,    71,    73,    74,    80,    81,    86,    87,    88,
      90,    92,    94,    96,    98,    99,   102,   103,   104,   108,
     109,   111,   112,   113,   114,   115,   116,   118,   121,   122,
     123,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     140,   141,   146,   151,   152,   153,   154,   163,   164,   165,
     170,   172,   173,   197,   198,   199,    99,   111,   128,   128,
     128,   128,   128,   196,   196,   196,   196,   196,   196,   196,
     196,   111,   137,   139,   137,    93,   200,   201,   196,   134,
       4,    29,    98,   119,   120,   124,   125,   126,   134,   117,
     120,    75,    90,   155,   157,     0,    85,    93,   198,   199,
     110,   114,     5,     6,     7,     8,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    90,    91,
      92,   127,     4,    23,    24,    25,    26,    27,    28,    30,
      31,    32,    33,    34,    35,     3,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      84,   196,    90,   174,    93,    96,    98,   202,   203,    96,
      98,    90,   131,   132,    90,   132,   134,   203,   134,   142,
     143,   134,   203,   203,     3,   139,   105,   106,   107,   108,
      93,   100,   126,    96,    97,    98,    95,    96,     1,    29,
     125,   139,   158,   159,   160,   195,   108,   114,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     100,   126,    97,   126,    50,    90,   128,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,    82,    83,    94,   111,   161,   166,
     167,    29,   111,   175,   176,   111,    93,    96,    98,    76,
      77,    78,    79,   179,   180,   181,   184,   185,   187,   188,
     191,   192,   132,     3,   132,     3,   195,   105,   195,    52,
      61,    62,   144,   145,   203,   105,   105,   138,    85,   202,
     203,    98,   120,   124,   125,   134,   120,   100,   156,    98,
     108,    98,   100,    97,   134,    91,    91,    95,   111,   162,
       3,   157,   168,   203,   111,     3,    98,   100,    30,   177,
     178,   196,   196,   196,   196,   203,   174,   174,   174,   174,
       3,   134,     3,   134,   203,    59,   203,   196,   196,    64,
      65,   147,   148,   149,   150,    70,    52,    72,   134,   108,
     160,   100,   111,   111,    95,    98,   111,   167,   203,   105,
     138,   176,   111,    27,   181,   185,   188,   192,   196,   203,
     203,   203,   203,   134,   195,   134,   195,   105,   134,   105,
     203,   203,   196,   196,    52,   149,   150,   196,   196,   111,
     105,    52,    85,   169,   134,    91,   111,    52,   171,   111,
     182,   183,   165,   186,   111,   189,   190,   111,   193,   194,
     100,   203,    98,   203,    52,   134,   105,   203,   203,   203,
     203,   169,   111,    91,     3,   203,   203,   203,    90,   203,
     203,   105,   134,   105,   195,   134,   105,   105,   105,   111,
     138,    52,   183,    52,   165,    52,   190,   134,    52,   194,
     105,    52,   100,    52,   203,   195,    52,    52,   134,   100,
      52,   203,   105,   203,    96,   105,   105,    52
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

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  return yypull_parse (YY_NULL, parser);
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
  if (yyps)
    yyps_local = yyps;
  else
    {
      yyps_local = yypstate_new ();
      if (!yyps_local)
        {
          yyerror (parser, YY_("memory exhausted"));
          return 2;
        }
    }
  do {
    yychar = YYLEX;
    yystatus =
      yypush_parse (yyps_local, yychar, &yylval, parser);
  } while (yystatus == YYPUSH_MORE);
  if (!yyps)
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
    return YY_NULL;
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


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 311 "parse-tree/oct-parse.yy"
    {
                    parser.stmt_list = (yyvsp[(1) - (2)].tree_statement_list_type);
                    YYACCEPT;
                  }
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 316 "parse-tree/oct-parse.yy"
    {
                    lexer.end_of_input = true;
                    parser.stmt_list = (yyvsp[(1) - (2)].tree_statement_list_type);
                    YYACCEPT;
                  }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 322 "parse-tree/oct-parse.yy"
    { ABORT_PARSE; }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 326 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = 0; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 328 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), false); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 332 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 334 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), false); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 338 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = new tree_statement_list (); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 340 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = (yyvsp[(1) - (1)].tree_statement_list_type); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 344 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.set_stmt_print_flag ((yyvsp[(1) - (2)].tree_statement_list_type), (yyvsp[(2) - (2)].sep_type), true); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 348 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.make_statement_list ((yyvsp[(1) - (1)].tree_statement_type)); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 350 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_list_type) = parser.append_statement_list ((yyvsp[(1) - (3)].tree_statement_list_type), (yyvsp[(2) - (3)].sep_type), (yyvsp[(3) - (3)].tree_statement_type), true); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 354 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 356 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_command_type)); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 358 "parse-tree/oct-parse.yy"
    { (yyval.tree_statement_type) = make_statement ((yyvsp[(1) - (1)].tree_index_expression_type)); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 370 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_index_expression_type) = parser.make_index_expression ((yyvsp[(1) - (2)].tree_identifier_type), (yyvsp[(2) - (2)].tree_argument_list_type), '(');
                    if (! (yyval.tree_index_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 378 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 380 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_argument_list_type)->append ((yyvsp[(2) - (2)].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type);
                  }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 391 "parse-tree/oct-parse.yy"
    {
                    symbol_table::symbol_record *sr = (yyvsp[(1) - (1)].tok_val)->sym_rec ();
                    (yyval.tree_identifier_type) = new tree_identifier (*sr, (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                  }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 399 "parse-tree/oct-parse.yy"
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ()); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 403 "parse-tree/oct-parse.yy"
    { (yyval.tree_identifier_type) = new tree_identifier ((yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ()); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 407 "parse-tree/oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (DQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 409 "parse-tree/oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (SQ_STRING, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 413 "parse-tree/oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 415 "parse-tree/oct-parse.yy"
    { (yyval.tree_constant_type) = parser.make_constant (IMAG_NUM, (yyvsp[(1) - (1)].tok_val)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 417 "parse-tree/oct-parse.yy"
    { (yyval.tree_constant_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 421 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_matrix ((yyvsp[(2) - (3)].tree_matrix_type)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 425 "parse-tree/oct-parse.yy"
    { (yyval.tree_matrix_type) = (yyvsp[(1) - (1)].tree_argument_list_type) ? new tree_matrix ((yyvsp[(1) - (1)].tree_argument_list_type)) : 0; }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 427 "parse-tree/oct-parse.yy"
    {
                    if ((yyvsp[(1) - (3)].tree_matrix_type))
                      {
                        if ((yyvsp[(3) - (3)].tree_argument_list_type))
                          (yyvsp[(1) - (3)].tree_matrix_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));

                        (yyval.tree_matrix_type) = (yyvsp[(1) - (3)].tree_matrix_type);
                      }
                    else
                      (yyval.tree_matrix_type) = (yyvsp[(3) - (3)].tree_argument_list_type) ? new tree_matrix ((yyvsp[(3) - (3)].tree_argument_list_type)) : 0;
                  }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 441 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_cell ((yyvsp[(2) - (3)].tree_cell_type)); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 445 "parse-tree/oct-parse.yy"
    { (yyval.tree_cell_type) = (yyvsp[(1) - (1)].tree_argument_list_type) ? new tree_cell ((yyvsp[(1) - (1)].tree_argument_list_type)) : 0; }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 447 "parse-tree/oct-parse.yy"
    {
                    if ((yyvsp[(1) - (3)].tree_cell_type))
                      {
                        if ((yyvsp[(3) - (3)].tree_argument_list_type))
                          (yyvsp[(1) - (3)].tree_cell_type)->append ((yyvsp[(3) - (3)].tree_argument_list_type));

                        (yyval.tree_cell_type) = (yyvsp[(1) - (3)].tree_cell_type);
                      }
                    else
                      (yyval.tree_cell_type) = (yyvsp[(3) - (3)].tree_argument_list_type) ? new tree_cell ((yyvsp[(3) - (3)].tree_argument_list_type)) : 0;
                  }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 465 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = 0; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 467 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = 0; }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 469 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (1)].tree_argument_list_type); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 471 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(1) - (2)].tree_argument_list_type); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 473 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(2) - (2)].tree_argument_list_type); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 475 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = (yyvsp[(2) - (3)].tree_argument_list_type); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 479 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_fcn_handle_type) = parser.make_fcn_handle ((yyvsp[(2) - (2)].tok_val));
                    lexer.looking_at_function_handle--;
                  }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 486 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_anon_fcn_handle_type) = parser.make_anon_fcn_handle ((yyvsp[(2) - (4)].tree_parameter_list_type), (yyvsp[(4) - (4)].tree_statement_type));
                    lexer.nesting_level.remove ();
                  }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 493 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 495 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_constant_type); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 497 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_fcn_handle_type); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 499 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_matrix_or_assign_lhs = false;
                    (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type);
                  }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 504 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 506 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 508 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_identifier_type); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 510 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(2) - (3)].tree_expression_type)->mark_in_parens (); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 514 "parse-tree/oct-parse.yy"
    {
                    octave_value tmp (octave_value::magic_colon_t);
                    (yyval.tree_constant_type) = new tree_constant (tmp);
                  }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 521 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_identifier_type) = new tree_black_hole ();
                  }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 527 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 529 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_constant_type)); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 531 "parse-tree/oct-parse.yy"
    { (yyval.tree_argument_list_type) = new tree_argument_list ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 533 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_constant_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 538 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_identifier_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 543 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_argument_list_type)->append ((yyvsp[(3) - (3)].tree_expression_type));
                    (yyval.tree_argument_list_type) = (yyvsp[(1) - (3)].tree_argument_list_type);
                  }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 550 "parse-tree/oct-parse.yy"
    { lexer.looking_at_indirect_ref = true; }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 554 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 556 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (PLUS_PLUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 558 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (MINUS_MINUS, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 560 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '(');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 566 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '(');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 572 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (3)].tree_expression_type), 0, '{');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 578 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_expression_type) = parser.make_index_expression ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(3) - (4)].tree_argument_list_type), '{');
                    if (! (yyval.tree_expression_type))
                      ABORT_PARSE;
                  }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 584 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (HERMITIAN, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 586 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_postfix_op (TRANSPOSE, (yyvsp[(1) - (2)].tree_expression_type), (yyvsp[(2) - (2)].tok_val)); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 588 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(3) - (3)].tok_val)->text ()); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 590 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_indirect_ref ((yyvsp[(1) - (5)].tree_expression_type), (yyvsp[(4) - (5)].tree_expression_type)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 592 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (PLUS_PLUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 594 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (MINUS_MINUS, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 596 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op (EXPR_NOT, (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 598 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op ('+', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 600 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_prefix_op ('-', (yyvsp[(2) - (2)].tree_expression_type), (yyvsp[(1) - (2)].tok_val)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 602 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (POW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 604 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EPOW, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 606 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 608 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 610 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('*', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 612 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('/', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 614 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('+', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 616 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op ('-', (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 618 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EMUL, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 620 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 622 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (LEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 624 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (ELEFTDIV, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 628 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.finish_colon_expression ((yyvsp[(1) - (1)].tree_colon_expression_type)); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 632 "parse-tree/oct-parse.yy"
    { (yyval.tree_colon_expression_type) = new tree_colon_expression ((yyvsp[(1) - (1)].tree_expression_type)); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 634 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_colon_expression_type) = (yyvsp[(1) - (3)].tree_colon_expression_type)->append ((yyvsp[(3) - (3)].tree_expression_type))))
                      ABORT_PARSE;
                  }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 641 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 643 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (LSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 645 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (RSHIFT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 647 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 649 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_LE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 651 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_EQ, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 653 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 655 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_GT, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 98:
/* Line 1787 of yacc.c  */
#line 657 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_NE, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 659 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 100:
/* Line 1787 of yacc.c  */
#line 661 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_binary_op (EXPR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 663 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_AND_AND, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 102:
/* Line 1787 of yacc.c  */
#line 665 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_boolean_op (EXPR_OR_OR, (yyvsp[(1) - (3)].tree_expression_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 669 "parse-tree/oct-parse.yy"
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

  case 104:
/* Line 1787 of yacc.c  */
#line 683 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op ('=', (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 685 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (ADD_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 687 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (SUB_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 689 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (MUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 691 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (DIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 693 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (LEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 695 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (POW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 697 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (LSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 699 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (RSHIFT_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 701 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EMUL_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 703 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 705 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (ELEFTDIV_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 707 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (EPOW_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 709 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (AND_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 711 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = parser.make_assign_op (OR_EQ, (yyvsp[(1) - (3)].tree_argument_list_type), (yyvsp[(2) - (3)].tok_val), (yyvsp[(3) - (3)].tree_expression_type)); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 715 "parse-tree/oct-parse.yy"
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

  case 120:
/* Line 1787 of yacc.c  */
#line 730 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_expression_type); }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 732 "parse-tree/oct-parse.yy"
    { (yyval.tree_expression_type) = (yyvsp[(1) - (1)].tree_anon_fcn_handle_type); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 740 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_decl_command_type); }
    break;

  case 123:
/* Line 1787 of yacc.c  */
#line 742 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 744 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 746 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 748 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 750 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 128:
/* Line 1787 of yacc.c  */
#line 752 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 129:
/* Line 1787 of yacc.c  */
#line 754 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_command_type); }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 762 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (GLOBAL, (yyvsp[(1) - (2)].tok_val), (yyvsp[(2) - (2)].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 767 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_decl_command_type) = parser.make_decl_command (PERSISTENT, (yyvsp[(1) - (2)].tok_val), (yyvsp[(2) - (2)].tree_decl_init_list_type));
                    lexer.looking_at_decl_list = false;
                  }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 774 "parse-tree/oct-parse.yy"
    { (yyval.tree_decl_init_list_type) = new tree_decl_init_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 776 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_decl_init_list_type)->append ((yyvsp[(2) - (2)].tree_decl_elt_type));
                    (yyval.tree_decl_init_list_type) = (yyvsp[(1) - (2)].tree_decl_init_list_type);
                  }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 783 "parse-tree/oct-parse.yy"
    { lexer.looking_at_initializer_expression = true; }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 786 "parse-tree/oct-parse.yy"
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 788 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_initializer_expression = false;
                    (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (4)].tree_identifier_type), (yyvsp[(4) - (4)].tree_expression_type));
                  }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 799 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_if_command_type); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 801 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = (yyvsp[(1) - (1)].tree_switch_command_type); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 809 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_if_command_type) = parser.finish_if_command ((yyvsp[(1) - (4)].tok_val), (yyvsp[(3) - (4)].tree_if_command_list_type), (yyvsp[(4) - (4)].tok_val), (yyvsp[(2) - (4)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 816 "parse-tree/oct-parse.yy"
    { (yyval.tree_if_command_list_type) = (yyvsp[(1) - (1)].tree_if_command_list_type); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 818 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
                  }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 825 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (4)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_command_list_type) = parser.start_if_command ((yyvsp[(1) - (4)].tree_expression_type), (yyvsp[(4) - (4)].tree_statement_list_type));
                  }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 831 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_if_command_list_type)->append ((yyvsp[(2) - (2)].tree_if_clause_type));
                    (yyval.tree_if_command_list_type) = (yyvsp[(1) - (2)].tree_if_command_list_type);
                  }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 838 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(4) - (7)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    (yyval.tree_if_clause_type) = parser.make_elseif_clause ((yyvsp[(1) - (7)].tok_val), (yyvsp[(4) - (7)].tree_expression_type), (yyvsp[(7) - (7)].tree_statement_list_type), (yyvsp[(2) - (7)].comment_type));
                  }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 846 "parse-tree/oct-parse.yy"
    { (yyval.tree_if_clause_type) = new tree_if_clause ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type)); }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 854 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_switch_command_type) = parser.finish_switch_command ((yyvsp[(1) - (6)].tok_val), (yyvsp[(3) - (6)].tree_expression_type), (yyvsp[(5) - (6)].tree_switch_case_list_type), (yyvsp[(6) - (6)].tok_val), (yyvsp[(2) - (6)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 861 "parse-tree/oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list (); }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 863 "parse-tree/oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[(1) - (1)].tree_switch_case_type)); }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 865 "parse-tree/oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (1)].tree_switch_case_list_type); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 867 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
                  }
    break;

  case 151:
/* Line 1787 of yacc.c  */
#line 874 "parse-tree/oct-parse.yy"
    { (yyval.tree_switch_case_list_type) = new tree_switch_case_list ((yyvsp[(1) - (1)].tree_switch_case_type)); }
    break;

  case 152:
/* Line 1787 of yacc.c  */
#line 876 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (2)].tree_switch_case_list_type)->append ((yyvsp[(2) - (2)].tree_switch_case_type));
                    (yyval.tree_switch_case_list_type) = (yyvsp[(1) - (2)].tree_switch_case_list_type);
                  }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 883 "parse-tree/oct-parse.yy"
    { (yyval.tree_switch_case_type) = parser.make_switch_case ((yyvsp[(1) - (7)].tok_val), (yyvsp[(4) - (7)].tree_expression_type), (yyvsp[(7) - (7)].tree_statement_list_type), (yyvsp[(2) - (7)].comment_type)); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 887 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_switch_case_type) = new tree_switch_case ((yyvsp[(4) - (4)].tree_statement_list_type), (yyvsp[(2) - (4)].comment_type));
                  }
    break;

  case 155:
/* Line 1787 of yacc.c  */
#line 897 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(3) - (7)].tree_expression_type)->mark_braindead_shortcircuit (lexer.fcn_file_full_name);

                    if (! ((yyval.tree_command_type) = parser.make_while_command ((yyvsp[(1) - (7)].tok_val), (yyvsp[(3) - (7)].tree_expression_type), (yyvsp[(6) - (7)].tree_statement_list_type), (yyvsp[(7) - (7)].tok_val), (yyvsp[(2) - (7)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 904 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_do_until_command ((yyvsp[(5) - (6)].tok_val), (yyvsp[(4) - (6)].tree_statement_list_type), (yyvsp[(6) - (6)].tree_expression_type), (yyvsp[(2) - (6)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 909 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[(1) - (9)].tok_val), (yyvsp[(3) - (9)].tree_argument_list_type), (yyvsp[(5) - (9)].tree_expression_type), 0,
                                                  (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 915 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (FOR, (yyvsp[(1) - (10)].tok_val), (yyvsp[(4) - (10)].tree_argument_list_type), (yyvsp[(6) - (10)].tree_expression_type), 0,
                                                  (yyvsp[(9) - (10)].tree_statement_list_type), (yyvsp[(10) - (10)].tok_val), (yyvsp[(2) - (10)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 921 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[(1) - (9)].tok_val), (yyvsp[(3) - (9)].tree_argument_list_type), (yyvsp[(5) - (9)].tree_expression_type),
                                                  0, (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 927 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_for_command (PARFOR, (yyvsp[(1) - (12)].tok_val), (yyvsp[(4) - (12)].tree_argument_list_type), (yyvsp[(6) - (12)].tree_expression_type),
                                                  (yyvsp[(8) - (12)].tree_expression_type), (yyvsp[(11) - (12)].tree_statement_list_type), (yyvsp[(12) - (12)].tok_val), (yyvsp[(2) - (12)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 939 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_break_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 944 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_continue_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 949 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_return_command ((yyvsp[(1) - (1)].tok_val))))
                      ABORT_PARSE;
                  }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 961 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_unwind_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 967 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[(1) - (9)].tok_val), (yyvsp[(4) - (9)].tree_statement_list_type), (yyvsp[(7) - (9)].sep_type), (yyvsp[(8) - (9)].tree_statement_list_type), (yyvsp[(9) - (9)].tok_val), (yyvsp[(2) - (9)].comment_type), (yyvsp[(6) - (9)].comment_type))))
                      ABORT_PARSE;
                  }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 972 "parse-tree/oct-parse.yy"
    {
                    if (! ((yyval.tree_command_type) = parser.make_try_command ((yyvsp[(1) - (5)].tok_val), (yyvsp[(4) - (5)].tree_statement_list_type), 0, 0, (yyvsp[(5) - (5)].tok_val), (yyvsp[(2) - (5)].comment_type), 0)))
                      ABORT_PARSE;
                  }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 983 "parse-tree/oct-parse.yy"
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

  case 168:
/* Line 1787 of yacc.c  */
#line 1011 "parse-tree/oct-parse.yy"
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

  case 169:
/* Line 1787 of yacc.c  */
#line 1024 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_parameter_list = false;
                    lexer.looking_for_object_index = false;
                  }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1031 "parse-tree/oct-parse.yy"
    {
                    if ((yyvsp[(2) - (3)].tree_parameter_list_type))
                      lexer.mark_as_variables ((yyvsp[(2) - (3)].tree_parameter_list_type)->variable_names ());

                    (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
                  }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1038 "parse-tree/oct-parse.yy"
    {
                    parser.bison_error ("invalid parameter list");
                    (yyval.tree_parameter_list_type) = 0;
                    ABORT_PARSE;
                  }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1046 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1048 "parse-tree/oct-parse.yy"
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

  case 174:
/* Line 1787 of yacc.c  */
#line 1061 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list ((yyvsp[(1) - (1)].tree_decl_elt_type)); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1063 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_parameter_list_type)->append ((yyvsp[(3) - (3)].tree_decl_elt_type));
                    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
                  }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1070 "parse-tree/oct-parse.yy"
    { (yyval.tree_decl_elt_type) = (yyvsp[(1) - (1)].tree_decl_elt_type); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 1072 "parse-tree/oct-parse.yy"
    { (yyval.tree_decl_elt_type) = new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type)); }
    break;

  case 178:
/* Line 1787 of yacc.c  */
#line 1080 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;

                    (yyval.tree_parameter_list_type) = new tree_parameter_list ();
                  }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1086 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;

                    tree_parameter_list *tmp = new tree_parameter_list ((yyvsp[(1) - (1)].tree_identifier_type));

                    // Even though this parameter list can contain only
                    // a single identifier, we still need to validate it
                    // to check for varargin or varargout.

                    if (tmp->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = tmp;
                    else
                      ABORT_PARSE;
                  }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1101 "parse-tree/oct-parse.yy"
    {
                    lexer.looking_at_return_list = false;

                    // Check for duplicate parameter names, varargin,
                    // or varargout.

                    if ((yyvsp[(2) - (3)].tree_parameter_list_type)->validate (tree_parameter_list::out))
                      (yyval.tree_parameter_list_type) = (yyvsp[(2) - (3)].tree_parameter_list_type);
                    else
                      ABORT_PARSE;
                  }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 1115 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = new tree_parameter_list (new tree_decl_elt ((yyvsp[(1) - (1)].tree_identifier_type))); }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1117 "parse-tree/oct-parse.yy"
    {
                    (yyvsp[(1) - (3)].tree_parameter_list_type)->append (new tree_decl_elt ((yyvsp[(3) - (3)].tree_identifier_type)));
                    (yyval.tree_parameter_list_type) = (yyvsp[(1) - (3)].tree_parameter_list_type);
                  }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1128 "parse-tree/oct-parse.yy"
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

  case 184:
/* Line 1787 of yacc.c  */
#line 1148 "parse-tree/oct-parse.yy"
    {
                    (yyval.tok_val) = (yyvsp[(2) - (2)].tok_val);
                    if (lexer.reading_classdef_file
                        || lexer.parsing_classdef)
                      lexer.maybe_classdef_get_set_method = true;
                  }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 1157 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_command_type) = parser.finish_function (0, (yyvsp[(3) - (3)].octave_user_function_type), (yyvsp[(2) - (3)].comment_type), (yyvsp[(1) - (3)].tok_val)->line (),
                                                 (yyvsp[(1) - (3)].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1163 "parse-tree/oct-parse.yy"
    {
                    (yyval.tree_command_type) = parser.finish_function ((yyvsp[(3) - (5)].tree_parameter_list_type), (yyvsp[(5) - (5)].octave_user_function_type), (yyvsp[(2) - (5)].comment_type), (yyvsp[(1) - (5)].tok_val)->line (),
                                                 (yyvsp[(1) - (5)].tok_val)->column ());
                    parser.recover_from_parsing_function ();
                  }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1171 "parse-tree/oct-parse.yy"
    {
                    std::string id_name = (yyvsp[(1) - (1)].tree_identifier_type)->name ();

                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;

                    (yyval.tree_identifier_type) = (yyvsp[(1) - (1)].tree_identifier_type);
                  }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 1180 "parse-tree/oct-parse.yy"
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[(3) - (3)].tree_identifier_type);
                  }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 1186 "parse-tree/oct-parse.yy"
    {
                    lexer.parsed_function_name.top () = true;
                    lexer.maybe_classdef_get_set_method = false;
                    (yyval.tree_identifier_type) = (yyvsp[(3) - (3)].tree_identifier_type);
                  }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 1194 "parse-tree/oct-parse.yy"
    {
                    std::string fname = (yyvsp[(1) - (2)].tree_identifier_type)->name ();

                    delete (yyvsp[(1) - (2)].tree_identifier_type);

                    if (! ((yyval.octave_user_function_type) = parser.frob_function (fname, (yyvsp[(2) - (2)].octave_user_function_type))))
                      ABORT_PARSE;
                  }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1205 "parse-tree/oct-parse.yy"
    { (yyval.octave_user_function_type) = parser.start_function ((yyvsp[(1) - (4)].tree_parameter_list_type), (yyvsp[(3) - (4)].tree_statement_list_type), (yyvsp[(4) - (4)].tree_statement_type)); }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1207 "parse-tree/oct-parse.yy"
    { (yyval.octave_user_function_type) = parser.start_function (0, (yyvsp[(2) - (3)].tree_statement_list_type), (yyvsp[(3) - (3)].tree_statement_type)); }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1211 "parse-tree/oct-parse.yy"
    {
                    parser.endfunction_found = true;
                    if (parser.end_token_ok ((yyvsp[(1) - (1)].tok_val), token::function_end))
                      (yyval.tree_statement_type) = parser.make_end ("endfunction", false,
                                            (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1220 "parse-tree/oct-parse.yy"
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

  case 195:
/* Line 1787 of yacc.c  */
#line 1260 "parse-tree/oct-parse.yy"
    {
                    (yyval.comment_type) = 0;
                    lexer.parsing_classdef = true;
                  }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1267 "parse-tree/oct-parse.yy"
    {
                    lexer.parsing_classdef = false;

                    if (parser.end_token_ok ((yyvsp[(1) - (1)].tok_val), token::classdef_end))
                      (yyval.tree_statement_type) = parser.make_end ("endclassdef", false,
                                            (yyvsp[(1) - (1)].tok_val)->line (), (yyvsp[(1) - (1)].tok_val)->column ());
                    else
                      ABORT_PARSE;
                  }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1279 "parse-tree/oct-parse.yy"
    { (yyval.octave_user_function_type) = 0; }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1283 "parse-tree/oct-parse.yy"
    { (yyval.tree_command_type) = 0; }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1287 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1289 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1293 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1295 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1299 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 1301 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1303 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1308 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1310 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1314 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1316 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1318 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 1320 "parse-tree/oct-parse.yy"
    { (yyval.tree_parameter_list_type) = 0; }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 1324 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1326 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1328 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1330 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1332 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1334 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1336 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1338 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1342 "parse-tree/oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1347 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1352 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1354 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 1358 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1360 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1364 "parse-tree/oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1368 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1372 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1374 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1378 "parse-tree/oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1382 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 1386 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 1388 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 1392 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 1396 "parse-tree/oct-parse.yy"
    { (yyval.comment_type) = 0; }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 1400 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 1404 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 1406 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 1410 "parse-tree/oct-parse.yy"
    { (yyval.dummy_type) = 0; }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 1418 "parse-tree/oct-parse.yy"
    { lexer.at_beginning_of_statement = true; }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 1422 "parse-tree/oct-parse.yy"
    { (yyval.comment_type) = octave_comment_buffer::get_comment (); }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 1426 "parse-tree/oct-parse.yy"
    { parser.bison_error ("parse error"); }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 1431 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = ','; }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 1433 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = ';'; }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 1435 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 1437 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 1441 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 1443 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 1447 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 1449 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 1453 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = '\n'; }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 1455 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 1459 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = ','; }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 1461 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = ';'; }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 1463 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = '\n'; }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 1465 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 1467 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 1469 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (2)].sep_type); }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 1473 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = 0; }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 1475 "parse-tree/oct-parse.yy"
    { (yyval.sep_type) = (yyvsp[(1) - (1)].sep_type); }
    break;


/* Line 1787 of yacc.c  */
#line 4329 "parse-tree/oct-parse.cc"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2050 of yacc.c  */
#line 1478 "parse-tree/oct-parse.yy"


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
                                      char catch_sep,
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

      tree_identifier *id = 0;

      if (! catch_sep && cleanup_stmts && ! cleanup_stmts->empty ())
        {
          tree_statement *stmt = cleanup_stmts->front ();

          if (stmt)
            {
              tree_expression *expr = stmt->expression ();

              if (expr && expr->is_identifier ())
                {
                  id = dynamic_cast<tree_identifier *> (expr);

                  cleanup_stmts->pop_front ();
                }
            }
        }

      retval = new tree_try_catch_command (body, cleanup_stmts, id,
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
  return (m
          ? finish_array_list (m)
          : new tree_constant (octave_null_matrix::instance));
}

// Finish building a cell list.

tree_expression *
octave_base_parser::finish_cell (tree_cell *c)
{
  return (c
          ? finish_array_list (c)
          : new tree_constant (octave_value (Cell ())));
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
@deftypefn  {Built-in Function} {} autoload (@var{function}, @var{file})\n\
@deftypefnx {Built-in Function} {} autoload (@dots{}, @asis{\"remove\"})\n\
Define @var{function} to autoload from @var{file}.\n\
\n\
The second argument, @var{file}, should be an absolute file name or\n\
a file name in the same directory as the function or script from which\n\
the autoload command was run.  @var{file} should not depend on the\n\
Octave load path.\n\
\n\
Normally, calls to @code{autoload} appear in PKG_ADD script files that\n\
are evaluated when a directory is added to Octave's load path.  To\n\
avoid having to hardcode directory names in @var{file}, if @var{file}\n\
is in the same directory as the PKG_ADD script then\n\
\n\
@example\n\
autoload (\"foo\", \"bar.oct\");\n\
@end example\n\
\n\
@noindent\n\
will load the function @code{foo} from the file @code{bar.oct}.  The above\n\
usage when @code{bar.oct} is not in the same directory or usages such as\n\
\n\
@example\n\
autoload (\"foo\", file_in_loadpath (\"bar.oct\"))\n\
@end example\n\
\n\
@noindent\n\
are strongly discouraged, as their behavior may be unpredictable.\n\
\n\
With no arguments, return a structure containing the current autoload map.\n\
\n\
If a third argument @asis{'remove'} is given, the function is cleared and\n\
not loaded anymore during the current Octave session.\n\
\n\
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
  else if (nargin == 2 || nargin == 3)
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
          if (nargin == 2)
            autoload_map[argv[1]] = nm;
          else if (nargin == 3)
            {
              if (argv[3].compare ("remove") != 0)
                error_with_id ("Octave:invalid-input-arg",
                               "autoload: third argument can only be 'remove'");

              // Remove function from symbol table and autoload map.
              symbol_table::clear_dld_function (argv[1]);
              autoload_map.erase (argv[1]);
            }
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
return the empty string.  Given the argument @qcode{\"fullpath\"},\n\
include the directory part of the file name, but not the extension.\n\
Given the argument @qcode{\"fullpathext\"}, include the directory part\n\
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
are passed as inputs to the named function.  For example,\n\
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
cannot be predicted beforehand whether @var{f} is a function handle,\n\
function name in a string, or inline function then @code{feval} can be used\n\
instead.\n\
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
@deftypefn {Loadable Function} {[@dots{}] =} builtin (@var{f}, @dots{})\n\
Call the base function @var{f} even if @var{f} is overloaded to\n\
another function for the given type signature.\n\
\n\
This is normally useful when doing object-oriented programming and there\n\
is a requirement to call one of Octave's base functions rather than\n\
the overloaded one of a new class.\n\
\n\
A trivial example which redefines the @code{sin} function to be the\n\
@code{cos} function shows how @code{builtin} works.\n\
\n\
@example\n\
@group\n\
sin (0)\n\
  @result{} 0\n\
function y = sin (x), y = cos (x); endfunction\n\
sin (0)\n\
  @result{} 1\n\
builtin (\"sin\", 0)\n\
  @result{} 0\n\
@end group\n\
@end example\n\
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
The following example makes the variable @var{A} with the approximate\n\
value 3.1416 available.\n\
\n\
@example\n\
eval (\"A = acos(-1);\");\n\
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
may be either @qcode{\"base\"} or @qcode{\"caller\"}.\n\
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
context @var{context}, which may be either @qcode{\"caller\"} or\n\
@qcode{\"base\"}.\n\
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

DEFUN (__parse_file__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __parse_file__ (@var{file}, @var{verbose})\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  int nargin = args.length ();

  if (nargin == 1 || nargin == 2)
    {
      std::string file = args(0).string_value ();
      
      std::string full_file = octave_env::make_absolute (file);

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

      if (! error_state)
        {
          if (nargin == 2)
            octave_stdout << "parsing " << full_file << std::endl;

          octave_function *fcn = parse_fcn_file (full_file, file, "",
                                                 true, false, false,
                                                 false, "__parse_file__");

          if (fcn)
            delete fcn;
        }
      else
        error ("__parse_file__: expecting file name as argument");
    }
  else
    print_usage ();

  return retval;
}
