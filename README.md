# Autocompletion in C

Uses a ternary search tree to store known words, allows for manual and dictionary file insertion.
A visualization of the tree can be viewed at https://www.cs.usfca.edu/~galles/visualization/TST.html

![Screenshot](https://image.prntscr.com/image/CXIxYXcySAikJx4D7Z1DIw.png)

#### Building
For the standard REPL, just run the included `build.sh` file, which will produce the `./autocomp` binary.

#### Usage
This is just a demo; to use build, then run the binary. Press `t` to run tests,
'e' to exit, and `w` to enter a word and have the program return completions.

#### Verifying Memory Integrity
To check for memory leaks, install `valgrind` and run the following command:
`valgrind --leak-check=yes ./autocomp -v`


#### API

`Node* TST_insert(Node* node, const char* word);`
Inserts the word into the tree, returns the new root of the tree.

`bool TST_doesContain(Node* root, const char* word);`
Returns whether word is contained in the tree referenced at root.

`Node* TST_seed_from_file(Node* root, const char* file_name);`
Seeds the autocompletion tree with words from the given dictionary file,
in this repository the included `dictionary.txt` file is used. Returns the new root Node.

`void TST_clear(Node* node);`
Deletes all words in the tree and frees the tree's memory.

`void TST_get_completions(Node* root, char* word);`
Prints a list of all completions of `word` that are contained in the tree.
