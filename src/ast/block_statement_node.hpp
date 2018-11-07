#pragma once
#include <node.hpp>
#include <token.hpp>
#include <vector>
#include <memory>

namespace walnut
{

struct BlockStatementNode : Node
{
  std::vector<NodePtr> statements;
  BlockStatementNode(Token token) : Node(token, BLOCK_STATEMENT),
                                    statements({}) {}

  String ToString() override
  {
    String result = "{ ";
    for (auto &statement : statements)
    {
      result += statement->ToString() + "; ";
    }
    result += "}";
    return result;
  }
};

typedef std::shared_ptr<BlockStatementNode> BlockStatementNodePtr;

} // namespace walnut