#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct CharStack {
    char data[MAX];
    int top;
};

struct StringStack {
    char data[MAX][MAX];
    int top;
};

void initCharStack(struct CharStack *s) {
    s->top = -1;
}

void initStringStack(struct StringStack *s) {
    s->top = -1;
}

int isCharStackEmpty(struct CharStack *s) {
    return s->top == -1;
}

void pushChar(struct CharStack *s, char value) {
    s->data[++(s->top)] = value;
}

char popChar(struct CharStack *s) {
    if (isCharStackEmpty(s)) return '\0';
    return s->data[(s->top)--];
}

char peekChar(struct CharStack *s) {
    if (isCharStackEmpty(s)) return '\0';
    return s->data[s->top];
}

void pushString(struct StringStack *s, char *value) {
    strcpy(s->data[++(s->top)], value);
}

void popString(struct StringStack *s, char *res) {
    if (s->top >= 0) {
        strcpy(res, s->data[(s->top)--]);
    }
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    struct CharStack s;
    initCharStack(&s);
    int i, j = 0;
    
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            pushChar(&s, ch);
        } else if (ch == ')') {
            while (!isCharStackEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            popChar(&s);
        } else {
            while (!isCharStackEmpty(&s) && precedence(peekChar(&s)) >= precedence(ch)) {
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, ch);
        }
    }

    while (!isCharStackEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0';
}

void postfixToInfix(char *postfix, char *infix) {
    struct StringStack s;
    initStringStack(&s);
    char temp[MAX], op1[MAX], op2[MAX];
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch[2] = {postfix[i], '\0'};
        if ((postfix[i] >= '0' && postfix[i] <= '9') || (postfix[i] >= 'A' && postfix[i] <= 'Z') || (postfix[i] >= 'a' && postfix[i] <= 'z')) {
            pushString(&s, ch);
        } else {
            popString(&s, op2);
            popString(&s, op1);
            sprintf(temp, "(%s%c%s)", op1, postfix[i], op2);
            pushString(&s, temp);
        }
    }

    popString(&s, infix);
}

int main() {
    char infix[MAX], postfix[MAX], convertedInfix[MAX];
    int choice;

    while (1) {
        printf("\n1. Konversi Infix ke Postfix\n");
        printf("2. Konversi Postfix ke Infix\n");
        printf("3. Keluar\n");
        printf("Input pilihanmu: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi Infix: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Ekspresi Postfixnya adalah: %s\n", postfix);
                break;

            case 2:
                printf("Masukkan ekspresi Postfix: ");
                scanf("%s", postfix);
                postfixToInfix(postfix, convertedInfix);
                printf("Ekspresi Infixnya adalah: %s\n", convertedInfix);
                break;

            case 3:
                printf("See you next time!\n");
                return 0;

            default:
                printf("Pilihan invalid\n");
        }
    }
}

