#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
	char *arr;
	int size;
	int top;
};

int push(struct stack *s, char *ch) {
	if (s->top == s->size)	return -1;
	s->arr[s->top++] = *ch;
	return 0;
}

char pop(struct stack *s) {
	if (s->top == 0)	return -1;
	return s->arr[--(s->top)];
}

int is_parenthesis_balanced(char *str) {
	char ch, ch2;
	struct stack s;
	s.size = 100;
	s.top = 0;
	s.arr = (char *)calloc(100, sizeof(char));
	while ((ch = *str)) {
		printf ("%d\n", ch);
		if ((ch == '{') || (ch == '(') || (ch == '[')) {
			if (push(&s, &ch)) return 0;
		}
		else if ((ch == '}') || (ch == ')') || (ch == ']')) {
			ch2 = pop(&s);
			if (ch2 == -1)	return 0;
			if (((ch == '}') && (ch2 != '{')) || ((ch == ')') && (ch2 != '(')) ||((ch == ']') && (ch2 != '['))) {
				return 0;
			}
		}
		str++;
	}
	return (s.top == 0) ? 1 : 0;
}

int main(int argc, char **argv) {
	printf("%d\n", is_parenthesis_balanced(argv[1]));
	return 0;
}
