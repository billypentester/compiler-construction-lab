#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void postfixToInfix(char *postfix, char *infix) {
    int i, j = 0;
    Stack s;
    s.top = -1;
    for (i = 0; i < strlen(postfix); i++) {
        if (isalnum(postfix[i])) {
            infix[j++] = postfix[i];
        } else {
            char op1 = pop(&s);
            char op2 = pop(&s);
            infix[j++] = '(';
            infix[j++] = op2;
            infix[j++] = postfix[i];
            infix[j++] = op1;
            infix[j++] = ')';
        }
    }
    infix[j] = '\0';
}

int main() {
    char postfix[MAX_EXPR_SIZE], infix[MAX_EXPR_SIZE];
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);
    postfixToInfix(postfix, infix);
    printf("Infix expression: %s\n", infix);
    return 0;
}
