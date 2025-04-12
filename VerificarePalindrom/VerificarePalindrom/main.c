#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int data;
    struct Node* next;
} Node;

void addEnd(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL)
        *head = newNode;
    else {
        Node* current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

void display(Node* head) {
    if (head == NULL) {
        printf("lista goala\n");
        return;
    }

    printf("lista: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

bool isPalindrome(Node* head) {
    if (head == NULL) return true;

    int values[100];
    int count = 0;

    Node* current = head;
    while (current != NULL) {
        values[count++] = current->data;
        current = current->next;
    }

    for (int i = 0; i < count / 2; i++) {
        if (values[i] != values[count - 1 - i])
            return false;
    }
    return true;
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
        printf("3. Verifica daca e palindrom\n");
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
            if (isPalindrome(head))
                printf("este palindrom.\n");
            else
                printf("nu este palindrom.\n");
            break;
        case 4:
            freeList(&head);
            printf("lista  stearsa.\n");
            break;
        case 0:
            freeList(&head);
            printf("program inchis\n");
            break;
        default:
            printf("optiune nevalida.\n");
        }

    } while (option != 0);

    return 0;
}