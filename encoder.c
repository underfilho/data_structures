#include <stdio.h>
#include "headers/priority_queue.h"
#include "headers/huffman/huffman_tree.h"
#include "headers/huffman/huffman_converter.h"
#include "headers/utils.h"

int main() {
    char* pattern = "AAAABCDD";

    PQueue* pq = buildPriorityQueue(pattern);
    forEach(pq, printQ);
    printf("\n");

    getchar();

    HuffmanTree* tree = buildTree(pq);
    printTree(tree);

    getchar();
    
    Array* codes = getCodes(tree);
    forEach(codes, printMap);

    getchar();

    char* example = "AAABCD";
    printf("\n%s = ", example);
    printEncoded(codes, example);
}