#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include "list.h"

typedef struct Node {
  char val;
  bool isEndOfWord;
  struct Node* leftChild;
  struct Node* eqChild;
  struct Node* rightChild;
} Node;

// Public
Node* TST_insert(Node* node, const char* word);
bool TST_doesContain(Node* root, const char* word);
Node* TST_seed_from_file(Node* root, const char* file_name); // default is "dictionary.txt"
void TST_clear(Node* node);
void TST_get_completions(Node* root, char* word);

// Private
bool is_leaf_node(Node* node);
Node* TST_getNewNode(char value);
Node* TST_getLastNode(Node* node, const char* word);
void TST_find_completions(Node* node, char* prefix, List* completions);

#endif
