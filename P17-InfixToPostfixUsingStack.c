#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//This will be an algorithm that converts infix expressions to postfix

//For something like A+B*C-D*E. In order to convert this into a postfix, a computer would read it left to right. So first it will read A and then +, but it cannot put + into the postfix expression yet since we dont have the second operand
//That is when you would put that operator into a stack. But for any expressoin with a higher precedence in the stack, can be popped and placed into the post fix expression. Also just note that if stuff like +/- is in the same expression, go left to right to rank precendence.
//In the end the postfix expression would be ABC*+DE*-. In the stack * would go in first but it will come out first, thereby it being the first operator in the expression. Other operators would be popped early due to order of operations
//You also would need to take care of paranthesis.

struct node{
    char data;
    struct node *next;
};

struct node *top = NULL;

void push(char x){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp -> data = x;
    temp -> next = top;
    top = temp;
}

char pop(){
    struct node *temp = top;
    char op;

    if(top == NULL){
        printf("Stack Empty");
        exit(1);
    }
    op = top -> data;
    temp = top;
    top = temp -> next;
    free(temp);
    return op;
}

int precedence(char x){
    switch (x){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

bool isOperand(char x){
    if(x=='^' || x=='/' || x=='+' || x=='-' || x=='*') return 1;
    else return 0;
}

int main(){
    char x[100];
    char c[100];
    printf("Enter infix expression: \n");
    scanf("%s", c);
    
    int i = 0;
    int j = 0;

    while(c[i]){

        if(isOperand(c[i])){
           if (top == NULL || (precedence(c[i])) >= (precedence(top->data)) || top -> data == '('){
                push(c[i]);
            }
            else{
                x[j] = pop();
                j++;
                push(c[i]);
            }
        }
        else if(c[i] == '('){
            push(c[i]);
        }
        else if(c[i] == ')'){
            while(top -> data != '('){
                x[j] = pop();
                j++;
            }
            pop();
        }
        else{
            x[j] = c[i];
            j++;
        }
        i++;
    }

    printf("%s", x);
}