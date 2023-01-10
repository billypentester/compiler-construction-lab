#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_EXPR_SIZE 100

typedef struct {
    char data[MAX_EXPR_SIZE];
    int top;
} Stack;

void push(Stack *s, char c) {
    s->data[++(s->top)] = c;
}

char pop(Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}

void infixToPostfix(char *infix, char *postfix) {
    int i, j = 0;
    Stack operators;
    operators.top = -1;
    for (i = 0; i < strlen(infix); i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&operators, infix[i]);
        } else if (infix[i] == ')') {
            while (operators.data[operators.top] != '(') {
                postfix[j++] = pop(&operators);
            }
            pop(&operators);
        } else {
            while (operators.top != -1 && priority(infix[i]) <= priority(operators.data[operators.top])) {
                postfix[j++] = pop(&operators);
            }
            push(&operators, infix[i]);
        }
    }
    while (operators.top != -1) {
        postfix[j++] = pop(&operators);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_EXPR_SIZE], postfix[MAX_EXPR_SIZE];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
