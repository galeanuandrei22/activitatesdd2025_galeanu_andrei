#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node* left;
	struct Node* right;
} Node;

Node* createNode(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = value;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insert(Node* root, int value) {
	if (root == NULL) return createNode(value);
	if (value < root->data) {
		root->left = insert(root->left, value);
	}
	else if (value > root->data) {
		root->right = insert(root->right, value);
	}
	else {
		printf("valoarea %d exista deja\n", value);
	}
	return root;
}

Node* search(Node* root, int value) {
	if (root == NULL || root->data == value) {
		return root;
	}
	if (value < root->data) {
		return search(root->left, value);
	}
	return search(root->right, value);
}

Node* minValueNode(Node* node) {
	Node* current = node;
	while (current && current->left != NULL) {
		current = current->left;
	}
	return current;
}

Node* delete(Node* root, int value) {
	if (root == NULL) return root;
	if (value < root->data) {
		root->left = delete(root->left, value);
	}
	else if (value > root->data) {
		root->right = delete(root->right, value);
	}
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}

		Node* temp = minValueNode(root->right);
		root->data = temp->data;
		root->
		right = delete(root->right, temp->data);
	}
	return root;
}

void inorder(Node* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void preorder(Node* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(Node* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

void freeTree(Node* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main() {
	Node* root = NULL;
	int opt, val;

	do {
		printf("1. inserare\n");
		printf("2. cautare\n");
		printf("3. stergere\n");
		printf("4. inorder\n");
		printf("5. preorder\n");
		printf("6. postorder\n");
		printf("0. iesire\n");
		printf("alege optiune: ");
		scanf("%d", &opt);

		switch (opt) {
		case 1:
			printf("valoare: ");
			scanf("%d", &val);
			root = insert(root, val);
			break;
		case 2:
			printf("valoare: ");
			scanf("%d", &val);
			if (search(root, val))
				printf("valoarea %d a fost gasita\n", val);
			else
				printf("valoarea %d NU a fost gasita\n", val);
			break;
		case 3:
			printf("valoare: ");
			scanf("%d", &val);
			root = delete(root, val);
			printf("valoarea %d a fost stearsa\n", val);
			break;
		case 4:
			printf("inorder: ");
			inorder(root);
			printf("\n");
			break;
		case 5:
			printf("preorder: ");
			preorder(root);
			printf("\n");
			break;
		case 6:
			printf("postorder: ");
			postorder(root);
			printf("\n");
			break;
		case 0:
			freeTree(root);
			printf("program incheiat\n");
			break;
		default:
			printf("optiune invalida\n");
		}

	} while (opt != 0);

	return 0;
}