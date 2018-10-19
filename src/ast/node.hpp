#pragma once
#include <string>
#include <memory>

typedef std::string String;
typedef const std::string &StringConstRef;

struct Node
{
  enum Type
  {
    IDENTIFIER,
    IDENTIFIER_LIST,
    INTEGER,
    DOUBLE,
    STRING_LITERAL,
    BOOLEAN,
    VAR_STATEMENT,
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
    INVALID
  };

  Type type;

  explicit Node(Type type) : 
    type(type) {}
  virtual ~Node() {}

  virtual String ToString() { return ""; }
};

typedef std::shared_ptr<Node> NodePtr;
typedef Node::Type NodeType;
