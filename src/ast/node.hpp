#pragma once
#include <string>
#include <memory>

struct Node
{
  enum Type
  {
    IDENTIFIER,
    INTEGER,
    DOUBLE,
    STRING_LITERAL,
    BOOLEAN,
    VAR_STATEMENT,
    RETURN_STATEMENT,
    PREFIX_EXPRESSION,
    INFIX_EXPRESSION,
    IF_EXPRESSION,
    BLOCK_STATEMENT,
    FUNCTION,
    CALL_EXPRESSION,
    INVALID
  };

  Type type;
  explicit Node(Type type) : 
    type(type) {}
  virtual ~Node() {}
};

typedef std::string String;
typedef const std::string &StringConstRef;
typedef std::shared_ptr<Node> NodePtr;
typedef Node::Type NodeType;
