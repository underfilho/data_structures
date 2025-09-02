typedef struct doubleNode {
    double value;
    struct doubleNode* next;
} doubleNode;

typedef struct doubleList {
    doubleNode* head;
    int size;
} doubleList;

doubleList* newEmptyDoubleList() {
    doubleList* newList = malloc(sizeof(doubleList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

doubleList* newDoubleList(int num, ...) {
    doubleList* newList = newEmptyDoubleList();
    va_list args;

    va_start(args, num);
    doubleNode* actualNode = newList->head;

    for (int i = 0; i < num; i++) {
        double value = va_arg(args, double);
        doubleNode* newNode = malloc(sizeof(doubleNode));
        newNode->value = value;
        newNode->next = NULL;

        if (actualNode == NULL) {
            newList->head = actualNode = newNode;
            newList->size++;
        } else {
            actualNode->next = newNode;
            actualNode = actualNode->next;
            newList->size++;
        }
    }
    va_end(args);

    return newList;
}

double getDouble(doubleList* list, int index) {
    if (index > list->size - 1)
        return 123456.0;

    doubleNode* actualNode = list->head;
    for (int i = 0; i < index; i++) {
        actualNode = actualNode->next;
    }

    return actualNode->value;
}

int findDouble(doubleList* list, double element) {
    doubleNode* actualNode = list->head;

    for (int i = 0; i < list->size; i++) {
        if (actualNode->value == element)
            return i;
        actualNode = actualNode->next;
    }

    return -1;
}

void addDouble(doubleList* list, double value) {
    doubleNode* newNode = malloc(sizeof(doubleNode));
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->size++;
        return;
    }

    doubleNode* actualNode = list->head;
    while (actualNode->next != NULL)
        actualNode = actualNode->next;

    actualNode->next = newNode;
    list->size++;
}

void deleteDouble(doubleList* list, int index) {
    doubleNode* actualNode = list->head;
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

void forEachDouble(doubleList* list, void (*action)(double)) {
    doubleNode* actualNode = list->head;

    while (actualNode != NULL) {
        action(actualNode->value);
        actualNode = actualNode->next;
    }
}

bool anyDouble(doubleList* list, bool (*condition)(double)) {
    doubleNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            return true;
        else
            actualNode = actualNode->next;
    }

    return false;
}

bool everyDouble(doubleList* list, bool (*condition)(double)) {
    doubleNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            actualNode = actualNode->next;
        else
            return false;
    }

    return true;
}

doubleList* whereDouble(doubleList* list, bool (*condition)(double)) {
    doubleList* newList = newEmptyDoubleList();

    doubleNode* actualNode = list->head;
    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            addDouble(newList, actualNode->value);
        actualNode = actualNode->next;
    }

    return newList;
}