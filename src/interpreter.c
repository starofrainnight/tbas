#include "interpreter.h"
#include "ast.h"
#include "common.h"
#include "list.h"

typedef struct interp_impl_t {
  /* data */
  list_t stack;
} interp_impl_t;

interp_t interp_new() {
  interp_t self = NULL;
  safe_maclloc(interp_impl_t, self);
  return self;
}

void interp_del(interp_t* self_ptr) {
  ENSURE(self_ptr && *self_ptr);

  safe_free(self_ptr);
}

interp_error_t interp_run(interp_t self, struct an_program_t* ast_root) {
  ENSURE((self != NULL) && "Interpreter instance must not NULL!");
  ENSURE((ast_root != NULL) && "AST Root must not NULL!");

  return IET_OK;
}