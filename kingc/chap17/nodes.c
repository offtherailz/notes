#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node *next;
};

struct node *add_to_list(struct node *list, int n);

int main(void)
{
	int *p;
	struct node *first = NULL;
	struct node *iter;

	first = malloc(sizeof(struct node));
	first->next = NULL;

	printf("Enter an integer value (0 to quit): ");
	scanf(" %d", p);
	first->value = *p;

	while (*p != 0) {
		printf("Enter an integer value (0 to quit): ");
		scanf(" %d", p);
		first = add_to_list(first, *p);
	}

	for (iter = first; iter != NULL; iter = iter->next) {
		if (iter->value != 0) {
			printf("Node value: %d\n", iter->value);
		}
	}

	return 0;
}

struct node *add_to_list(struct node *list, int n)
{
	struct node *new_node;

	new_node = malloc(sizeof(struct node));
	if (new_node == NULL) {
		printf("Error: malloc failed in add_to_list.\n");
		exit(EXIT_FAILURE);
	}

	new_node->value = n;
	new_node->next = list;

	return new_node;
}
