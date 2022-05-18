
#include <stdlib.h>
#include "dyn_arr.h"
#include "generic_dyn_arr.h"

struct dyn_arr dyn_arr_init(void)
{
    int def_cap = DEFAULT_CAP;
    int array_buffer = (sizeof(int) * def_cap);
    struct dyn_arr dyn_arr_t = {.push = push, .pop = pop, .get = get, .find = find, .size = 0, .cap = def_cap};
    dyn_arr_t.arr_ptr = (int(*))malloc(array_buffer);
    return dyn_arr_t;
}

struct dyn_arr dyn_arr_init_with_cap(int cap)
{
    int array_buffer = (sizeof(int) * cap);
    struct dyn_arr dyn_arr_t = {.push = push, .pop = pop, .get = get, .find = find, .size = 0, .cap = cap};
    dyn_arr_t.arr_ptr = (int(*))malloc(array_buffer);
    return dyn_arr_t;
}

struct dyn_arr *dyn_arr_init_heap(void)
{
    int def_cap = DEFAULT_CAP;
    int array_buffer = (sizeof(int) * def_cap);
    struct dyn_arr(*dyn_arr_ptr) = (struct dyn_arr(*))malloc(sizeof(struct dyn_arr) + array_buffer);
    dyn_arr_ptr->push = push;
    dyn_arr_ptr->pop = pop;
    dyn_arr_ptr->get = get;
    dyn_arr_ptr->find = find;
    dyn_arr_ptr->size = 0;
    dyn_arr_ptr->cap = DEFAULT_CAP;
    dyn_arr_ptr->arr_ptr = &dyn_arr_ptr->cap + sizeof(int);
    return dyn_arr_ptr;
}

struct dyn_arr *dyn_arr_init_with_cap_heap(int cap)
{
    int array_buffer = (sizeof(int) * cap);
    struct dyn_arr(*dyn_arr_ptr) = (struct dyn_arr(*))malloc(sizeof(struct dyn_arr) + array_buffer);
    dyn_arr_ptr->push = push;
    dyn_arr_ptr->pop = pop;
    dyn_arr_ptr->get = get;
    dyn_arr_ptr->find = find;
    dyn_arr_ptr->size = 0;
    dyn_arr_ptr->cap = cap;
    dyn_arr_ptr->arr_ptr = &dyn_arr_ptr->cap + sizeof(int);
    return dyn_arr_ptr;
}

void push(struct dyn_arr(*dyn_arr_ptr), int data)
{
    if (dyn_arr_ptr->cap > dyn_arr_ptr->size)
    {
        *(dyn_arr_ptr->arr_ptr + dyn_arr_ptr->size) = data;
        dyn_arr_ptr->size++;
        return;
    }
    extend_memory(dyn_arr_ptr);
    push(dyn_arr_ptr, data);
}

int pop(struct dyn_arr(*dyn_arr_ptr))
{
    if (dyn_arr_ptr->size > 0)
    {
        int res = *(dyn_arr_ptr->arr_ptr + dyn_arr_ptr->size - 1);
        dyn_arr_ptr->size--;
        return res;
    }
    return -1;
}

int get(struct dyn_arr(*dyn_arr_ptr), int index)
{
    if (index > dyn_arr_ptr->size || index < 0)
        return -1;

    return *(dyn_arr_ptr->arr_ptr + index - 1);
}

int find(struct dyn_arr(*dyn_arr_ptr), int data)
{
    int index = 0;
    while (index < dyn_arr_ptr->size)
    {
        if (*(dyn_arr_ptr->arr_ptr + index) == data)
        {
            return index;
        }
        index++;
    }
    return -1;
}

static void extend_memory(struct dyn_arr(*dyn_arr_ptr))
{
    int new_arr_buff = dyn_arr_ptr->cap * 2;
    int *new_arr_mem = (int *)malloc(new_arr_buff);
    dyn_arr_ptr->cap *= 2;
    memcopy(new_arr_mem, dyn_arr_ptr);
    free(dyn_arr_ptr->arr_ptr);
    dyn_arr_ptr->arr_ptr = new_arr_mem;
}


static void memcopy(int(*new_arr_mem), struct dyn_arr(*dyn_arr_ptr))
{
    int index = 0;
    while (index < dyn_arr_ptr->size)
    {
      *(new_arr_mem + index) = *(dyn_arr_ptr->arr_ptr + index);
        index++;
    }
}

static void zeroed(struct dyn_arr(*dyn_arr_ptr))
{
    int index = 0;
    while (index < dyn_arr_ptr->cap)
    {
        *(dyn_arr_ptr->arr_ptr) = 0;
        index++;
    }
}