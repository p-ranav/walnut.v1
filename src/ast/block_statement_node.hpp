#pragma once
#include <node.hpp>
#include <vector>
#include <memory>

struct BlockStatementNode : Node
{
  std::vector<NodePtr> statements;
  BlockStatementNode() : 
    Node(BLOCK_STATEMENT), 
    statements({}) {}
};

typedef std::shared_ptr<BlockStatementNode> BlockStatementNodePtr;