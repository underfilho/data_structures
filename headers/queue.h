#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ENQUEUE(queue, value) do { \
    __typeof__(value) tmp = (value);   \
    enqueue((queue), &tmp);            \
} while(0)

typedef struct Queue {
    void* data;
    int size;
    int capacity;
    int front;
    int rear;
    size_t type_size;
} Queue;

void* _realloc(void* ptr, int oldSize, int newSize, size_t type_size);

Queue* newQueue(size_t type_size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
	q->data = malloc(type_size * 8);
    q->capacity = 8;
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    q->type_size = type_size;

    return q;
}

void enqueue(Queue* q, void* item) {
    if (q->size == q->capacity) {
        int newCapacity = q->capacity * 2;
        q->data = _realloc(q->data, q->capacity, newCapacity, q->type_size);
        q->capacity = newCapacity;
    }

    q->rear = (q->rear + 1) % q->capacity;
    memcpy(q->data + q->rear * q->type_size, item, q->type_size);
    q->size++;
}

void* dequeue(Queue* q) {
    if (q->size == 0) {
        return NULL;
    }

    void* item = malloc(q->type_size);
    memcpy(item, q->data + q->front * q->type_size, q->type_size);
    
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return item;
}

void* peek(Queue* q) {
    if (q->size == 0) {
        return NULL;
    }
    
    void* item = malloc(q->type_size);
    memcpy(item, q->data + q->front * q->type_size, q->type_size);
    return item;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

void freeQueue(Queue* q) {
    free(q->data);
    free(q);
}

void forEach(Queue* q, void (*action)(void*)) {
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        action(q->data + index * q->type_size);
    }
}

bool any(Queue* q, bool (*condition)(void*)) {
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        if (condition(q->data + index * q->type_size)) {
            return true;
        }
    }
    return false;
}

bool every(Queue* q, bool (*condition)(void*)) {
    for (int i = 0; i < q->size; i++) {
        int index = (q->front + i) % q->capacity;
        if (!condition(q->data + index * q->type_size)) {
            return false;
        }
    }
    return true;
}

int _min(int a, int b) {
	return (a < b) ? a : b;
}

void* _realloc(void* ptr, int oldSize, int newSize, size_t type_size) {
	void* newPtr = malloc(sizeof(int) * newSize);
	
	int min = _min(oldSize, newSize);
	for (int i = 0; i < min; i++) {
        memcpy(newPtr + i * type_size, ptr + i * type_size, type_size);
    }

	return newPtr;
}