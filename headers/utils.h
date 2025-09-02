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