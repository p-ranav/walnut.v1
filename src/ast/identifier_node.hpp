#pragma once
#include <node.hpp>
#include <string>

typedef std::string String;
typedef const std::string &StringConstRef;

struct AstIdentifierNode : AstNode
{
  String value;
  explicit AstIdentifierNode(StringConstRef value) : 
    AstNode(IDENTIFIER), 
    value(value) {}
};

typedef std::shared_ptr<AstIdentifierNode> AstIdentifierNodePtr;