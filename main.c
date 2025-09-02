#include <stdio.h>
#include "headers/priority_queue.h"

void print(void* e) {
	Element* element = (Element*)e;
	printf("%d ", element->priority);
}

int main() {
	// -- Arrays --
    // Array* array = newArray(sizeof(int), 10, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20);

	// int num = 0;
	// while(num != -1) {
	// 	printf("Digite um numero para pesquisar: ");
	// 	scanf("%d", &num);
	// 	fflush(stdin);
		
	// 	int index = binarySearch(array, num);
	// 	printf("%d\n", index);
	// 	forEach(array, print);
	// 	printf("\n");
	// 	getchar();
	// }
	
	// -- Stacks --
    // Stack* stack = newStack(sizeof(int));
    // PUSH(stack, 1);
    // PUSH(stack, 2);
    // PUSH(stack, 3);

    // int value;
    // pop(stack, &value);
    // printf("%d\n", value);
    // pop(stack, &value);
    // printf("%d\n", value);

    // forEach(stack, print);

	// -- Queues --
	// Queue* q = newQueue(sizeof(int));
	// ENQUEUE(q, 3);
	// ENQUEUE(q, 4);
	// ENQUEUE(q, 2);
	// ENQUEUE(q, 1);

	// int* item = dequeue(q);
	// printf("%d\n", *item);
	// getchar();

	// -- Priority Queue --
	PQueue* pq = newPriorityQueue(sizeof(Element));

	int prioridades[] = {5, 3, 8, 1, 6, 4, 7, 2};

	for (int i = 0; i < 8; i++) {
		INSERT_PQ(pq, prioridades[i], 'c');
    }

	forEach(pq, print);
	printf("\n");

	while(pq->size > 0) {
		Element* e = pop_pq(pq);
        printf("%d\n", e->priority);
	}
}