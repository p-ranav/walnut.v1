#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

namespace walnut
{

  Lexer::Lexer(StringConstRef filename, StringConstRef buffer) : file(filename),
    line(1),
    cursor(1),
    buffer(buffer),
    index(0) {}

  void Lexer::Tokenize()
  {
    for (index = 0; index < buffer.size();)
    {
      if (isutf(buffer[index]))
      {
        String character = PeekCharacter();

        if (character[0] == '/')
          ParseComment(character);

        else if (isdigit(character[0]))
          ParseNumber(character);

        else if (character[0] == '"')
          ParseStringLiteral(character);

        else if (character[0] == '\'')
          ParseCharacter(character);

        else if (IsValidPunctuation(character))
          ParsePunctuation(character);

        else if (IsValidSymbol(character))
          ParseSymbol(character);

        else if (IsValidWhitespace(character))
          ParseWhitespace(character);

        if (character[0] == '\n')
        {
          line += 1;
          NextCharacter();
          cursor = 1;
        }

        continue;
      }
    }

    // update token type for 2-character operator sequences
    for (size_t i = 0; i < tokens.size(); i++)
    {
      // assignment operators
      MergeTokenPair(i, Token::Type::ADDITION_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::ADD_AND_ASSIGN_OPERATOR, "+=");
      MergeTokenPair(i, Token::Type::SUBTRACTION_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::SUBTRACT_AND_ASSIGN_OPERATOR, "-=");
      MergeTokenPair(i, Token::Type::MULTIPLICATION_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::MULTIPLY_AND_ASSIGN_OPERATOR, "*=");
      MergeTokenPair(i, Token::Type::DIVISION_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::DIVIDE_AND_ASSIGN_OPERATOR, "/=");
      MergeTokenPair(i, Token::Type::MODULUS_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::MODULUS_AND_ASSIGN_OPERATOR, "%=");

      // comparison operators
      MergeTokenPair(i, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::EQUALITY_OPERATOR, "==");
      MergeTokenPair(i, Token::Type::LOGICAL_NOT_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::INEQUALITY_OPERATOR, "!=");
      MergeTokenPair(i, Token::Type::GREATER_THAN_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR, ">=");
      MergeTokenPair(i, Token::Type::LESSER_THAN_OPERATOR, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR, "<=");

      // bitwise operators
      MergeTokenPair(i, Token::Type::LESSER_THAN_OPERATOR, Token::Type::LESSER_THAN_OPERATOR, Token::Type::BITWISE_LEFT_SHIFT_OPERATOR, "<<");
      MergeTokenPair(i, Token::Type::GREATER_THAN_OPERATOR, Token::Type::GREATER_THAN_OPERATOR, Token::Type::BITWISE_RIGHT_SHIFT_OPERATOR, ">>");

      // logical operators
      MergeTokenPair(i, Token::Type::BITWISE_AND_OPERATOR, Token::Type::BITWISE_AND_OPERATOR, Token::Type::LOGICAL_AND_OPERATOR, "and");
      MergeTokenPair(i, Token::Type::BITWISE_OR_OPERATOR, Token::Type::BITWISE_OR_OPERATOR, Token::Type::LOGICAL_OR_OPERATOR, "or");

      MergeTokenPair(i, Token::Type::ASSIGNMENT_OPERATOR, Token::Type::GREATER_THAN_OPERATOR, Token::Type::ARROW_OPERATOR, "=>");
      MergeTokenPair(i, Token::Type::KEYWORD_ELSE, Token::Type::KEYWORD_IF, Token::Type::KEYWORD_ELSE_IF, "else if");

    }

    for (size_t i = 0; i < tokens.size(); i++)
      InsertKeywordVar(i);

    Token eof(file, line, cursor, Token::Type::END_OF_FILE, "EOF");
    tokens.push_back(eof);

    //for (auto& token : tokens)
    //  std::cout << "[LEXER] " << token.value << std::endl;
  }

