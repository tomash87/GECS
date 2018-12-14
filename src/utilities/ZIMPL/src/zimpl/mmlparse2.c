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
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DECLSET = 258,
     DECLPAR = 259,
     DECLVAR = 260,
     DECLMIN = 261,
     DECLMAX = 262,
     DECLSUB = 263,
     DECLSOS = 264,
     DEFNUMB = 265,
     DEFSTRG = 266,
     DEFBOOL = 267,
     DEFSET = 268,
     PRINT = 269,
     CHECK = 270,
     BINARY = 271,
     INTEGER = 272,
     REAL = 273,
     IMPLICIT = 274,
     ASGN = 275,
     DO = 276,
     WITH = 277,
     IN = 278,
     TO = 279,
     UNTIL = 280,
     BY = 281,
     FORALL = 282,
     EXISTS = 283,
     PRIORITY = 284,
     STARTVAL = 285,
     DEFAULT = 286,
     CMP_LE = 287,
     CMP_GE = 288,
     CMP_EQ = 289,
     CMP_LT = 290,
     CMP_GT = 291,
     CMP_NE = 292,
     INFTY = 293,
     AND = 294,
     OR = 295,
     XOR = 296,
     NOT = 297,
     SUM = 298,
     MIN = 299,
     MAX = 300,
     ARGMIN = 301,
     ARGMAX = 302,
     PROD = 303,
     IF = 304,
     THEN = 305,
     ELSE = 306,
     END = 307,
     INTER = 308,
     UNION = 309,
     CROSS = 310,
     SYMDIFF = 311,
     WITHOUT = 312,
     PROJ = 313,
     MOD = 314,
     DIV = 315,
     POW = 316,
     FAC = 317,
     CARD = 318,
     ROUND = 319,
     FLOOR = 320,
     CEIL = 321,
     RANDOM = 322,
     ORD = 323,
     ABS = 324,
     SGN = 325,
     LOG = 326,
     LN = 327,
     EXP = 328,
     SQRT = 329,
     SIN = 330,
     COS = 331,
     TAN = 332,
     ASIN = 333,
     ACOS = 334,
     ATAN = 335,
     POWER = 336,
     SGNPOW = 337,
     READ = 338,
     AS = 339,
     SKIP = 340,
     USE = 341,
     COMMENT = 342,
     MATCH = 343,
     SUBSETS = 344,
     INDEXSET = 345,
     POWERSET = 346,
     VIF = 347,
     VABS = 348,
     TYPE1 = 349,
     TYPE2 = 350,
     LENGTH = 351,
     SUBSTR = 352,
     NUMBSYM = 353,
     STRGSYM = 354,
     VARSYM = 355,
     SETSYM = 356,
     NUMBDEF = 357,
     STRGDEF = 358,
     BOOLDEF = 359,
     SETDEF = 360,
     DEFNAME = 361,
     NAME = 362,
     STRG = 363,
     NUMB = 364,
     SCALE = 365,
     SEPARATE = 366,
     CHECKONLY = 367,
     INDICATOR = 368
   };
#endif
/* Tokens.  */
#define DECLSET 258
#define DECLPAR 259
#define DECLVAR 260
#define DECLMIN 261
#define DECLMAX 262
#define DECLSUB 263
#define DECLSOS 264
#define DEFNUMB 265
#define DEFSTRG 266
#define DEFBOOL 267
#define DEFSET 268
#define PRINT 269
#define CHECK 270
#define BINARY 271
#define INTEGER 272
#define REAL 273
#define IMPLICIT 274
#define ASGN 275
#define DO 276
#define WITH 277
#define IN 278
#define TO 279
#define UNTIL 280
#define BY 281
#define FORALL 282
#define EXISTS 283
#define PRIORITY 284
#define STARTVAL 285
#define DEFAULT 286
#define CMP_LE 287
#define CMP_GE 288
#define CMP_EQ 289
#define CMP_LT 290
#define CMP_GT 291
#define CMP_NE 292
#define INFTY 293
#define AND 294
#define OR 295
#define XOR 296
#define NOT 297
#define SUM 298
#define MIN 299
#define MAX 300
#define ARGMIN 301
#define ARGMAX 302
#define PROD 303
#define IF 304
#define THEN 305
#define ELSE 306
#define END 307
#define INTER 308
#define UNION 309
#define CROSS 310
#define SYMDIFF 311
#define WITHOUT 312
#define PROJ 313
#define MOD 314
#define DIV 315
#define POW 316
#define FAC 317
#define CARD 318
#define ROUND 319
#define FLOOR 320
#define CEIL 321
#define RANDOM 322
#define ORD 323
#define ABS 324
#define SGN 325
#define LOG 326
#define LN 327
#define EXP 328
#define SQRT 329
#define SIN 330
#define COS 331
#define TAN 332
#define ASIN 333
#define ACOS 334
#define ATAN 335
#define POWER 336
#define SGNPOW 337
#define READ 338
#define AS 339
#define SKIP 340
#define USE 341
#define COMMENT 342
#define MATCH 343
#define SUBSETS 344
#define INDEXSET 345
#define POWERSET 346
#define VIF 347
#define VABS 348
#define TYPE1 349
#define TYPE2 350
#define LENGTH 351
#define SUBSTR 352
#define NUMBSYM 353
#define STRGSYM 354
#define VARSYM 355
#define SETSYM 356
#define NUMBDEF 357
#define STRGDEF 358
#define BOOLDEF 359
#define SETDEF 360
#define DEFNAME 361
#define NAME 362
#define STRG 363
#define NUMB 364
#define SCALE 365
#define SEPARATE 366
#define CHECKONLY 367
#define INDICATOR 368




/* Copy the first part of user declarations.  */
#line 1 "src/zimpl/mmlparse2.y"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: mmlparse2.y                                                   */
/*   Name....: MML Parser                                                    */
/*   Author..: Thorsten Koch                                                 */
/*   Copyright by Author, All rights reserved                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Copyright (C) 2001-2018 by Thorsten Koch <koch@zib.de>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wimplicit-function-declaration"
#pragma clang diagnostic ignored "-Wunreachable-code"

#pragma GCC   diagnostic ignored "-Wstrict-prototypes"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
   
#include "zimpl/mshell.h"
#include "zimpl/ratlptypes.h"
#include "zimpl/numb.h"
#include "zimpl/elem.h"
#include "zimpl/tuple.h"
#include "zimpl/mme.h"
#include "zimpl/set.h"
#include "zimpl/symbol.h"
#include "zimpl/entry.h"
#include "zimpl/idxset.h"
#include "zimpl/rdefpar.h"
#include "zimpl/bound.h"
#include "zimpl/define.h"
#include "zimpl/mono.h"
#include "zimpl/term.h"
#include "zimpl/list.h"
#include "zimpl/stmt.h"
#include "zimpl/local.h"
#include "zimpl/code.h"
#include "zimpl/inst.h"
        
#define YYERROR_VERBOSE 1

/* the function is actually getting a YYSTYPE* as argument, but the
 * type isn't available here, so it is decalred to accept any number of
 * arguments, i.e. yylex() and not yylex(void).
 */
extern int yylex();

