#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 100

bool is_empty(void);
bool is_full(void);
void push(int item);
int pop(void);
void stack_overflow(void);
void stack_underflow(void);

int contents[STACK_SIZE];
int *top;

int
main(void)
{
	top = &contents[0];
	int c;
	int left;

	printf("Enter parentheses and/or braces: ");

	while ((c = getchar()) != '\n') {
		switch(c) {
		case '{': case '(': case '[':
			push(c);
			break;
		case '}':
			left = pop();
			if (left != '{') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		case ')':
			left = pop();
			if (left != '(') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		case ']':
			left = pop();
			if (left != '[') {
				printf("Wanted '%c'. Got '%c'.\n", left, c);
				exit(EXIT_FAILURE);
			}
			break;
		default:
			break;
		}
	}

	if (is_empty()) {
		printf("Everything nested properly.\n");
		exit(EXIT_FAILURE);
	}
	else {
		left = pop();
		printf("Improper nesting: '%c' remaining.\n", left);
		exit(EXIT_SUCCESS);
	}
}

bool
is_empty()
{
	return top == &contents[0];
}

bool
is_full()
{
	return top == &contents[STACK_SIZE];
}

void
push(int item)
{
	if (is_full())
		stack_overflow();
	else {
		*top++ = item;
	}
}

int
pop(void)
{
	if (is_empty())
		stack_underflow();
	return *--top;
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
