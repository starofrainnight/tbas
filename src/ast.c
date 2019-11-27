#include "ast.h"
#include "common.h"

#define safe_maclloc_node_ptr(node_struct, var_name, node_type) \
  node_struct *var_name = 0;                                    \
  safe_maclloc(node_struct, (var_name));                        \
  (var_name)->type = node_type;

an_program_t *an_program_new() {
  safe_maclloc_node_ptr(an_program_t, self, ANT_PROGRAM);

  self->stmts = list_new(NULL);
  return self;
}

an_node_t *an_node_new(an_type_t an_type) {
  safe_maclloc_node_ptr(an_node_t, self, an_type);

  return self;
}

an_assignment_t *an_assignment_new(an_node_t *left, an_node_t *right) {
  ENSURE((left != 0) && (right != 0) && "Assigment elements must not NULL!");

  safe_maclloc_node_ptr(an_assignment_t, self, ANT_ASSIGNMENT);

  self->left = left;
  self->right = right;

  return self;
}

an_value_int_t *an_value_int_new(int value) {
  safe_maclloc_node_ptr(an_value_int_t, self, ANT_VALUE_INT);

  self->value = value;
  return self;
}

an_value_float_t *an_value_float_new(float value) {
  safe_maclloc_node_ptr(an_value_float_t, self, ANT_VALUE_FLOAT);

  self->value = value;
  return self;
}

an_value_str_t *an_value_str_new(const char *value) {
  ENSURE((value != NULL) && "String value must not NULL!")

  safe_maclloc_node_ptr(an_value_str_t, self, ANT_VALUE_STR);
  self->value = strdup(value);
  return self;
}

an_func_call_t *an_func_call_new(const char *name) {
  ENSURE((name != NULL) && "Function name must not NULL!");

  safe_maclloc_node_ptr(an_func_call_t, self, ANT_FUNC_CALL);

  self->name = strdup(name);
  self->params = list_new(NULL);
  return self;
}

an_expr_math_t *an_expr_math_new(an_type_t an_type, an_node_t *left,
                                 an_node_t *right) {
  ENSURE((left != NULL) && (right != NULL));

  safe_maclloc_node_ptr(an_expr_math_t, self, an_type);
  self->left = left;
  self->right = right;
  return self;
}