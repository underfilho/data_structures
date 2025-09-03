#include <stdio.h>
#include "headers/priority_queue.h"
#include "headers/huffman/huffman_tree.h"
#include "headers/huffman/huffman_converter.h"
#include "headers/utils.h"

int main() {
    char* pattern = "AAAABCDD";
    PQueue* pq = buildPriorityQueue(pattern);
    HuffmanTree* tree = buildTree(pq);

    printDecoded(tree, "00011011110");
}