/*lint -sem(yyerror, 1p && nulterm(1), r_no) */ 
extern void yyerror(const char* s);
 


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
#line 80 "src/zimpl/mmlparse2.y"
{
   unsigned int bits;
   Numb*        numb;
   const char*  strg;
   const char*  name;
   Symbol*      sym;
   Define*      def;
   CodeNode*    code;
}
/* Line 193 of yacc.c.  */
#line 408 "src/zimpl/mmlparse2.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 421 "src/zimpl/mmlparse2.c"

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
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  126
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  307
/* YYNRULES -- Number of states.  */
#define YYNSTATES  920

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   368

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     121,   122,   116,   114,   120,   115,     2,   123,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   117,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   118,     2,   119,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   124,     2,   125,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    31,    40,    49,    57,    59,    63,
      70,    79,    84,    87,    96,   105,   114,   123,   125,   129,
     139,   148,   154,   156,   158,   160,   161,   164,   174,   181,
     190,   196,   206,   213,   225,   234,   235,   237,   240,   241,
     244,   248,   258,   268,   269,   272,   275,   284,   293,   294,
     297,   298,   301,   303,   307,   309,   312,   315,   319,   323,
     328,   334,   340,   346,   348,   352,   357,   363,   371,   376,
     381,   386,   391,   398,   405,   412,   419,   432,   445,   458,
     471,   484,   497,   510,   523,   536,   549,   562,   575,   588,
     601,   614,   627,   636,   645,   654,   663,   667,   671,   675,
     679,   683,   687,   691,   695,   699,   703,   707,   711,   715,
     719,   723,   727,   731,   735,   739,   743,   747,   750,   754,
     755,   759,   761,   763,   765,   767,   769,   771,   773,   775,
     779,   783,   787,   791,   795,   799,   801,   805,   809,   813,
     817,   819,   822,   825,   827,   831,   836,   839,   844,   849,
     854,   859,   864,   869,   874,   879,   884,   889,   896,   903,
     911,   915,   921,   926,   931,   932,   934,   936,   940,   943,
     946,   949,   952,   955,   960,   962,   964,   970,   974,   976,
     980,   984,   988,   992,   996,  1000,  1002,  1007,  1009,  1013,
    1017,  1022,  1025,  1030,  1033,  1041,  1047,  1055,  1061,  1066,
    1074,  1079,  1087,  1091,  1095,  1099,  1103,  1109,  1115,  1122,
    1127,  1135,  1140,  1143,  1146,  1149,  1152,  1155,  1157,  1161,
    1163,  1167,  1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,
    1203,  1207,  1211,  1215,  1219,  1223,  1226,  1230,  1234,  1239,
    1244,  1252,  1255,  1259,  1260,  1264,  1266,  1270,  1272,  1276,
    1280,  1282,  1286,  1290,  1294,  1298,  1303,  1305,  1308,  1311,
    1313,  1317,  1322,  1327,  1332,  1337,  1342,  1344,  1346,  1348,
    1351,  1354,  1359,  1364,  1367,  1372,  1377,  1382,  1387,  1392,
    1397,  1402,  1407,  1412,  1417,  1422,  1427,  1432,  1437,  1442,
    1447,  1451,  1456,  1465,  1472,  1480,  1489,  1494
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     127,     0,    -1,   128,    -1,   136,    -1,   139,    -1,   149,
      -1,   150,    -1,   162,    -1,   131,    -1,   132,    -1,   133,
      -1,   134,    -1,   165,    -1,     3,   107,    20,   169,   117,
      -1,     3,   107,   118,   167,   119,    20,   169,   117,    -1,
       3,   107,   118,   167,   119,    20,   129,   117,    -1,     3,
     107,   118,   119,    20,   129,   117,    -1,   130,    -1,   129,
     120,   130,    -1,    89,   121,   169,   120,   180,   122,    -1,
      89,   121,   169,   120,   180,   120,   180,   122,    -1,    91,
     121,   169,   122,    -1,   177,   169,    -1,    10,   106,   121,
     135,   122,    20,   180,   117,    -1,    11,   106,   121,   135,
     122,    20,   180,   117,    -1,    12,   106,   121,   135,   122,
      20,   176,   117,    -1,    13,   106,   121,   135,   122,    20,
     169,   117,    -1,   107,    -1,   135,   120,   107,    -1,     4,
     107,   118,   167,   119,    20,   145,   138,   117,    -1,     4,
     107,   118,   167,   119,    20,   180,   117,    -1,     4,   107,
      20,   137,   117,    -1,     4,    -1,   145,    -1,   180,    -1,
      -1,    31,   180,    -1,     5,   107,   118,   167,   119,   140,
     141,   142,   117,    -1,     5,   107,   140,   141,   142,   117,
      -1,     5,   107,   118,   167,   119,    19,    16,   117,    -1,
       5,   107,    19,    16,   117,    -1,     5,   107,   118,   167,
     119,    16,   143,   144,   117,    -1,     5,   107,    16,   143,
     144,   117,    -1,     5,   107,   118,   167,   119,    17,   141,
     142,   143,   144,   117,    -1,     5,   107,    17,   141,   142,
     143,   144,   117,    -1,    -1,    18,    -1,    19,    17,    -1,
      -1,    33,   180,    -1,    33,   115,    38,    -1,    33,    49,
     176,    50,   180,    51,   115,    38,    52,    -1,    33,    49,
     176,    50,   115,    38,    51,   180,    52,    -1,    -1,    32,
     180,    -1,    32,    38,    -1,    32,    49,   176,    50,   180,
      51,    38,    52,    -1,    32,    49,   176,    50,    38,    51,
     180,    52,    -1,    -1,    29,   180,    -1,    -1,    30,   180,
      -1,   146,    -1,   145,   120,   146,    -1,   173,    -1,   147,
     148,    -1,   177,   180,    -1,    22,   179,    22,    -1,   147,
     179,    22,    -1,   148,   147,   179,    22,    -1,     6,   107,
      21,   157,   117,    -1,     7,   107,    21,   157,   117,    -1,
       8,   107,    21,   151,   117,    -1,   152,    -1,   151,    39,
     152,    -1,    27,   167,    21,   151,    -1,    49,   176,    50,
     151,    52,    -1,    49,   176,    50,   151,    51,   151,    52,
      -1,   157,   156,   157,   154,    -1,   157,   156,   180,   154,
      -1,   180,   156,   157,   154,    -1,   180,   156,   180,   154,
      -1,   180,   156,   157,    32,   180,   154,    -1,   180,   156,
     180,    32,   180,   154,    -1,   180,   156,   157,    33,   180,
     154,    -1,   180,   156,   180,    33,   180,   154,    -1,    92,
     153,    50,   157,   156,   157,    51,   157,   156,   157,    52,
     154,    -1,    92,   153,    50,   180,   156,   157,    51,   157,
     156,   157,    52,   154,    -1,    92,   153,    50,   157,   156,
     180,    51,   157,   156,   157,    52,   154,    -1,    92,   153,
      50,   157,   156,   157,    51,   180,   156,   157,    52,   154,
      -1,    92,   153,    50,   157,   156,   157,    51,   157,   156,
     180,    52,   154,    -1,    92,   153,    50,   180,   156,   180,
      51,   157,   156,   157,    52,   154,    -1,    92,   153,    50,
     180,   156,   157,    51,   180,   156,   157,    52,   154,    -1,
      92,   153,    50,   180,   156,   157,    51,   157,   156,   180,
      52,   154,    -1,    92,   153,    50,   157,   156,   180,    51,
     180,   156,   157,    52,   154,    -1,    92,   153,    50,   157,
     156,   180,    51,   157,   156,   180,    52,   154,    -1,    92,
     153,    50,   157,   156,   157,    51,   180,   156,   180,    52,
     154,    -1,    92,   153,    50,   180,   156,   180,    51,   180,
     156,   157,    52,   154,    -1,    92,   153,    50,   180,   156,
     180,    51,   157,   156,   180,    52,   154,    -1,    92,   153,
      50,   180,   156,   157,    51,   180,   156,   180,    52,   154,
      -1,    92,   153,    50,   157,   156,   180,    51,   180,   156,
     180,    52,   154,    -1,    92,   153,    50,   180,   156,   180,
      51,   180,   156,   180,    52,   154,    -1,    92,   153,    50,
     157,   156,   157,    52,   154,    -1,    92,   153,    50,   180,
     156,   157,    52,   154,    -1,    92,   153,    50,   157,   156,
     180,    52,   154,    -1,    92,   153,    50,   180,   156,   180,
      52,   154,    -1,   157,    37,   157,    -1,   180,    37,   157,
      -1,   157,    37,   180,    -1,   157,    34,   157,    -1,   180,
      34,   157,    -1,   157,    34,   180,    -1,   157,    32,   157,
      -1,   180,    32,   157,    -1,   157,    32,   180,    -1,   157,
      33,   157,    -1,   180,    33,   157,    -1,   157,    33,   180,
      -1,   157,    35,   157,    -1,   180,    35,   157,    -1,   157,
      35,   180,    -1,   157,    36,   157,    -1,   180,    36,   157,
      -1,   157,    36,   180,    -1,   153,    39,   153,    -1,   153,
      40,   153,    -1,   153,    41,   153,    -1,    42,   153,    -1,
     121,   153,   122,    -1,    -1,   154,   120,   155,    -1,   110,
      -1,   111,    -1,   112,    -1,   113,    -1,    32,    -1,    33,
      -1,    34,    -1,   158,    -1,   157,   114,   158,    -1,   157,
     115,   158,    -1,   157,   114,   181,    -1,   157,   115,   181,
      -1,   180,   114,   158,    -1,   180,   115,   158,    -1,   159,
      -1,   158,   116,   182,    -1,   158,   123,   182,    -1,   181,
     116,   159,    -1,   158,   116,   159,    -1,   160,    -1,   114,
     159,    -1,   115,   159,    -1,   161,    -1,   161,    61,   182,
      -1,    43,   167,    21,   158,    -1,   100,   178,    -1,    93,
     121,   157,   122,    -1,    74,   121,   157,   122,    -1,    71,
     121,   157,   122,    -1,    73,   121,   157,   122,    -1,    72,
     121,   157,   122,    -1,    75,   121,   157,   122,    -1,    76,
     121,   157,   122,    -1,    77,   121,   157,   122,    -1,    69,
     121,   157,   122,    -1,    70,   121,   157,   122,    -1,    81,
     121,   157,   120,   180,   122,    -1,    82,   121,   157,   120,
     180,   122,    -1,    49,   176,    50,   157,    51,   157,    52,
      -1,   121,   157,   122,    -1,     9,   107,    21,   163,   117,
      -1,   164,   143,    21,   157,    -1,    27,   167,    21,   163,
      -1,    -1,    94,    -1,    95,    -1,    21,   166,   117,    -1,
      14,   179,    -1,    14,   177,    -1,    14,   169,    -1,    14,
     100,    -1,    15,   176,    -1,    27,   167,    21,   166,    -1,
     168,    -1,   169,    -1,   177,    23,   169,    22,   176,    -1,
     177,    23,   169,    -1,   170,    -1,   169,    54,   170,    -1,
     169,   114,   170,    -1,   169,    56,   170,    -1,   169,   115,
     170,    -1,   169,    57,   170,    -1,   169,    53,   170,    -1,
     171,    -1,    54,   167,    21,   171,    -1,   172,    -1,   171,
      55,   172,    -1,   171,   116,   172,    -1,    53,   167,    21,
     172,    -1,   101,   178,    -1,   105,   121,   179,   122,    -1,
     124,   125,    -1,   124,   180,    24,   180,    26,   180,   125,
      -1,   124,   180,    24,   180,   125,    -1,   124,   180,    25,
     180,    26,   180,   125,    -1,   124,   180,    25,   180,   125,
      -1,    46,   167,    21,   180,    -1,    46,   121,   180,   122,
     167,    21,   180,    -1,    47,   167,    21,   180,    -1,    47,
     121,   180,   122,   167,    21,   180,    -1,   121,   169,   122,
      -1,   124,   175,   125,    -1,   124,   179,   125,    -1,   124,
     167,   125,    -1,   124,   167,    21,   180,   125,    -1,   124,
     167,    21,   177,   125,    -1,    58,   121,   169,   120,   177,
     122,    -1,    90,   121,   101,   122,    -1,    49,   176,    50,
     169,    51,   169,    52,    -1,    83,   180,    84,   180,    -1,
     173,   174,    -1,    85,   180,    -1,    86,   180,    -1,    87,
     180,    -1,    88,   180,    -1,   177,    -1,   175,   120,   177,
      -1,   173,    -1,   180,    34,   180,    -1,   180,    37,   180,
      -1,   180,    36,   180,    -1,   180,    33,   180,    -1,   180,
      35,   180,    -1,   180,    32,   180,    -1,   169,    34,   169,
      -1,   169,    37,   169,    -1,   169,    36,   169,    -1,   169,
      33,   169,    -1,   169,    35,   169,    -1,   169,    32,   169,
      -1,   176,    39,   176,    -1,   176,    40,   176,    -1,   176,
      41,   176,    -1,    42,   176,    -1,   121,   176,   122,    -1,
     177,    23,   169,    -1,    28,   121,   167,   122,    -1,   104,
     121,   179,   122,    -1,    49,   176,    50,   176,    51,   176,
      52,    -1,    35,    36,    -1,    35,   179,    36,    -1,    -1,
     118,   179,   119,    -1,   180,    -1,   179,   120,   180,    -1,
     181,    -1,   180,   114,   181,    -1,   180,   115,   181,    -1,
     182,    -1,   181,   116,   182,    -1,   181,   123,   182,    -1,
     181,    59,   182,    -1,   181,    60,   182,    -1,    48,   167,
      21,   182,    -1,   183,    -1,   114,   183,    -1,   115,   183,
      -1,   184,    -1,   184,    61,   182,    -1,    43,   167,    21,
     181,    -1,    44,   168,    21,   182,    -1,    45,   168,    21,
     182,    -1,    44,   121,   167,   122,    -1,    45,   121,   167,
     122,    -1,   109,    -1,   108,    -1,   107,    -1,    98,   178,
      -1,    99,   178,    -1,   102,   121,   179,   122,    -1,   103,
     121,   179,   122,    -1,   184,    62,    -1,    63,   121,   169,
     122,    -1,    69,   121,   180,   122,    -1,    70,   121,   180,
     122,    -1,    64,   121,   180,   122,    -1,    65,   121,   180,
     122,    -1,    66,   121,   180,   122,    -1,    71,   121,   180,
     122,    -1,    72,   121,   180,   122,    -1,    73,   121,   180,
     122,    -1,    74,   121,   180,   122,    -1,    75,   121,   180,
     122,    -1,    76,   121,   180,   122,    -1,    77,   121,   180,
     122,    -1,    78,   121,   180,   122,    -1,    79,   121,   180,
     122,    -1,    80,   121,   180,   122,    -1,   121,   180,   122,
      -1,    96,   121,   180,   122,    -1,    97,   121,   180,   120,
     180,   120,   180,   122,    -1,    67,   121,   180,   120,   180,
     122,    -1,    49,   176,    50,   180,    51,   180,    52,    -1,
      68,   121,   169,   120,   180,   120,   180,   122,    -1,    44,
     121,   179,   122,    -1,    45,   121,   179,   122,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   149,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   167,   174,   180,   186,   196,   197,   200,
     203,   206,   212,   221,   230,   239,   248,   257,   260,   270,
     273,   276,   283,   286,   287,   294,   295,   303,   310,   319,
     329,   340,   349,   359,   363,   373,   374,   375,   379,   382,
     383,   384,   389,   397,   398,   399,   400,   405,   413,   414,
     418,   419,   427,   428,   431,   432,   436,   440,   444,   447,
     459,   462,   472,   478,   481,   484,   489,   494,   502,   505,
     510,   515,   522,   526,   531,   535,   541,   544,   549,   554,
     559,   563,   570,   577,   583,   589,   595,   600,   608,   617,
     626,   634,   645,   648,   652,   657,   665,   666,   669,   672,
     673,   676,   679,   680,   683,   686,   687,   690,   693,   694,
     697,   700,   701,   704,   707,   708,   709,   710,   711,   715,
     716,   720,   721,   722,   723,   727,   728,   729,   733,   734,
     735,   736,   737,   740,   741,   749,   750,   751,   755,   756,
     760,   761,   762,   768,   769,   772,   778,   781,   782,   783,
     784,   785,   786,   787,   788,   789,   790,   791,   794,   797,
     800,   808,   814,   817,   823,   824,   825,   833,   837,   838,
     839,   840,   841,   842,   852,   853,   860,   863,   869,   870,
     871,   874,   875,   878,   879,   882,   883,   887,   888,   889,
     892,   896,   899,   904,   905,   908,   911,   914,   917,   920,
     923,   926,   929,   930,   931,   932,   933,   934,   935,   938,
     941,   947,   948,   952,   953,   954,   955,   959,   962,   965,
     969,   970,   971,   972,   973,   974,   975,   976,   977,   978,
     979,   980,   981,   982,   983,   984,   985,   986,   987,   988,
     993,   999,  1000,  1004,  1007,  1013,  1016,  1022,  1023,  1024,
    1028,  1029,  1030,  1031,  1032,  1033,  1039,  1040,  1041,  1045,
    1046,  1047,  1050,  1053,  1056,  1059,  1065,  1066,  1067,  1070,
    1073,  1076,  1081,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1104,  1105,  1106,  1109,  1112,  1115,  1118,  1121
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLSET", "DECLPAR", "DECLVAR",
  "DECLMIN", "DECLMAX", "DECLSUB", "DECLSOS", "DEFNUMB", "DEFSTRG",
  "DEFBOOL", "DEFSET", "PRINT", "CHECK", "BINARY", "INTEGER", "REAL",
  "IMPLICIT", "ASGN", "DO", "WITH", "IN", "TO", "UNTIL", "BY", "FORALL",
  "EXISTS", "PRIORITY", "STARTVAL", "DEFAULT", "CMP_LE", "CMP_GE",
  "CMP_EQ", "CMP_LT", "CMP_GT", "CMP_NE", "INFTY", "AND", "OR", "XOR",
  "NOT", "SUM", "MIN", "MAX", "ARGMIN", "ARGMAX", "PROD", "IF", "THEN",
  "ELSE", "END", "INTER", "UNION", "CROSS", "SYMDIFF", "WITHOUT", "PROJ",
  "MOD", "DIV", "POW", "FAC", "CARD", "ROUND", "FLOOR", "CEIL", "RANDOM",
  "ORD", "ABS", "SGN", "LOG", "LN", "EXP", "SQRT", "SIN", "COS", "TAN",
  "ASIN", "ACOS", "ATAN", "POWER", "SGNPOW", "READ", "AS", "SKIP", "USE",
  "COMMENT", "MATCH", "SUBSETS", "INDEXSET", "POWERSET", "VIF", "VABS",
  "TYPE1", "TYPE2", "LENGTH", "SUBSTR", "NUMBSYM", "STRGSYM", "VARSYM",
  "SETSYM", "NUMBDEF", "STRGDEF", "BOOLDEF", "SETDEF", "DEFNAME", "NAME",
  "STRG", "NUMB", "SCALE", "SEPARATE", "CHECKONLY", "INDICATOR", "'+'",
  "'-'", "'*'", "';'", "'['", "']'", "','", "'('", "')'", "'/'", "'{'",
  "'}'", "$accept", "stmt", "decl_set", "set_entry_list", "set_entry",
  "def_numb", "def_strg", "def_bool", "def_set", "name_list", "decl_par",
  "par_singleton", "par_default", "decl_var", "var_type", "lower", "upper",
  "priority", "startval", "cexpr_entry_list", "cexpr_entry", "matrix_head",
  "matrix_body", "decl_obj", "decl_sub", "constraint_list", "constraint",
  "vbool", "con_attr_list", "con_attr", "con_type", "vexpr", "vproduct",
  "vfactor", "vexpo", "vval", "decl_sos", "soset", "sos_type", "exec_do",
  "command", "idxset", "pure_idxset", "sexpr", "sunion", "sproduct",
  "sval", "read", "read_par", "tuple_list", "lexpr", "tuple", "symidx",
  "cexpr_list", "cexpr", "cproduct", "cfactor", "cexpo", "cval", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,    43,    45,    42,    59,    91,    93,
      44,    40,    41,    47,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   128,   128,   128,   129,   129,   129,
     129,   129,   130,   131,   132,   133,   134,   135,   135,   136,
     136,   136,   136,   137,   137,   138,   138,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   140,   140,   141,   141,
     141,   141,   141,   142,   142,   142,   142,   142,   143,   143,
     144,   144,   145,   145,   145,   145,   146,   147,   148,   148,
     149,   149,   150,   151,   151,   151,   151,   151,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   154,
     154,   155,   155,   155,   155,   156,   156,   156,   157,   157,
     157,   157,   157,   157,   157,   158,   158,   158,   158,   158,
     159,   159,   159,   160,   160,   160,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   161,   161,   161,
     161,   162,   163,   163,   164,   164,   164,   165,   166,   166,
     166,   166,   166,   166,   167,   167,   168,   168,   169,   169,
     169,   169,   169,   169,   169,   170,   170,   171,   171,   171,
     171,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   173,   173,   174,   174,   174,   174,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   177,   177,   178,   178,   179,   179,   180,   180,   180,
     181,   181,   181,   181,   181,   181,   182,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     8,     8,     7,     1,     3,     6,
       8,     4,     2,     8,     8,     8,     8,     1,     3,     9,
       8,     5,     1,     1,     1,     0,     2,     9,     6,     8,
       5,     9,     6,    11,     8,     0,     1,     2,     0,     2,
       3,     9,     9,     0,     2,     2,     8,     8,     0,     2,
       0,     2,     1,     3,     1,     2,     2,     3,     3,     4,
       5,     5,     5,     1,     3,     4,     5,     7,     4,     4,
       4,     4,     6,     6,     6,     6,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,     8,     8,     8,     8,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       1,     2,     2,     1,     3,     4,     2,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     6,     6,     7,
       3,     5,     4,     4,     0,     1,     1,     3,     2,     2,
       2,     2,     2,     4,     1,     1,     5,     3,     1,     3,
       3,     3,     3,     3,     3,     1,     4,     1,     3,     3,
       4,     2,     4,     2,     7,     5,     7,     5,     4,     7,
       4,     7,     3,     3,     3,     3,     5,     5,     6,     4,
       7,     4,     2,     2,     2,     2,     2,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     4,     4,
       7,     2,     3,     0,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     4,     1,     2,     2,     1,
       3,     4,     4,     4,     4,     4,     1,     1,     1,     2,
       2,     4,     4,     2,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     4,     8,     6,     7,     8,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     8,     9,    10,    11,     3,
       4,     5,     6,     7,    12,     0,     0,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,     0,    58,    48,    46,     0,     0,
      48,     0,     0,     0,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   253,   253,   181,   253,     0,     0,     0,   278,   277,
     276,     0,     0,     0,     0,   180,   188,   195,   197,   179,
     178,   255,   257,   260,   266,   269,     0,     0,     0,     0,
       0,     0,   182,     0,     0,     0,     0,     0,   184,   185,
       0,   177,     0,     0,     0,     0,     0,     0,     0,     0,
      33,    62,     0,    64,     0,    34,     0,     0,    60,     0,
      53,     0,    47,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,   138,   145,   150,   153,     0,   257,
       0,     0,     0,     0,     0,    73,     0,     0,     0,   175,
     176,     0,    58,    27,     0,     0,     0,     0,   251,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   279,   280,   201,     0,
       0,     0,   267,   268,     0,     0,   203,     0,   229,     0,
     227,     0,   255,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   283,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,     0,     0,     0,
       0,     0,    31,     0,     0,    65,     0,     0,     0,     0,
     222,    66,     0,    59,     0,     0,     0,     0,    49,     0,
      58,    40,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   156,     0,
       0,   151,   152,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,    72,   135,   136,   137,     0,     0,     0,
     171,     0,     0,     0,     0,     0,     0,   252,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   212,
     300,     0,   215,     0,   213,   214,     0,     0,   194,   189,
     191,   193,   190,   192,   198,   199,   256,   258,   259,   263,
     264,   261,   262,   270,     0,     0,     0,   246,   241,   239,
     236,   240,   238,   237,   242,   243,   244,   247,   235,   233,
     230,   234,   232,   231,     0,   183,   187,     0,     0,     0,
      17,     0,     0,    67,     0,     0,    63,     0,     0,   223,
     224,   225,   226,     0,    61,    42,     0,    50,    55,     0,
      54,    60,    58,    48,     0,    48,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   139,   141,   140,   142,   149,   146,   147,
     154,   143,   258,   144,   259,   148,     0,     0,   127,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    74,   129,
     129,   129,   129,   174,     0,    28,     0,     0,     0,     0,
     271,   274,   306,   272,   275,   307,   273,     0,   208,     0,
     210,   265,     0,     0,   200,   196,     0,   284,   287,   288,
     289,     0,     0,   285,   286,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   219,   301,     0,   254,   281,
     282,   202,     0,     0,   228,     0,     0,   248,     0,     0,
       0,   249,     0,     0,     0,    16,     0,    22,     0,     0,
     221,    68,     0,    35,     0,     0,     0,     0,    60,    53,
       0,    53,   155,   271,     0,     0,   165,   166,   159,   161,
     160,   158,   162,   163,   164,     0,     0,   157,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,   128,   124,   125,   126,     0,     0,   112,
     114,   115,   117,   109,   111,   118,   120,   121,   123,   106,
     108,   113,   116,   110,   119,   122,   107,    78,    79,     0,
       0,    80,     0,     0,    81,   173,   172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   217,
     216,     0,   205,     0,   207,     0,   186,     0,     0,    18,
      15,    14,    69,     0,     0,    30,     0,     0,     0,    44,
       0,    58,    39,     0,     0,     0,     0,     0,     0,     0,
      76,     0,     0,     0,   129,   129,   129,   129,    23,    24,
      25,    26,     0,     0,     0,     0,   218,   303,     0,     0,
       0,     0,     0,     0,    21,    36,    29,     0,     0,     0,
       0,    41,    60,    37,     0,   167,   168,     0,     0,     0,
       0,     0,     0,   131,   132,   133,   134,   130,    82,    84,
      83,    85,   209,   211,   220,   304,     0,     0,   204,   206,
     250,     0,     0,     0,     0,     0,     0,   169,    77,     0,
     129,     0,   129,     0,   129,     0,   129,   305,   302,     0,
      19,     0,     0,     0,     0,    43,     0,     0,   102,     0,
       0,   104,     0,     0,   103,     0,     0,   105,     0,    52,
      51,    57,    56,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,    86,    90,    89,    96,    88,    95,
      94,   100,    87,    93,    92,    99,    91,    98,    97,   101
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,   469,   470,    15,    16,    17,    18,   194,
      19,   139,   744,    20,    50,   150,   320,   148,   315,   140,
     141,   142,   305,    21,    22,   184,   185,   359,   707,   807,
     367,   360,   174,   175,   176,   177,    23,   191,   192,    24,
      39,   127,   128,   129,   106,   107,   108,   143,   310,   249,
     122,   130,   236,   110,   178,   112,   113,   114,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -522
