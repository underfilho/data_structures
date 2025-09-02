#include "array.h"

#define INSERT_PQ(pq, priority_val, val) do { \
    __typeof__(val) tmp_val = (val);            \
    Element tmp;                                \
    tmp.priority = (priority_val);              \
    tmp.value = &tmp_val;                       \
    insert_pq((pq), &tmp);                      \
} while(0)

typedef struct Element {
    int priority;
    void* value;
} Element;

typedef Array PQueue;

PQueue* newPriorityQueue(size_t type_size) {
    int capacity = 8;
    PQueue* pq = newEmptyArray(type_size, capacity);

    return pq;
}

int _parentIndex(int i) {
    return (i - 1) / 2;
}

int _lChildIndex(int i) {
    return 2*i + 1;
}

int _rChildIndex(int i) {
    return 2*i + 2;
}

void _swap(PQueue* pq, int i, int j) {
    Element* ei = (Element*)_get(pq, i);
    Element* ej = (Element*)_get(pq, j);

    Element tmp = *ei;
    *ei = *ej;
    *ej = tmp;
}

int _getPriority(PQueue* pq, int i) {
    Element* element = (Element*)_get(pq, i);
    return element->priority;
}

void _shiftUp(PQueue* pq, int i) {
    while(i > 0) {
        int p = _parentIndex(i);
        if(_getPriority(pq, i) >= _getPriority(pq, p))
            break;

        _swap(pq, i, p);
        i = p;
    }
}

void _shiftDown(PQueue* pq, int i) {
    int minIndex = i;

    int l = _lChildIndex(i);
    if(l < pq->size && _getPriority(pq, l) < _getPriority(pq, minIndex))
        minIndex = l;

    int r = _rChildIndex(i);
    if(r < pq->size && _getPriority(pq, r) < _getPriority(pq, minIndex))
        minIndex = r;

    if(i != minIndex) {
        _swap(pq, i, minIndex);
        _shiftDown(pq, minIndex);
    }
}

void insert_pq(PQueue* pq, Element* element) {
    add(pq, element);
    _shiftUp(pq, pq->size-1);
}

Element* pop_pq(PQueue* pq) {
    if (pq->size == 0) 
        return NULL;

    Element* root = (Element*)malloc(sizeof(Element));
    *root = *(Element*)_get(pq, 0);

    Element* last = (Element*)_get(pq, pq->size - 1);
    *(Element*)_get(pq, 0) = *last;
    _pop(pq);

    if (pq->size > 0) 
        _shiftDown(pq, 0);

    return root;
}

Element* peek_pq(PQueue* pq) {
    if (pq->size == 0) return NULL;
    return (Element*)_get(pq, 0);
}


