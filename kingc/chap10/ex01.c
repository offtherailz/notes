#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100

bool is_empty(int top);
bool is_full(int top);
void push(char contents[], int *top, char item);
char pop(char contents[], int *top);
void stack_overflow(void);
void stack_underflow(void);

int
main(void)
{
	char contents[STACK_SIZE];
	int top = 0;
	char c;
	char left;

	printf("Enter parentheses and/or braces: ");

	while (scanf("%c", &c) == 1 && c != '\n') {
		switch(c) {
		case '{': case '(': case '[':
			push(contents, &top, c);
			break;
		case '}':
			left = pop(contents, &top);
			if (left != '{') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		case ')':
			left = pop(contents, &top);
			if (left != '(') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		case ']':
			left = pop(contents, &top);
			if (left != '[') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		default:
			break;
		}
	}

	if (is_empty(top)) {
		printf("Everything nested properly.\n");
		exit(EXIT_FAILURE);
	}
	else {
		left = pop(contents, &top);
		printf("Improper nesting: '%c' remaining.\n", left);
		exit(EXIT_SUCCESS);
	}
}

bool
is_empty(int top)
{
	return top == 0;
}

bool
is_full(int top)
{
	return top == STACK_SIZE;
}

void
push(char contents[], int *top, char item)
{
	if (is_full(*top))
		stack_overflow();
	else {
		contents[(*top)++] = item;
	}
}

char
pop(char contents[], int *top)
{
	if (is_empty(*top))
		stack_underflow();
	return contents[--(*top)];
}

void
stack_overflow(void)
{
	printf("Stack full: can't push!\n");
	exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
	printf("Stack empty: can't pop!\n");
	exit(EXIT_FAILURE);
}