static const yytype_int16 yypact[] =
{
    1403,   -85,   -38,   -32,   -24,    -9,    -1,    37,   -16,    56,
      62,    77,    65,   154,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,     4,    11,    27,   181,   185,
     215,   219,   136,   182,   190,   222,  1765,  1518,   865,   208,
    -522,  1281,   522,  1413,   865,   307,   316,  -522,   587,   865,
     316,  2608,  2608,  1601,    32,   250,   250,   250,   250,  1997,
     865,    30,    39,   918,  1052,   865,  1518,   865,   865,   239,
     263,   267,   281,   297,   301,   309,   315,   334,   352,   363,
     391,   393,   446,   458,   469,   513,   521,   554,   561,   564,
     575,   332,   332,  -522,   332,   583,   592,   601,  -522,  -522,
    -522,  3124,  3124,  2404,  1682,  1111,  -522,    15,  -522,  -522,
     537,   556,   333,  -522,  -522,   745,   607,  1518,  1518,   611,
    1518,   630,   958,   712,   364,  1518,  1281,   728,  -522,  1111,
     740,  -522,   708,   753,   649,  2798,  1518,  2798,  2798,   661,
     680,  -522,   759,   992,  2798,   556,   697,  2798,   789,  2866,
     792,   736,  -522,   739,   792,   865,  1518,   754,   758,   760,
     783,   787,   831,   837,   839,   852,   861,   862,   870,   332,
    2669,  2669,  2608,   668,     0,  -522,  -522,   893,   624,   344,
     817,   865,  1518,  2472,     8,  -522,   144,   268,   865,  -522,
    -522,   796,   307,  -522,   106,   233,   251,   339,  -522,   -17,
     972,  1847,   995,  1847,   997,  2404,  1000,  2404,  1005,  1011,
     639,  1012,  1017,  1281,  1281,  2798,  2798,  2798,  2798,  1281,
    2798,  2798,  2798,  2798,  2798,  2798,  2798,  2798,  2798,  2798,
    2798,  2798,   943,  2798,  2798,  2798,  -522,  -522,  -522,  2798,
    2798,  2798,  -522,  -522,   579,   326,  -522,   -11,   992,    90,
     740,   149,    25,  1281,  1281,  1281,  1281,  1281,  1281,  1042,
    1042,  2798,  2798,  2798,  3063,  3063,  3063,  3063,  3063,  -522,
     865,  -522,   833,  2798,   305,    21,    20,  1281,  1281,  1281,
    1281,  1281,  1281,  1518,  1518,  1518,  1281,  2798,  2798,  2798,
    2798,  2798,  2798,   866,    65,  1281,  -522,   386,  1030,    13,
     940,   -21,  -522,  1022,  2798,   759,  2798,  2798,  2798,  2798,
    -522,   556,  1039,   556,  2798,   965,  1518,  1179,   556,  2065,
     307,  -522,  1401,   967,  1069,   955,  2608,  2608,  2608,  2608,
    2608,  2608,  2608,  2608,  2608,  2608,  2608,  2608,  -522,  1236,
    1236,  -522,  -522,   737,   811,  2608,  2608,  -522,  2730,  3063,
    3063,  2608,  2608,  2730,  -522,  1071,   962,  2472,  2472,  1008,
     496,   502,  2540,  -522,  -522,  -522,  -522,  2608,  2608,  1075,
    -522,  1091,  1007,  1087,  1095,  1096,  1110,  -522,  2798,  1009,
     346,  3063,  1018,   381,  3063,   813,  2798,   847,  2798,  3063,
    2404,  1042,   910,   748,   652,   895,   915,   989,    97,   921,
    1055,  1086,  1089,  1105,  1150,  1169,  1175,  1180,  1200,  1211,
    1231,  1233,  1019,  1244,   213,   750,   467,   532,   578,  -522,
    -522,  1929,  -522,  1022,  -522,  -522,  2798,  2798,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,   556,   333,   333,  -522,
    -522,  -522,  -522,  -522,  1034,  1518,   676,  -522,  1111,  1111,
    1111,  1111,  1111,  1111,  -522,  1100,  1100,  1111,   556,   556,
     556,   556,   556,   556,  1281,  -522,    99,  1023,  1037,   162,
    -522,  1281,   548,  -522,  2798,  2798,  -522,    18,  2798,   556,
     556,   556,   556,  1413,   556,  -522,  1121,  -522,  -522,  1518,
     556,   789,   307,   316,   848,   316,  -522,  2608,  2608,  1246,
    1248,  1266,  1270,  1319,  1322,  1324,  1328,  1337,  1349,  1353,
    1380,  1385,  1391,  1404,  1409,  1415,  1418,   485,   511,  1421,
     865,  1518,  1051,  1053,  1054,  1057,  1073,  1076,  1084,  1093,
    1108,  2608,  -522,     0,   344,     0,   344,  -522,  -522,  -522,
    -522,     0,   344,     0,   344,  -522,  1601,  1601,  -522,   324,
     252,   343,  2472,  2472,  2472,  2608,  2608,  2608,  2608,  2608,
    2608,  2608,  2608,  2608,  2608,  2608,  2608,  2608,  -522,   771,
     624,    86,   384,    32,  2608,  -522,  2798,  2798,  1518,  1281,
     333,  -522,  -522,  -522,  -522,  -522,  -522,   865,   556,   865,
     556,  -522,   971,   199,  -522,    15,  1022,  -522,  -522,  -522,
    -522,  2798,  2798,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  2798,  -522,  -522,
    -522,  -522,  1085,   105,  -522,   -18,   -10,  -522,   378,   533,
     209,  -522,  1518,  1281,  1281,  -522,  1022,  1111,   192,  1081,
     556,  -522,    29,    17,  1101,  2934,  1149,  1104,   789,   792,
    1113,   792,     0,   344,   357,   382,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  2798,  2798,  -522,  1210,  1152,
    2608,  2608,  2608,  2608,  2608,  2608,  2608,  2608,  2608,  1202,
     295,    44,   230,  -522,  -522,  1230,  1230,   144,   268,   771,
     624,   771,   624,   771,   624,   771,   624,   771,   624,   771,
     624,   771,   771,   771,   771,   771,   771,  1153,  1153,  2798,
    2798,  1153,  2798,  2798,  1153,  -522,   771,  1184,  1250,    47,
    1092,  1271,  1275,  1281,  2798,  1181,  1427,   655,   706,  -522,
    -522,  2798,  -522,  2798,  -522,  1518,   958,   931,   662,  -522,
    -522,  -522,  -522,  2798,  1187,  -522,  2268,   394,  2133,  -522,
    1214,   307,  -522,  1215,  2608,  1430,  1436,  2608,  2608,  1601,
    -522,  2608,  2608,  1524,   556,   556,   556,   556,  -522,  -522,
    -522,  -522,  2798,  2798,  1098,   376,  -522,  -522,  2798,  2798,
     204,   380,   329,  2798,  -522,   556,  -522,  1268,  3002,  1286,
     429,  -522,   789,  -522,   463,  -522,  -522,   344,   157,   355,
     372,   392,   412,  -522,  -522,  -522,  -522,  -522,  1153,  1153,
    1153,  1153,   556,   556,  -522,  -522,  1455,  1485,  -522,  -522,
    -522,   795,  2798,  2335,  2798,  2201,  1224,  -522,  -522,  2608,
    -522,  2608,  -522,  2608,  -522,  2608,  -522,  -522,  -522,  2798,
    -522,   493,  1291,   507,  1297,  -522,   144,   268,  1153,   144,
     268,  1153,   144,   268,  1153,   144,   268,  1153,  1488,  -522,
    -522,  -522,  -522,  2608,  2608,  2608,  2608,  2608,  2608,  2608,
    2608,  -522,   530,   536,   541,   546,   576,   588,   596,   606,
     616,   665,   677,   694,   696,   703,   735,   742,  -522,  -522,
    -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,  -522,
    -522,  -522,  -522,  -522,  1153,  1153,  1153,  1153,  1153,  1153,
    1153,  1153,  1153,  1153,  1153,  1153,  1153,  1153,  1153,  1153
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -522,  -522,  -522,   880,   718,  -522,  -522,  -522,  -522,   996,
    -522,  -522,  -522,  -522,  1047,   -41,  -149,  -188,  -485,   873,
    1080,  -130,  -522,  -522,  -522,  -521,  1025,  -330,    48,  -522,
     -96,   562,  -331,  -132,  -522,  -522,  -522,   816,  -522,  -522,
    1102,   -31,   860,   269,  1398,   998,  -218,  1290,  -522,  -522,
      -8,   977,   -28,    26,   -36,   509,   -33,   -99,  -522
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     111,   124,   242,   243,   371,   323,   647,   145,   731,   154,
     421,   134,   304,   146,   533,   535,   733,   187,   153,   377,
     541,   543,    25,   111,    41,   679,   680,   548,   549,   200,
     124,    43,   206,   208,   209,   473,   211,   212,   341,   342,
     641,   434,   435,    45,    46,    47,    48,   362,   743,   426,
     427,   742,   287,   288,   289,   290,   291,   292,   210,   188,
     283,   284,   285,   475,   237,    59,   238,   245,   252,    26,
     259,   242,   243,   247,    59,    27,   364,   365,   366,    36,
      37,   124,   124,    28,   276,   199,   283,   284,   285,   124,
      32,   368,    38,   262,   263,   754,   262,   263,    29,   111,
     124,   301,   245,   261,   262,   263,    30,   732,   311,   271,
     272,   313,   275,   318,   422,   734,   348,   293,   709,   710,
     124,   632,    42,   349,   324,   363,   189,   190,   300,    44,
     251,   260,   491,   261,   262,   263,   344,   303,   261,   262,
     263,   338,   420,   447,    31,    49,   124,   361,   325,   261,
     355,   201,   253,   254,    40,   255,   256,   369,   345,   346,
     203,   299,    33,   750,   770,   111,   652,   111,    34,   385,
     379,   387,   382,   594,   356,   478,   364,   365,   366,   395,
     396,   397,   398,    35,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   362,   413,   414,   111,
     345,   346,    51,   111,   111,   111,    52,   341,   342,   828,
     423,   262,   263,   257,   258,   424,   537,   601,   243,   262,
     263,   545,   684,   685,   686,   436,   372,   380,   373,   383,
     730,   439,   440,   441,   442,   443,    53,   111,   798,   444,
      54,   287,   288,   289,   290,   291,   292,   124,   124,   124,
     724,   458,   459,   460,   461,   462,   463,    55,   345,   346,
     724,   415,   364,   365,   366,   416,   417,   418,   111,   261,
     479,   480,   481,   482,   425,   454,   455,   456,   484,   635,
     124,   724,   636,   490,   556,   557,   558,   559,   560,   561,
     500,   502,   504,   506,   508,   510,   512,   514,   516,   446,
     364,   365,   366,    56,   648,   105,   121,   826,   486,   740,
     132,    57,   636,   262,   263,   538,   539,   540,   262,   263,
     441,   361,   551,   262,   263,   131,   187,   262,   263,   818,
     477,   570,   572,   617,   362,   121,   147,   277,   278,   279,
     280,   281,   282,    58,   351,   352,   759,   760,   583,   149,
     588,   586,   590,   372,   593,   374,   591,   193,   253,   254,
     213,   255,   256,   552,   553,   554,   345,   346,   283,   284,
     285,   372,   244,   375,   532,   562,   563,   564,   565,   566,
     567,   820,   351,   352,   214,   623,   121,   121,   215,   274,
     625,   626,   264,   265,   121,   244,   287,   288,   289,   290,
     291,   292,   216,   264,   265,   121,   829,   830,   754,   630,
     277,   278,   279,   280,   281,   282,   712,   713,   217,   257,
     258,    59,   218,   831,   832,   121,   652,   419,   815,   723,
     219,   253,   254,   724,   255,   256,   220,   629,   593,   640,
     262,   263,   111,   833,   834,   788,   683,   644,   420,   266,
     235,   121,   649,   124,   651,   221,   267,   351,   352,   372,
     353,   376,   655,   835,   836,   420,   261,   267,   582,   345,
     346,   345,   346,   222,   244,   467,   244,   468,   262,   263,
     825,   646,   393,   394,   223,   124,   351,   352,   399,   668,
     262,   263,   257,   258,   262,   263,   351,   352,   351,   352,
     751,   261,   753,   585,   642,   819,   345,   346,   262,   263,
     187,   682,   224,   669,   225,   827,   361,   361,   361,   688,
     690,   692,   694,   696,   698,   700,   351,   352,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     717,   718,   124,   262,   263,   859,   448,   449,   450,   451,
     452,   453,   121,   121,   121,   457,   721,    59,   722,   861,
     179,   179,   179,   792,   466,   726,   727,   226,    63,    64,
     719,   125,   283,   284,   285,    67,    68,   345,   346,   227,
      69,   728,   888,    59,   735,   121,   368,   261,   889,   619,
     228,   761,   762,   890,    63,    64,   124,   125,   891,   345,
     346,    67,    68,   151,   152,   665,    69,   262,   263,   747,
     345,   346,    88,   173,   180,   186,   351,   352,   708,   711,
     714,   262,   263,    94,   736,   345,   346,    97,   892,   755,
     756,   666,   253,   254,   229,   255,   256,   467,    88,   468,
     893,   133,   230,   126,   345,   346,   104,   243,   894,    94,
     351,   352,   261,    97,   620,   345,   346,   261,   895,   592,
     351,   352,   277,   278,   279,   280,   281,   282,   896,   126,
     262,   263,   104,   764,   765,   231,   766,   767,   283,   284,
     285,   179,   232,   253,   254,   233,   255,   256,   775,   390,
     345,   346,   179,   257,   258,   780,   234,   781,   261,   124,
     621,   419,   351,   352,   239,   253,   254,   785,   255,   256,
     345,   346,   790,   240,   628,   253,   254,   897,   255,   256,
     351,   352,   241,   187,   243,   800,   802,   782,   270,   898,
     345,   346,   273,   592,   343,   286,   812,   813,   351,   352,
     637,   639,   816,   817,   257,   258,   899,   821,   900,   294,
     863,   864,   775,   865,   866,   901,   867,   868,   121,   869,
     870,   253,   254,   295,   255,   256,   257,   258,   298,   262,
     263,   437,   438,   297,   597,   778,   257,   258,   302,   351,
     352,   135,   345,   346,   784,   347,   841,   902,   843,   775,
     121,   345,   346,   847,   903,   850,   261,   853,   631,   856,
     303,   253,   254,   858,   255,   256,   268,   269,   351,   352,
     345,   346,   808,   809,   810,   811,   312,   351,   352,   314,
     262,   263,   257,   258,   319,   296,   779,   873,   875,   877,
     879,   881,   883,   885,   887,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   121,   720,   345,
     346,   345,   346,   321,   534,   536,   351,   352,   322,   532,
     542,   544,   257,   258,   650,   152,   179,   179,   596,   618,
     261,   179,   283,   284,   285,   326,   179,   179,   848,   327,
     851,   328,   854,   445,   857,   345,   346,   580,   499,   501,
     503,   505,   507,   509,   511,   513,   515,   517,   518,   519,
      59,   121,   737,   738,   329,   283,   284,   285,   330,   262,
     263,    63,    64,   370,   125,   839,   464,   840,    67,    68,
     550,   202,   204,    69,   186,   351,   352,   262,   263,   569,
     571,   345,   346,   420,   354,   587,   904,   905,   906,   907,
     908,   909,   910,   911,   912,   913,   914,   915,   916,   917,
     918,   919,   331,    59,   350,    88,    63,    64,   332,   125,
     333,   262,   263,    67,    63,    64,    94,   125,    69,   589,
      97,    67,    68,   334,   253,   254,    69,   255,   256,   283,
     284,   285,   335,   336,   253,   254,   126,   255,   256,   104,
     474,   337,   774,   378,   283,   284,   285,   283,   284,   285,
      88,   283,   284,   285,   121,   498,   653,   179,    88,   262,
     263,    94,   547,   109,   123,    97,   381,   598,   384,    94,
     144,   386,   723,    97,   253,   254,   388,   255,   256,   262,
     263,   126,   389,   391,   104,   257,   258,   599,   392,   205,
     179,   602,   104,   123,   412,   257,   258,   552,   553,   554,
     472,   783,   195,   196,   197,   179,   179,    59,   555,   483,
     654,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   306,   307,   308,
     309,   250,   485,   179,   496,   257,   258,    59,    63,    64,
     497,   125,   546,   343,   123,   123,   573,   123,    63,    64,
      69,   125,   123,   262,   263,    67,    68,   576,   186,   681,
      69,   600,   574,   123,   575,   577,   578,   687,   689,   691,
     693,   695,   697,   699,   701,   702,   703,   704,   705,   706,
     579,   581,    88,   123,   253,   254,   716,   255,   256,   283,
     584,   615,    88,    94,   633,   253,   254,    97,   255,   256,
     814,   253,   254,    94,   255,   256,   627,    97,   634,   123,
     283,   284,   285,   126,   253,   254,   104,   255,   256,   262,
     263,   645,   670,   207,   671,   672,   104,   603,   673,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   283,   284,
     285,   283,   284,   285,   674,   257,   258,   675,   741,   748,
     262,   263,   758,   262,   263,   676,   257,   258,   604,   771,
     729,   605,   257,   258,   677,   262,   263,   487,   745,   262,
     263,   749,    60,    61,    62,   257,   258,   606,   136,   678,
     752,   757,   499,   501,   503,   505,   507,   509,   511,   513,
     515,   362,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
     123,   123,   123,   179,   262,   263,   797,   179,   179,   552,
     179,   179,   607,   763,   471,    89,    90,    91,    92,   520,
     144,    95,    96,   262,   263,   521,    98,    99,   100,   262,
     263,   608,   772,   123,   262,   263,   773,   609,   262,   263,
     138,   768,   610,   776,   786,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   262,   263,   794,   166,   167,   822,
     654,   186,   611,   799,   801,   262,   263,    63,    64,   168,
     125,   791,   793,   612,    67,    68,   169,   824,   179,    69,
     179,   845,   179,   860,   179,   262,   263,   262,   263,   862,
     339,   340,   638,   613,   739,   614,   643,   531,   262,   263,
     345,   346,   351,   352,   262,   263,   616,   769,   656,   495,
     603,    88,   179,   179,   179,   179,   179,   179,   179,   179,
     345,   346,    94,   476,   351,   352,    97,   568,   657,   715,
     595,   846,   604,   849,   248,   852,   465,   855,   622,     0,
     624,     0,   126,     0,     0,   104,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,   492,   493,    47,
     494,     0,   123,     0,    12,   872,   874,   876,   878,   880,
     882,   884,   886,   345,   346,   135,   351,   352,   345,   346,
       0,   658,   351,   352,   605,     0,   659,     0,    59,   471,
     606,   345,   346,     0,     0,     0,    60,    61,    62,   660,
     144,    65,   136,   351,   352,     0,   123,   345,   346,     0,
       0,   607,     0,     0,     0,   661,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,   351,   352,   137,     0,   123,   345,
     346,     0,   608,     0,     0,   351,   352,   662,     0,    89,
      90,    91,    92,   609,     0,    95,    96,     0,   345,   346,
      98,    99,   100,   351,   352,     0,   663,   101,   102,   345,
     346,   610,   351,   352,   138,   345,   346,   664,     0,     0,
     611,   262,   263,   667,   262,   263,   116,     0,     0,   777,
     262,   263,   795,    59,     0,   123,     0,     0,   796,     0,
     117,    60,    61,    62,    63,    64,    65,   118,     0,   262,
     263,    67,    68,   725,     0,     0,    69,   837,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   262,
     263,     0,   262,   263,     0,     0,     0,   838,    88,   123,
     871,     0,     0,   471,    89,    90,    91,    92,     0,    94,
      95,    96,   119,    97,     0,    98,    99,   100,   181,     0,
       0,     0,   101,   102,   803,   804,   805,   806,     0,   120,
       0,     0,   104,     0,   155,    61,    62,     0,     0,    65,
     182,   428,   429,   430,   431,   432,   433,     0,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    85,
      86,    87,   166,   167,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   183,   168,     0,     0,    89,    90,    91,
      92,   169,     0,    95,    96,     0,     0,     0,    98,    99,
     100,     0,   123,     0,     0,   170,   171,    59,     0,     0,
       0,     0,   172,     0,     0,    60,    61,    62,    63,    64,
      65,    66,     0,     0,     0,    67,    68,     0,     0,     0,
      69,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,     0,   137,     0,     0,     0,     0,
       0,     0,    88,     0,     0,     0,     0,     0,    89,    90,
      91,    92,     0,    94,    95,    96,     0,    97,     0,    98,
      99,   100,     0,     0,     0,     0,   101,   102,     0,     0,
      59,     0,     0,   103,     0,     0,   104,   246,    60,    61,
      62,    63,    64,    65,    66,     0,     0,     0,    67,    68,
       0,     0,     0,    69,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,     0,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    95,    96,     0,
      97,     0,    98,    99,   100,     0,     0,     0,     0,   101,
     102,     0,    59,     0,     0,     0,   103,     0,     0,   104,
      60,    61,    62,    63,    64,    65,    66,     0,     0,     0,
      67,    68,     0,     0,     0,    69,     0,     0,     0,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,    89,    90,    91,    92,     0,    94,    95,
      96,     0,    97,     0,    98,    99,   100,     0,     0,     0,
       0,   101,   102,     0,    59,     0,     0,     0,   103,     0,
       0,   104,    60,    61,    62,     0,     0,    65,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    90,    91,    92,     0,
       0,    95,    96,   198,     0,     0,    98,    99,   100,     0,
      60,    61,    62,   101,   102,    65,   136,     0,     0,     0,
     138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,    91,    92,     0,     0,    95,
      96,     0,     0,   488,    98,    99,   100,     0,    60,    61,
      62,   101,   102,    65,   489,     0,     0,     0,   138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,    91,    92,     0,     0,    95,    96,     0,
       0,   789,    98,    99,   100,     0,    60,    61,    62,   101,
     102,    65,   136,     0,     0,     0,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,    91,    92,     0,     0,    95,    96,     0,     0,   844,
      98,    99,   100,     0,    60,    61,    62,   101,   102,    65,
     136,     0,     0,     0,   138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,    91,
      92,     0,     0,    95,    96,     0,   787,     0,    98,    99,
     100,    60,    61,    62,     0,   101,   102,   136,     0,     0,
       0,     0,   138,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,    91,    92,     0,     0,
      95,    96,     0,   842,     0,    98,    99,   100,    60,    61,
      62,     0,     0,     0,   136,     0,     0,     0,     0,   138,
       0,     0,     0,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,    91,    92,     0,     0,    95,    96,     0,
       0,     0,    98,    99,   100,     0,     0,    60,    61,    62,
      63,    64,    65,    66,     0,     0,   138,    67,    68,     0,
       0,     0,    69,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,     0,     0,     0,     0,     0,
      89,    90,    91,    92,     0,    94,    95,    96,     0,    97,
       0,    98,    99,   100,   357,   155,    61,    62,   101,   102,
      65,   156,     0,     0,     0,   103,     0,     0,   104,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,   157,   158,   159,   160,   161,   162,   163,   164,   165,
      85,    86,    87,   166,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,     0,     0,    89,    90,
      91,    92,   169,     0,    95,    96,     0,     0,     0,    98,
      99,   100,     0,   155,    61,    62,   170,   171,    65,   156,
       0,     0,     0,   358,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,    71,    72,    73,    74,    75,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    85,    86,
      87,   166,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   183,   168,     0,     0,    89,    90,    91,    92,
     169,     0,    95,    96,     0,     0,     0,    98,    99,   100,
       0,   155,    61,    62,   170,   171,    65,   156,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    85,    86,    87,   166,
     167,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   168,     0,     0,    89,    90,    91,    92,   169,     0,
      95,    96,   155,    61,    62,    98,    99,   100,   156,     0,
       0,     0,   170,   171,     0,     0,     0,     0,     0,   172,
       0,     0,    70,    71,    72,    73,    74,    75,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    85,    86,    87,
     166,   167,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   168,     0,     0,    89,    90,    91,    92,   169,
       0,    95,    96,   155,    61,    62,    98,    99,   100,   156,
       0,     0,     0,   339,   340,     0,     0,     0,     0,     0,
     172,     0,     0,    70,    71,    72,    73,    74,    75,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    85,    86,
      87,   166,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   168,     0,     0,    89,    90,    91,    92,
     169,     0,    95,    96,     0,     0,     0,    98,    99,   100,
       0,    60,    61,    62,   170,   171,    65,   136,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,    91,    92,     0,     0,
      95,    96,     0,     0,     0,    98,    99,   100,     0,    60,
      61,    62,   101,   102,    65,   316,     0,     0,     0,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,    91,    92,     0,     0,    95,    96,
       0,     0,     0,    98,    99,   100,     0,    60,    61,    62,
     101,   317,    65,   136,     0,     0,     0,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,    91,    92,     0,     0,    95,    96,     0,     0,
       0,    98,    99,   100,     0,    60,    61,    62,   101,   746,
      65,   136,     0,     0,     0,   138,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
      91,    92,     0,     0,    95,    96,    60,    61,    62,    98,
      99,   100,   136,     0,     0,     0,   101,   823,     0,     0,
       0,     0,     0,   138,     0,     0,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,    91,    92,     0,     0,    95,    96,    60,    61,    62,
      98,    99,   100,   136,     0,     0,     0,   101,   102,     0,
       0,     0,     0,     0,   138,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,    91,    92,     0,     0,    95,    96,     0,     0,
       0,    98,    99,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138
};

