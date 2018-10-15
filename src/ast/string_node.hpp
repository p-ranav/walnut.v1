#pragma once
#include <node.hpp>
#include <string>

typedef std::string String;

struct AstStringNode : AstNode
{
  String value;
  explicit AstStringNode(String value) : AstNode(DOUBLE), value(value) {}
};