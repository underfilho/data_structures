char chars[] = { 'o', 'l', 'a', 'm', 'u', 'n', 'd', ' ' };
int size = 8;

typedef struct HuffmanNode {
    char symbol;
    int freq;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
} HuffmanNode;

typedef struct HuffmanTree {
    HuffmanNode* root;
} HuffmanTree;

int* countFrequencies(char* text) {
    int* freq = (int*)calloc(size, sizeof(int));

    for (int i = 0; text[i] != '\0'; i++) {
        for (int j = 0; j < size; j++) {
            if(text[i]==chars[j])
                freq[j]++;
        }
    }

    return freq;
}

PQueue* buildPriorityQueue(char* text) {
    PQueue* pq = newPriorityQueue(sizeof(Element));
    int* freq = countFrequencies(text);

    for (int i = 0; i < size; i++) {
        if (freq[i] > 0) {
            HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
            node->symbol = chars[i];
            node->freq = freq[i];
            node->left = NULL;
            node->right = NULL;

            Element e = { freq[i], node };
            insert_pq(pq, &e);
        }
    }

    return pq;
}

HuffmanTree* buildTree(PQueue* pq) {
    while (pq->size > 1) {
        Element* e1 = pop_pq(pq);
        Element* e2 = pop_pq(pq);

        HuffmanNode* n1 = (HuffmanNode*) e1->value;
        HuffmanNode* n2 = (HuffmanNode*) e2->value;

        HuffmanNode* merged = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        merged->symbol = '\0';
        merged->freq = n1->freq + n2->freq;
        merged->left = n1;
        merged->right = n2;

        Element e;
        e.priority = merged->freq;
        e.value = merged;

        insert_pq(pq, &e);
    }

    Element* root = pop_pq(pq);
    HuffmanTree* tree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    tree->root = (HuffmanNode*)root->value;
    return tree;
}

HuffmanTree* buildHuffmanTreeFromString(char* text) {
    PQueue* pq = buildPriorityQueue(text);
    HuffmanTree* tree = buildTree(pq);

    return tree;
}

void _recPrintTree(HuffmanNode* root, int level) {
    if (root == NULL) return;

    _recPrintTree(root->left, level + 1);

    for (int i = 0; i < level; i++) printf("     ");

    if (root->symbol != '\0')
        printf("'%c' (%d)\n", root->symbol, root->freq);
    else
        printf("(%d)<\n", root->freq);

    _recPrintTree(root->right, level + 1);
}

void printTree(HuffmanTree* tree) {
    _recPrintTree(tree->root, 0);
    printf("\n");
}
