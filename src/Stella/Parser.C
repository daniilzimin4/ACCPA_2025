/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         Stellaparse
#define yylex           Stellalex
#define yyerror         Stellaerror
#define yydebug         Stelladebug
#define yynerrs         Stellanerrs

/* First part of user prologue.  */
#line 22 "Stella.y"

/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE Stella_scan_string(const char *str, yyscan_t scanner);
extern void Stella_delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void Stellalex_destroy(yyscan_t scanner);
extern char* Stellaget_text(yyscan_t scanner);

extern yyscan_t Stella_initialize_lexer(FILE * inp);

/* End C preamble code */

#line 105 "Parser.C"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Bison.H"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL__ERROR_ = 3,                    /* _ERROR_  */
  YYSYMBOL__BANGEQ = 4,                    /* _BANGEQ  */
  YYSYMBOL__LPAREN = 5,                    /* _LPAREN  */
  YYSYMBOL__RPAREN = 6,                    /* _RPAREN  */
  YYSYMBOL__STAR = 7,                      /* _STAR  */
  YYSYMBOL__PLUS = 8,                      /* _PLUS  */
  YYSYMBOL__COMMA = 9,                     /* _COMMA  */
  YYSYMBOL__MINUS = 10,                    /* _MINUS  */
  YYSYMBOL__RARROW = 11,                   /* _RARROW  */
  YYSYMBOL__DOT = 12,                      /* _DOT  */
  YYSYMBOL__SLASH = 13,                    /* _SLASH  */
  YYSYMBOL__COLON = 14,                    /* _COLON  */
  YYSYMBOL__SEMI = 15,                     /* _SEMI  */
  YYSYMBOL__LT = 16,                       /* _LT  */
  YYSYMBOL__LDARROW = 17,                  /* _LDARROW  */
  YYSYMBOL__SYMB_11 = 18,                  /* _SYMB_11  */
  YYSYMBOL__EQ = 19,                       /* _EQ  */
  YYSYMBOL__DEQ = 20,                      /* _DEQ  */
  YYSYMBOL__RDARROW = 21,                  /* _RDARROW  */
  YYSYMBOL__GT = 22,                       /* _GT  */
  YYSYMBOL__GTEQ = 23,                     /* _GTEQ  */
  YYSYMBOL__KW_Bool = 24,                  /* _KW_Bool  */
  YYSYMBOL__SYMB_26 = 25,                  /* _SYMB_26  */
  YYSYMBOL__SYMB_27 = 26,                  /* _SYMB_27  */
  YYSYMBOL__SYMB_28 = 27,                  /* _SYMB_28  */
  YYSYMBOL__KW_Nat = 28,                   /* _KW_Nat  */
  YYSYMBOL__SYMB_30 = 29,                  /* _SYMB_30  */
  YYSYMBOL__SYMB_29 = 30,                  /* _SYMB_29  */
  YYSYMBOL__SYMB_31 = 31,                  /* _SYMB_31  */
  YYSYMBOL__KW_Unit = 32,                  /* _KW_Unit  */
  YYSYMBOL__LBRACK = 33,                   /* _LBRACK  */
  YYSYMBOL__RBRACK = 34,                   /* _RBRACK  */
  YYSYMBOL__KW_and = 35,                   /* _KW_and  */
  YYSYMBOL__KW_as = 36,                    /* _KW_as  */
  YYSYMBOL__KW_cons = 37,                  /* _KW_cons  */
  YYSYMBOL__KW_core = 38,                  /* _KW_core  */
  YYSYMBOL__KW_else = 39,                  /* _KW_else  */
  YYSYMBOL__KW_extend = 40,                /* _KW_extend  */
  YYSYMBOL__KW_false = 41,                 /* _KW_false  */
  YYSYMBOL__KW_fix = 42,                   /* _KW_fix  */
  YYSYMBOL__KW_fn = 43,                    /* _KW_fn  */
  YYSYMBOL__KW_fold = 44,                  /* _KW_fold  */
  YYSYMBOL__KW_if = 45,                    /* _KW_if  */
  YYSYMBOL__KW_in = 46,                    /* _KW_in  */
  YYSYMBOL__KW_inl = 47,                   /* _KW_inl  */
  YYSYMBOL__KW_inline = 48,                /* _KW_inline  */
  YYSYMBOL__KW_inr = 49,                   /* _KW_inr  */
  YYSYMBOL__KW_language = 50,              /* _KW_language  */
  YYSYMBOL__KW_let = 51,                   /* _KW_let  */
  YYSYMBOL__KW_letrec = 52,                /* _KW_letrec  */
  YYSYMBOL__KW_match = 53,                 /* _KW_match  */
  YYSYMBOL__KW_not = 54,                   /* _KW_not  */
  YYSYMBOL__KW_or = 55,                    /* _KW_or  */
  YYSYMBOL__KW_return = 56,                /* _KW_return  */
  YYSYMBOL__KW_succ = 57,                  /* _KW_succ  */
  YYSYMBOL__KW_then = 58,                  /* _KW_then  */
  YYSYMBOL__KW_throws = 59,                /* _KW_throws  */
  YYSYMBOL__KW_true = 60,                  /* _KW_true  */
  YYSYMBOL__KW_type = 61,                  /* _KW_type  */
  YYSYMBOL__KW_unfold = 62,                /* _KW_unfold  */
  YYSYMBOL__KW_unit = 63,                  /* _KW_unit  */
  YYSYMBOL__KW_with = 64,                  /* _KW_with  */
  YYSYMBOL__LBRACE = 65,                   /* _LBRACE  */
  YYSYMBOL__BAR = 66,                      /* _BAR  */
  YYSYMBOL__SYMB_12 = 67,                  /* _SYMB_12  */
  YYSYMBOL__RBRACE = 68,                   /* _RBRACE  */
  YYSYMBOL__KW_65 = 69,                    /* _KW_65  */
  YYSYMBOL_T_ExtensionName = 70,           /* T_ExtensionName  */
  YYSYMBOL_T_StellaIdent = 71,             /* T_StellaIdent  */
  YYSYMBOL__INTEGER_ = 72,                 /* _INTEGER_  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_ListStellaIdent = 74            /* ListStellaIdent  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 97 "Stella.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, Stellaget_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 225 "Parser.C"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  2
/* YYNRULES -- Number of rules.  */
#define YYNRULES  4
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  6

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   236,   236,   237,   238
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "_ERROR_", "_BANGEQ",
  "_LPAREN", "_RPAREN", "_STAR", "_PLUS", "_COMMA", "_MINUS", "_RARROW",
  "_DOT", "_SLASH", "_COLON", "_SEMI", "_LT", "_LDARROW", "_SYMB_11",
  "_EQ", "_DEQ", "_RDARROW", "_GT", "_GTEQ", "_KW_Bool", "_SYMB_26",
  "_SYMB_27", "_SYMB_28", "_KW_Nat", "_SYMB_30", "_SYMB_29", "_SYMB_31",
  "_KW_Unit", "_LBRACK", "_RBRACK", "_KW_and", "_KW_as", "_KW_cons",
  "_KW_core", "_KW_else", "_KW_extend", "_KW_false", "_KW_fix", "_KW_fn",
  "_KW_fold", "_KW_if", "_KW_in", "_KW_inl", "_KW_inline", "_KW_inr",
  "_KW_language", "_KW_let", "_KW_letrec", "_KW_match", "_KW_not",
  "_KW_or", "_KW_return", "_KW_succ", "_KW_then", "_KW_throws", "_KW_true",
  "_KW_type", "_KW_unfold", "_KW_unit", "_KW_with", "_LBRACE", "_BAR",
  "_SYMB_12", "_RBRACE", "_KW_65", "T_ExtensionName", "T_StellaIdent",
  "_INTEGER_", "$accept", "ListStellaIdent", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -71,    -8,     2,   -71,   -72,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     3,     0,     2,     1,     4
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -72,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       1,     3,     4,     5
};

