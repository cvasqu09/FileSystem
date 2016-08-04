#include "fileSystemHeader.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

node_ptr createNode(char name[], int fileBit){
    node_ptr newNode = (node_ptr)malloc(sizeof(node_type));
    strcpy(newNode->name, name);
    newNode->fileBit = fileBit;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = NULL;
    return newNode;
}

void printNode(node_ptr n){
    printf("Printing node info\n");
    printf("Name: %s\n", n->name);
    printf("File bit: %d\n", n->fileBit);

    if(n->parent == NULL){
        printf("Parent: NULL\n");
    } else {
        printf("Parent: %s\n", n->parent->name);
    }

    if(n->sibling == NULL){
        printf("Sibling: NULL\n");
    } else {
        printf("Sibling: %s\n", n->sibling->name);
    }

    if(n->child == NULL){
        printf("Child: NULL\n");
    } else {
        printf("Child: %s\n", n->child->name);
    }
}

void getPWD(node_ptr n, char returnPath[]){
    memset(returnPath, 0, 1000);
    node_ptr temp = n;
    while(temp != NULL){
        if(strcmp(temp->name, "/") == 0){
        } else {
            strcat(returnPath, temp->name);
            strcat(returnPath, "/");
        }
        temp = temp->parent;
    }

    reversePath(returnPath);
    return;
}

void reversePath(char pathToReverse[]){
    stack_ptr s1 = createStack();

    char* token;
    token = strtok(pathToReverse, "/");
    while(token != NULL){
        sNode_ptr newNode = createStackNode(token);
        push(s1, newNode);
        token = strtok(NULL, "/");
    }

    memset(pathToReverse, 0, 1000);
    strcpy(pathToReverse, "/");
    sNode_ptr temp = s1->top;
    while(temp != NULL){
        if(s1->numElements == 1){
            sNode_ptr currentSNode = pop(s1);
            strcat(pathToReverse, currentSNode->name);
            temp = s1->top;
        } else {
            sNode_ptr currentSNode = pop(s1);
            strcat(pathToReverse, currentSNode->name);
            strcat(pathToReverse, "/");
            temp = s1->top;
        }
    }
    clearStack(s1->top);
}

void getNames(char path[], char stringsArray[][21], int* numStrings){
    char* token = strtok(path, "/");
    int i = 0;
    while(token != NULL){
        strcpy(stringsArray[i], token);
        token = strtok(NULL, "/");
        i++;
        (*numStrings)++;
    }
    return;
}

node_ptr searchChildren(node_ptr n, char name[]){
    node_ptr temp = n->child;
    while(temp != NULL){
        if(strcmp(temp->name, name) == 0){
            break;
        }
        temp = temp->sibling;
    }
    return temp;
}

node_ptr follow(node_ptr n, char path[]){
    //Copy the path
    char copyPath[1000];
    memset(copyPath, 0, 1000);
    strcpy(copyPath, path);
    node_ptr temp = n;

    if(path[0] == '/'){
        while(temp->parent != NULL){
            temp = temp->parent;
        }
    }

    char namesArray[100][21];
    char errorPath[1000];
    memset(errorPath, 0, 1000);

    int numPaths = 0;
    getNames(copyPath, namesArray, &numPaths);

    int i = 0;
    for(i = 0; i < numPaths; i++){
        strcat(errorPath, "/");
        strcat(errorPath, namesArray[i]);
        temp = searchChildren(temp, namesArray[i]);
        if(temp == NULL){
            printf("Path Error: directory %s does not exist\n", errorPath);
            return NULL;
        }
    }
    return temp;
}

bool safeToCreate(node_ptr n, char path[]){
    char copyPath[1000];
    memset(copyPath, 0, 1000);
    strcpy(copyPath, path);
    int numNames = 0;
    char namesArray[100][21];
    getNames(copyPath, namesArray, &numNames);
    char errorPath[1000];
    memset(errorPath, 0, 1000);

    node_ptr temp = n;
    int i;
    for(i = 0; i < numNames; i++){
        temp = searchChildren(temp, namesArray[i]);
        if(temp == NULL){
            return true;
        } else if(temp->fileBit == 0 && i != numNames - 1){
            printf("Path Error: Cannot create sub-directory content, %s is a file.\n", path);
            return false;
        } else if(temp != NULL && i == numNames - 1){
            printf("%s already exists and cannot be created\n", path);
            return false;
        }
    }

    return true;
}

void listDirectoryContents(node_ptr n, char path[]){
    node_ptr temp;
    temp = follow(n, path);
    if(temp == NULL){
        printf("List Error: Cannot perform list operation.\n");
        return;
    } else if(temp->fileBit == 0){
        printf("List Error: Cannot perform list operation. %s is a file.\n", path);
        return;
    } else {
        node_ptr tempChild = temp->child;
        printf("Listing For %s\n", path);
        while(tempChild != NULL){
            if(tempChild->fileBit == 0){
                printf("F ");
            } else {
                printf("D ");
            }
            printf("%s\n", tempChild->name);
            tempChild = tempChild->sibling;
        }
    }
}

int getCharValue(char c){
    if(c == '\0'){
        return 0;
    } else if(c == '.'){
        return 1;
    } else if(c == '-'){
        return 2;
    } else if(c == '_'){
        return 3;
    } else {
        return (int)c;
    }
}

