#include <stdio.h>
#include "headers/priority_queue.h"
#include "headers/huffman/huffman_tree.h"
#include "headers/huffman/huffman_converter.h"

void printMap(void* e) {
    CodeMap* map = (CodeMap*)e;
	printf("%c: %s\n", map->symbol, map->code);
}

int main() {
    char* text = "AAAABCDD";

    HuffmanTree* tree = buildHuffmanTreeFromString(text);
    printTree(tree);

    getchar();
    
    Array* codes = getCodes(tree);
    forEach(codes, printMap);

    char* example = "AAABCD";
    printf("\n%s = ", example);
    printEncoded(codes, example);

    printDecoded(tree, "00011011110");
}