static const yytype_int8 yycheck[] =
{
      71,     9,     0,     3
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,    74,     9,     0,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, result);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, YYSTYPE *result)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, result); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (result);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, YYSTYPE *result)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* ListStellaIdent: %empty  */
#line 236 "Stella.y"
                              { (yyval.liststellaident_) = new Stella::ListStellaIdent(); result->liststellaident_ = (yyval.liststellaident_); }
#line 1312 "Parser.C"
    break;

  case 3: /* ListStellaIdent: T_StellaIdent  */
#line 237 "Stella.y"
                  { (yyval.liststellaident_) = new Stella::ListStellaIdent(); (yyval.liststellaident_)->push_back((yyvsp[0]._string)); result->liststellaident_ = (yyval.liststellaident_); }
#line 1318 "Parser.C"
    break;

  case 4: /* ListStellaIdent: T_StellaIdent _COMMA ListStellaIdent  */
#line 238 "Stella.y"
                                         { (yyvsp[0].liststellaident_)->push_back((yyvsp[-2]._string)); (yyval.liststellaident_) = (yyvsp[0].liststellaident_); result->liststellaident_ = (yyval.liststellaident_); }
#line 1324 "Parser.C"
    break;


#line 1328 "Parser.C"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (&yylloc, scanner, result, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc, scanner, result);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, result, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, result);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 441 "Stella.y"


