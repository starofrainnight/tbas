#ifndef _9M_COMMON_92E10088
#define _9M_COMMON_92E10088

#include <memory.h>

#ifndef ENSURE
#define ENSURE(cond)                                                     \
  if (!(cond)) {                                                         \
    fprintf(stderr, "%s (%d): ENSURE failed at : " #cond "\n", __FILE__, \
            __LINE__);                                                   \
    exit(-1);                                                            \
  };
#endif  // !ENSURE

#ifndef safe_maclloc
#define safe_maclloc(type, ret)                                        \
  do {                                                                 \
    (ret) = (type *)malloc(sizeof(type));                              \
    ENSURE(((ret) != NULL) && "Failed to allocate for type : " #type); \
    memset((ret), 0, sizeof(type));                                    \
  } while (0);
#endif  // !safe_maclloc

#ifndef safe_free
#define safe_free(ptr_ptr) \
  do {                     \
    free(*(ptr_ptr));      \
    *(ptr_ptr) = NULL;     \
  } while (0);
#endif  // !safe_free

#endif  // !_9M_COMMON_92E10088