static const yytype_int16 yycheck[] =
{
      36,    37,   101,   102,   192,   154,   491,    43,    26,    50,
      21,    42,   142,    44,   345,   346,    26,    53,    49,    36,
     351,   352,   107,    59,    20,   546,   547,   357,   358,    60,
      66,    20,    63,    64,    65,    22,    67,    68,   170,   171,
      22,   259,   260,    16,    17,    18,    19,    39,    31,    24,
      25,    22,    32,    33,    34,    35,    36,    37,    66,    27,
      39,    40,    41,    84,    92,    35,    94,   103,   104,   107,
      55,   170,   171,   104,    35,   107,    32,    33,    34,    14,
      15,   117,   118,   107,   120,    59,    39,    40,    41,   125,
     106,   187,    27,   114,   115,    51,   114,   115,   107,   135,
     136,   137,   138,   120,   114,   115,   107,   125,   144,   117,
     118,   147,   120,   149,   125,   125,   116,   125,    32,    33,
     156,    22,   118,   123,   155,   117,    94,    95,   136,   118,
     104,   116,   320,   120,   114,   115,   172,   120,   120,   114,
     115,   169,   122,   122,   107,   118,   182,   183,   156,   120,
     181,   121,    53,    54,     0,    56,    57,   188,   114,   115,
     121,   135,   106,   648,   117,   201,   497,   203,   106,   205,
     201,   207,   203,   391,   182,   305,    32,    33,    34,   215,
     216,   217,   218,   106,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,    39,   233,   234,   235,
     114,   115,    21,   239,   240,   241,    21,   339,   340,    52,
     120,   114,   115,   114,   115,   125,   348,   120,   317,   114,
     115,   353,   552,   553,   554,   261,   120,   201,   122,   203,
     125,   264,   265,   266,   267,   268,    21,   273,   759,   270,
      21,    32,    33,    34,    35,    36,    37,   283,   284,   285,
      51,   287,   288,   289,   290,   291,   292,   121,   114,   115,
      51,   235,    32,    33,    34,   239,   240,   241,   304,   120,
     306,   307,   308,   309,   125,   283,   284,   285,   314,   117,
     316,    51,   120,   319,    32,    33,    34,    35,    36,    37,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   273,
      32,    33,    34,   121,   492,    36,    37,   792,   316,   117,
      41,   121,   120,   114,   115,   348,   349,   350,   114,   115,
     353,   357,   358,   114,   115,   117,   362,   114,   115,   125,
     304,   367,   368,   120,    39,    66,    29,    32,    33,    34,
      35,    36,    37,   121,   114,   115,    51,    52,   381,    33,
     386,   384,   388,   120,   390,   122,   389,   107,    53,    54,
     121,    56,    57,    39,    40,    41,   114,   115,    39,    40,
      41,   120,   103,   122,   122,    32,    33,    34,    35,    36,
      37,    52,   114,   115,   121,   421,   117,   118,   121,   120,
     426,   427,    59,    60,   125,   126,    32,    33,    34,    35,
      36,    37,   121,    59,    60,   136,    51,    52,    51,   445,
      32,    33,    34,    35,    36,    37,    32,    33,   121,   114,
     115,    35,   121,    51,    52,   156,   757,   122,    52,    51,
     121,    53,    54,    51,    56,    57,   121,   445,   474,   475,
     114,   115,   478,    51,    52,    51,   122,   483,   122,   116,
     118,   182,   493,   489,   495,   121,   123,   114,   115,   120,
     116,   122,   498,    51,    52,   122,   120,   123,   122,   114,
     115,   114,   115,   121,   205,    89,   207,    91,   114,   115,
      51,   489,   213,   214,   121,   521,   114,   115,   219,   520,
     114,   115,   114,   115,   114,   115,   114,   115,   114,   115,
     649,   120,   651,   122,   478,   125,   114,   115,   114,   115,
     546,   547,   121,   521,   121,    52,   552,   553,   554,   555,
     556,   557,   558,   559,   560,   561,   114,   115,    32,    33,
      34,    35,    36,    37,    32,    33,    34,    35,    36,    37,
     576,   577,   578,   114,   115,    52,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   587,    35,   589,    52,
      51,    52,    53,   751,   295,   601,   602,   121,    46,    47,
     578,    49,    39,    40,    41,    53,    54,   114,   115,   121,
      58,   617,    52,    35,    51,   316,   682,   120,    52,   122,
     121,   687,   688,    52,    46,    47,   632,    49,    52,   114,
     115,    53,    54,    16,    17,   120,    58,   114,   115,   645,
     114,   115,    90,    51,    52,    53,   114,   115,   570,   571,
     572,   114,   115,   101,   632,   114,   115,   105,    52,   665,
     666,   120,    53,    54,   121,    56,    57,    89,    90,    91,
      52,   119,   121,   121,   114,   115,   124,   746,    52,   101,
     114,   115,   120,   105,   122,   114,   115,   120,    52,   390,
     114,   115,    32,    33,    34,    35,    36,    37,    52,   121,
     114,   115,   124,   709,   710,   121,   712,   713,    39,    40,
      41,   172,   121,    53,    54,   121,    56,    57,   724,    50,
     114,   115,   183,   114,   115,   731,   121,   733,   120,   735,
     122,   122,   114,   115,   121,    53,    54,   743,    56,    57,
     114,   115,   748,   121,   445,    53,    54,    52,    56,    57,
     114,   115,   121,   759,   823,   761,   762,   735,   121,    52,
     114,   115,   121,   464,   172,    23,   772,   773,   114,   115,
     471,   472,   778,   779,   114,   115,    52,   783,    52,    21,
     846,   847,   788,   849,   850,    52,   852,   853,   489,   855,
     856,    53,    54,    23,    56,    57,   114,   115,   119,   114,
     115,   262,   263,    20,   122,   120,   114,   115,   117,   114,
     115,    22,   114,   115,   122,   117,   822,    52,   824,   825,
     521,   114,   115,   829,    52,   831,   120,   833,   122,   835,
     120,    53,    54,   839,    56,    57,    61,    62,   114,   115,
     114,   115,   764,   765,   766,   767,   119,   114,   115,    30,
     114,   115,   114,   115,    32,   117,   120,   863,   864,   865,
     866,   867,   868,   869,   870,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   578,   579,   114,
     115,   114,   115,   117,   345,   346,   114,   115,   119,   122,
     351,   352,   114,   115,    16,    17,   357,   358,   120,   119,
     120,   362,    39,    40,    41,   121,   367,   368,   830,   121,
     832,   121,   834,    50,   836,   114,   115,   378,   326,   327,
     328,   329,   330,   331,   332,   333,   334,   335,   336,   337,
      35,   632,   633,   634,   121,    39,    40,    41,   121,   114,
     115,    46,    47,   117,    49,   120,    50,   122,    53,    54,
     358,    61,    62,    58,   362,   114,   115,   114,   115,   367,
     368,   114,   115,   122,   117,   122,   888,   889,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   899,   900,   901,
     902,   903,   121,    35,    61,    90,    46,    47,   121,    49,
     121,   114,   115,    53,    46,    47,   101,    49,    58,   122,
     105,    53,    54,   121,    53,    54,    58,    56,    57,    39,
      40,    41,   121,   121,    53,    54,   121,    56,    57,   124,
      50,   121,   723,    21,    39,    40,    41,    39,    40,    41,
      90,    39,    40,    41,   735,    50,   497,   498,    90,   114,
     115,   101,    50,    36,    37,   105,    21,   122,    21,   101,
      43,    21,    51,   105,    53,    54,    21,    56,    57,   114,
     115,   121,    21,    21,   124,   114,   115,   122,    21,   121,
     531,   120,   124,    66,   101,   114,   115,    39,    40,    41,
      20,   120,    56,    57,    58,   546,   547,    35,    50,    20,
     498,   552,   553,   554,   555,   556,   557,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   567,    85,    86,    87,
      88,   104,   117,   574,   117,   114,   115,    35,    46,    47,
      21,    49,    21,   531,   117,   118,    21,   120,    46,    47,
      58,    49,   125,   114,   115,    53,    54,    20,   546,   547,
      58,   122,    21,   136,   107,    20,    20,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
      20,   122,    90,   156,    53,    54,   574,    56,    57,    39,
     122,   122,    90,   101,   121,    53,    54,   105,    56,    57,
      52,    53,    54,   101,    56,    57,   122,   105,   121,   182,
      39,    40,    41,   121,    53,    54,   124,    56,    57,   114,
     115,    50,   121,   121,   121,   121,   124,   122,   121,   670,
     671,   672,   673,   674,   675,   676,   677,   678,    39,    40,
      41,    39,    40,    41,   121,   114,   115,   121,   117,    50,
     114,   115,    50,   114,   115,   121,   114,   115,   122,   117,
     125,   122,   114,   115,   121,   114,   115,    38,   117,   114,
     115,   117,    43,    44,    45,   114,   115,   122,    49,   121,
     117,    21,   670,   671,   672,   673,   674,   675,   676,   677,
     678,    39,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
     283,   284,   285,   754,   114,   115,   757,   758,   759,    39,
     761,   762,   122,   120,   297,    96,    97,    98,    99,    43,
     303,   102,   103,   114,   115,    49,   107,   108,   109,   114,
     115,   122,    21,   316,   114,   115,    21,   122,   114,   115,
     121,   117,   122,   122,   117,    69,    70,    71,    72,    73,
      74,    75,    76,    77,   114,   115,   754,    81,    82,    51,
     758,   759,   122,   761,   762,   114,   115,    46,    47,    93,
      49,   117,   117,   122,    53,    54,   100,    51,   829,    58,
     831,   117,   833,    52,   835,   114,   115,   114,   115,    52,
     114,   115,   472,   122,   636,   122,   483,   121,   114,   115,
     114,   115,   114,   115,   114,   115,   122,   117,   122,   322,
     122,    90,   863,   864,   865,   866,   867,   868,   869,   870,
     114,   115,   101,   303,   114,   115,   105,   362,   122,   573,
     392,   829,   122,   831,   104,   833,   294,   835,   421,    -1,
     423,    -1,   121,    -1,    -1,   124,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    16,    17,    18,
      19,    -1,   445,    -1,    21,   863,   864,   865,   866,   867,
     868,   869,   870,   114,   115,    22,   114,   115,   114,   115,
      -1,   122,   114,   115,   122,    -1,   122,    -1,    35,   472,
     122,   114,   115,    -1,    -1,    -1,    43,    44,    45,   122,
     483,    48,    49,   114,   115,    -1,   489,   114,   115,    -1,
      -1,   122,    -1,    -1,    -1,   122,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,   114,   115,    83,    -1,   521,   114,
     115,    -1,   122,    -1,    -1,   114,   115,   122,    -1,    96,
      97,    98,    99,   122,    -1,   102,   103,    -1,   114,   115,
     107,   108,   109,   114,   115,    -1,   122,   114,   115,   114,
     115,   122,   114,   115,   121,   114,   115,   122,    -1,    -1,
     122,   114,   115,   122,   114,   115,    28,    -1,    -1,   122,
     114,   115,   122,    35,    -1,   578,    -1,    -1,   122,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,    -1,   114,
     115,    53,    54,   596,    -1,    -1,    58,   122,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,   114,
     115,    -1,   114,   115,    -1,    -1,    -1,   122,    90,   632,
     122,    -1,    -1,   636,    96,    97,    98,    99,    -1,   101,
     102,   103,   104,   105,    -1,   107,   108,   109,    27,    -1,
      -1,    -1,   114,   115,   110,   111,   112,   113,    -1,   121,
      -1,    -1,   124,    -1,    43,    44,    45,    -1,    -1,    48,
      49,   253,   254,   255,   256,   257,   258,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    93,    -1,    -1,    96,    97,    98,
      99,   100,    -1,   102,   103,    -1,    -1,    -1,   107,   108,
     109,    -1,   735,    -1,    -1,   114,   115,    35,    -1,    -1,
      -1,    -1,   121,    -1,    -1,    43,    44,    45,    46,    47,
      48,    49,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    -1,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,    -1,   101,   102,   103,    -1,   105,    -1,   107,
     108,   109,    -1,    -1,    -1,    -1,   114,   115,    -1,    -1,
      35,    -1,    -1,   121,    -1,    -1,   124,   125,    43,    44,
      45,    46,    47,    48,    49,    -1,    -1,    -1,    53,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
     105,    -1,   107,   108,   109,    -1,    -1,    -1,    -1,   114,
     115,    -1,    35,    -1,    -1,    -1,   121,    -1,    -1,   124,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    -1,
      53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    97,    98,    99,    -1,   101,   102,
     103,    -1,   105,    -1,   107,   108,   109,    -1,    -1,    -1,
      -1,   114,   115,    -1,    35,    -1,    -1,    -1,   121,    -1,
      -1,   124,    43,    44,    45,    -1,    -1,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    96,    97,    98,    99,    -1,
      -1,   102,   103,    36,    -1,    -1,   107,   108,   109,    -1,
      43,    44,    45,   114,   115,    48,    49,    -1,    -1,    -1,
     121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    96,    97,    98,    99,    -1,    -1,   102,
     103,    -1,    -1,    38,   107,   108,   109,    -1,    43,    44,
      45,   114,   115,    48,    49,    -1,    -1,    -1,   121,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,    -1,    -1,   102,   103,    -1,
      -1,    38,   107,   108,   109,    -1,    43,    44,    45,   114,
     115,    48,    49,    -1,    -1,    -1,   121,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      97,    98,    99,    -1,    -1,   102,   103,    -1,    -1,    38,
     107,   108,   109,    -1,    43,    44,    45,   114,   115,    48,
      49,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,    98,
      99,    -1,    -1,   102,   103,    -1,    38,    -1,   107,   108,
     109,    43,    44,    45,    -1,   114,   115,    49,    -1,    -1,
      -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    97,    98,    99,    -1,    -1,
     102,   103,    -1,    38,    -1,   107,   108,   109,    43,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    96,    97,    98,    99,    -1,    -1,   102,   103,    -1,
      -1,    -1,   107,   108,   109,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,   121,    53,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    97,    98,    99,    -1,   101,   102,   103,    -1,   105,
      -1,   107,   108,   109,    42,    43,    44,    45,   114,   115,
      48,    49,    -1,    -1,    -1,   121,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    -1,    96,    97,
      98,    99,   100,    -1,   102,   103,    -1,    -1,    -1,   107,
     108,   109,    -1,    43,    44,    45,   114,   115,    48,    49,
      -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    92,    93,    -1,    -1,    96,    97,    98,    99,
     100,    -1,   102,   103,    -1,    -1,    -1,   107,   108,   109,
      -1,    43,    44,    45,   114,   115,    48,    49,    -1,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    -1,    -1,    96,    97,    98,    99,   100,    -1,
     102,   103,    43,    44,    45,   107,   108,   109,    49,    -1,
      -1,    -1,   114,   115,    -1,    -1,    -1,    -1,    -1,   121,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    -1,    -1,    96,    97,    98,    99,   100,
      -1,   102,   103,    43,    44,    45,   107,   108,   109,    49,
      -1,    -1,    -1,   114,   115,    -1,    -1,    -1,    -1,    -1,
     121,    -1,    -1,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    96,    97,    98,    99,
     100,    -1,   102,   103,    -1,    -1,    -1,   107,   108,   109,
      -1,    43,    44,    45,   114,   115,    48,    49,    -1,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    97,    98,    99,    -1,    -1,
     102,   103,    -1,    -1,    -1,   107,   108,   109,    -1,    43,
      44,    45,   114,   115,    48,    49,    -1,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    96,    97,    98,    99,    -1,    -1,   102,   103,
      -1,    -1,    -1,   107,   108,   109,    -1,    43,    44,    45,
     114,   115,    48,    49,    -1,    -1,    -1,   121,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    97,    98,    99,    -1,    -1,   102,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,    43,    44,    45,   114,   115,
      48,    49,    -1,    -1,    -1,   121,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,    97,
      98,    99,    -1,    -1,   102,   103,    43,    44,    45,   107,
     108,   109,    49,    -1,    -1,    -1,   114,   115,    -1,    -1,
      -1,    -1,    -1,   121,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    96,
      97,    98,    99,    -1,    -1,   102,   103,    43,    44,    45,
     107,   108,   109,    49,    -1,    -1,    -1,   114,   115,    -1,
      -1,    -1,    -1,    -1,   121,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      96,    97,    98,    99,    -1,    -1,   102,   103,    -1,    -1,
      -1,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   121
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    21,   127,   128,   131,   132,   133,   134,   136,
     139,   149,   150,   162,   165,   107,   107,   107,   107,   107,
     107,   107,   106,   106,   106,   106,    14,    15,    27,   166,
       0,    20,   118,    20,   118,    16,    17,    18,    19,   118,
     140,    21,    21,    21,    21,   121,   121,   121,   121,    35,
      43,    44,    45,    46,    47,    48,    49,    53,    54,    58,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    90,    96,
      97,    98,    99,   100,   101,   102,   103,   105,   107,   108,
     109,   114,   115,   121,   124,   169,   170,   171,   172,   177,
     179,   180,   181,   182,   183,   184,    28,    42,    49,   104,
     121,   169,   176,   177,   180,    49,   121,   167,   168,   169,
     177,   117,   169,   119,   167,    22,    49,    83,   121,   137,
     145,   146,   147,   173,   177,   180,   167,    29,   143,    33,
     141,    16,    17,   167,   141,    43,    49,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    81,    82,    93,   100,
     114,   115,   121,   157,   158,   159,   160,   161,   180,   181,
     157,    27,    49,    92,   151,   152,   157,   180,    27,    94,
      95,   163,   164,   107,   135,   135,   135,   135,    36,   179,
     167,   121,   168,   121,   168,   121,   167,   121,   167,   167,
     176,   167,   167,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   118,   178,   178,   178,   121,
     121,   121,   183,   183,   169,   180,   125,   167,   173,   175,
     177,   179,   180,    53,    54,    56,    57,   114,   115,    55,
     116,   120,   114,   115,    59,    60,   116,   123,    61,    62,
     121,   176,   176,   121,   169,   176,   180,    32,    33,    34,
      35,    36,    37,    39,    40,    41,    23,    32,    33,    34,
      35,    36,    37,   176,    21,    23,   117,    20,   119,   179,
     176,   180,   117,   120,   147,   148,    85,    86,    87,    88,
     174,   180,   119,   180,    30,   144,    49,   115,   180,    32,
     142,   117,   119,   142,   167,   176,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   178,   114,
     115,   159,   159,   157,   180,   114,   115,   117,   116,   123,
      61,   114,   115,   116,   117,   167,   176,    42,   121,   153,
     157,   180,    39,   117,    32,    33,    34,   156,   156,   167,
     117,   143,   120,   122,   122,   122,   122,    36,    21,   167,
     179,    21,   167,   179,    21,   180,    21,   180,    21,    21,
      50,    21,    21,   169,   169,   180,   180,   180,   180,   169,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   101,   180,   180,   179,   179,   179,   179,   122,
     122,    21,   125,   120,   125,   125,    24,    25,   170,   170,
     170,   170,   170,   170,   172,   172,   180,   181,   181,   182,
     182,   182,   182,   182,   167,    50,   179,   122,   169,   169,
     169,   169,   169,   169,   176,   176,   176,   169,   180,   180,
     180,   180,   180,   180,    50,   166,   169,    89,    91,   129,
     130,   177,    20,    22,    50,    84,   146,   179,   147,   180,
     180,   180,   180,    20,   180,   117,   176,    38,    38,    49,
     180,   143,    16,    17,    19,   140,   117,    21,    50,   157,
     180,   157,   180,   157,   180,   157,   180,   157,   180,   157,
     180,   157,   180,   157,   180,   157,   180,   157,   157,   157,
      43,    49,    69,    70,    71,    72,    73,    74,    75,    76,
      77,   121,   122,   158,   181,   158,   181,   159,   182,   182,
     182,   158,   181,   158,   181,   159,    21,    50,   153,   153,
     157,   180,    39,    40,    41,    50,    32,    33,    34,    35,
      36,    37,    32,    33,    34,    35,    36,    37,   152,   157,
     180,   157,   180,    21,    21,   107,    20,    20,    20,    20,
     181,   122,   122,   182,   122,   122,   182,   122,   180,   122,
     180,   182,   169,   180,   172,   171,   120,   122,   122,   122,
     122,   120,   120,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   120,   119,   122,
     122,   122,   177,   180,   177,   180,   180,   122,   169,   176,
     180,   122,    22,   121,   121,   117,   120,   169,   129,   169,
     180,    22,   179,   145,   180,    50,   176,   144,   143,   141,
      16,   141,   158,   181,   157,   180,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   120,   120,   122,   167,   176,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   151,
     151,   157,   180,   122,   153,   153,   153,   157,   180,   157,
     180,   157,   180,   157,   180,   157,   180,   157,   180,   157,
     180,   157,   157,   157,   157,   157,   157,   154,   154,    32,
      33,   154,    32,    33,   154,   163,   157,   180,   180,   176,
     169,   167,   167,    51,    51,   177,   180,   180,   180,   125,
     125,    26,   125,    26,   125,    51,   176,   169,   169,   130,
     117,   117,    22,    31,   138,   117,   115,   180,    50,   117,
     144,   142,   117,   142,    51,   180,   180,    21,    50,    51,
      52,   156,   156,   120,   180,   180,   180,   180,   117,   117,
     117,   117,    21,    21,   169,   180,   122,   122,   120,   120,
     180,   180,   176,   120,   122,   180,   117,    38,    51,    38,
     180,   117,   143,   117,   157,   122,   122,   181,   151,   157,
     180,   157,   180,   110,   111,   112,   113,   155,   154,   154,
     154,   154,   180,   180,    52,    52,   180,   180,   125,   125,
      52,   180,    51,   115,    51,    51,   144,    52,    52,    51,
      52,    51,    52,    51,    52,    51,    52,   122,   122,   120,
     122,   180,    38,   180,    38,   117,   157,   180,   154,   157,
     180,   154,   157,   180,   154,   157,   180,   154,   180,    52,
      52,    52,    52,   156,   156,   156,   156,   156,   156,   156,
     156,   122,   157,   180,   157,   180,   157,   180,   157,   180,
     157,   180,   157,   180,   157,   180,   157,   180,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

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
        case 2:
#line 149 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 3:
#line 150 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 4:
#line 151 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 5:
#line 152 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 6:
#line 153 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 7:
#line 154 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 8:
#line 155 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 9:
#line 156 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 10:
#line 157 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 11:
#line 158 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 12:
#line 159 "src/zimpl/mmlparse2.y"
    { code_set_root((yyvsp[(1) - (1)].code)); ;}
    break;

  case 13:
#line 167 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (5)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(4) - (5)].code));                                              /* initial set */
      ;}
    break;

  case 14:
