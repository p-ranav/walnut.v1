#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

  struct KeywordParameterNode : Node
  {
    String value;
    explicit KeywordParameterNode(Token token, StringConstRef value) :
      Node(token, KEYWORD_PARAMETER),
      value(value) {}

    String ToString() override
    {
      return "**" + value;
    }
  };

  typedef std::shared_ptr<KeywordParameterNode> KeywordParameterNodePtr;

} // namespace walnut