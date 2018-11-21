#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

  struct BreakStatementNode : Node
  {
    explicit BreakStatementNode(Token token) : Node(token, BREAK_STATEMENT) {}

    String ToString() override
    {
      return "break";
    }
  };

  typedef std::shared_ptr<BreakStatementNode> BreakStatementNodePtr;

} // namespace walnut