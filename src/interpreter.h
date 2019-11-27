#ifndef _9M_INTERPRETER_343785A6
#define _9M_INTERPRETER_343785A6

struct an_program_t;

typedef enum interp_error_t { IET_OK, IET_ERROR, IET_COUNT_ } interp_error_t;

typedef struct interp_impl_t* interp_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate an interpreter instance
 */
interp_t interp_new();

/**
 * Delete and clear the interpreter instance.
 */
void interp_del(interp_t* self_ptr);

/**
 * Execute codes from ast root
 */
interp_error_t interp_run(interp_t self, struct an_program_t* ast_root);

#ifdef __cplusplus
}
#endif

#endif  // !_9M_INTERPRETER_343785A6
