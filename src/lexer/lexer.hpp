#pragma once
#include <utf8.hpp>
#include <token.hpp>

#include <vector>
#include <fstream>
#include <stdlib.h>

typedef std::string String;
typedef std::string &StringRef;
typedef const std::string &StringConstRef;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef std::ifstream InputFileStream;
typedef std::istreambuf_iterator<char> EndOfStreamIterator;

struct Lexer
{
  explicit Lexer(StringConstRef filename, StringConstRef buffer);

  void Tokenize();

  String NextCharacter(Bool update_index = true);
  String PeekCharacter();

  void ParseComment(StringRef character);
  void ParseLineComment(StringRef character);
  void ParseBlockComment(StringRef character);

  void ParseNumber(StringRef character);

  bool IsValidSymbol(StringRef character);
  void ParseSymbol(StringRef character);

  bool IsValidWhitespace(StringRef character);
  void ParseWhitespace(StringRef character);

  void ParseStringLiteral(StringRef character);
  void ParsePunctuation(StringRef character);

  void MergeTokenPair(size_t &index, Token::Type first, Token::Type second, Token::Type result, const String &result_value);
  void InsertKeywordVar(size_t &index);

  TokenVector tokens;
  String file;
  UnsignedInt line;
  UnsignedInt cursor;
  String buffer;
  UnsignedInt index;
  bool exception_to_semicolon_rule;
};