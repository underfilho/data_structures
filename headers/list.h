#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define ADD(list, value) do { \
    __typeof__(value) tmp = (value);  \
    add((list), &tmp);                \
} while(0)

typedef struct Node {
    void* value;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
    int size;
    size_t type_size;
} List;

void add(List* list, void* value);

List* newEmptyList(size_t type_size) {
    List* newList = (List*)malloc(sizeof(List));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->type_size = type_size;
    return newList;
}

// TODO: Support double data types
List* newList(size_t type_size, int num, ...) {
    List* newList = newEmptyList(type_size);
    va_list args;

    va_start(args, num);
    for (int i = 0; i < num; i++) {
        int value = va_arg(args, int);
        add(newList, &value);
    }
    va_end(args);

    return newList;
}

void add(List* list, void* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = malloc(list->type_size);
    memcpy(newNode->value, value, list->type_size);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->size++;
    } else {
        Node* lastNode = list->tail;
        lastNode->next = newNode;
        list->tail = newNode;
        list->size++;
    }
}

void get(List* list, int index, void* out) {
    if (index > list->size - 1) {
        out = NULL;
        return;
    }

    Node* actualNode = list->head;
    for (int i = 0; i < index; i++) {
        actualNode = actualNode->next;
    }

    memcpy(out, actualNode->value, list->type_size);
    return;
}

int find(List* list, void* element, int (*compare)(void*, void*)) {
    Node* actualNode = list->head;

    for (int i = 0; i < list->size; i++) {
        if (compare(actualNode->value, element) == 0) 
            return i;
        actualNode = actualNode->next;
    }

    return -1;
}

void removeAt(List* list, int index) {
    Node* actualNode = list->head;
    if (actualNode == NULL || index > list->size - 1)
        return;

    for (int i = 0; i < index; i++) {
        if (i + 1 == index) {
            actualNode->next = actualNode->next->next;
        } else {
            actualNode = actualNode->next;
        }
    }
}

void forEach(List* list, void (*action)(void*)) {
    Node* actualNode = list->head;

    while (actualNode != NULL) {
        action(actualNode->value);
        actualNode = actualNode->next;
    }
}

bool any(List* list, bool (*condition)(void*)) {
    Node* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            return true;
        else
            actualNode = actualNode->next;
    }

    return false;
}

bool every(List* list, bool (*condition)(void*)) {
    Node* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            actualNode = actualNode->next;
        else
            return false;
    }

    return true;
}

List* where(List* list, bool (*condition)(void*)) {
    List* newList = newEmptyList(list->type_size);

    Node* actualNode = list->head;
    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            add(newList, actualNode->value);
        actualNode = actualNode->next;
    }

    return newList;
}

void reduce(List* list, void* (*combine)(void*, void*), void* out) {
    if (list->head == NULL) {
        out = NULL;
        return;
    }

    void* value = list->head->value;
    Node* actualNode = list->head->next;
    while (actualNode != NULL) {
        value = combine(value, actualNode->value);
        actualNode = actualNode->next;
    }

    memcpy(out, value, list->type_size);
    return;
}