  String Lexer::NextCharacter(Bool update_index)
  {
    String result = "";
    int length = u8_seqlen(&(buffer[index]));

    for (int i = 0; i < length; i++, index++)
      result += buffer[index];

    if (!update_index)
      index -= length;
    else
      cursor += 1;

    return result;
  }

  String Lexer::PeekCharacter()
  {
    return NextCharacter(false);
  }

  void Lexer::MergeTokenPair(size_t &index, Token::Type first, Token::Type second, Token::Type result, StringConstRef result_value)
  {
    auto &current = tokens[index].type;
    auto next = (index + 1) < tokens.size() ? tokens[index + 1].type : Token::Type::INVALID;

    if (current == first && next == second)
    {
      current = result;
      tokens[index].value = result_value;
      if (tokens[index].cursor != 1)
        tokens[index].cursor -= 1;
      tokens.erase(tokens.begin() + index + 1);
    }
  }

  void Lexer::InsertKeywordVar(size_t &index)
  {
    auto &current = tokens[index].type;
    auto next = (index + 1) < tokens.size() ? tokens[index + 1].type : Token::Type::INVALID;

    if (current == Token::Type::SYMBOL && next == Token::Type::ASSIGNMENT_OPERATOR)
    {
      Token result(tokens[index].file, tokens[index].line, tokens[index].cursor, Token::Type::KEYWORD_VAR, "var");
      tokens.insert(tokens.begin() + index, result);
      index += 1;
    }
  }

  void Lexer::ParseComment(StringRef character)
  {
    character = NextCharacter();
    String peek_character = PeekCharacter();
    if (peek_character[0] == '/')
    {
      NextCharacter();
      ParseLineComment(peek_character);
    }
    else if (peek_character[0] == '*')
      ParseBlockComment(peek_character);
    else
    {
      cursor -= 1;
      Token result(file, line, cursor, Token::Type::DIVISION_OPERATOR, character);
      cursor += 1;
      tokens.push_back(result);
    }
  }

  void Lexer::ParseLineComment(StringRef character)
  {
    while (character[0] != 0x0A && index < buffer.size())
      character = NextCharacter();

    if (character[0] != EOF)
    {
      line += 1;
      cursor = 1;
    }
  }

  void Lexer::ParseBlockComment(StringRef character)
  {
    while (true)
    {
      character = PeekCharacter();
      if (character[0] == EOF)
        throw std::runtime_error("unterminated block comment");

      if (character[0] == 0x0A)
      {
        NextCharacter();
        line += 1;
        cursor = 1;
        continue;
      }

      if (character[0] == '*')
      {
        NextCharacter();
        character = PeekCharacter();

        if (character[0] == EOF)
          throw std::runtime_error("unterminated block comment");

        if (character[0] == '/')
        {
          NextCharacter();
          return;
        }
      }
      NextCharacter();
    }
  }

  void Lexer::ParseNumber(StringRef character)
  {
    Token result(file, line, cursor, Token::Type::INTEGER, character);
    character = NextCharacter();

    while (true)
    {
      character = PeekCharacter();
      if (character.size() == 1 &&
        (character[0] == '.' || isdigit(character[0])))
      {
        character = NextCharacter();
        result.value += character;
        continue;
      }
      break;
    }

    if (result.value.find(".") != std::string::npos)
      result.type = Token::Type::DOUBLE;

    tokens.push_back(result);
  }

