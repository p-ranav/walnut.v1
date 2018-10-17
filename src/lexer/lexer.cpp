#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

Lexer::Lexer(StringConstRef filename, StringConstRef buffer) : 
  file(filename), 
  line(1), 
  cursor(0),
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

      else if (IsValidPunctuation(character))
        ParsePunctuation(character);

      else if (IsValidSymbol(character))
        ParseSymbol(character);

      else if (IsValidWhitespace(character))
        ParseWhitespace(character);

      if (tokens.size() > 0) {
        if (tokens[tokens.size() - 1].type == TokenType::KEYWORD_IF)
          exception_to_semicolon_rule = true;
        else if (tokens[tokens.size() - 1].type == TokenType::KEYWORD_FUNCTION)
          exception_to_semicolon_rule = true;
        else if (tokens[tokens.size() - 1].type == TokenType::KEYWORD_WHILE)
          exception_to_semicolon_rule = true;
        else if (tokens[tokens.size() - 1].type == TokenType::LEFT_CURLY_BRACES)
          exception_to_semicolon_rule = false;
      }

      if (character[0] == '\n')
      {
        line += 1;
        cursor = 0;
      }

      // semicolon rule
      if (character[0] == '\n')
      {
        if (tokens.size() > 0)
        {
          Token previous = tokens[tokens.size() - 1];
          std::vector<TokenType> valid_tokens = { 
            TokenType::SYMBOL, TokenType::INTEGER, TokenType::DOUBLE, TokenType::STRING_LITERAL,
            TokenType::KEYWORD_TRUE, TokenType::KEYWORD_FALSE, TokenType::KEYWORD_RETURN,
            TokenType::RIGHT_PARENTHESIS, TokenType::RIGHT_CURLY_BRACES 
          };
          if (std::find(valid_tokens.begin(), valid_tokens.end(), previous.type) != valid_tokens.end())
          {
            if (!(previous.type == TokenType::RIGHT_PARENTHESIS && exception_to_semicolon_rule))
            {
              Token semi_colon(previous.file, previous.line, previous.cursor + 1, TokenType::SEMI_COLON_OPERATOR, ";");
              tokens.push_back(semi_colon);
            }
          }
        }
        NextCharacter();
      }

      continue;
    }
  }

  // update token type for 2-character operator sequences
  for (size_t i = 0; i < tokens.size(); i++)
  {
    // assignment operators
    MergeTokenPair(i, TokenType::ADDITION_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::ADD_AND_ASSIGN_OPERATOR, "+=");
    MergeTokenPair(i, TokenType::SUBTRACTION_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::SUBTRACT_AND_ASSIGN_OPERATOR, "-=");
    MergeTokenPair(i, TokenType::MULTIPLICATION_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::MULTIPLY_AND_ASSIGN_OPERATOR, "*=");
    MergeTokenPair(i, TokenType::DIVISION_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::DIVIDE_AND_ASSIGN_OPERATOR, "/=");
    MergeTokenPair(i, TokenType::MODULUS_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::MODULUS_AND_ASSIGN_OPERATOR, "%=");

    // comparison operators
    MergeTokenPair(i, TokenType::ASSIGNMENT_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::EQUALITY_OPERATOR, "==");
    MergeTokenPair(i, TokenType::LOGICAL_NOT_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::INEQUALITY_OPERATOR, "!=");
    MergeTokenPair(i, TokenType::GREATER_THAN_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::GREATER_THAN_OR_EQUAL_OPERATOR, ">=");
    MergeTokenPair(i, TokenType::LESSER_THAN_OPERATOR, TokenType::ASSIGNMENT_OPERATOR, TokenType::LESSER_THAN_OR_EQUAL_OPERATOR, "<=");

    // bitwise operators
    MergeTokenPair(i, TokenType::LESSER_THAN_OPERATOR, TokenType::LESSER_THAN_OPERATOR, TokenType::BITWISE_LEFT_SHIFT_OPERATOR, "<<");
    MergeTokenPair(i, TokenType::GREATER_THAN_OPERATOR, TokenType::GREATER_THAN_OPERATOR, TokenType::BITWISE_RIGHT_SHIFT_OPERATOR, ">>");

    // logical operators
    MergeTokenPair(i, TokenType::BITWISE_AND_OPERATOR, TokenType::BITWISE_AND_OPERATOR, TokenType::LOGICAL_AND_OPERATOR, "&&");
    MergeTokenPair(i, TokenType::BITWISE_OR_OPERATOR, TokenType::BITWISE_OR_OPERATOR, TokenType::BITWISE_OR_OPERATOR, "||");
  }

  for (size_t i = 0; i < tokens.size(); i++)
    InsertKeywordVar(i);

  Token eof(file, line, cursor, TokenType::END_OF_FILE, "EOF");
  tokens.push_back(eof);
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
  auto next = (index + 1) < tokens.size() ? tokens[index + 1].type : TokenType::INVALID;

  if (current == first && next == second)
  {
    current = result;
    tokens[index].value = result_value;
    tokens.erase(tokens.begin() + index + 1);
  }
}

