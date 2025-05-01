#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct Queue {
	Node* front;
	Node* rear;
} Queue;

Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

void enqueue(Queue* q, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;

	if (q->rear == NULL) {
		q->front = q->rear = newNode;
	}
	else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
	printf("adaugat: %d\n", value);
}

void dequeue(Queue* q) {
	if (q->front == NULL) {
		printf("coada este goala\n");
		return;
	}

	Node* temp = q->front;
	q->front = q->front->next;

	if (q->front == NULL) {
		q->rear == NULL;
	}
	printf("scos: %d\n", temp->data);
	free(temp);
}

void peek(Queue* q) {
	if (q->front == NULL) {
		printf("coada este goala\n");
	}
	else {
		printf("primul element: %d\n", q->front->data);
	}
}

void display(Queue* q) {
	if (q->front == NULL) {
		printf("coada este goala\n");
		return;
	}

	printf("coada: ");
	Node* current = q->front;
	while (current != NULL) {
		printf("%d <- ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}

void freeQueue(Queue* q) {
	while (q->front != NULL) {
		dequeue(q);
	}
	free(q);
}

int main() {
	Queue* q = createQueue();
	int opt, val;

	do {
		printf("1. adauga\n");
		printf("2. scoate\n");
		printf("3. vezi primul\n");
		printf("4. afiseaza coada\n");
		printf("0. iesire\n");
		printf("alege optiune: ");
		scanf("%d", &opt);

		switch (opt) {
		case 1:
			printf("valoare: ");
			scanf("%d", &val);
			enqueue(q, val);
			break;
		case 2:
			dequeue(q);
			break;
		case 3:
			peek(q);
			break;
		case 4:
			display(q);
			break;
		case 0:
			freeQueue(q);
			printf("program terminat\n");
			break;
		default:
			printf("optiune invalida\n");
		}

	} while (opt != 0);

	return 0;
}