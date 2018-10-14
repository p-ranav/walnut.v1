#pragma once

namespace parser
{
  enum node_type
  {
    IDENTIFIER,
    INTEGER,
    DOUBLE,
    STRING_LITERAL,
    BOOLEAN,
    VAR_STATEMENT,
    RETURN_STATEMENT,
    PREFIX_EXPRESSION,
    INFIX_EXPRESSION,
    IF_EXPRESSION,
    BLOCK,
    FUNCTION,
    CALL_EXPRESSION
  };

}
