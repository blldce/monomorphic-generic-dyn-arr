#ifndef DYN_ARR_H
#define DYN_ARR_H

#define DEFAULT_CAP 2;

struct dyn_arr
{
    void (*push)(struct dyn_arr(*), int); // 8 bytes
    int (*pop)(struct dyn_arr(*));        // 8 bytes
    int (*get)(struct dyn_arr(*), int);   // 8 bytes
    int (*find)(struct dyn_arr(*), int);  // 8 bytes
    int size;                             // 4 bytes
    int cap;                              // 4 bytes
    int(*arr_ptr);                        // 8 bytes
};

struct dyn_arr_gen
{
    int size;       // 4 bytes
    int cap;        // 4 bytes
    void(*arr_ptr); // 8 bytes
};

extern struct dyn_arr dyn_arr_init(void);

extern struct dyn_arr dyn_arr_init_with_cap(int);

extern struct dyn_arr *dyn_arr_init_heap(void);

extern struct dyn_arr *dyn_arr_init_with_cap_heap(int);

extern void push(struct dyn_arr(*), int);

extern int pop(struct dyn_arr(*));

extern int get(struct dyn_arr(*), int);

extern int find(struct dyn_arr(*), int);

static void extend_memory(struct dyn_arr(*));

static void zeroed(struct dyn_arr(*));

static void memcopy(int(*), struct dyn_arr(*));

#endif