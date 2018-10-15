#pragma once
#include <memory>

struct AstNode
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
    BLOCK,
    FUNCTION,
    CALL_EXPRESSION,
    INVALID
  };

  Type type;
  explicit AstNode(Type type) : type(type) {}
  virtual ~AstNode() = 0;
};

typedef std::shared_ptr<AstNode> AstNodePtr;