namespace Stella
{
/* Entrypoint: parse ListStellaIdent* from file. */
ListStellaIdent* pListStellaIdent(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.liststellaident_->begin(), result.liststellaident_->end());
    return result.liststellaident_;
  }
}

/* Entrypoint: parse ListStellaIdent* from string. */
ListStellaIdent* psListStellaIdent(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.liststellaident_->begin(), result.liststellaident_->end());
    return result.liststellaident_;
  }
}

/* Entrypoint: parse Program* from file. */
Program* pProgram(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.program_;
  }
}

/* Entrypoint: parse Program* from string. */
Program* psProgram(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.program_;
  }
}

/* Entrypoint: parse LanguageDecl* from file. */
LanguageDecl* pLanguageDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.languagedecl_;
  }
}

/* Entrypoint: parse LanguageDecl* from string. */
LanguageDecl* psLanguageDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.languagedecl_;
  }
}

/* Entrypoint: parse Extension* from file. */
Extension* pExtension(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.extension_;
  }
}

/* Entrypoint: parse Extension* from string. */
Extension* psExtension(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.extension_;
  }
}

/* Entrypoint: parse ListExtensionName* from file. */
ListExtensionName* pListExtensionName(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listextensionname_->begin(), result.listextensionname_->end());
    return result.listextensionname_;
  }
}

/* Entrypoint: parse ListExtensionName* from string. */
ListExtensionName* psListExtensionName(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listextensionname_->begin(), result.listextensionname_->end());
    return result.listextensionname_;
  }
}

/* Entrypoint: parse ListExtension* from file. */
ListExtension* pListExtension(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listextension_;
  }
}

/* Entrypoint: parse ListExtension* from string. */
ListExtension* psListExtension(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listextension_;
  }
}

/* Entrypoint: parse Decl* from file. */
Decl* pDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.decl_;
  }
}

/* Entrypoint: parse Decl* from string. */
Decl* psDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.decl_;
  }
}

/* Entrypoint: parse ListDecl* from file. */
ListDecl* pListDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listdecl_;
  }
}

/* Entrypoint: parse ListDecl* from string. */
ListDecl* psListDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listdecl_;
  }
}

/* Entrypoint: parse LocalDecl* from file. */
LocalDecl* pLocalDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.localdecl_;
  }
}

/* Entrypoint: parse LocalDecl* from string. */
LocalDecl* psLocalDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.localdecl_;
  }
}

/* Entrypoint: parse ListLocalDecl* from file. */
ListLocalDecl* pListLocalDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listlocaldecl_;
  }
}

/* Entrypoint: parse ListLocalDecl* from string. */
ListLocalDecl* psListLocalDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listlocaldecl_;
  }
}

/* Entrypoint: parse Annotation* from file. */
Annotation* pAnnotation(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.annotation_;
  }
}

/* Entrypoint: parse Annotation* from string. */
Annotation* psAnnotation(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.annotation_;
  }
}

/* Entrypoint: parse ListAnnotation* from file. */
ListAnnotation* pListAnnotation(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listannotation_;
  }
}

/* Entrypoint: parse ListAnnotation* from string. */
ListAnnotation* psListAnnotation(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.listannotation_;
  }
}

/* Entrypoint: parse ParamDecl* from file. */
ParamDecl* pParamDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.paramdecl_;
  }
}

/* Entrypoint: parse ParamDecl* from string. */
ParamDecl* psParamDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.paramdecl_;
  }
}

