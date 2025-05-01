#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
	char name[50];
	int arrivalTime;
	int processingTime;
	struct Client* next;
} Client;

typedef struct {
	Client* front;
	Client* rear;
} Queue;

Queue* createQueue() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

void enqueue(Queue* q, const char* name, int arrivalTime, int processingTime) {
	Client* newClient = (Client*)malloc(sizeof(Client));
	strcpy(newClient->name, name);
	newClient->arrivalTime = arrivalTime;
	newClient->processingTime = processingTime;
	newClient->next = NULL;

	if (q->rear = NULL) {
		q->front = q->rear = newClient;
	}
	else {
		q->rear->next = newClient;
		q->rear = newClient;
	}
	printf("clientul %s a fost adaugat\n", name);
}

void simulate(Queue* q) {
	if (q->front = NULL) {
		printf("nu exista clienti in coada\n");
		return;
	}

	int currentTime = 0;
	int totalWait = 0;
	printf("SIMULARE\n");
	Client* current = q->front;
	while (current != NULL) {
		if (current->arrivalTime > currentTime) {
			currentTime = current->arrivalTime;
		}
		int start = currentTime;
		int end = start + current->processingTime;
		int wait = start - current->arrivalTime;
		totalWait += wait;
		printf("client: %s, sosire: %d, start: %d, sfarsit: %d, asteptare: %d secunde\n", current->name, current->arrivalTime, start, end, wait);
		currentTime = end;
		current = current->next;
	}
	printf("Timp total de asteptare: %d secunde\n", totalWait);
}

void freeQueue(Queue* q) {
	Client* current = q->front;
	while (current != NULL) {
		Client* temp = current;
		current = current->next;
		free(temp);
	}
	free(q);
}

int main() {
	Queue* q = createQueue();
	int opt;
	char name[100];
	int arrival, duration;
	do {
		printf("1. adauga client\n");
		printf("2. simuleaza coada\n");
		printf("0. iesire\n");
		printf("alege optiune: ");
		scanf("%d", &opt);
		getchar();

		switch (opt) {
		case 1:
			printf("nume: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = 0;
			printf("timp sosire (secunde): ");
			scanf("%d", &arrival);
			printf("timp procesare (secunde): ");
			scanf("%d", &duration);
			enqueue(q, name, arrival, duration);
			break;
		case 2:
			simulate(q);
			break;
		case 0:
			freeQueue(q);
			printf("simulare incheiata.\n");
			break;
		default:
			printf("optiune invalida.\n");
		}

	} while (opt != 0);

	return 0;
}