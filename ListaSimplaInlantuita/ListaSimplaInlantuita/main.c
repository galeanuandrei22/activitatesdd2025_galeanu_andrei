#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* next;
} Node;

void addFront(Node** head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = *head;
	*head = newNode;
	printf("%d a fost adaugat la inceputul listei.\n", value);
}

void addEnd(Node** head, int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		Node* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
	}
	printf("%d a fost adaugat la sfarsitul listei.\n", value);
}

void deleteByValue(Node** head, int value) {
	Node* current = *head;
	Node* prev = NULL;

	while (current != NULL && current->data != value) {
		prev = current;
		current = current->next;
	}

	if (current == NULL) {
		printf("%d nu a fost gasit\n", value);
		return;
	}

	if (prev == NULL) {
		*head = current->next;
	}
	else {
		prev->next = current->next;
	}

	free(current);
	printf("%d a fost sters\n", value);
}

void search(Node* head, int value) {
	Node* current = head;
	int index = 0;
	while (current != NULL) {
		if (current->data == value) {
			printf("%d a fost gasit la pozitia %d\n", value, index);
			return;
		}
		current = current->next;
		index++;
	}
	printf("%d nu a fost gasit.\n", value);
}

void display(Node* head) {
	if (head == NULL) {
		printf("Lista este goala\n");
		return;
	}
	printf("Lista: ");
	Node* current = head;
	while (current != NULL) {
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}

void freeList(Node** head) {
	Node* current = *head;
	while (current != NULL) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

int main() {
	Node* head = NULL;
	int option, value;
	do {
		printf("\n--- MENIU ---\n");
		printf("1. Adauga la inceput\n");
		printf("2. Adauga la sfarsit\n");
		printf("3. Sterge dupa valoare\n");
		printf("4. Cauta element\n");
		printf("5. Afiseaza lista\n");
		printf("6. Elibereaza memoria\n");
		printf("0. Iesire\n");
		printf("Alege o optiune: ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			printf("Valoare: ");
			scanf("%d", &value);
			addFront(&head, value);
			break;
		case 2:
			printf("Valoare: ");
			scanf("%d", &value);
			addEnd(&head, value);
			break;
		case 3:
			printf("Valoare de sters: ");
			scanf("%d", &value);
			deleteByValue(&head, value);
			break;
		case 4:
			printf("Valoare de cautat: ");
			scanf("%d", &value);
			search(head, value);
			break;
		case 5:
			display(head);
			break;
		case 6:
			freeList(&head);
			printf("Memoria a fost eliberata.\n");
			break;
		case 0:
			freeList(&head);
			printf("Iesire din program.\n");
			break;
		default:
			printf("Optiune invalida.\n");
		}
	} while (option != 0);
	return 0;
}