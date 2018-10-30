#pragma once
#include <node.hpp>
#include <identifier_node.hpp>
#include <token.hpp>

namespace walnut
{

  struct KeyValueArgumentNode : Node
  {
    IdentifierNodePtr key;
    NodePtr value;
    explicit KeyValueArgumentNode(Token token) : Node(token, KEY_VALUE_ARGUMENT),
      key(nullptr), 
      value(nullptr) {}

    String ToString() override
    {
      String result = "";
      result += key->ToString() + " = " + value->ToString();
      return result;
    }
  };

  typedef std::shared_ptr<KeyValueArgumentNode> KeyValueArgumentNodePtr;

}