#include "array.h"

#define PUSH(stack, value) do { \
    __typeof__(value) tmp = (value);    \
    push((stack), &tmp);                \
} while(0)

typedef Array Stack;

Stack* newStack(size_t type_size) {
    return newEmptyArray(type_size, 8);
}

void push(Stack* stack, void* value) {
    add(stack, value);
}

void top(Stack* stack, void* out) {
    if (stack->size == 0) {
        out = NULL;
        return;
    }

    void* src = malloc(stack->type_size);;
    get(stack, 0, src);
    memcpy(out, src, stack->type_size);
}

void pop(Stack* stack, void* out) {
    if (stack->size == 0) {
        out = NULL;
        return;
    }

    void* src = malloc(stack->type_size);
    get(stack, stack->size - 1, src);
    memcpy(out, src, stack->type_size);
    stack->size--;
}