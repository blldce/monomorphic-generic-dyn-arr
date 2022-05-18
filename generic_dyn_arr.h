#ifndef GEN_DYN_ARR
#define GEN_DYN_ARR 1

#include <stdlib.h>
#include "dyn_arr.h"

#define dyn_arr_init_gen(generic_t) ({                      \
    int array_buffer = (sizeof(generic_t) * 2);             \
    struct dyn_arr_gen dyn_arr_t = {.size = 0, .cap = 2};   \
    dyn_arr_t.arr_ptr = (generic_t(*))malloc(array_buffer); \
    struct dyn_arr_gen(*dyn_arr_ptr) = &dyn_arr_t;          \
    zeroed_gen(dyn_arr_ptr);                                \
    dyn_arr_t;                                              \
})

#define push_gen(dyn_arr_ptr, data, generic_t) ({                        \
    if (dyn_arr_ptr->cap > dyn_arr_ptr->size)                            \
    {                                                                    \
        *(generic_t *)(dyn_arr_ptr->arr_ptr + dyn_arr_ptr->size) = data; \
        dyn_arr_ptr->size++;                                             \
        display(dyn_arr_ptr);                                            \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        expand_memory_gen(dyn_arr_ptr, generic_t);                       \
        push_gen_after_expand(dyn_arr_ptr, data, generic_t);             \
    }                                                                    \
})

#define push_gen_after_expand(dyn_arr_ptr, data, generic_t) ({       \
    *(generic_t *)(dyn_arr_ptr->arr_ptr + dyn_arr_ptr->size) = data; \
    dyn_arr_ptr->size++;                                             \
    display(dyn_arr_ptr);                                            \
})

#define expand_memory_gen(dyn_arr_ptr, generic_t) ({               \
    generic_t(*old_arr_ptr) = (generic_t *)dyn_arr_ptr->arr_ptr;   \
    int new_arr_buffer = dyn_arr_ptr->cap * 2;                     \
    generic_t(*new_arr_mem) = (generic_t *)malloc(new_arr_buffer); \
    dyn_arr_ptr->cap *= 2;                                         \
    dyn_arr_ptr->arr_ptr = new_arr_mem;                            \
    zeroed_gen(dyn_arr_ptr);                                       \
    memcopy_gen(old_arr_ptr, dyn_arr_ptr);                         \
})

#define zeroed_gen(dyn_arr_ptr) ({           \
    int index = 0;                           \
    while (index < dyn_arr_ptr->cap)         \
    {                                        \
        *(int(*))(dyn_arr_ptr->arr_ptr) = 0; \
        index++;                             \
    }                                        \
})

#define memcopy_gen(old_arr_ptr, dyn_arr_ptr) ({                                                                                  \
    int index = 0;                                                                                                                \
    while (index < dyn_arr_ptr->size)                                                                                             \
    {                                                                                                                             \
        *(typeof(dyn_arr_ptr->arr_ptr) *)(dyn_arr_ptr->arr_ptr + index) = *(typeof(dyn_arr_ptr->arr_ptr) *)(old_arr_ptr + index); \
        index++;                                                                                                                  \
    }                                                                                                                             \
})

#define display(dyn_arr_ptr) ({                                                                                         \
    int index = 0;                                                                                                      \
    while (index < dyn_arr_ptr->cap)                                                                                    \
    {                                                                                                                   \
        printf("Address : %p - Data : %c \n", (dyn_arr_ptr->arr_ptr + index), *(char *)(dyn_arr_ptr->arr_ptr + index)); \
        index++;                                                                                                        \
    }                                                                                                                   \
    printf("********************** \n");                                                                                \
})

#endif