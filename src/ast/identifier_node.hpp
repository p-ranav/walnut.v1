#pragma once
#include <node.hpp>
#include <string>

struct AstIdentifierNode : AstNode
{
  String value;
  explicit AstIdentifierNode(StringConstRef value) : 
    AstNode(IDENTIFIER), 
    value(value) {}
};

typedef std::shared_ptr<AstIdentifierNode> AstIdentifierNodePtr;