#pragma once
#include <node.hpp>
#include <token.hpp>
#include <map>

namespace walnut
{

struct HashLiteralNode : Node
{
  std::map<NodePtr, NodePtr> pairs;
  explicit HashLiteralNode(Token token) : Node(token, HASH_LITERAL),
                                          pairs({}) {}

  String ToString() override
  {
    String result = "{";
    size_t index = 1;
    for (auto &pair : pairs)
    {
      result += pair.first->ToString() + " : " + pair.second->ToString();
      if (index < pairs.size())
        result += ", ";
      index += 1;
    }
    result += "}";
    return result;
  }
};

typedef std::shared_ptr<HashLiteralNode> HashLiteralNodePtr;

} // namespace walnut