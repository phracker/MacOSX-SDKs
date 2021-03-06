/* -*- buffer-read-only: t -*-
   !!!!!!!   DO NOT EDIT THIS FILE   !!!!!!!
   This file is built by regen_perly.pl from perly.y.
   Any changes made here will be lost!
 */

#define PERL_BISON_VERSION  20003

#ifdef PERL_CORE
/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GRAMPROG = 258,
     GRAMEXPR = 259,
     GRAMBLOCK = 260,
     GRAMBARESTMT = 261,
     GRAMFULLSTMT = 262,
     GRAMSTMTSEQ = 263,
     BAREWORD = 264,
     METHOD = 265,
     FUNCMETH = 266,
     THING = 267,
     PMFUNC = 268,
     PRIVATEREF = 269,
     QWLIST = 270,
     FUNC0OP = 271,
     FUNC0SUB = 272,
     UNIOPSUB = 273,
     LSTOPSUB = 274,
     PLUGEXPR = 275,
     PLUGSTMT = 276,
     LABEL = 277,
     FORMAT = 278,
     SUB = 279,
     SIGSUB = 280,
     ANONSUB = 281,
     ANON_SIGSUB = 282,
     PACKAGE = 283,
     USE = 284,
     WHILE = 285,
     UNTIL = 286,
     IF = 287,
     UNLESS = 288,
     ELSE = 289,
     ELSIF = 290,
     CONTINUE = 291,
     FOR = 292,
     GIVEN = 293,
     WHEN = 294,
     DEFAULT = 295,
     LOOPEX = 296,
     DOTDOT = 297,
     YADAYADA = 298,
     FUNC0 = 299,
     FUNC1 = 300,
     FUNC = 301,
     UNIOP = 302,
     LSTOP = 303,
     RELOP = 304,
     EQOP = 305,
     MULOP = 306,
     ADDOP = 307,
     DOLSHARP = 308,
     DO = 309,
     HASHBRACK = 310,
     NOAMP = 311,
     LOCAL = 312,
     MY = 313,
     REQUIRE = 314,
     COLONATTR = 315,
     FORMLBRACK = 316,
     FORMRBRACK = 317,
     PREC_LOW = 318,
     DOROP = 319,
     OROP = 320,
     ANDOP = 321,
     NOTOP = 322,
     ASSIGNOP = 323,
     DORDOR = 324,
     OROR = 325,
     ANDAND = 326,
     BITOROP = 327,
     BITANDOP = 328,
     SHIFTOP = 329,
     MATCHOP = 330,
     REFGEN = 331,
     UMINUS = 332,
     POWOP = 333,
     POSTJOIN = 334,
     POSTDEC = 335,
     POSTINC = 336,
     PREDEC = 337,
     PREINC = 338,
     ARROW = 339
   };
#endif
/* Tokens.  */
#define GRAMPROG 258
#define GRAMEXPR 259
#define GRAMBLOCK 260
#define GRAMBARESTMT 261
#define GRAMFULLSTMT 262
#define GRAMSTMTSEQ 263
#define BAREWORD 264
#define METHOD 265
#define FUNCMETH 266
#define THING 267
#define PMFUNC 268
#define PRIVATEREF 269
#define QWLIST 270
#define FUNC0OP 271
#define FUNC0SUB 272
#define UNIOPSUB 273
#define LSTOPSUB 274
#define PLUGEXPR 275
#define PLUGSTMT 276
#define LABEL 277
#define FORMAT 278
#define SUB 279
#define SIGSUB 280
#define ANONSUB 281
#define ANON_SIGSUB 282
#define PACKAGE 283
#define USE 284
#define WHILE 285
#define UNTIL 286
#define IF 287
#define UNLESS 288
#define ELSE 289
#define ELSIF 290
#define CONTINUE 291
#define FOR 292
#define GIVEN 293
#define WHEN 294
#define DEFAULT 295
#define LOOPEX 296
#define DOTDOT 297
#define YADAYADA 298
#define FUNC0 299
#define FUNC1 300
#define FUNC 301
#define UNIOP 302
#define LSTOP 303
#define RELOP 304
#define EQOP 305
#define MULOP 306
#define ADDOP 307
#define DOLSHARP 308
#define DO 309
#define HASHBRACK 310
#define NOAMP 311
#define LOCAL 312
#define MY 313
#define REQUIRE 314
#define COLONATTR 315
#define FORMLBRACK 316
#define FORMRBRACK 317
#define PREC_LOW 318
#define DOROP 319
#define OROP 320
#define ANDOP 321
#define NOTOP 322
#define ASSIGNOP 323
#define DORDOR 324
#define OROR 325
#define ANDAND 326
#define BITOROP 327
#define BITANDOP 328
#define SHIFTOP 329
#define MATCHOP 330
#define REFGEN 331
#define UMINUS 332
#define POWOP 333
#define POSTJOIN 334
#define POSTDEC 335
#define POSTINC 336
#define PREDEC 337
#define PREINC 338
#define ARROW 339




#ifdef PERL_IN_TOKE_C
static bool
S_is_opval_token(int type) {
    switch (type) {
    case BAREWORD:
    case FUNC0OP:
    case FUNC0SUB:
    case FUNCMETH:
    case LABEL:
    case LSTOPSUB:
    case METHOD:
    case PLUGEXPR:
    case PLUGSTMT:
    case PMFUNC:
    case PRIVATEREF:
    case QWLIST:
    case THING:
    case UNIOPSUB:
	return 1;
    }
    return 0;
}
#endif /* PERL_IN_TOKE_C */
#endif /* PERL_CORE */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
    I32	ival; /* __DEFAULT__ (marker for regen_perly.pl;
				must always be 1st union member) */
    char *pval;
    OP *opval;
    GV *gvval;
}
/* Line 1529 of yacc.c.  */
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif




/* Generated from:
 * 7aa97cfabf5b87a95ed263373e76c7af6d7e075e83d12e84ccdca9690c15a68d perly.y
 * b6fae5748f9bef6db4740aa5e122b84ac5181852d42474d0ecad621fa4253306 regen_perly.pl
 * ex: set ro: */
