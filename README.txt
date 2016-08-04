The following program is used as a mock file system supporting Unix-like commands and operations. This program expects a single program parameter which should be the name of the text file containing the commands to perform. The text file should be saved in the same directory where the project, .c, and .h files are saved to avoid any errors 

The following assumptions are made regarding the file system.
1) Names of individual files/folders are no longer than 20 characters.
2) The valid characters are A-Z, a-z, 0-9, '-', '.', '_'
3) The maximum length of a path is 1000 characters 

The following are a list of valid operations that can be performed:

-----------------------------------------------------------------------------------
ls - List Command
Use:
ls <Path>
ls

Lists the contents of a given path if it exists within the file system otherwise an error message will be displayed. If no path is specified then the contents of the current working directory will be displayed.

Examples of use:
ls /Books
ls /Books/C_Programming

-----------------------------------------------------------------------------------
mkdir - Make directory
Use:
mkdir <Path>

Creates all missing directories as long as the path given is valid (no file in the middle of the path).

Examples of use:
mkdir /Books
mkdir /Recipes/BreakfastRecipes

-----------------------------------------------------------------------------------
touch - Make file
Use:
touch <Path>

Creates a file at the end of the given path and also creates missing directories if they do not yet exist in the file system.

Examples of use:
touch /Books/C_Books/C_by_Ritchie
touch /Books/C_Books/C_A_Modern_Approach

-----------------------------------------------------------------------------------
cd - Change directory
Use:
cd <Path>

Changes the current working directory to the node specified by <Path>. If it does not exist or an error occurs along the path then an error message will be displayed.

Examples of use:
cd /Books
cd /Books/C_Books

-----------------------------------------------------------------------------------
rm - Remove file/directory
Use:
rm <Path>
rm -f <Path>

The remove operation WITHOUT the '-f' parameter will remove a directory only if it is empty or simply remove a file if the end of the path indicates a file. Remove WITH the '-f' parameter will force remove the file/directory indicated by the path which includes all the sub-directories.

Examples of use:
rm /Books/C_Books/C_by_Ritchie
rm -f /Books/C_Books

-----------------------------------------------------------------------------------
find - Find in file system
Use:
find <Keyword>

Finds all directories/files that contain <Keyword> as a substring of the directory/file names. They are listed in a pre-order basis (the first successful finding will be printed first followed by subsequent finds in sibling and children nodes).

Examples of use:
find Books
find C_