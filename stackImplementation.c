#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printStack(stack_ptr s){
    sNode_ptr temp = s->top;
    while(temp != NULL){
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

void push(stack_ptr s, sNode_ptr n){
    n->next = s->top;
    s->top = n;
    s->numElements++;
}

void clearStack(sNode_ptr n){
    if(n == NULL){
        return;
    } else {
        clearStack(n->next);
        free(n);
    }
}

sNode_ptr pop(stack_ptr s){
    sNode_ptr returnNode = s->top;
    s->numElements--;
    s->top = s->top->next;
    returnNode->next = NULL;
    return returnNode;
}

sNode_ptr createStackNode(char name[]){
    sNode_ptr newNode = (sNode_ptr)malloc(sizeof(sNode_type));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

stack_ptr createStack(){
    stack_ptr newStack = (stack_ptr)malloc(sizeof(stack_type));
    newStack->top = NULL;
    newStack->numElements = 0;
    return newStack;
}