void Lexer::InsertKeywordVar(size_t &index)
{
  auto& current = tokens[index].type;
  auto next = (index + 1) < tokens.size() ? tokens[index + 1].type : TokenType::INVALID;

  if (current == TokenType::SYMBOL && next == TokenType::ASSIGNMENT_OPERATOR)
  {
    Token result(tokens[index].file, tokens[index].line, tokens[index].cursor, TokenType::KEYWORD_VAR, "var");
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
    ParseLineComment(peek_character);
  }
  else if (peek_character[0] == '*')
    ParseBlockComment(peek_character);
  else
  {
    Token result(file, line, cursor, TokenType::DIVISION_OPERATOR, character);
    tokens.push_back(result);
  }
}

void Lexer::ParseLineComment(StringRef character)
{
  Token semicolon(file, line, cursor, TokenType::SEMI_COLON_OPERATOR, ";");
  tokens.push_back(semicolon);
  while (character[0] != 0x0A && index < buffer.size())
    character = NextCharacter();
  line += 1;
  cursor = 0;
}

void Lexer::ParseBlockComment(StringRef character)
{
  while (true)
  {
    character = NextCharacter();
    if (character[0] == EOF)
      throw std::runtime_error("unterminated block comment");

    if (character[0] == 0x0A)
    {
      line += 1;
      cursor = 0;
      continue;
    }

    if (character[0] == '*')
    {
      character = PeekCharacter();

      if (character[0] == EOF)
        throw std::runtime_error("unterminated block comment");

      if (character[0] == '/')
      {
        NextCharacter();
        NextCharacter();
        return;
      }
    }
  }
}

void Lexer::ParseNumber(StringRef character)
{
  character = NextCharacter();
  Token result(file, line, cursor, TokenType::INTEGER, character);

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
    result.type = TokenType::DOUBLE;

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
  Token result(file, line, cursor, TokenType::SYMBOL, "");

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
    result.type = TokenType::KEYWORD_TRUE;
  else if (result.value == "false")
    result.type = TokenType::KEYWORD_FALSE;
  else if (result.value == "if")
    result.type = TokenType::KEYWORD_IF;
  else if (result.value == "else")
    result.type = TokenType::KEYWORD_ELSE;
  else if (result.value == "while")
    result.type = TokenType::KEYWORD_WHILE;
  else if (result.value == "for")
    result.type = TokenType::KEYWORD_FOR;
  else if (result.value == "function")
    result.type = TokenType::KEYWORD_FUNCTION;
  else if (result.value == "ƒ")
    result.type = TokenType::KEYWORD_FUNCTION;
  else if (result.value == "𝑓")
    result.type = TokenType::KEYWORD_FUNCTION;
  else if (result.value == "return")
    result.type = TokenType::KEYWORD_RETURN;

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
  while (true)
  {
    character = PeekCharacter();
    if (IsValidWhitespace(character))
      character = NextCharacter();
    else
      return;
  }
}

