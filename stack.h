#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct Stack stack_type;
typedef struct Stack* stack_ptr;
typedef struct stackNode sNode_type;
typedef struct stackNode* sNode_ptr;

struct stackNode{
    char name[20];
    sNode_ptr next;
};

struct Stack{
    sNode_ptr top;
    int numElements;
};

void clearStack(sNode_ptr);
void push(stack_ptr, sNode_ptr);
void printStack(stack_ptr);

stack_ptr createStack();
sNode_ptr pop(stack_ptr);
sNode_ptr createStackNode(char []);

#endif // STACK_H_INCLUDED
