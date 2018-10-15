#pragma once
#include <node.hpp>
#include <string>

typedef std::string String;

struct AstIdentifierNode : AstNode
{
  String value;
  explicit AstIdentifierNode(String value) : AstNode(IDENTIFIER), value(value) {}
};

typedef std::shared_ptr<AstIdentifierNode> AstIdentifierNodePtr;