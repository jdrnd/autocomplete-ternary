#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "list.c"

typedef struct Node {
  char val;
  bool isEndOfWord;
  struct Node* leftChild;
  struct Node* eqChild;
  struct Node* rightChild;
} Node;


Node* TST_getNewNode(char value) {
  Node* newNode = (Node*)malloc( sizeof(Node) );
  if (newNode == NULL) printf("Error with malloc");
  newNode->val = value;
  newNode->isEndOfWord = false;
  newNode->leftChild = newNode->eqChild = newNode->rightChild = NULL;

  return newNode;
}

// Returns last node inserted into tree
Node* TST_insert(Node* node, const char* word){
  // Add letter if it does not exist
  if (!node) {
    node = TST_getNewNode(*word);
  }

  // In case the word we want to insert as a subword of an already inserted word
  if (!(*word)) node->isEndOfWord = true;

  // Recures to correct child
  if (*word < node->val) {
    node->leftChild = TST_insert(node->leftChild, word);
  }
  else if (*word == node->val) {
    if (*word != '\0') {
      node->eqChild = TST_insert(node->eqChild, ++word);
    }
    else {
      node->isEndOfWord = true;
    }
  }
  else {
    node->rightChild = TST_insert(node->rightChild, word);
  }
  return node;
}

// Word does not have marked as a word in the tree,
// But all its letters must be inserted in order
Node* TST_getLastNode(Node* node, const char* word){
  // Required letter is not in the tree
  if (!node) return NULL;

  if (*word != '\0') {
    if (*word < node->val) {
      return TST_getLastNode(node->leftChild, word);
    }
    else if (*word == node->val) {
      if (*word != '\0') return TST_getLastNode(node->eqChild, ++word);
    }
    else {
      return TST_getLastNode(node->rightChild, word);
    }
  }

  // Implicitly *word must be NULL character
  return node;
}

bool TST_doesContain(Node* root, const char* word){
  Node* node = TST_getLastNode(root, word);

  if (!word || !*word || !node) return false;
  if (!node->isEndOfWord) return false;

  return true;
}

const char* TST_getCompletions(Node* root, const char* word){
  // TODO use custom stack impilemtation to traverse the tree
  // TODO break out into .c and .h files
  return NULL;
}

Node* TST_seed_from_file(Node* root, const char* file_name) {
  FILE* inputf = fopen(file_name, "r");
  if (!inputf) {
    puts("Error opening ");
    puts(file_name);
    return NULL;
  }

  char word[100]; //Words in file will have legnths less that 100 chars

  while (fgets(word, sizeof(word), inputf)) {
    word[strlen(word) - 1] = 0;
    root = TST_insert(root, word);
    assert(TST_doesContain(root, word)); // TODO remove

  }
  return root;
}


// Recursive method to find completions
void TST_find_completions(Node* node, const char* prefix, List* completions) {
  if (!node) return;
  if (node->isEndOfWord) List_add_to_list(completions, prefix);

  // Node has no children, we've reached a leaf node
  if (node->val == '\0') {
    return;
  }

  // DFS returns completions in order
  TST_find_completions(node->leftChild, prefix, completions);
  TST_find_completions(node->eqChild, prefix + node->val, completions);
  TST_find_completions(node->rightChild, prefix, completions);


}

// Wrapper function to manage output
void TST_get_completions(Node* root) {
  List* completions = List_get_empty_list();
  TST_find_completions(root, "", completions);
  List_print_list(completions);
}
