#ifndef NODE_TYPE_H
#define NODE_TYPE_H

/* Each node in the AST can be one of the following types */
enum node_type_t
{
  IDENTIFIER,
  INTEGER,
  DOUBLE,

  VAR_STATEMENT,
  RETURN_STATEMENT,
  PREFIX_EXPRESSION,
  INFIX_EXPRESSION
};

#endif