/* Entrypoint: parse ListParamDecl* from file. */
ListParamDecl* pListParamDecl(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listparamdecl_->begin(), result.listparamdecl_->end());
    return result.listparamdecl_;
  }
}

/* Entrypoint: parse ListParamDecl* from string. */
ListParamDecl* psListParamDecl(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listparamdecl_->begin(), result.listparamdecl_->end());
    return result.listparamdecl_;
  }
}

/* Entrypoint: parse ReturnType* from file. */
ReturnType* pReturnType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.returntype_;
  }
}

/* Entrypoint: parse ReturnType* from string. */
ReturnType* psReturnType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.returntype_;
  }
}

/* Entrypoint: parse ThrowType* from file. */
ThrowType* pThrowType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.throwtype_;
  }
}

/* Entrypoint: parse ThrowType* from string. */
ThrowType* psThrowType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.throwtype_;
  }
}

/* Entrypoint: parse Type* from file. */
Type* pType9(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from string. */
Type* psType9(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse ListType* from file. */
ListType* pListType9(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listtype_->begin(), result.listtype_->end());
    return result.listtype_;
  }
}

/* Entrypoint: parse ListType* from string. */
ListType* psListType9(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listtype_->begin(), result.listtype_->end());
    return result.listtype_;
  }
}

/* Entrypoint: parse MatchCase* from file. */
MatchCase* pMatchCase(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.matchcase_;
  }
}

/* Entrypoint: parse MatchCase* from string. */
MatchCase* psMatchCase(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.matchcase_;
  }
}

/* Entrypoint: parse ListMatchCase* from file. */
ListMatchCase* pListMatchCase(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listmatchcase_->begin(), result.listmatchcase_->end());
    return result.listmatchcase_;
  }
}

/* Entrypoint: parse ListMatchCase* from string. */
ListMatchCase* psListMatchCase(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listmatchcase_->begin(), result.listmatchcase_->end());
    return result.listmatchcase_;
  }
}

/* Entrypoint: parse OptionalTyping* from file. */
OptionalTyping* pOptionalTyping(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.optionaltyping_;
  }
}

/* Entrypoint: parse OptionalTyping* from string. */
OptionalTyping* psOptionalTyping(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.optionaltyping_;
  }
}

/* Entrypoint: parse PatternData* from file. */
PatternData* pPatternData(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.patterndata_;
  }
}

/* Entrypoint: parse PatternData* from string. */
PatternData* psPatternData(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.patterndata_;
  }
}

/* Entrypoint: parse ExprData* from file. */
ExprData* pExprData(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.exprdata_;
  }
}

/* Entrypoint: parse ExprData* from string. */
ExprData* psExprData(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.exprdata_;
  }
}

/* Entrypoint: parse Pattern* from file. */
Pattern* pPattern(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.pattern_;
  }
}

/* Entrypoint: parse Pattern* from string. */
Pattern* psPattern(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.pattern_;
  }
}

/* Entrypoint: parse ListPattern* from file. */
ListPattern* pListPattern(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listpattern_->begin(), result.listpattern_->end());
    return result.listpattern_;
  }
}

/* Entrypoint: parse ListPattern* from string. */
ListPattern* psListPattern(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listpattern_->begin(), result.listpattern_->end());
    return result.listpattern_;
  }
}

/* Entrypoint: parse LabelledPattern* from file. */
LabelledPattern* pLabelledPattern(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.labelledpattern_;
  }
}

/* Entrypoint: parse LabelledPattern* from string. */
LabelledPattern* psLabelledPattern(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.labelledpattern_;
  }
}

/* Entrypoint: parse ListLabelledPattern* from file. */
ListLabelledPattern* pListLabelledPattern(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listlabelledpattern_->begin(), result.listlabelledpattern_->end());
    return result.listlabelledpattern_;
  }
}

/* Entrypoint: parse ListLabelledPattern* from string. */
ListLabelledPattern* psListLabelledPattern(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listlabelledpattern_->begin(), result.listlabelledpattern_->end());
    return result.listlabelledpattern_;
  }
}

/* Entrypoint: parse Binding* from file. */
Binding* pBinding(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.binding_;
  }
}

/* Entrypoint: parse Binding* from string. */
Binding* psBinding(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.binding_;
  }
}

/* Entrypoint: parse ListBinding* from file. */
ListBinding* pListBinding(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listbinding_->begin(), result.listbinding_->end());
    return result.listbinding_;
  }
}

