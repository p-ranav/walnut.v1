#pragma once
#include <token.hpp>
#include <string>
#include <memory>

namespace walnut
{

  typedef std::string String;
  typedef const std::string &StringConstRef;

  struct Node
  {
    enum Type
    {
      IDENTIFIER,
      INTEGER,
      DOUBLE,
      CHARACTER,
      STRING_LITERAL,
      BOOLEAN,
      VAR_STATEMENT,
      EXPRESSION_ASSIGNMENT_STATEMENT,
      RETURN_STATEMENT,
      PREFIX_EXPRESSION,
      INFIX_EXPRESSION,
      IF_EXPRESSION,
      WHILE_EXPRESSION,
      FOR_EXPRESSION,
      BLOCK_STATEMENT,
      FUNCTION,
      CALL_EXPRESSION,
      ARRAY_LITERAL,
      INDEX_EXPRESSION,
      HASH_LITERAL,
      SET_LITERAL,
      TUPLE,
      IMPORT_STATEMENT,
      INVALID
    };

    Token token;
    Type type;
    bool iterable;

    explicit Node(Token token, Type type, bool iterable = false) : token(token), type(type),
      iterable(iterable) {}

    virtual ~Node() {}

    virtual String ToString() { return ""; }
  };

  typedef std::shared_ptr<Node> NodePtr;
  typedef Node::Type NodeType;

}
