#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

void addEnd(Node** head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		Node* current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = newNode;
	}
}

void display(Node* head) {
	if (head == NULL) {
		printf("Lista este goala\n");
		return;
	}

	printf("Lista ");
	while (head != NULL) {
		printf("%d -> ", head->data);
		head = head->next;
	}
	printf("NULL\n");
}

void reverseList(Node** head) {
	Node* prev = NULL, * current = *head, * next = NULL;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
	printf("Lista inversata\n");
}

void freeList(Node** head) {
	Node* temp;
	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

int main() {
	Node* head = NULL;
	int option, value;

	do {
		printf("1. Adauga element\n");
		printf("2. Afiseaza lista\n");
		printf("3. Inverseaza lista\n");
		printf("4. Elibereaza lista\n");
		printf("0. Iesire\n");
		scanf("%d", &option);

		switch (option) {
		case 1:
			printf("Valoare: ");
			scanf("%d", &value);
			addEnd(&head, value);
			break;
		case 2:
			display(head);
			break;
		case 3:
			reverseList(&head);
			break;
		case 4:
			freeList(&head);
			printf("Lista stearsa\n");
			break;
		case 0:
			freeList(&head);
			printf("program inchis\n");
			break;
		default:
			printf("nu exista\n");
		}

	} while (option != 0);

	return 0;
}