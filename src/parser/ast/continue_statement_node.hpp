#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

  struct ContinueStatementNode : Node
  {
    explicit ContinueStatementNode(Token token) : Node(token, CONTINUE_STATEMENT) {}

    String ToString() override
    {
      return "continue";
    }
  };

  typedef std::shared_ptr<ContinueStatementNode> ContinueStatementNodePtr;

} // namespace walnut