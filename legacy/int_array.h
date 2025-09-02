#include <stdlib.h>
#include <stdarg.h>

int* _realloc(int* ptr, int oldSize, int newSize);

typedef struct intArray {
	int* i;
	int size;
	int capacity;
} intArray;

intArray* newEmptyArray(int capacity) {
	intArray* array = malloc(sizeof(intArray));
	array->i = malloc(sizeof(int) * capacity);
	array->size = 0;
	array->capacity = capacity;

	return array;
}

intArray* newArray(int size, ...) {
	intArray* array = newEmptyArray(size);
	va_list args;

	va_start(args, size);
	for (int i = 0; i < size; i++) {
		int value = va_arg(args, int);
		array->i[i] = value;
		array->size++;
	}
	va_end(args);

	return array;
}

void add(intArray* array, int value) {
	int index = array->size;
	if (index >= array->capacity) {
		array->i = _realloc(array->i, array->capacity, array->capacity * 2);
		array->capacity = array->capacity * 2;
	}

	array->i[index] = value;
	array->size++;
}

void pop(intArray* array) {
	int index = array->size - 1;
	if (index <= array->capacity / 2) {
		array->i = _realloc(array->i, array->capacity, array->capacity / 2);
		array->capacity = array->capacity / 2;
	}

	array->i[index] = 0;
	array->size--;
}

void insert(intArray* array, int value, int index) {
	add(array, array->i[array->size - 1]);
	for (int i = array->size - 2; i >= index; i--) {
		array->i[i + 1] = array->i[i];
		if (i == index)
			array->i[i] = value;
	}
}

void delete(intArray* array, int index) {
	for (int i = index; i <= array->size - 2; i++)
		array->i[i] = array->i[i + 1];
	pop(array);
}

int get(intArray* array, int index) {
	return array->i[index];
}

void forEach(intArray* array, void (*action)(int)) {
	for (int i = 0; i < array->size; i++) {
		action(array->i[i]);
	}
}

int _internalBinarySearch(intArray* array, int start, int end, int value) {
	int mid = start + (end - start) / 2;
	int midValue = array->i[mid];

	if(start >= end && midValue != value) return -1;

	if(midValue == value) 
		return mid;
	else if (midValue > value) 
		return _internalBinarySearch(array, start, mid - 1, value);
	else 
		return _internalBinarySearch(array, mid + 1, end, value);
}

int binarySearch(intArray* array, int value) {
	return _internalBinarySearch(array, 0, array->size, value);
}

int _min(int a, int b) {
	return (a < b) ? a : b;
}

int* _realloc(int* ptr, int oldSize, int newSize) {
	int* newPtr = malloc(sizeof(int) * newSize);
	
	int min = _min(oldSize, newSize);
	for (int i = 0; i < min; i++)
		newPtr[i] = ptr[i];

	return newPtr;
}
