typedef struct {
    char symbol;
    char code[4];
} CodeMap;

void _getCodesRec(HuffmanNode* node, char* buffer, int depth, Array* out) {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) {
        buffer[depth] = '\0';
        CodeMap* map = malloc(sizeof(CodeMap));
        map->symbol = node->symbol;
        strcpy(map->code, buffer);
        add(out, map);
        return;
    }

    buffer[depth] = '0';
    _getCodesRec(node->left, buffer, depth + 1, out);

    buffer[depth] = '1';
    _getCodesRec(node->right, buffer, depth + 1, out);
}

Array* getCodes(HuffmanTree* tree) {
    Array* result = newEmptyArray(sizeof(CodeMap), 4);

    char buffer[4];
    _getCodesRec(tree->root, buffer, 0, result);

    return result;
}

void printEncoded(Array* codes, char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        for (int j = 0; j < codes->size; j++) {
            CodeMap* map = (CodeMap*)_get(codes,j);
            if (map->symbol == text[i]) {
                printf("%s", map->code);
                break;
            }
        }
    }
    printf("\n");
}

void printDecoded(HuffmanTree* tree, char* encoded) {
    HuffmanNode* node = tree->root;

    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '0') 
            node = node->left;
        if (encoded[i] == '1') 
            node = node->right;

        if (node->left == NULL && node->right == NULL) {
            printf("%c", node->symbol);
            node = tree->root;
        }
    }

    printf("\n");
}