#ifndef _9M_AST_73F53C50
#define _9M_AST_73F53C50

#include "list.h"

// AN: AST Node

typedef enum an_type_t {
  ANT_PROGRAM,
  ANT_ASSIGNMENT,
  ANT_EXPR,
  ANT_STMT,
  ANT_FUNC_CALL,
  ANT_FUNC_DECL,
  ANT_EXPR_PLUS,
  ANT_EXPR_MINUS,
  ANT_EXPR_MULTIPLY,
  ANT_EXPR_DIV,
  ANT_END,

  ANT_VALUE_INT,
  ANT_VALUE_FLOAT,
  ANT_VALUE_STR,

  ANT_COUNT_,
} an_type_t;

typedef struct an_node_t {
  // Node type
  an_type_t type;
} an_node_t;

typedef struct an_assignment_t {
  an_type_t type;
  an_node_t *left;
  an_node_t *right;
} an_assignment_t;

typedef struct an_program_t {
  an_type_t type;
  list_t stmts;  ///< A list of statements
} an_program_t;

typedef struct an_value_int_t {
  an_type_t type;
  int value;
} an_value_int_t;

typedef struct an_value_float_t {
  an_type_t type;
  float value;
} an_value_float_t;

typedef struct an_value_str_t {
  an_type_t type;
  const char *value;
} an_value_str_t;

typedef struct an_func_call_t {
  an_type_t type;
  const char *name;
  list_t params;
} an_func_call_t;

typedef struct an_func_decl_t {
  an_type_t type;
  const char *result_type;
} an_func_decl_t;

typedef struct an_expr_math_t {
  an_type_t type;
  an_node_t *left;
  an_node_t *right;
} an_expr_math_t;

#ifdef __cplusplus
extern "C" {
#endif

// Extern ast node generate functions
extern an_program_t *an_program_new();
extern an_node_t *an_node_new(an_type_t an_type);
extern an_assignment_t *an_assignment_new(an_node_t *left, an_node_t *right);
extern an_value_int_t *an_value_int_new(int value);
extern an_value_float_t *an_value_float_new(float value);
extern an_value_str_t *an_value_str_new(const char *value);
extern an_func_call_t *an_func_call_new(const char *name);
extern an_expr_math_t *an_expr_math_new(an_type_t an_type, an_node_t *left,
                                        an_node_t *right);

#ifdef __cplusplus
}
#endif

#endif  // !_9M_AST_73F53C50