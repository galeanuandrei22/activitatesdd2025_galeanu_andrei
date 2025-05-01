#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
	int id;
	char name[100];
	float grade;
	struct Student* next;
} Student;

void addStudent(Student** head, int id, const char* name, float grade) {
	Student* newStudent = (Student*)malloc(sizeof(Student));
	newStudent->id = id;
	strcpy(newStudent->name, name);
	newStudent->grade = grade;
	newStudent->next = NULL;

	if (*head == NULL) {
		*head = newStudent;
	}
	else {
		Student* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newStudent;
	}
	printf("studentul %s a fost adaugat\n", name);
}

void displayStudents(Student* head) {
	if (head == NULL) {
		printf("lista de studenti este goala\n");
		return;
	}

	printf("LISTA STUDENTI\n");
	while (head != NULL) {
		printf("ID: %d, nume: %s, medie: %.2f\n", head->id, head->name, head->grade);
		head = head->next;
	}
}

void findStudent(Student* head, int id) {
	while (head != NULL) {
		if (head->id == id) {
			printf("student gasit: %s, id: %d, medie: %.2f\n", head->name, head->id, head->grade);
			return;
		}
		head = head->next;
	}
	printf("studentul cu id %d nu a fost gasit\n", id);
}

void deleteStudent(Student** head, int id) {
	Student* current = *head;
	Student* prev = NULL;

	while (current != NULL && current->id != id) {
		prev = current;
		current = current->next;
	}
	if (current == NULL) {
		printf("studentul cu id %d nu a fost gasit\n", id);
		return;
	}
	if (prev == NULL) {
		*head = current->next;
	}
	else {
		prev->next = current->next;
	}
	free(current);
	printf("studentul cu id %d a fost sters", id);
}

void freeList(Student** head) {
	Student* current = *head;
	while (current != NULL) {
		Student* temp = current;
		current = current-> next;
		free(temp);
	}
	*head = NULL;
}

int main() {
	Student* head = NULL;
	int opt, id;
	float grade;
	char name[100];

	do {
		printf("1. adauga student\n");
		printf("2. afiseaza toti studentii\n");
		printf("3. cauta student dupa ID\n");
		printf("4. sterge student dupa ID\n");
		printf("0. iesire\n");
		printf("alege optiune: ");
		scanf("%d", &opt);
		getchar();

		switch (opt) {
		case 1:
			printf("ID: ");
			scanf("%d", &id);
			getchar();
			printf("nume: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = 0;
			printf("medie: ");
			scanf("%f", &grade);
			addStudent(&head, id, name, grade);
			break;
		case 2:
			displayStudents(head);
			break;
		case 3:
			printf("ID de cautat: ");
			scanf("%d", &id);
			findStudent(head, id);
			break;
		case 4:
			printf("ID de sters: ");
			scanf("%d", &id);
			deleteStudent(&head, id);
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