int compare(node_ptr node1, node_ptr node2){
    if(node1->fileBit > node2->fileBit){
        return -1;
    } else if(node1->fileBit < node2->fileBit){
        return 1;
    } else {
        char name1[20];
        char name2[20];
        memset(name1, 0, 20);
        memset(name2, 0, 20);
        strcpy(name1, node1->name);
        strcpy(name2, node2->name);
        int i;
        for(i = 0; i < 20; i++){
            int c1Value = getCharValue(name1[i]);
            int c2Value = getCharValue(name2[i]);
            if(c1Value > c2Value){
                return 1;
            } else if(c1Value < c2Value){
                return -1;
            }
        }
        return 0;
    }
}

void addNode(node_ptr parent, node_ptr child){
    node_ptr temp = parent->child;
    if(temp == NULL){
        parent->child = child;
        child->parent = parent;
    }

    while(temp != NULL){
        if(temp == parent->child && compare(child, temp) < 0){
            parent->child = child;
            child->parent = parent;
            child->sibling = temp;
            return;
        } else if(temp->sibling == NULL){
            temp->sibling = child;
            child->parent = parent;
            return;
        } else if(compare(child, temp->sibling) < 0){
            child->parent = parent;
            child->sibling = temp->sibling;
            temp->sibling = child;
            return;
        } else {
            temp = temp->sibling;
        }
    }
}

void makeDirectory(node_ptr n, char path[]){
    bool safe = safeToCreate(n, path);
    if(safe == 0){
        printf("Make Dir Error: Cannot create directory.\n");
        return;
    } else {
        char copyPath[1000];
        memset(copyPath, 0, 1000);
        strcpy(copyPath, path);
        char namesArray[100][21];
        int numNames = 0;
        getNames(copyPath, namesArray, &numNames);

        int i;
        node_ptr temp;
        node_ptr tempParent;
        temp = n;
        for(i = 0; i < numNames; i++){
            tempParent = temp;
            temp = searchChildren(tempParent, namesArray[i]);
            if(temp == NULL){
                node_ptr newNode = createNode(namesArray[i], 1);
                addNode(tempParent, newNode);
                temp = newNode;
            }
        }
        return;
    }
}

void touch(node_ptr n, char path[]){
    bool safe = safeToCreate(n, path);
    if(safe == false){
        printf("Touch Error: Cannot create file.\n");
        return;
    } else {
        char copyPath[1000];
        memset(copyPath, 0, 1000);
        strcpy(copyPath, path);
        char stringArr[100][21];
        int numNames = 0;
        getNames(copyPath, stringArr, &numNames);
        int i;
        node_ptr temp;
        node_ptr tempParent;
        temp = n;
        for(i = 0; i < numNames; i++){
            tempParent = temp;
            if(i == numNames - 1){
                node_ptr newNode = createNode(stringArr[i], 0);
                addNode(tempParent, newNode);
                return;
            } else {
                temp = searchChildren(temp, stringArr[i]);
                if(temp == NULL){
                    node_ptr newDir = createNode(stringArr[i], 0);
                    addNode(tempParent, newDir);
                    temp = newDir;
                }
            }
        }
    }
}

node_ptr changeDirectory(node_ptr n, char path[]){
    n = follow(n, path);
    if(n == NULL){
        printf("Change Directory Error: Cannot change working directory.\n");
        return NULL;
    } else {
        return n;
    }
}

void removePath(node_ptr n, char path[]){
    n = follow(n, path);
    if(n == NULL){
        printf("Remove Error: Cannot remove file or directory.\n");
        return;
    } else if(n->child != NULL){
        printf("Remove Error: Directory %s is not empty.\n", path);
        return;
    } else {
        node_ptr tempParent = n->parent;
        node_ptr temp = tempParent->child;
        if(n == temp){
            temp = temp->sibling;
            tempParent->child = temp;
            n->sibling = NULL;
            n->parent = NULL;
            free(n);
            return;
        } else {
            while(temp->sibling != n){
                temp = temp->sibling;
            }
            printf("Removing node: %s\n", temp->sibling->name);
            temp->sibling = n->sibling;
            n->parent = NULL;
            n->sibling = NULL;
            free(n);
            return;
        }
    }
}

void forceRemove(node_ptr n, char path[]){
    n = follow(n, path);
    if(n == NULL){
        printf("Remove Error: Cannot remove file or directory.\n");
        return;
    } else {
        node_ptr tempParent = n->parent;
        node_ptr temp = tempParent->child;
        if(temp == n){
            temp = temp->sibling;
            tempParent->child = temp;
            n->sibling = NULL;
            n->parent = NULL;
            recursiveRemove(n->child);
            free(n);
            return;
        } else {
            while(temp->sibling != n){
                temp = temp->sibling;
            }
            temp->sibling = n->sibling;
            n->parent = NULL;
            n->sibling = NULL;
            recursiveRemove(n->child);
            free(n);
            return;

        }
    }
}

void recursiveRemove(node_ptr n){
    if(n == NULL){
        return;
    } else {
        recursiveRemove(n->sibling);
        recursiveRemove(n->child);
        free(n);
        n = NULL;
        return;
    }
}

void fileSystemFind(node_ptr n, char item[]){
    char* charPtr;
    if(n == NULL){
        return;
    } else {
        charPtr = strstr(n->name, item);
        if(charPtr != NULL){
            if(n->fileBit == 1){
                printf("D ");
            } else {
                printf("F ");
            }
            char path[1000];
            getPWD(n, path);
            printf("%s\n", path);
            fileSystemFind(n->child, item);
            fileSystemFind(n->sibling, item);
        } else {
            fileSystemFind(n->child, item);
            fileSystemFind(n->sibling, item);
        }
    }
}

void printFileSystem(node_ptr n){
    if(n == NULL){
        return;
    } else {
        printf("%s->", n->name);
        printFileSystem(n->sibling);
        printf("\n");
        printFileSystem(n->child);
    }

}




