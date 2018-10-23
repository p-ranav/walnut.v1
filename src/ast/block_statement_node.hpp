#pragma once
#include <node.hpp>
#include <vector>
#include <memory>

struct BlockStatementNode : Node
{
  std::vector<NodePtr> statements;
  BlockStatementNode() : Node(BLOCK_STATEMENT),
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