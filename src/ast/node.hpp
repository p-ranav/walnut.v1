#pragma once
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
      INVALID
    };

    Type type;
    bool iterable;

    explicit Node(Type type, bool iterable = false) : type(type),
      iterable(iterable) {}

    virtual ~Node() {}

    virtual String ToString() { return ""; }
  };

  typedef std::shared_ptr<Node> NodePtr;
  typedef Node::Type NodeType;

}