#line 174 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set1, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                                      /* set */
      ;}
    break;

  case 15:
#line 180 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (8)].name)),                                       /* Name */
            (yyvsp[(4) - (8)].code),                                                 /* index set */
            (yyvsp[(7) - (8)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 16:
#line 186 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_set2, 3,
            code_new_name((yyvsp[(2) - (7)].name)),                                       /* Name */
            code_new_inst(i_idxset_pseudo_new, 1,               /* index set */
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(6) - (7)].code));                                   /* initial set_entry_list */
      ;}
    break;

  case 17:
#line 196 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 18:
#line 197 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 19:
#line 200 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_subsets, 3, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code), code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 20:
#line 203 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_subsets, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 21:
#line 206 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_powerset, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 22:
#line 212 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 23:
#line 221 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 24:
#line 230 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 25:
#line 239 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 26:
#line 248 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newdef, 3,
            code_new_define((yyvsp[(2) - (8)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(4) - (8)].code)),
            (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 27:
#line 257 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 28:
#line 260 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), code_new_name((yyvsp[(3) - (3)].name)));
      ;}
    break;

  case 29:
#line 270 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4, code_new_name((yyvsp[(2) - (9)].name)), (yyvsp[(4) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code));
      ;}
    break;

  case 30:
#line 273 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para2, 4, code_new_name((yyvsp[(2) - (8)].name)), (yyvsp[(4) - (8)].code), (yyvsp[(7) - (8)].code), code_new_inst(i_nop, 0));
      ;}
    break;

  case 31:
#line 276 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_para1, 4,
            code_new_name((yyvsp[(2) - (5)].name)),
            code_new_inst(i_idxset_pseudo_new, 1, code_new_inst(i_bool_true, 0)),
            (yyvsp[(4) - (5)].code),
            code_new_inst(i_nop, 0));
      ;}
    break;

  case 32:
#line 283 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 33:
#line 286 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 34:
#line 287 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_new, 1,
            code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (1)].code)));
      ;}
    break;

  case 35:
#line 294 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_nop, 0); ;}
    break;

  case 36:
#line 295 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, code_new_inst(i_tuple_empty, 0), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 37:
#line 303 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (9)].name)),
            (yyvsp[(4) - (9)].code), (yyvsp[(6) - (9)].code), (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code),
            code_new_numb(numb_copy(numb_unknown())),
            code_new_numb(numb_copy(numb_unknown())));
      ;}
    break;

  case 38:
#line 310 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (6)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            (yyvsp[(3) - (6)].code), (yyvsp[(4) - (6)].code), (yyvsp[(5) - (6)].code),
            code_new_numb(numb_copy(numb_unknown())),
            code_new_numb(numb_copy(numb_unknown())));
      ;}
    break;

  case 39:
#line 319 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (8)].name)),
            (yyvsp[(4) - (8)].code),
            code_new_varclass(VAR_IMP),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            code_new_numb(numb_copy(numb_unknown())),
            code_new_numb(numb_copy(numb_unknown())));
      ;}
    break;

  case 40:
#line 329 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (5)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_IMP),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            code_new_numb(numb_copy(numb_unknown())),
            code_new_numb(numb_copy(numb_unknown())));
      ;}
    break;

  case 41:
#line 340 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (9)].name)),
            (yyvsp[(4) - (9)].code),
            code_new_varclass(VAR_INT),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            (yyvsp[(7) - (9)].code), (yyvsp[(8) - (9)].code));
      ;}
    break;

  case 42:
#line 349 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (6)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_INT),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0))),
            code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(1))),
            (yyvsp[(4) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 43:
#line 359 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (11)].name)), (yyvsp[(4) - (11)].code), code_new_varclass(VAR_INT), (yyvsp[(7) - (11)].code), (yyvsp[(8) - (11)].code), (yyvsp[(9) - (11)].code), (yyvsp[(10) - (11)].code));
      ;}
    break;

  case 44:
#line 363 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_newsym_var, 7,
            code_new_name((yyvsp[(2) - (8)].name)),
            code_new_inst(i_idxset_pseudo_new, 1,
               code_new_inst(i_bool_true, 0)),              
            code_new_varclass(VAR_INT), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 45:
#line 373 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 46:
#line 374 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_CON); ;}
    break;

  case 47:
#line 375 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_varclass(VAR_IMP); ;}
    break;

  case 48:
#line 379 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_bound_new, 1, code_new_numb(numb_new_integer(0)));
      ;}
    break;

  case 49:
#line 382 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 50:
#line 383 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_MINUS_INFTY); ;}
    break;

  case 51:
#line 384 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(3) - (9)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (9)].code)),
            code_new_bound(BOUND_MINUS_INFTY));
      ;}
    break;

  case 52:
#line 389 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(3) - (9)].code),
            code_new_bound(BOUND_MINUS_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(8) - (9)].code)));
      ;}
    break;

  case 53:
#line 397 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 54:
#line 398 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bound_new, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 55:
#line 399 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_bound(BOUND_INFTY); ;}
    break;

  case 56:
#line 400 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(3) - (8)].code),
            code_new_inst(i_bound_new, 1, (yyvsp[(5) - (8)].code)),
            code_new_bound(BOUND_INFTY));
      ;}
    break;

  case 57:
#line 405 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(3) - (8)].code),
            code_new_bound(BOUND_INFTY),
            code_new_inst(i_bound_new, 1, (yyvsp[(7) - (8)].code)));
      ;}
    break;

  case 58:
#line 413 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(0)); ;}
    break;

  case 59:
#line 414 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 60:
#line 418 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_copy(numb_unknown())); ;}
    break;

  case 61:
#line 419 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 62:
#line 427 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry_list_new, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 63:
#line 428 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_entry_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 64:
#line 431 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 65:
#line 432 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_list_matrix, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 66:
#line 436 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_entry, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 67:
#line 440 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 68:
#line 444 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_new, 2, (yyvsp[(1) - (3)].code), (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 69:
#line 447 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_matrix_list_add, 3, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 70:
#line 459 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_object_min, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 71:
#line 462 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_object_max, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
      ;}
    break;

  case 72:
#line 472 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_subto, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 73:
#line 478 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint_list, 2, (yyvsp[(1) - (1)].code), code_new_inst(i_nop, 0));
     ;}
    break;

  case 74:
#line 481 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint_list, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
     ;}
    break;

  case 75:
#line 484 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint_list, 2, 
           code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)),
           code_new_inst(i_nop, 0));
     ;}
    break;

  case 76:
#line 489 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint_list, 2, 
           code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_inst(i_nop, 0)),
           code_new_inst(i_nop, 0));
      ;}
    break;

  case 77:
#line 494 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint_list, 2, 
           code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code)),
           code_new_inst(i_nop, 0));
      ;}
    break;

  case 78:
#line 502 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 79:
#line 505 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4, (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 80:
#line 510 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code), (yyvsp[(3) - (4)].code), code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 81:
#line 515 "src/zimpl/mmlparse2.y"
    { 
        (yyval.code) = code_new_inst(i_constraint, 4,
           code_new_inst(i_term_expr, 1, (yyvsp[(1) - (4)].code)),
           (yyvsp[(2) - (4)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (4)].code)),
           code_new_bits((yyvsp[(4) - (4)].bits)));
     ;}
    break;

  case 82:
#line 522 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 83:
#line 526 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(1) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)), (yyvsp[(5) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_RHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 84:
#line 531 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code), (yyvsp[(3) - (6)].code), (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 85:
#line 535 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_rangeconst, 6, (yyvsp[(5) - (6)].code),
           code_new_inst(i_term_expr, 1, (yyvsp[(3) - (6)].code)),
           (yyvsp[(1) - (6)].code), (yyvsp[(2) - (6)].code),
           code_new_contype(CON_LHS), code_new_bits((yyvsp[(6) - (6)].bits))); 
     ;}
    break;

  case 86:
#line 541 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 87:
#line 544 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 88:
#line 549 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 89:
#line 554 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 90:
#line 559 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 91:
#line 563 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 92:
#line 570 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 93:
#line 577 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code), (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 94:
#line 583 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 95:
#line 589 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 96:
#line 595 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 97:
#line 600 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code), (yyvsp[(10) - (12)].code), code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 98:
#line 608 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            (yyvsp[(8) - (12)].code), (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 99:
#line 617 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code), (yyvsp[(6) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 100:
#line 626 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code), (yyvsp[(4) - (12)].code), (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 101:
#line 634 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif_else, 8, (yyvsp[(2) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (12)].code)),
            (yyvsp[(5) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (12)].code)),
            code_new_inst(i_term_expr, 1, (yyvsp[(8) - (12)].code)),
            (yyvsp[(9) - (12)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(10) - (12)].code)), 
            code_new_bits((yyvsp[(12) - (12)].bits)));
      ;}
    break;

  case 102:
#line 645 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 103:
#line 648 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), 
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (8)].code)), (yyvsp[(5) - (8)].code), (yyvsp[(6) - (8)].code), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 104:
#line 652 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code), 
            (yyvsp[(4) - (8)].code), (yyvsp[(5) - (8)].code), code_new_inst(i_term_expr, 1, (yyvsp[(6) - (8)].code)), 
            code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 105:
#line 657 "src/zimpl/mmlparse2.y"
    { /* ??? This is an error */
         (yyval.code) = code_new_inst(i_vif, 5, (yyvsp[(2) - (8)].code),
            code_new_inst(i_term_expr, 1, (yyvsp[(4) - (8)].code)), (yyvsp[(5) - (8)].code), 
            code_new_inst(i_term_expr, 1, (yyvsp[(6) - (8)].code)), code_new_bits((yyvsp[(8) - (8)].bits)));
      ;}
    break;

  case 106:
#line 665 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 107:
#line 666 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 108:
#line 669 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ne, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 109:
#line 672 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 110:
#line 673 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 111:
#line 676 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_eq, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 112:
#line 679 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 113:
#line 680 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 114:
#line 683 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_le, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 115:
#line 686 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 116:
#line 687 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 117:
#line 690 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_ge, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 118:
#line 693 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 119:
#line 694 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 120:
#line 697 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_lt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 121:
#line 700 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 122:
#line 701 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 123:
#line 704 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vbool_gt, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 124:
#line 707 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 125:
#line 708 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 126:
#line 709 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 127:
#line 710 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vbool_not, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 128:
#line 711 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 129:
#line 715 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = 0; ;}
    break;

  case 130:
#line 716 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = (yyvsp[(1) - (3)].bits) | (yyvsp[(3) - (3)].bits); ;}
    break;

  case 131:
#line 720 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_SCALE; ;}
    break;

  case 132:
#line 721 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_SEPAR; ;}
    break;

  case 133:
#line 722 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_CHECK; ;}
    break;

  case 134:
#line 723 "src/zimpl/mmlparse2.y"
    { (yyval.bits) = LP_FLAG_CON_INDIC; ;}
    break;

  case 135:
#line 727 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_RHS); ;}
    break;

  case 136:
#line 728 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_LHS); ;}
    break;

  case 137:
#line 729 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_contype(CON_EQUAL); ;}
    break;

  case 138:
#line 733 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 139:
#line 734 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 140:
#line 735 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 141:
#line 736 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 142:
#line 737 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2, (yyvsp[(1) - (3)].code), code_new_inst(i_term_expr, 1, (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 143:
#line 740 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_const, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 144:
#line 741 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sub, 2,
            code_new_inst(i_term_expr, 1, (yyvsp[(1) - (3)].code)),
            (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 145:
#line 749 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 146:
#line 750 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));  ;}
    break;

  case 147:
#line 751 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(1) - (3)].code),
            code_new_inst(i_expr_div, 2, code_new_numb(numb_new_integer(1)), (yyvsp[(3) - (3)].code)));
      ;}
    break;

  case 148:
#line 755 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 149:
#line 756 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_term_mul, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 151:
#line 761 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 152:
#line 762 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_term_coeff, 2, (yyvsp[(2) - (2)].code), code_new_numb(numb_new_integer(-1)));
      ;}
    break;

  case 153:
#line 768 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 154:
#line 769 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_term_power, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 155:
#line 772 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_term_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 156:
#line 778 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 157:
#line 781 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vabs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 158:
#line 782 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(-2)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 159:
#line 783 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(3)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 160:
#line 784 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(4)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 161:
#line 785 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(5)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 162:
#line 786 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(6)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 163:
#line 787 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(7)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 164:
#line 788 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(8)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 165:
#line 789 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(9)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 166:
#line 790 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_vexpr_fun, 2, code_new_numb(numb_new_integer(10)), (yyvsp[(3) - (4)].code)); ;}
    break;

  case 167:
#line 791 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vexpr_fun, 3, code_new_numb(numb_new_integer(11)), (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 168:
#line 794 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_vexpr_fun, 3, code_new_numb(numb_new_integer(12)), (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 169:
#line 797 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 170:
#line 800 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 171:
#line 808 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_sos, 2, code_new_name((yyvsp[(2) - (5)].name)), (yyvsp[(4) - (5)].code));
     ;}
    break;

  case 172:
#line 814 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_soset, 3, (yyvsp[(4) - (4)].code), (yyvsp[(1) - (4)].code), (yyvsp[(2) - (4)].code));
     ;}
    break;

  case 173:
#line 817 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 174:
#line 823 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 175:
#line 824 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(1)); ;}
    break;

  case 176:
#line 825 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb(numb_new_integer(2)); ;}
    break;

  case 177:
#line 833 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 178:
#line 837 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 179:
#line 838 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 180:
#line 839 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 181:
#line 840 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_print, 1, code_new_symbol((yyvsp[(2) - (2)].sym))); ;}
    break;

  case 182:
#line 841 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_check, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 183:
#line 842 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_forall, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
     ;}
    break;

  case 184:
#line 852 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 185:
#line 853 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3,
            code_new_inst(i_tuple_empty, 0), (yyvsp[(1) - (1)].code), code_new_inst(i_bool_true, 0));
      ;}
    break;

  case 186:
#line 860 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3, (yyvsp[(1) - (5)].code), (yyvsp[(3) - (5)].code), (yyvsp[(5) - (5)].code));
      ;}
    break;

  case 187:
#line 863 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_idxset_new, 3, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code), code_new_inst(i_bool_true, 0));
      ;}
    break;

  case 189:
#line 870 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 190:
#line 871 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_union, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 191:
#line 874 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_sdiff, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 192:
#line 875 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 193:
#line 878 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_minus, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 194:
#line 879 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_inter, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 196:
#line 883 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_union2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 198:
#line 888 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 199:
#line 889 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_cross, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 200:
#line 892 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_inter2, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 201:
#line 896 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 202:
#line 899 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 203:
#line 904 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_empty, 1, code_new_size(0)); ;}
    break;

  case 204:
#line 905 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 205:
#line 908 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range2, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 206:
#line 911 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 207:
#line 914 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_range, 3, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code), code_new_numb(numb_new_integer(1)));
      ;}
    break;

  case 208:
#line 917 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 209:
#line 920 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmin, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 210:
#line 923 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, code_new_numb(numb_new_integer(1)), (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 211:
#line 926 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_argmax, 3, (yyvsp[(3) - (7)].code), (yyvsp[(5) - (7)].code), (yyvsp[(7) - (7)].code));
      ;}
    break;

  case 212:
#line 929 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 213:
#line 930 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_new_tuple, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 214:
#line 931 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_new_elem, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 215:
#line 932 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_idxset, 1, (yyvsp[(2) - (3)].code)); ;}
    break;

  case 216:
#line 933 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 217:
#line 934 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_set_expr, 2, (yyvsp[(2) - (5)].code), (yyvsp[(4) - (5)].code)); ;}
    break;

  case 218:
#line 935 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_set_proj, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
       ;}
    break;

  case 219:
#line 938 "src/zimpl/mmlparse2.y"
    {
          (yyval.code) = code_new_inst(i_set_indexset, 1, code_new_symbol((yyvsp[(3) - (4)].sym)));
       ;}
    break;

  case 220:
#line 941 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 221:
#line 947 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_new, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code)); ;}
    break;

  case 222:
#line 948 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_param, 2, (yyvsp[(1) - (2)].code), (yyvsp[(2) - (2)].code)); ;}
    break;

  case 223:
#line 952 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_skip, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 224:
#line 953 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_use, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 225:
#line 954 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_comment, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 226:
#line 955 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read_match, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 227:
#line 959 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 228:
#line 962 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 229:
#line 965 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_read, 1, (yyvsp[(1) - (1)].code)); ;}
    break;

  case 230:
#line 969 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_eq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 231:
#line 970 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_ne, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 232:
#line 971 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_gt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 233:
#line 972 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_ge, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 234:
#line 973 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_lt, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 235:
#line 974 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_le, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 236:
#line 975 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_seq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 237:
#line 976 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sneq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 238:
#line 977 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 239:
#line 978 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(3) - (3)].code), (yyvsp[(1) - (3)].code)); ;}
    break;

  case 240:
#line 979 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_subs, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 241:
#line 980 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_sseq, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 242:
#line 981 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_and, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 243:
#line 982 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_or,  2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 244:
#line 983 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_xor, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 245:
#line 984 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_not, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 246:
#line 985 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 247:
#line 986 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_is_elem, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 248:
#line 987 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_bool_exists, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 249:
#line 988 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 250:
#line 993 "src/zimpl/mmlparse2.y"
    {
        (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
     ;}
    break;

  case 251:
#line 999 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_tuple_empty, 0); ;}
    break;

  case 252:
#line 1000 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));  ;}
    break;

  case 253:
#line 1004 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_empty, 0);
      ;}
    break;

  case 254:
#line 1007 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_tuple_new, 1, (yyvsp[(2) - (3)].code));
      ;}
    break;

  case 255:
#line 1013 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_new, 1, (yyvsp[(1) - (1)].code));
      ;}
    break;

  case 256:
#line 1016 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_elem_list_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code));
      ;}
    break;

  case 257:
#line 1022 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 258:
#line 1023 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_add, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 259:
#line 1024 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sub, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 260:
#line 1028 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(1) - (1)].code); ;}
    break;

  case 261:
#line 1029 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_mul, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 262:
#line 1030 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_div, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 263:
#line 1031 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_mod, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 264:
#line 1032 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_intdiv, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 265:
#line 1033 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_prod, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 267:
#line 1040 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (2)].code); ;}
    break;

  case 268:
#line 1041 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_neg, 1, (yyvsp[(2) - (2)].code)); ;}
    break;

  case 270:
#line 1046 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_pow, 2, (yyvsp[(1) - (3)].code), (yyvsp[(3) - (3)].code)); ;}
    break;

  case 271:
#line 1047 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sum, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 272:
#line 1050 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_min, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 273:
#line 1053 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_max, 2, (yyvsp[(2) - (4)].code), (yyvsp[(4) - (4)].code));
      ;}
    break;

  case 274:
#line 1056 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmin, 1, (yyvsp[(3) - (4)].code));
         ;}
    break;

  case 275:
#line 1059 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_sglmax, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 276:
#line 1065 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_numb((yyvsp[(1) - (1)].numb)); ;}
    break;

  case 277:
#line 1066 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_strg((yyvsp[(1) - (1)].strg));  ;}
    break;

  case 278:
#line 1067 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_local_deref, 1, code_new_name((yyvsp[(1) - (1)].name)));
      ;}
    break;

  case 279:
#line 1070 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 280:
#line 1073 "src/zimpl/mmlparse2.y"
    { 
         (yyval.code) = code_new_inst(i_symbol_deref, 2, code_new_symbol((yyvsp[(1) - (2)].sym)), (yyvsp[(2) - (2)].code));
      ;}
    break;

  case 281:
#line 1076 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 282:
#line 1081 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_define_deref, 2,
            code_new_define((yyvsp[(1) - (4)].def)),
            code_new_inst(i_tuple_new, 1, (yyvsp[(3) - (4)].code)));
      ;}
    break;

  case 283:
#line 1086 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_fac, 1, (yyvsp[(1) - (2)].code)); ;}
    break;

  case 284:
#line 1087 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_card, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 285:
#line 1088 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_abs, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 286:
#line 1089 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sgn, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 287:
#line 1090 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_round, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 288:
#line 1091 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_floor, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 289:
#line 1092 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_ceil, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 290:
#line 1093 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_log, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 291:
#line 1094 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_ln, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 292:
#line 1095 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_exp, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 293:
#line 1096 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sqrt, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 294:
#line 1097 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_sin, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 295:
#line 1098 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_cos, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 296:
#line 1099 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_tan, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 297:
#line 1100 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_asin, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 298:
#line 1101 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_acos, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 299:
#line 1102 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_atan, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 300:
#line 1104 "src/zimpl/mmlparse2.y"
    { (yyval.code) = (yyvsp[(2) - (3)].code); ;}
    break;

  case 301:
#line 1105 "src/zimpl/mmlparse2.y"
    { (yyval.code) = code_new_inst(i_expr_length, 1, (yyvsp[(3) - (4)].code)); ;}
    break;

  case 302:
#line 1106 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_substr, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 303:
#line 1109 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_rand, 2, (yyvsp[(3) - (6)].code), (yyvsp[(5) - (6)].code));
      ;}
    break;

  case 304:
#line 1112 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_if_else, 3, (yyvsp[(2) - (7)].code), (yyvsp[(4) - (7)].code), (yyvsp[(6) - (7)].code));
      ;}
    break;

  case 305:
#line 1115 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_ord, 3, (yyvsp[(3) - (8)].code), (yyvsp[(5) - (8)].code), (yyvsp[(7) - (8)].code));
      ;}
    break;

  case 306:
#line 1118 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_min2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;

  case 307:
#line 1121 "src/zimpl/mmlparse2.y"
    {
         (yyval.code) = code_new_inst(i_expr_max2, 1, (yyvsp[(3) - (4)].code));
      ;}
    break;


/* Line 1267 of yacc.c.  */
#line 4802 "src/zimpl/mmlparse2.c"
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



