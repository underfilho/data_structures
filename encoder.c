#include <stdio.h>
#include "headers/priority_queue.h"
#include "headers/huffman/huffman_tree.h"
#include "headers/huffman/huffman_converter.h"
#include "headers/utils.h"

int main() {
    char* keyword = "ooalmndu ";

    PQueue* queue = buildPriorityQueue(keyword);
    forEach(queue, printQ);
    printf("\n");
    
    getchar();

    HuffmanTree* tree = buildTree(queue);
    printTree(tree);

    getchar();
    
    Array* codes = getCodes(tree);
    forEach(codes, printMap);

    char* example = "ola mundo";
    printf("\n%s = ", example);
    printEncoded(codes, example);
}