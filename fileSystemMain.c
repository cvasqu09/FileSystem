#include <stdio.h>
#include "fileSystemHeader.h"
#include "string.h"
void clearString(char* s){
    memset(s, 0, strlen(s));
}

void readLine(char line[], char commandStrings[][1000]){
    char* token = strtok(line, " \n");
    char* newLineExists = strchr(commandStrings[0], '\n');
    strcpy(commandStrings[0], token);
    if(newLineExists){
        *newLineExists = 0;
    }

    token = strtok(NULL, " ");
    int i = 1;
    while(i < 3){
        if(token == NULL){
            strcpy(commandStrings[i], "");
            i++;
        } else {
            strcpy(commandStrings[i], token);
            newLineExists = strchr(commandStrings[i], '\n');
            if(newLineExists){
                *newLineExists = 0;
            }
            token = strtok(NULL, " ");
            i++;
        }
    }
}

int main(int argc, char* argv[]){
    FILE* filePtr;
    if(argc == 1){
        printf("No program parameter was passed. \nThe program expects"
               " one program parameter which should be the name of the text"
               " file containing the commands to be run. Please try again.");
        return 0;
    }

    if(argc > 2){
        printf("Too many arguments were given. \nThe program expects"
               " only one program parameter which should be the name of the text"
               " file containing the commands to be run. Please try again.");
        return 0;
    }

    filePtr = fopen(argv[1], "r");
    if(filePtr == NULL){
        printf("Error: Could not open %s.\n Please make sure the file is saved"
               " in the same directory as the project, .c, and .h files and try"
               " again.", argv[1]);
        return 0;
    }

    char line[81];
    char commandStrings[3][1000];
    char path[1000];
    node_ptr root = createNode("/", 1);
    node_ptr current = root;
    while(fgets(line, 81, filePtr) != NULL){
        clearString(commandStrings[0]);
        clearString(commandStrings[1]);
        clearString(commandStrings[2]);
        readLine(line, commandStrings);

        printf("Command is: %s %s %s\n", commandStrings[0], commandStrings[1], commandStrings[2]);
        if(strcmp(commandStrings[0], "ls") == 0){
            if(strcmp(commandStrings[1], "\0") == 0 || strcmp(commandStrings[1], "\n") == 0){
                clearString(path);
                getPWD(current, path);
                listDirectoryContents(current, path);
            } else {
                listDirectoryContents(current, commandStrings[1]);
            }
        } else if(strcmp(commandStrings[0], "mkdir") == 0){
            int i;
            for(i = 0; i < strlen(commandStrings[1]); i++){
            }
            makeDirectory(current, commandStrings[1]);
        } else if(strcmp(commandStrings[0], "touch") == 0){
            touch(current, commandStrings[1]);
        } else if(strcmp(commandStrings[0], "cd") == 0){
            current = changeDirectory(current, commandStrings[1]);
            printf("Current directory is now: %s\n", current->name);
        } else if(strcmp(commandStrings[0], "rm") == 0){
            if(strcmp(commandStrings[1], "-f") == 0){
                forceRemove(current, commandStrings[2]);
            } else {
                removePath(current, commandStrings[1]);
            }
        } else if(strcmp(commandStrings[0], "find") == 0){
            fileSystemFind(root, commandStrings[1]);
        } else {
            printf("Command '%s' not recognized.\n", commandStrings[0]);
        }
    }

    return 0;
}

