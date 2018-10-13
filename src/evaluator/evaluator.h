#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <object.h>
#include <node.h>

object * eval(node * ast_node);

/* eval functions for ast node types */
object * eval_integer(node * ast_node);
object * eval_boolean(node * ast_node);

#endif