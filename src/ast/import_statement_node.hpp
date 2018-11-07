#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>
#include <iomanip>
#include <sstream>

namespace walnut
{

struct ImportStatementNode : Node
{
  String value;
  explicit ImportStatementNode(Token token, String value) : Node(token, IMPORT_STATEMENT),
                                                            value(value) {}

  String ToString() override
  {
    return "import " + value;
  }
};

typedef std::shared_ptr<ImportStatementNode> ImportStatementNodePtr;

} // namespace walnut