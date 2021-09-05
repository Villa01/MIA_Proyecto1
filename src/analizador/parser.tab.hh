// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


/**
 ** \file parser.tab.hh
 ** Define the yy::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
// "%code requires" blocks.
#line 14 "parser.yy"

   class Driver;
   class Comando;
   class Parametro;
   class Mkdisk;
   class Rmdisk;
   class Fdisk;
   class Script;
   class Mount;
   class Unmount;
   class Mkfs;


#line 62 "parser.tab.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif


#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

namespace yy {
#line 196 "parser.tab.hh"




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // comando
      char dummy1[sizeof (Comando)];

      // parametro
      char dummy2[sizeof (Parametro)];

      // "MKDISK"
      // "RMDISK"
      // "FDISK"
      // "EXEC"
      // "TMOUNT"
      // "TUNMOUNT"
      // "MKFS"
      // "REP"
      // "SIZE"
      // "F"
      // "PATH"
      // "U"
      // "TYPE"
      // "DELETE"
      // "NAME"
      // "ADD"
      // "ID"
      // "FS"
      // "ROOT"
      // "NUM"
      // "BF"
      // "FF"
      // "WF"
      // "K"
      // "M"
      // "B"
      // "RUTA"
      // "P"
      // "E"
      // "L"
      // "FAST"
      // "FULL"
      // "CADENA"
      // "DOSFS"
      // "TRESFS"
      // "MBR"
      // "DISK"
      // "REPRUTA"
      // nom_param
      // atributo
      char dummy3[sizeof (std::string)];

      // lista_param
      char dummy4[sizeof (std::vector<Parametro>)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        MKDISK = 258,
        RMDISK = 259,
        FDISK = 260,
        EXEC = 261,
        TMOUNT = 262,
        TUNMOUNT = 263,
        MKFS = 264,
        REP = 265,
        SIZE = 266,
        F = 267,
        PATH = 268,
        U = 269,
        TYPE = 270,
        DELETE = 271,
        NAME = 272,
        ADD = 273,
        ID = 274,
        FS = 275,
        ROOT = 276,
        NUM = 277,
        BF = 278,
        FF = 279,
        WF = 280,
        K = 281,
        M = 282,
        B = 283,
        RUTA = 284,
        P = 285,
        E = 286,
        L = 287,
        FAST = 288,
        FULL = 289,
        CADENA = 290,
        DOSFS = 291,
        TRESFS = 292,
        MBR = 293,
        DISK = 294,
        REPRUTA = 295,
        GUION = 296,
        IGUAL = 297
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef signed char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Comando&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Comando& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Parametro&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Parametro& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<Parametro>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<Parametro>& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
    {
      case 46: // comando
        value.template destroy< Comando > ();
        break;

      case 48: // parametro
        value.template destroy< Parametro > ();
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "SIZE"
      case 12: // "F"
      case 13: // "PATH"
      case 14: // "U"
      case 15: // "TYPE"
      case 16: // "DELETE"
      case 17: // "NAME"
      case 18: // "ADD"
      case 19: // "ID"
      case 20: // "FS"
      case 21: // "ROOT"
      case 22: // "NUM"
      case 23: // "BF"
      case 24: // "FF"
      case 25: // "WF"
      case 26: // "K"
      case 27: // "M"
      case 28: // "B"
      case 29: // "RUTA"
      case 30: // "P"
      case 31: // "E"
      case 32: // "L"
      case 33: // "FAST"
      case 34: // "FULL"
      case 35: // "CADENA"
      case 36: // "DOSFS"
      case 37: // "TRESFS"
      case 38: // "MBR"
      case 39: // "DISK"
      case 40: // "REPRUTA"
      case 49: // nom_param
      case 50: // atributo
        value.template destroy< std::string > ();
        break;

      case 47: // lista_param
        value.template destroy< std::vector<Parametro> > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == 0 || tok == token::GUION || tok == token::IGUAL);
      }
#else
      symbol_type (int tok)
        : super_type(token_type (tok))
      {
        YY_ASSERT (tok == 0 || tok == token::GUION || tok == token::IGUAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type(token_type (tok), std::move (v))
      {
        YY_ASSERT (tok == token::MKDISK || tok == token::RMDISK || tok == token::FDISK || tok == token::EXEC || tok == token::TMOUNT || tok == token::TUNMOUNT || tok == token::MKFS || tok == token::REP || tok == token::SIZE || tok == token::F || tok == token::PATH || tok == token::U || tok == token::TYPE || tok == token::DELETE || tok == token::NAME || tok == token::ADD || tok == token::ID || tok == token::FS || tok == token::ROOT || tok == token::NUM || tok == token::BF || tok == token::FF || tok == token::WF || tok == token::K || tok == token::M || tok == token::B || tok == token::RUTA || tok == token::P || tok == token::E || tok == token::L || tok == token::FAST || tok == token::FULL || tok == token::CADENA || tok == token::DOSFS || tok == token::TRESFS || tok == token::MBR || tok == token::DISK || tok == token::REPRUTA);
      }
#else
      symbol_type (int tok, const std::string& v)
        : super_type(token_type (tok), v)
      {
        YY_ASSERT (tok == token::MKDISK || tok == token::RMDISK || tok == token::FDISK || tok == token::EXEC || tok == token::TMOUNT || tok == token::TUNMOUNT || tok == token::MKFS || tok == token::REP || tok == token::SIZE || tok == token::F || tok == token::PATH || tok == token::U || tok == token::TYPE || tok == token::DELETE || tok == token::NAME || tok == token::ADD || tok == token::ID || tok == token::FS || tok == token::ROOT || tok == token::NUM || tok == token::BF || tok == token::FF || tok == token::WF || tok == token::K || tok == token::M || tok == token::B || tok == token::RUTA || tok == token::P || tok == token::E || tok == token::L || tok == token::FAST || tok == token::FULL || tok == token::CADENA || tok == token::DOSFS || tok == token::TRESFS || tok == token::MBR || tok == token::DISK || tok == token::REPRUTA);
      }
#endif
    };

    /// Build a parser object.
    Parser (Driver& driver_yyarg);
    virtual ~Parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKDISK (std::string v)
      {
        return symbol_type (token::MKDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_MKDISK (const std::string& v)
      {
        return symbol_type (token::MKDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RMDISK (std::string v)
      {
        return symbol_type (token::RMDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_RMDISK (const std::string& v)
      {
        return symbol_type (token::RMDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FDISK (std::string v)
      {
        return symbol_type (token::FDISK, std::move (v));
      }
#else
      static
      symbol_type
      make_FDISK (const std::string& v)
      {
        return symbol_type (token::FDISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXEC (std::string v)
      {
        return symbol_type (token::EXEC, std::move (v));
      }
#else
      static
      symbol_type
      make_EXEC (const std::string& v)
      {
        return symbol_type (token::EXEC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TMOUNT (std::string v)
      {
        return symbol_type (token::TMOUNT, std::move (v));
      }
#else
      static
      symbol_type
      make_TMOUNT (const std::string& v)
      {
        return symbol_type (token::TMOUNT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TUNMOUNT (std::string v)
      {
        return symbol_type (token::TUNMOUNT, std::move (v));
      }
#else
      static
      symbol_type
      make_TUNMOUNT (const std::string& v)
      {
        return symbol_type (token::TUNMOUNT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MKFS (std::string v)
      {
        return symbol_type (token::MKFS, std::move (v));
      }
#else
      static
      symbol_type
      make_MKFS (const std::string& v)
      {
        return symbol_type (token::MKFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REP (std::string v)
      {
        return symbol_type (token::REP, std::move (v));
      }
#else
      static
      symbol_type
      make_REP (const std::string& v)
      {
        return symbol_type (token::REP, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZE (std::string v)
      {
        return symbol_type (token::SIZE, std::move (v));
      }
#else
      static
      symbol_type
      make_SIZE (const std::string& v)
      {
        return symbol_type (token::SIZE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_F (std::string v)
      {
        return symbol_type (token::F, std::move (v));
      }
#else
      static
      symbol_type
      make_F (const std::string& v)
      {
        return symbol_type (token::F, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PATH (std::string v)
      {
        return symbol_type (token::PATH, std::move (v));
      }
#else
      static
      symbol_type
      make_PATH (const std::string& v)
      {
        return symbol_type (token::PATH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U (std::string v)
      {
        return symbol_type (token::U, std::move (v));
      }
#else
      static
      symbol_type
      make_U (const std::string& v)
      {
        return symbol_type (token::U, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TYPE (std::string v)
      {
        return symbol_type (token::TYPE, std::move (v));
      }
#else
      static
      symbol_type
      make_TYPE (const std::string& v)
      {
        return symbol_type (token::TYPE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DELETE (std::string v)
      {
        return symbol_type (token::DELETE, std::move (v));
      }
#else
      static
      symbol_type
      make_DELETE (const std::string& v)
      {
        return symbol_type (token::DELETE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NAME (std::string v)
      {
        return symbol_type (token::NAME, std::move (v));
      }
#else
      static
      symbol_type
      make_NAME (const std::string& v)
      {
        return symbol_type (token::NAME, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD (std::string v)
      {
        return symbol_type (token::ADD, std::move (v));
      }
#else
      static
      symbol_type
      make_ADD (const std::string& v)
      {
        return symbol_type (token::ADD, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (std::string v)
      {
        return symbol_type (token::ID, std::move (v));
      }
#else
      static
      symbol_type
      make_ID (const std::string& v)
      {
        return symbol_type (token::ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FS (std::string v)
      {
        return symbol_type (token::FS, std::move (v));
      }
#else
      static
      symbol_type
      make_FS (const std::string& v)
      {
        return symbol_type (token::FS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ROOT (std::string v)
      {
        return symbol_type (token::ROOT, std::move (v));
      }
#else
      static
      symbol_type
      make_ROOT (const std::string& v)
      {
        return symbol_type (token::ROOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUM (std::string v)
      {
        return symbol_type (token::NUM, std::move (v));
      }
#else
      static
      symbol_type
      make_NUM (const std::string& v)
      {
        return symbol_type (token::NUM, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BF (std::string v)
      {
        return symbol_type (token::BF, std::move (v));
      }
#else
      static
      symbol_type
      make_BF (const std::string& v)
      {
        return symbol_type (token::BF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FF (std::string v)
      {
        return symbol_type (token::FF, std::move (v));
      }
#else
      static
      symbol_type
      make_FF (const std::string& v)
      {
        return symbol_type (token::FF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WF (std::string v)
      {
        return symbol_type (token::WF, std::move (v));
      }
#else
      static
      symbol_type
      make_WF (const std::string& v)
      {
        return symbol_type (token::WF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_K (std::string v)
      {
        return symbol_type (token::K, std::move (v));
      }
#else
      static
      symbol_type
      make_K (const std::string& v)
      {
        return symbol_type (token::K, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_M (std::string v)
      {
        return symbol_type (token::M, std::move (v));
      }
#else
      static
      symbol_type
      make_M (const std::string& v)
      {
        return symbol_type (token::M, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_B (std::string v)
      {
        return symbol_type (token::B, std::move (v));
      }
#else
      static
      symbol_type
      make_B (const std::string& v)
      {
        return symbol_type (token::B, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RUTA (std::string v)
      {
        return symbol_type (token::RUTA, std::move (v));
      }
#else
      static
      symbol_type
      make_RUTA (const std::string& v)
      {
        return symbol_type (token::RUTA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_P (std::string v)
      {
        return symbol_type (token::P, std::move (v));
      }
#else
      static
      symbol_type
      make_P (const std::string& v)
      {
        return symbol_type (token::P, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_E (std::string v)
      {
        return symbol_type (token::E, std::move (v));
      }
#else
      static
      symbol_type
      make_E (const std::string& v)
      {
        return symbol_type (token::E, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_L (std::string v)
      {
        return symbol_type (token::L, std::move (v));
      }
#else
      static
      symbol_type
      make_L (const std::string& v)
      {
        return symbol_type (token::L, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FAST (std::string v)
      {
        return symbol_type (token::FAST, std::move (v));
      }
#else
      static
      symbol_type
      make_FAST (const std::string& v)
      {
        return symbol_type (token::FAST, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FULL (std::string v)
      {
        return symbol_type (token::FULL, std::move (v));
      }
#else
      static
      symbol_type
      make_FULL (const std::string& v)
      {
        return symbol_type (token::FULL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CADENA (std::string v)
      {
        return symbol_type (token::CADENA, std::move (v));
      }
#else
      static
      symbol_type
      make_CADENA (const std::string& v)
      {
        return symbol_type (token::CADENA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOSFS (std::string v)
      {
        return symbol_type (token::DOSFS, std::move (v));
      }
#else
      static
      symbol_type
      make_DOSFS (const std::string& v)
      {
        return symbol_type (token::DOSFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRESFS (std::string v)
      {
        return symbol_type (token::TRESFS, std::move (v));
      }
#else
      static
      symbol_type
      make_TRESFS (const std::string& v)
      {
        return symbol_type (token::TRESFS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MBR (std::string v)
      {
        return symbol_type (token::MBR, std::move (v));
      }
#else
      static
      symbol_type
      make_MBR (const std::string& v)
      {
        return symbol_type (token::MBR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DISK (std::string v)
      {
        return symbol_type (token::DISK, std::move (v));
      }
#else
      static
      symbol_type
      make_DISK (const std::string& v)
      {
        return symbol_type (token::DISK, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REPRUTA (std::string v)
      {
        return symbol_type (token::REPRUTA, std::move (v));
      }
#else
      static
      symbol_type
      make_REPRUTA (const std::string& v)
      {
        return symbol_type (token::REPRUTA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GUION ()
      {
        return symbol_type (token::GUION);
      }
#else
      static
      symbol_type
      make_GUION ()
      {
        return symbol_type (token::GUION);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IGUAL ()
      {
        return symbol_type (token::IGUAL);
      }
#else
      static
      symbol_type
      make_IGUAL ()
      {
        return symbol_type (token::IGUAL);
      }
#endif


  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 57,     ///< Last index in yytable_.
      yynnts_ = 8,  ///< Number of nonterminal symbols.
      yyfinal_ = 22, ///< Termination state number.
      yyntokens_ = 43  ///< Number of tokens.
    };


    // User arguments.
    Driver& driver;
  };

  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
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
      35,    36,    37,    38,    39,    40,    41,    42
    };
    const int user_token_number_max_ = 297;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
  {
    switch (this->type_get ())
    {
      case 46: // comando
        value.move< Comando > (std::move (that.value));
        break;

      case 48: // parametro
        value.move< Parametro > (std::move (that.value));
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "SIZE"
      case 12: // "F"
      case 13: // "PATH"
      case 14: // "U"
      case 15: // "TYPE"
      case 16: // "DELETE"
      case 17: // "NAME"
      case 18: // "ADD"
      case 19: // "ID"
      case 20: // "FS"
      case 21: // "ROOT"
      case 22: // "NUM"
      case 23: // "BF"
      case 24: // "FF"
      case 25: // "WF"
      case 26: // "K"
      case 27: // "M"
      case 28: // "B"
      case 29: // "RUTA"
      case 30: // "P"
      case 31: // "E"
      case 32: // "L"
      case 33: // "FAST"
      case 34: // "FULL"
      case 35: // "CADENA"
      case 36: // "DOSFS"
      case 37: // "TRESFS"
      case 38: // "MBR"
      case 39: // "DISK"
      case 40: // "REPRUTA"
      case 49: // nom_param
      case 50: // atributo
        value.move< std::string > (std::move (that.value));
        break;

      case 47: // lista_param
        value.move< std::vector<Parametro> > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->type_get ())
    {
      case 46: // comando
        value.copy< Comando > (YY_MOVE (that.value));
        break;

      case 48: // parametro
        value.copy< Parametro > (YY_MOVE (that.value));
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "SIZE"
      case 12: // "F"
      case 13: // "PATH"
      case 14: // "U"
      case 15: // "TYPE"
      case 16: // "DELETE"
      case 17: // "NAME"
      case 18: // "ADD"
      case 19: // "ID"
      case 20: // "FS"
      case 21: // "ROOT"
      case 22: // "NUM"
      case 23: // "BF"
      case 24: // "FF"
      case 25: // "WF"
      case 26: // "K"
      case 27: // "M"
      case 28: // "B"
      case 29: // "RUTA"
      case 30: // "P"
      case 31: // "E"
      case 32: // "L"
      case 33: // "FAST"
      case 34: // "FULL"
      case 35: // "CADENA"
      case 36: // "DOSFS"
      case 37: // "TRESFS"
      case 38: // "MBR"
      case 39: // "DISK"
      case 40: // "REPRUTA"
      case 49: // nom_param
      case 50: // atributo
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case 47: // lista_param
        value.copy< std::vector<Parametro> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 46: // comando
        value.move< Comando > (YY_MOVE (s.value));
        break;

      case 48: // parametro
        value.move< Parametro > (YY_MOVE (s.value));
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "SIZE"
      case 12: // "F"
      case 13: // "PATH"
      case 14: // "U"
      case 15: // "TYPE"
      case 16: // "DELETE"
      case 17: // "NAME"
      case 18: // "ADD"
      case 19: // "ID"
      case 20: // "FS"
      case 21: // "ROOT"
      case 22: // "NUM"
      case 23: // "BF"
      case 24: // "FF"
      case 25: // "WF"
      case 26: // "K"
      case 27: // "M"
      case 28: // "B"
      case 29: // "RUTA"
      case 30: // "P"
      case 31: // "E"
      case 32: // "L"
      case 33: // "FAST"
      case 34: // "FULL"
      case 35: // "CADENA"
      case 36: // "DOSFS"
      case 37: // "TRESFS"
      case 38: // "MBR"
      case 39: // "DISK"
      case 40: // "REPRUTA"
      case 49: // nom_param
      case 50: // atributo
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case 47: // lista_param
        value.move< std::vector<Parametro> > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

} // yy
#line 2041 "parser.tab.hh"





#endif // !YY_YY_PARSER_TAB_HH_INCLUDED
