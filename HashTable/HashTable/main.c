#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct Item {
	char* key;
	int value;
	struct Item* next;
} Item;

Item* table[SIZE];

unsigned int hash(const char* key) {
	unsigned int hash = 0;
	while (*key)
		hash = (hash * 31 + *key++) % SIZE;
	return hash;
}

Item* createItem(const char* key, int value) {
	Item* newItem = (Item*)malloc(sizeof(Item));
	newItem->key = _strdup(key);
	newItem->value = value;
	newItem->next = NULL;
	return newItem;
}

void insert(const char* key, int value) {
	unsigned int index = hash(key);
	Item* newItem = createItem(key, value);
	if (table[index] == NULL) {
		table[index] = newItem;
	}
	else {
		newItem->next = table[index];
		table[index] = newItem;
	}
	printf("Cheia %s a fost adaugata cu valoarea %d\n", key, value);
}

Item* search(const char* key) {
	unsigned int index = hash(key);
	Item* current = table[index];
	while (current != NULL) {
		if (strcmp(current->key, key) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

void delete(const char* key) {
	unsigned int index = hash(key);
	Item* current = table[index];
	Item* prev = NULL;
	while (current != NULL) {
		if (strcmp(current->key, key) == 0) {
			if (prev == NULL)
				table[index] = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current);
			printf("Cheia %s a fost stearsa\n", key);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Cheia %s nu a fost gasita\n", key);
}

void display() {
	for (int i = 0; i < SIZE; i++) {
		printf("[%d]: ", i);
		Item* current = table[i];
		while (current != NULL) {
			printf("(%s -> %d) ", current->key, current->value);
			current = current->next;
		}
		printf("\n");
	}
}

void freeTable() {
	for (int i = 0; i < SIZE; i++) {
		Item* current = table[i];
		while (current != NULL) {
			Item* temp = current;
			current = current->next;
			free(temp->key);
			free(temp);
		}
		table[i] = NULL;
	}
}

int main() {
	int opt, value;
	char key[256];

	do {
		printf("1. Inserare\n");
		printf("2. Cautare\n");
		printf("3. Stergere\n");
		printf("4. Afisare hash table\n");
		printf("0. Iesire\n");
		scanf("%d", &opt);
		getchar();

		switch (opt) {
		case 1:
			printf("Cheie: ");
			fgets(key, sizeof(key), stdin);
			key[strcspn(key, "\n")] = '\0';
			printf("Valoare: ");
			scanf("%d", &value);
			insert(key, value);
			break;
		case 2:
			printf("Cheie: ");
			fgets(key, sizeof(key), stdin);
			key[strcspn(key, "\n")] = '\0';
			Item* found = search(key);
			if (found)
				printf("Gasita: %s -> %d\n", found->key, found->value);
			else
				printf("cheia nu a fost gasita.\n");
			break;
		case 3:
			printf("Cheie: ");
			fgets(key, sizeof(key), stdin);
			key[strcspn(key, "\n")] = '\0';
			delete(key);
			break;
		case 4:
			display();
			break;
		case 0:
			freeTable();
			printf("program inchis\n");
			break;
		default:
			printf("invalid.\n");
		}
	} while (opt != 0);

	return 0;
}