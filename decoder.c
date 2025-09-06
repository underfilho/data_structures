#include <stdio.h>
#include "headers/priority_queue.h"
#include "headers/huffman/huffman_tree.h"
#include "headers/huffman/huffman_converter.h"
#include "headers/utils.h"

int main() {
    char* keyword = "ooalmndu ";
    PQueue* queue = buildPriorityQueue(keyword);
    HuffmanTree* tree = buildTree(queue);

    printDecoded(tree, "001001100111011111111001000");
}