  bool Lexer::IsValidSymbol(StringRef character)
  {
    for (auto &c : character)
    {
      if ((c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        (c == '_') ||
        ((unsigned char)c >= 0x80))
        continue;
      else
        return false;
    }
    return true;
  }

  void Lexer::ParseSymbol(StringRef character)
  {
    Token result(file, line, cursor, Token::Type::SYMBOL, "");

    while (true)
    {
      character = PeekCharacter();
      if (IsValidSymbol(character))
      {
        result.value += character;
        character = NextCharacter();
        continue;
      }
      break;
    }

    if (result.value == "true")
      result.type = Token::Type::KEYWORD_TRUE;
    else if (result.value == "false")
      result.type = Token::Type::KEYWORD_FALSE;
    else if (result.value == "if")
      result.type = Token::Type::KEYWORD_IF;
    else if (result.value == "else")
      result.type = Token::Type::KEYWORD_ELSE;
    else if (result.value == "while")
      result.type = Token::Type::KEYWORD_WHILE;
    else if (result.value == "for")
      result.type = Token::Type::KEYWORD_FOR;
    else if (result.value == "function")
      result.type = Token::Type::KEYWORD_FUNCTION;
    else if (result.value == "ƒ")
      result.type = Token::Type::KEYWORD_FUNCTION;
    else if (result.value == "𝑓")
      result.type = Token::Type::KEYWORD_FUNCTION;
    else if (result.value == "return")
      result.type = Token::Type::KEYWORD_RETURN;
    else if (result.value == "in")
      result.type = Token::Type::KEYWORD_IN;
    else if (result.value == "and")
      result.type = Token::Type::LOGICAL_AND_OPERATOR;
    else if (result.value == "or")
      result.type = Token::Type::LOGICAL_OR_OPERATOR;
    else if (result.value == "not")
      result.type = Token::Type::LOGICAL_NOT_OPERATOR;
    else if (result.value == "import")
      result.type = Token::Type::KEYWORD_IMPORT;

    tokens.push_back(result);
  }

  bool Lexer::IsValidWhitespace(StringRef character)
  {
    return (
      character[0] == ' ' ||
      character[0] == 0x09 ||
      character[0] == 0x08 ||
      character[0] == 0x0D);
  }

  void Lexer::ParseWhitespace(StringRef character)
  {
    NextCharacter();
    while (true)
    {
      character = PeekCharacter();
      if (IsValidWhitespace(character))
        character = NextCharacter();
      else
        return;
    }
  }

  void Lexer::ParseCharacter(StringRef character)
  {
    Token result(file, line, cursor, Token::Type::CHARACTER);
    character = NextCharacter();

    while (true)
    {
      character = PeekCharacter();

      if (character[0] == '\\')
      {
        character = NextCharacter();
        if (character[0] == '\'' || character[0] == '\\')
        {
          character = NextCharacter();

          if (character == "n")
          {
            result.value += '\n';
          }
          else
          {
            result.value += character;
          }
          continue;
        }

        else if (character[0] == 'n')
        {
          character = NextCharacter();
          result.value += '\n';
        }

        if (character[0] == 0x0A || character[0] == EOF)
          throw std::runtime_error("unterminated string literal");

        result.value += character;
        continue;
      }

      if (character[0] != '\'' && character[0] != EOF)
      {
        character = NextCharacter();
        result.value += character;
        continue;
      }

      if (character[0] == 0x0A || character[0] == EOF)
        throw std::runtime_error("unterminated string literal");

      NextCharacter();
      break;
    }

    // TODO: check length of result and warn user if necessary
    // x = 'ABC' will be recognized as a character
    // when the user probably intends to declare a string

    tokens.push_back(result);
  }

  void Lexer::ParseStringLiteral(StringRef character)
  {
    Token result(file, line, cursor, Token::Type::STRING_LITERAL);
    character = NextCharacter();

    while (true)
    {
      character = PeekCharacter();

      if (character[0] == '\\')
      {
        character = NextCharacter();
        if (character[0] == '\"' || character[0] == '\\')
        {
          character = NextCharacter();

          if (character == "n")
          {
            result.value += '\n';
          }
          else
          {
            // TODO: maybe report error here - unrecognized escape sequence
            result.value += character;
          }
          continue;
        }

        else if (character[0] == 'n')
        {
          character = NextCharacter();
          result.value += '\n';
        }

        if (character[0] == 0x0A || character[0] == EOF)
          throw std::runtime_error("unterminated string literal");

        result.value += character;
        continue;
      }

      if (character[0] != '\"' && character[0] != EOF)
      {
        character = NextCharacter();
        result.value += character;
        continue;
      }

      if (character[0] == 0x0A || character[0] == EOF)
        throw std::runtime_error("unterminated string literal");

      NextCharacter();
      break;
    }
    tokens.push_back(result);
  }

  bool Lexer::IsValidPunctuation(StringRef character)
  {
    return (
      ispunct(character[0]) ||
      character == "＝" || character == "≥" || character == "≤" ||
      character == "≠" || character == "⋅" || character == "•" ||
      character == "×");
  }

  void Lexer::ParsePunctuation(StringRef character)
  {
    Token result(file, line, cursor, Token::Type::PUNCTUATION, character);
    NextCharacter();

    // delimiters
    if (result.value == ".")
      result.type = Token::Type::DOT_OPERATOR;
    else if (result.value == ",")
      result.type = Token::Type::COMMA_OPERATOR;
    else if (result.value == ":")
      result.type = Token::Type::COLON_OPERATOR;
    else if (result.value == ";")
      result.type = Token::Type::SEMI_COLON_OPERATOR;

    // comparison operators
    else if (result.value == ">")
      result.type = Token::Type::GREATER_THAN_OPERATOR;
    else if (result.value == "<")
      result.type = Token::Type::LESSER_THAN_OPERATOR;

    // arithmetic operators
    else if (result.value == "+")
      result.type = Token::Type::ADDITION_OPERATOR;
    else if (result.value == "-")
      result.type = Token::Type::SUBTRACTION_OPERATOR;
    else if (result.value == "*")
      result.type = Token::Type::MULTIPLICATION_OPERATOR;
    else if (result.value == "/")
      result.type = Token::Type::DIVISION_OPERATOR;
    else if (result.value == "%")
      result.type = Token::Type::MODULUS_OPERATOR;

    // assignment operators */
    else if (result.value == "=")
      result.type = Token::Type::ASSIGNMENT_OPERATOR;

    // brackets, braces and PARENTHESIS
    else if (result.value == "(")
      result.type = Token::Type::LEFT_PARENTHESIS;
    else if (result.value == "{")
      result.type = Token::Type::LEFT_CURLY_BRACES;
    else if (result.value == "[")
      result.type = Token::Type::LEFT_SQUARE_BRACKETS;
    else if (result.value == ")")
      result.type = Token::Type::RIGHT_PARENTHESIS;
    else if (result.value == "}")
      result.type = Token::Type::RIGHT_CURLY_BRACES;
    else if (result.value == "]")
      result.type = Token::Type::RIGHT_SQUARE_BRACKETS;

    // bitwise operators
    else if (result.value == "&")
      result.type = Token::Type::BITWISE_AND_OPERATOR;
    else if (result.value == "|")
      result.type = Token::Type::BITWISE_OR_OPERATOR;
    else if (result.value == "^")
      result.type = Token::Type::BITWISE_XOR_OPERATOR;
    else if (result.value == "~")
      result.type = Token::Type::BITWISE_ONES_COMPLEMENT_OPERATOR;

    // logical operators
    else if (result.value == "!")
      result.type = Token::Type::LOGICAL_NOT_OPERATOR;

    // unicode operators
    else if (result.value == "＝")
      result.type = Token::Type::ASSIGNMENT_OPERATOR;
    else if (result.value == "≥")
      result.type = Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR;
    else if (result.value == "≤")
      result.type = Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR;
    else if (result.value == "≠")
      result.type = Token::Type::INEQUALITY_OPERATOR;
    else if (result.value == "⋅")
      result.type = Token::Type::MULTIPLICATION_OPERATOR;
    else if (result.value == "•")
      result.type = Token::Type::MULTIPLICATION_OPERATOR;
    else if (result.value == "×")
      result.type = Token::Type::MULTIPLICATION_OPERATOR;

    tokens.push_back(result);
  }

}