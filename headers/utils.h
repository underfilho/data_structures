#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void printChar(void* e) {
    printf("%c", *(char*)e);
}

void printInt(void* e) {
    printf("%d", *(int*)e);
}

void printDouble(void* e) {
    printf("%2.f", *(double*)e);
}

void printQ(void* e) {
	Element* element = (Element*)e;
    HuffmanNode* node = (HuffmanNode*)element->value;
	printf("%c: %d; ", node->symbol, element->priority);
}

void printMap(void* e) {
    CodeMap* map = (CodeMap*)e;
	printf("%c: %s\n", map->symbol, map->code);
}