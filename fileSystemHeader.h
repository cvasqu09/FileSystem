#include <stdbool.h>

typedef struct Node node_type;
typedef struct Node* node_ptr;

struct Node{
    char name[20];
    int fileBit;    //1 = directory, 0 = file
    node_ptr sibling;
    node_ptr child;
    node_ptr parent;
};

void addNode(node_ptr, node_ptr);
void printNode(node_ptr);
void reversePath(char[]);
void getNames(char [], char[][21], int*);
node_ptr searchChildren(node_ptr, char[]);
node_ptr createNode(char[], int);
int compare(node_ptr, node_ptr);
int getCharValue(char c);


void getPWD(node_ptr, char[]);
void listDirectoryContents(node_ptr, char[]);
void makeDirectory(node_ptr, char[]);
void touch(node_ptr, char[]);
void removePath(node_ptr, char[]);
void forceRemove(node_ptr, char[]);
void recursiveRemove(node_ptr);
void fileSystemFind(node_ptr, char[]);
void printFileSystem(node_ptr);
node_ptr follow(node_ptr, char[]);
node_ptr changeDirectory(node_ptr, char[]);
bool safeToCreate(node_ptr, char[]);
