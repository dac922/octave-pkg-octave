/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* "%code requires" blocks.  */

/* Line 2068 of yacc.c  */
#line 44 "oct-tex-parser.yy"
#include <string>


/* Line 2068 of yacc.c  */
#line 42 "corefcn/oct-tex-parser.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BF = 258,
     IT = 259,
     SL = 260,
     RM = 261,
     CMD = 262,
     FONTNAME = 263,
     FONTSIZE = 264,
     COLOR = 265,
     COLOR_RGB = 266,
     START = 267,
     END = 268,
     SUPER = 269,
     SUB = 270,
     CH = 271,
     ID = 272,
     NUM = 273,
     SCRIPT = 274,
     STR = 275
   };
#endif
/* Tokens.  */
#define BF 258
#define IT 259
#define SL 260
#define RM 261
#define CMD 262
#define FONTNAME 263
#define FONTSIZE 264
#define COLOR 265
#define COLOR_RGB 266
#define START 267
#define END 268
#define SUPER 269
#define SUB 270
#define CH 271
#define ID 272
#define NUM 273
#define SCRIPT 274
#define STR 275




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 46 "oct-tex-parser.yy"

  /* Leaf symbols produced by the scanner */
  char                       ch;
  double                     num;

  /* Used for string buffering */
  std::string*               str;

  /* Objects produced by the parser */
  text_element*              e_base;
  text_element_list*         e_list;



/* Line 2068 of yacc.c  */
#line 114 "corefcn/oct-tex-parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




