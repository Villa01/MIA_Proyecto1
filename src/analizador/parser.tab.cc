// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 28 "parser.yy"

   using namespace std;
   #include <stdio.h>
   #include <iostream>
   #include <string>
   #include <vector>
   
   #include "driver.h"

#line 50 "parser.tab.cc"


#include "parser.tab.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 127 "parser.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.type_get ())
    {
      case 47: // comando
        value.YY_MOVE_OR_COPY< Comando > (YY_MOVE (that.value));
        break;

      case 49: // parametro
        value.YY_MOVE_OR_COPY< Parametro > (YY_MOVE (that.value));
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "PAUSE"
      case 12: // "SIZE"
      case 13: // "F"
      case 14: // "PATH"
      case 15: // "U"
      case 16: // "TYPE"
      case 17: // "DELETE"
      case 18: // "NAME"
      case 19: // "ADD"
      case 20: // "ID"
      case 21: // "FS"
      case 22: // "ROOT"
      case 23: // "NUM"
      case 24: // "BF"
      case 25: // "FF"
      case 26: // "WF"
      case 27: // "K"
      case 28: // "M"
      case 29: // "B"
      case 30: // "RUTA"
      case 31: // "P"
      case 32: // "E"
      case 33: // "L"
      case 34: // "FAST"
      case 35: // "FULL"
      case 36: // "CADENA"
      case 37: // "DOSFS"
      case 38: // "TRESFS"
      case 39: // "MBR"
      case 40: // "DISK"
      case 41: // "REPRUTA"
      case 50: // nom_param
      case 51: // atributo
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 48: // lista_param
        value.YY_MOVE_OR_COPY< std::vector<Parametro> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.type_get ())
    {
      case 47: // comando
        value.move< Comando > (YY_MOVE (that.value));
        break;

      case 49: // parametro
        value.move< Parametro > (YY_MOVE (that.value));
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "PAUSE"
      case 12: // "SIZE"
      case 13: // "F"
      case 14: // "PATH"
      case 15: // "U"
      case 16: // "TYPE"
      case 17: // "DELETE"
      case 18: // "NAME"
      case 19: // "ADD"
      case 20: // "ID"
      case 21: // "FS"
      case 22: // "ROOT"
      case 23: // "NUM"
      case 24: // "BF"
      case 25: // "FF"
      case 26: // "WF"
      case 27: // "K"
      case 28: // "M"
      case 29: // "B"
      case 30: // "RUTA"
      case 31: // "P"
      case 32: // "E"
      case 33: // "L"
      case 34: // "FAST"
      case 35: // "FULL"
      case 36: // "CADENA"
      case 37: // "DOSFS"
      case 38: // "TRESFS"
      case 39: // "MBR"
      case 40: // "DISK"
      case 41: // "REPRUTA"
      case 50: // nom_param
      case 51: // atributo
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 48: // lista_param
        value.move< std::vector<Parametro> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 47: // comando
        value.copy< Comando > (that.value);
        break;

      case 49: // parametro
        value.copy< Parametro > (that.value);
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "PAUSE"
      case 12: // "SIZE"
      case 13: // "F"
      case 14: // "PATH"
      case 15: // "U"
      case 16: // "TYPE"
      case 17: // "DELETE"
      case 18: // "NAME"
      case 19: // "ADD"
      case 20: // "ID"
      case 21: // "FS"
      case 22: // "ROOT"
      case 23: // "NUM"
      case 24: // "BF"
      case 25: // "FF"
      case 26: // "WF"
      case 27: // "K"
      case 28: // "M"
      case 29: // "B"
      case 30: // "RUTA"
      case 31: // "P"
      case 32: // "E"
      case 33: // "L"
      case 34: // "FAST"
      case 35: // "FULL"
      case 36: // "CADENA"
      case 37: // "DOSFS"
      case 38: // "TRESFS"
      case 39: // "MBR"
      case 40: // "DISK"
      case 41: // "REPRUTA"
      case 50: // nom_param
      case 51: // atributo
        value.copy< std::string > (that.value);
        break;

      case 48: // lista_param
        value.copy< std::vector<Parametro> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 47: // comando
        value.move< Comando > (that.value);
        break;

      case 49: // parametro
        value.move< Parametro > (that.value);
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "PAUSE"
      case 12: // "SIZE"
      case 13: // "F"
      case 14: // "PATH"
      case 15: // "U"
      case 16: // "TYPE"
      case 17: // "DELETE"
      case 18: // "NAME"
      case 19: // "ADD"
      case 20: // "ID"
      case 21: // "FS"
      case 22: // "ROOT"
      case 23: // "NUM"
      case 24: // "BF"
      case 25: // "FF"
      case 26: // "WF"
      case 27: // "K"
      case 28: // "M"
      case 29: // "B"
      case 30: // "RUTA"
      case 31: // "P"
      case 32: // "E"
      case 33: // "L"
      case 34: // "FAST"
      case 35: // "FULL"
      case 36: // "CADENA"
      case 37: // "DOSFS"
      case 38: // "TRESFS"
      case 39: // "MBR"
      case 40: // "DISK"
      case 41: // "REPRUTA"
      case 50: // nom_param
      case 51: // atributo
        value.move< std::string > (that.value);
        break;

      case 48: // lista_param
        value.move< std::vector<Parametro> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 47: // comando
        yylhs.value.emplace< Comando > ();
        break;

      case 49: // parametro
        yylhs.value.emplace< Parametro > ();
        break;

      case 3: // "MKDISK"
      case 4: // "RMDISK"
      case 5: // "FDISK"
      case 6: // "EXEC"
      case 7: // "TMOUNT"
      case 8: // "TUNMOUNT"
      case 9: // "MKFS"
      case 10: // "REP"
      case 11: // "PAUSE"
      case 12: // "SIZE"
      case 13: // "F"
      case 14: // "PATH"
      case 15: // "U"
      case 16: // "TYPE"
      case 17: // "DELETE"
      case 18: // "NAME"
      case 19: // "ADD"
      case 20: // "ID"
      case 21: // "FS"
      case 22: // "ROOT"
      case 23: // "NUM"
      case 24: // "BF"
      case 25: // "FF"
      case 26: // "WF"
      case 27: // "K"
      case 28: // "M"
      case 29: // "B"
      case 30: // "RUTA"
      case 31: // "P"
      case 32: // "E"
      case 33: // "L"
      case 34: // "FAST"
      case 35: // "FULL"
      case 36: // "CADENA"
      case 37: // "DOSFS"
      case 38: // "TRESFS"
      case 39: // "MBR"
      case 40: // "DISK"
      case 41: // "REPRUTA"
      case 50: // nom_param
      case 51: // atributo
        yylhs.value.emplace< std::string > ();
        break;

      case 48: // lista_param
        yylhs.value.emplace< std::vector<Parametro> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 56 "parser.yy"
                              {}
#line 822 "parser.tab.cc"
    break;

  case 3:
#line 59 "parser.yy"
                                            {}
#line 828 "parser.tab.cc"
    break;

  case 4:
#line 60 "parser.yy"
                              {}
#line 834 "parser.tab.cc"
    break;

  case 5:
#line 64 "parser.yy"
               {
                  Mkdisk m;
                  m.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  m.assignParameters();
                  m.createDisk();
               }
#line 845 "parser.tab.cc"
    break;

  case 6:
#line 71 "parser.yy"
               {
                  Rmdisk r;
                  r.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  r.assignParameters();
                  r.deleteDisk();
               }
#line 856 "parser.tab.cc"
    break;

  case 7:
#line 78 "parser.yy"
               {
                  Fdisk f;
                  f.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  f.assignParameters();
                  f.start_action();
               }
#line 867 "parser.tab.cc"
    break;

  case 8:
#line 85 "parser.yy"
               { 
                  Script s(yystack_[0].value.as < std::vector<Parametro> > ());

               }
#line 876 "parser.tab.cc"
    break;

  case 9:
#line 90 "parser.yy"
               {
                  Mount m(&driver.parts);
                  m.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  m.assignParameters();
                  m.mount();
               }
#line 887 "parser.tab.cc"
    break;

  case 10:
#line 97 "parser.yy"
               {  
                  Unmount m(&driver.parts);
                  m.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  m.assignParameters();
                  m.unmount();

               }
#line 899 "parser.tab.cc"
    break;

  case 11:
#line 105 "parser.yy"
               {
                  Mkfs f(&driver.parts);
                  f.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  f.assignParameters();
                  f.format();
               }
#line 910 "parser.tab.cc"
    break;

  case 12:
#line 112 "parser.yy"
               {
                  Rep r(&driver.parts);
                  r.agregarParametros(yystack_[0].value.as < std::vector<Parametro> > ());
                  r.assignParameters();
                  r.selectReport();
               }
#line 921 "parser.tab.cc"
    break;

  case 13:
#line 119 "parser.yy"
               {
                  cout<<"\e[0;31m Presione cualquier letra para continuar..."<<endl;
                  cin.ignore();
               }
#line 930 "parser.tab.cc"
    break;

  case 14:
#line 126 "parser.yy"
                  {
                     yylhs.value.as < std::vector<Parametro> > ()=yystack_[1].value.as < std::vector<Parametro> > ();
                     yylhs.value.as < std::vector<Parametro> > ().push_back(yystack_[0].value.as < Parametro > ());
                  }
#line 939 "parser.tab.cc"
    break;

  case 15:
#line 131 "parser.yy"
                  {  
                     vector<Parametro> params;
                     params.push_back(yystack_[0].value.as < Parametro > ());
                     yylhs.value.as < std::vector<Parametro> > () = params;
                  }
#line 949 "parser.tab.cc"
    break;

  case 16:
#line 139 "parser.yy"
               {  
                  Parametro param;
                  param.setNombre(yystack_[2].value.as < std::string > ());
                  param.setValor(yystack_[0].value.as < std::string > ());
                  yylhs.value.as < Parametro > () = param;
               }
#line 960 "parser.tab.cc"
    break;

  case 17:
#line 147 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 966 "parser.tab.cc"
    break;

  case 18:
#line 148 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 972 "parser.tab.cc"
    break;

  case 19:
#line 149 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 978 "parser.tab.cc"
    break;

  case 20:
#line 150 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 984 "parser.tab.cc"
    break;

  case 21:
#line 151 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 990 "parser.tab.cc"
    break;

  case 22:
#line 152 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 996 "parser.tab.cc"
    break;

  case 23:
#line 153 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1002 "parser.tab.cc"
    break;

  case 24:
#line 154 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1008 "parser.tab.cc"
    break;

  case 25:
#line 155 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1014 "parser.tab.cc"
    break;

  case 26:
#line 156 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1020 "parser.tab.cc"
    break;

  case 27:
#line 157 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1026 "parser.tab.cc"
    break;

  case 28:
#line 158 "parser.yy"
                        { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1032 "parser.tab.cc"
    break;

  case 29:
#line 161 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1038 "parser.tab.cc"
    break;

  case 30:
#line 162 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1044 "parser.tab.cc"
    break;

  case 31:
#line 163 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1050 "parser.tab.cc"
    break;

  case 32:
#line 164 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1056 "parser.tab.cc"
    break;

  case 33:
#line 165 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1062 "parser.tab.cc"
    break;

  case 34:
#line 166 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1068 "parser.tab.cc"
    break;

  case 35:
#line 167 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1074 "parser.tab.cc"
    break;

  case 36:
#line 168 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1080 "parser.tab.cc"
    break;

  case 37:
#line 169 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1086 "parser.tab.cc"
    break;

  case 38:
#line 170 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1092 "parser.tab.cc"
    break;

  case 39:
#line 171 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1098 "parser.tab.cc"
    break;

  case 40:
#line 172 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1104 "parser.tab.cc"
    break;

  case 41:
#line 173 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1110 "parser.tab.cc"
    break;

  case 42:
#line 174 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1116 "parser.tab.cc"
    break;

  case 43:
#line 175 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1122 "parser.tab.cc"
    break;

  case 44:
#line 176 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1128 "parser.tab.cc"
    break;

  case 45:
#line 177 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1134 "parser.tab.cc"
    break;

  case 46:
#line 178 "parser.yy"
                     { yylhs.value.as < std::string > ()=yystack_[0].value.as < std::string > (); }
#line 1140 "parser.tab.cc"
    break;


#line 1144 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -22;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
       8,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -22,
      55,     8,   -22,   -12,   -21,   -22,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,    13,   -22,     7,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     2,     4,     0,     5,    15,     6,     7,     8,     9,
      10,    11,    12,     1,     3,    17,    19,    20,    21,    22,
      23,    24,    25,    26,    18,    28,    27,     0,    14,     0,
      29,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    30,    31,    45,    46,    16
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -22,   -22,   -22,    47,    46,     6,   -22,   -22
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    14,    15,    37,    58
  };

  const signed char
  Parser::yytable_[] =
  {
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      38,    13,    38,    38,    38,    38,    38,    38,    38,    36,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    16,    17,
      18,    19,    20,    21,    22,    23,    39,     0,    24
  };

  const signed char
  Parser::yycheck_[] =
  {
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      14,    42,    16,    17,    18,    19,    20,    21,    22,    41,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     2,     3,
       4,     5,     6,     7,     8,     0,    43,    -1,    11
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      45,    46,    47,    42,    48,    49,    48,    48,    48,    48,
      48,    48,    48,     0,    47,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    41,    50,    49,    43,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    51
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    48,    48,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "\"MKDISK\"", "\"RMDISK\"", "\"FDISK\"",
  "\"EXEC\"", "\"TMOUNT\"", "\"TUNMOUNT\"", "\"MKFS\"", "\"REP\"",
  "\"PAUSE\"", "\"SIZE\"", "\"F\"", "\"PATH\"", "\"U\"", "\"TYPE\"",
  "\"DELETE\"", "\"NAME\"", "\"ADD\"", "\"ID\"", "\"FS\"", "\"ROOT\"",
  "\"NUM\"", "\"BF\"", "\"FF\"", "\"WF\"", "\"K\"", "\"M\"", "\"B\"",
  "\"RUTA\"", "\"P\"", "\"E\"", "\"L\"", "\"FAST\"", "\"FULL\"",
  "\"CADENA\"", "\"DOSFS\"", "\"TRESFS\"", "\"MBR\"", "\"DISK\"",
  "\"REPRUTA\"", "\"GUION\"", "\"IGUAL\"", "$accept", "inicio",
  "lista_comandos", "comando", "lista_param", "parametro", "nom_param",
  "atributo", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    56,    56,    59,    60,    63,    70,    77,    84,    89,
      96,   104,   111,   118,   125,   130,   138,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1563 "parser.tab.cc"

#line 181 "parser.yy"


void yy::Parser::error( const std::string& error){
  std::cout <<"\e[0;31m--- ERROR:"<< error << std::endl;
}
