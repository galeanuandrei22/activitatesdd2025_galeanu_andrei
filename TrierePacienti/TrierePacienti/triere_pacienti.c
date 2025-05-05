#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
	char name[50];
	int age;
	int priority;
	struct Patient* next;

} Patient;

void insertByPriority(Patient** head, const char* name, int age, int priority) {
	Patient* newPatient = (Patient*)malloc(sizeof(Patient));
	strcpy(newPatient->name, name);
	newPatient->age = age;
	newPatient->priority = priority;
	newPatient->next = NULL;

	if (*head == NULL || priority < (*head)->priority) {
		newPatient->next = *head;
		*head = newPatient;
	}
	else {
		Patient* current = *head;
		while (current->next != NULL && current->next->priority <= priority) {
			current = current->next;
		}
		newPatient->next = current->next;
		current->next = newPatient;
	}
	printf("pacientul %s a fost adauga pe lista cu prioritate %d\n", name, priority);
}

void treatPatient(Patient** head) {
	if (*head == NULL) {
		printf("nu exista pacient in asteptare\n");
		return;
	}

	Patient* temp = *head;
	*head = (*head)->next;

	printf("pacient tratat %s (varsta: %d, prioritate: %d)\n", temp->name, temp->age, temp->priority);
	free(temp);
}

void displayPatients(Patient* head) {
	if (head == NULL) {
		printf("nu exista pacienti in lista\n");
		return;
	}

	printf("\nlista pacienti\n");
	while (head != NULL) {
		printf("nume: %s, varsta: %d, prioritate: %d\n", head->name, head->age, head->priority);
		head = head->next;
	}
}

void freeList(Patient** head) {
	Patient* current = *head;
	while (current != NULL) {
		Patient* temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

int main() {
	Patient* head = NULL;
	int opt, age, priority;
	char name[50];

	do {
		printf("1.adauga pacient\n");
		printf("2.trateaza pacient\n");
		printf("3.pacienti in asteptare\n");
		printf("0.iesire\n");
		printf("alege optiune: ");
		scanf("%d", &opt);
		getchar();

		switch (opt) {
		case 1:
			printf("Nume: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';
			printf("Varsta: ");
			scanf("%d", &age);
			printf("prioritate (1 = critic, 2 = grav, 3 = usor): ");
			scanf("%d", &priority);
			if (priority < 1 || priority > 3) {
				printf("prioritate invalida. foloseste 1, 2, 3.\n");
			}
			else {
				insertByPriority(&head, name, age, priority);
			}
			break;
		case 2:
			treatPatient(&head);
			break;
		case 3:
			displayPatients(head);
			break;
		case 0:
			freeList(&head);
			printf("program incheiat.\n");
			break;
		default:
			printf("optiune invalida.\n");
		}

	} while (opt != 0);

	return 0;
}