/* Entrypoint: parse ListBinding* from string. */
ListBinding* psListBinding(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listbinding_->begin(), result.listbinding_->end());
    return result.listbinding_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse ListExpr* from file. */
ListExpr* pListExpr(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listexpr_->begin(), result.listexpr_->end());
    return result.listexpr_;
  }
}

/* Entrypoint: parse ListExpr* from string. */
ListExpr* psListExpr(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listexpr_->begin(), result.listexpr_->end());
    return result.listexpr_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr1(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr1(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse PatternBinding* from file. */
PatternBinding* pPatternBinding(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.patternbinding_;
  }
}

/* Entrypoint: parse PatternBinding* from string. */
PatternBinding* psPatternBinding(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.patternbinding_;
  }
}

/* Entrypoint: parse ListPatternBinding* from file. */
ListPatternBinding* pListPatternBinding(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listpatternbinding_->begin(), result.listpatternbinding_->end());
    return result.listpatternbinding_;
  }
}

/* Entrypoint: parse ListPatternBinding* from string. */
ListPatternBinding* psListPatternBinding(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listpatternbinding_->begin(), result.listpatternbinding_->end());
    return result.listpatternbinding_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr2(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr2(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse ListExpr* from file. */
ListExpr* pListExpr2(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listexpr_->begin(), result.listexpr_->end());
    return result.listexpr_;
  }
}

/* Entrypoint: parse ListExpr* from string. */
ListExpr* psListExpr2(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listexpr_->begin(), result.listexpr_->end());
    return result.listexpr_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr3(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr3(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr4(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr4(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr6(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr6(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr7(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr7(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Type* from file. */
Type* pType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from string. */
Type* psType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from file. */
Type* pType1(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from string. */
Type* psType1(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from file. */
Type* pType2(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from string. */
Type* psType2(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from file. */
Type* pType3(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse Type* from string. */
Type* psType3(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.type_;
  }
}

/* Entrypoint: parse ListType* from file. */
ListType* pListType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listtype_->begin(), result.listtype_->end());
    return result.listtype_;
  }
}

/* Entrypoint: parse ListType* from string. */
ListType* psListType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listtype_->begin(), result.listtype_->end());
    return result.listtype_;
  }
}

/* Entrypoint: parse Expr* from file. */
Expr* pExpr5(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse Expr* from string. */
Expr* psExpr5(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.expr_;
  }
}

/* Entrypoint: parse VariantFieldType* from file. */
VariantFieldType* pVariantFieldType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.variantfieldtype_;
  }
}

/* Entrypoint: parse VariantFieldType* from string. */
VariantFieldType* psVariantFieldType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.variantfieldtype_;
  }
}

/* Entrypoint: parse ListVariantFieldType* from file. */
ListVariantFieldType* pListVariantFieldType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listvariantfieldtype_->begin(), result.listvariantfieldtype_->end());
    return result.listvariantfieldtype_;
  }
}

/* Entrypoint: parse ListVariantFieldType* from string. */
ListVariantFieldType* psListVariantFieldType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listvariantfieldtype_->begin(), result.listvariantfieldtype_->end());
    return result.listvariantfieldtype_;
  }
}

/* Entrypoint: parse RecordFieldType* from file. */
RecordFieldType* pRecordFieldType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.recordfieldtype_;
  }
}

/* Entrypoint: parse RecordFieldType* from string. */
RecordFieldType* psRecordFieldType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.recordfieldtype_;
  }
}

/* Entrypoint: parse ListRecordFieldType* from file. */
ListRecordFieldType* pListRecordFieldType(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listrecordfieldtype_->begin(), result.listrecordfieldtype_->end());
    return result.listrecordfieldtype_;
  }
}

/* Entrypoint: parse ListRecordFieldType* from string. */
ListRecordFieldType* psListRecordFieldType(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(result.listrecordfieldtype_->begin(), result.listrecordfieldtype_->end());
    return result.listrecordfieldtype_;
  }
}

/* Entrypoint: parse Typing* from file. */
Typing* pTyping(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.typing_;
  }
}

/* Entrypoint: parse Typing* from string. */
Typing* psTyping(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = Stella_initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = Stella_scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  Stella_delete_buffer(buf, scanner);
  Stellalex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.typing_;
  }
}


}