void Lexer::ParseStringLiteral(StringRef character)
{
  character = NextCharacter();
  Token result(file, line, cursor, TokenType::STRING_LITERAL);
  while (true)
  {
    character = PeekCharacter();

    if (character[0] == '\\')
    {
      character = NextCharacter();
      if (character[0] == '\"' || character[0] == '\\')
      {
        character = NextCharacter();
        result.value += character;
        continue;
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
    character == "×"
    );
}

void Lexer::ParsePunctuation(StringRef character)
{
  character = NextCharacter();
  Token result(file, line, cursor, TokenType::PUNCTUATION, character);

  // delimiters
  if (result.value == ".")
    result.type = TokenType::DOT_OPERATOR;
  else if (result.value == ",")
    result.type = TokenType::COMMA_OPERATOR;
  else if (result.value == ":")
    result.type = TokenType::COLON_OPERATOR;
  else if (result.value == ";")
    result.type = TokenType::SEMI_COLON_OPERATOR;

  // comparison operators
  else if (result.value == ">")
    result.type = TokenType::GREATER_THAN_OPERATOR;
  else if (result.value == "<")
    result.type = TokenType::LESSER_THAN_OPERATOR;

  // arithmetic operators
  else if (result.value == "+")
    result.type = TokenType::ADDITION_OPERATOR;
  else if (result.value == "-")
    result.type = TokenType::SUBTRACTION_OPERATOR;
  else if (result.value == "*")
    result.type = TokenType::MULTIPLICATION_OPERATOR;
  else if (result.value == "/")
    result.type = TokenType::DIVISION_OPERATOR;
  else if (result.value == "%")
    result.type = TokenType::MODULUS_OPERATOR;

  // assignment operators */
  else if (result.value == "=")
    result.type = TokenType::ASSIGNMENT_OPERATOR;

  // brackets, braces and PARENTHESIS
  else if (result.value == "(")
    result.type = TokenType::LEFT_PARENTHESIS;
  else if (result.value == "{")
    result.type = TokenType::LEFT_CURLY_BRACES;
  else if (result.value == "[")
    result.type = TokenType::LEFT_SQUARE_BRACKETS;
  else if (result.value == ")")
    result.type = TokenType::RIGHT_PARENTHESIS;
  else if (result.value == "}")
    result.type = TokenType::RIGHT_CURLY_BRACES;
  else if (result.value == "]")
    result.type = TokenType::RIGHT_SQUARE_BRACKETS;

  // bitwise operators
  else if (result.value == "&")
    result.type = TokenType::BITWISE_AND_OPERATOR;
  else if (result.value == "|")
    result.type = TokenType::BITWISE_OR_OPERATOR;
  else if (result.value == "^")
    result.type = TokenType::BITWISE_XOR_OPERATOR;
  else if (result.value == "~")
    result.type = TokenType::BITWISE_ONES_COMPLEMENT_OPERATOR;

  // logical operators
  else if (result.value == "!")
    result.type = TokenType::LOGICAL_NOT_OPERATOR;

  // unicode operators
  else if (result.value == "＝")
    result.type = TokenType::ASSIGNMENT_OPERATOR;
  else if (result.value == "≥")
    result.type = TokenType::GREATER_THAN_OR_EQUAL_OPERATOR;
  else if (result.value == "≤")
    result.type = TokenType::LESSER_THAN_OR_EQUAL_OPERATOR;
  else if (result.value == "≠")
    result.type = TokenType::INEQUALITY_OPERATOR;
  else if (result.value == "⋅")
    result.type = TokenType::MULTIPLICATION_OPERATOR;
  else if (result.value == "•")
    result.type = TokenType::MULTIPLICATION_OPERATOR;
  else if (result.value == "×")
    result.type = TokenType::MULTIPLICATION_OPERATOR;

  tokens.push_back(result);
}