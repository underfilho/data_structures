#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define ADD(array, value) do { \
    __typeof__(value) tmp = (value);   \
    add((array), &tmp);                \
} while(0)


typedef struct Array {
	void* data;
	int size;
	int capacity;
    size_t type_size;
} Array;

void* _realloc(void* ptr, int oldSize, int newSize, size_t type_size);
void* _get(Array* array, int index);
void _pop(Array* array);

Array* newEmptyArray(size_t type_size, int capacity) {
	Array* array = (Array*)malloc(sizeof(Array));
	array->data = malloc(type_size * capacity);
	array->size = 0;
	array->capacity = capacity;
    array->type_size = type_size;

	return array;
}

// TODO: Support double data types
Array* newArray(size_t type_size, int size, ...) {
	Array* array = newEmptyArray(type_size, 2*size);
	va_list args;

	va_start(args, size);
	for (int i = 0; i < size; i++) {
		int value = va_arg(args, int);
        void* dest = array->data + i * type_size;
        memcpy(dest, &value, type_size);
		array->size++;
	}
	va_end(args);

	return array;
}

void add(Array* array, void* value) {
	int index = array->size;
	if (index >= array->capacity) {
		array->data = _realloc(array->data, array->capacity, array->capacity * 2, array->type_size);
		array->capacity = array->capacity * 2;
	}

    memcpy(_get(array, index), value, array->type_size);
	array->size++;
}

void insert(Array* array, void* value, int index) {
	add(array, _get(array, index));
	for (int i = array->size - 2; i >= index; i--) {
        memcpy(_get(array, i+1), _get(array, i), array->type_size);
		if (i == index)
            memcpy(_get(array, i), value, array->type_size);
	}
}

int find(Array* array, void* element, int (*compare)(void*, void*)) {
    void* actual = malloc(array->type_size);;

    for (int i = 0; i < array->size; i++) {
        actual = _get(array, i);
        if (compare(actual, element) == 0)
            return i;
    }

    return -1;
}

void removeAt(Array* array, int index) {
	for (int i = index; i <= array->size - 2; i++)
        memcpy(_get(array, i), _get(array, i+1), array->type_size);
	_pop(array);
}

void get(Array* array, int index, void* out) {
    memcpy(out, _get(array, index), array->type_size);
}

void forEach(Array* array, void (*action)(void*)) {
	for (int i = 0; i < array->size; i++) {
		action(_get(array, i));
	}
}

bool any(Array* array, bool (*condition)(void*)) {
    void* element = malloc(array->type_size);;
    
    for (int i = 0; i < array->size; i++) {
        element = _get(array, i);

        bool result = condition(element);
        if (result)
            return true;
    }

    return false;
}

bool every(Array* array, bool (*condition)(void*)) {
    void* element = malloc(array->type_size);;

    for (int i = 0; i < array->size; i++) {
        element = _get(array, i);

        bool result = condition(element);
        if (!result)
            return false;
    }

    return true;
}

Array* where(Array* array, bool (*condition)(void*)) {
    Array* newArray = newEmptyArray(array->type_size, array->capacity);

    void* element = malloc(array->type_size);;
    for (int i = 0; i < array->size; i++) {
        element = _get(array, i);
        bool result = condition(element);
        if (result)
            add(newArray, element);
    }

    return newArray;
}

int _internalBinarySearch(Array* array, int start, int end, int value) {
	int mid = start + (end - start) / 2;
	int midValue = *(int*)_get(array, mid);

	if(start >= end && midValue != value) return -1;

	if(midValue == value) 
		return mid;
	else if (midValue > value) 
		return _internalBinarySearch(array, start, mid - 1, value);
	else 
		return _internalBinarySearch(array, mid + 1, end, value);
}

int binarySearch(Array* array, int value) {
	return _internalBinarySearch(array, 0, array->size, value);
}

void* _get(Array* array, int index) {
	return array->data + (index * array->type_size);;
}

void _pop(Array* array) {
	if(array->size == 0) return;

	int index = array->size - 1;
	if (index <= array->capacity / 2) {
		array->data = _realloc(array->data, array->capacity, array->capacity / 2, array->type_size);
		array->capacity = array->capacity / 2;
	}
	array->size--;
}

int _min(int a, int b) {
	return (a < b) ? a : b;
}

void* _realloc(void* ptr, int oldSize, int newSize, size_t type_size) {
	void* newPtr = malloc(type_size * newSize);
	
	int min = _min(oldSize, newSize);
	for (int i = 0; i < min; i++) {
        memcpy(newPtr + i * type_size, ptr + i * type_size, type_size);
    }

	free(ptr);
	return newPtr;
}
