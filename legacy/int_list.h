typedef struct intNode {
    int value;
    struct intNode* next;
} intNode;

typedef struct intList {
    intNode* head;
    intNode* last;
    int size;
} intList;

const int CONST_INT_ERROR = 123456;

void addInt(intList* list, int value);

intList* newEmptyIntList() {
    intList* newList = (intList*)malloc(sizeof(intList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

intList* newIntList(int num, ...) {
    intList* newList = newEmptyIntList();
    va_list args;

    va_start(args, num);

    for (int i = 0; i < num; i++) {
        int value = va_arg(args, int);
        addInt(newList, value);
    }
    va_end(args);

    return newList;
}

int getInt(intList* list, int index) {
    if (index > list->size - 1)
        return CONST_INT_ERROR;

    intNode* actualNode = list->head;
    for (int i = 0; i < index; i++) {
        actualNode = actualNode->next;
    }

    return actualNode->value;
}

int findInt(intList* list, int element) {
    intNode* actualNode = list->head;

    for (int i = 0; i < list->size; i++) {
        if (actualNode->value == element)
            return i;
        actualNode = actualNode->next;
    }

    return -1;
}

void addInt(intList* list, int value) {
    intNode* newNode = (intNode*)malloc(sizeof(intNode));
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->last = newNode;
        list->size++;
    } else {
        intNode* lastNode = list->last;
        lastNode->next = newNode;
        list->last = newNode;
        list->size++;
    }
}

void deleteInt(intList* list, int index) {
    intNode* actualNode = list->head;
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

void forEachInt(intList* list, void (*action)(int)) {
    intNode* actualNode = list->head;

    while (actualNode != NULL) {
        action(actualNode->value);
        actualNode = actualNode->next;
    }
}

bool anyInt(intList* list, bool (*condition)(int)) {
    intNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            return true;
        else
            actualNode = actualNode->next;
    }

    return false;
}

bool everyInt(intList* list, bool (*condition)(int)) {
    intNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            actualNode = actualNode->next;
        else
            return false;
    }

    return true;
}

intList* whereInt(intList* list, bool (*condition)(int)) {
    intList* newList = newEmptyIntList();

    intNode* actualNode = list->head;
    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            addInt(newList, actualNode->value);
        actualNode = actualNode->next;
    }

    return newList;
}

int reduceInt(intList* list, int (*combine)(int, int)) {
    if (list->head == NULL)
        return CONST_INT_ERROR;

    int value = list->head->value;
    intNode* actualNode = list->head->next;
    while (actualNode != NULL) {
        value = combine(value, actualNode->value);
        actualNode = actualNode->next;
    }

    return value;
}
