typedef struct charNode {
    char value;
    struct charNode* next;
} charNode;

typedef struct charList {
    charNode* head;
    int size;
} charList;

charList* newEmptyCharList() {
    charList* newList = malloc(sizeof(charList));
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

charList* newCharList(int num, ...) {
    charList* newList = newEmptyCharList();
    va_list args;

    va_start(args, num);
    charNode* actualNode = newList->head;

    for (int i = 0; i < num; i++) {
        char value = va_arg(args, int);
        charNode* newNode = malloc(sizeof(charNode));
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

char getChar(charList* list, int index) {
    if (index > list->size - 1)
        return '\0';

    charNode* actualNode = list->head;
    for (int i = 0; i < index; i++) {
        actualNode = actualNode->next;
    }

    return actualNode->value;
}

int findChar(charList* list, char element) {
    charNode* actualNode = list->head;

    for (int i = 0; i < list->size; i++) {
        if (actualNode->value == element)
            return i;
        actualNode = actualNode->next;
    }

    return -1;
}

void addChar(charList* list, char value) {
    charNode* newNode = malloc(sizeof(charNode));
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->size++;
        return;
    }

    charNode* actualNode = list->head;
    while (actualNode->next != NULL)
        actualNode = actualNode->next;

    actualNode->next = newNode;
    list->size++;
}

void deleteChar(charList* list, int index) {
    charNode* actualNode = list->head;
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

void forEachChar(charList* list, void (*action)(char)) {
    charNode* actualNode = list->head;

    while (actualNode != NULL) {
        action(actualNode->value);
        actualNode = actualNode->next;
    }
}

bool anyChar(charList* list, bool (*condition)(char)) {
    charNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            return true;
        else
            actualNode = actualNode->next;
    }

    return false;
}

bool everyChar(charList* list, bool (*condition)(char)) {
    charNode* actualNode = list->head;

    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            actualNode = actualNode->next;
        else
            return false;
    }

    return true;
}

charList* whereChar(charList* list, bool (*condition)(char)) {
    charList* newList = newEmptyCharList();

    charNode* actualNode = list->head;
    while (actualNode != NULL) {
        bool result = condition(actualNode->value);
        if (result)
            addChar(newList, actualNode->value);
        actualNode = actualNode->next;
    }

    return newList;
}
