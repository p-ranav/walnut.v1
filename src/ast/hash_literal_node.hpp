#pragma once
#include <node.hpp>
#include <map>

struct HashLiteralNode : Node
{
  std::map<NodePtr, NodePtr> pairs;
  explicit HashLiteralNode() : Node(HASH_LITERAL),
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