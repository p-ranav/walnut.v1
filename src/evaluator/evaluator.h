#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <object.h>
#include <node.h>
#include <token.h>

object * eval(node * ast_node);

/* eval functions for ast node types */
object * eval_integer(node * ast_node);
object * eval_boolean(node * ast_node);
object * eval_null();

object * eval_prefix_expression(node * ast_node);
object * eval_bang_operator(object * right);
object * eval_unary_minus_operator(object * right);
object * eval_negate_integer(object * right);

object * eval_infix_expression(node * ast_node);
object * eval_integer_infix_expression(token operator, object * left, object * right);
object * eval_boolean_infix_expression(token operator, object * left, object * right);

object * eval_if_expression(node * ast_node);
int is_condition_true(object * obj);
object * eval_block(node * ast_node);

object * eval_return(node * ast_node);

#endif