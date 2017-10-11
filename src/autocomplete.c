#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "autocomplete.h"


bool is_leaf_node(Node* node) {
  return (!node->leftChild && !node->rightChild && !node->eqChild);
}

Node* TST_getNewNode(char value) {
  Node* newNode = (Node*)malloc( sizeof(Node) );
  if (newNode == NULL) printf("Error with malloc");
  newNode->val = value;
  newNode->isEndOfWord = false;
  newNode->leftChild = newNode->eqChild = newNode->rightChild = NULL;

  return newNode;
}

// Returns last node inserted into tree
Node* TST_insert(Node* node, const char* word) {
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

/*
 Gets the last character of a word contained in the tree,
 ie. the Node that contains to isEndOfWord marker; this will either
 contain the NULL character or a character in another word
 Word does not have marked as a word in the tree,
 But all its letters must be inserted in order
*/
Node* TST_getLastNode(Node* node, const char* word) {
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

bool TST_doesContain(Node* root, const char* word) {
  Node* node = TST_getLastNode(root, word);

  if (!word || !*word || !node) return false;
  if (!node->isEndOfWord) return false;

  return true;
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
  }
  return root;
}

// Clears tree and frees memory
void TST_clear(Node* node) {
  if (!node) return;

  if (!is_leaf_node(node)){
    TST_clear(node->leftChild);
    TST_clear(node->eqChild);
    TST_clear(node->rightChild);
  }
  free(node);
  node = NULL;
}


// Recursive method to find completions
void TST_find_completions(Node* node, char* prefix, List* completions) {
  if (!node) return;
  if (node->isEndOfWord) {
    List_add_to_list(completions, prefix);
  }
  // Node has no children, we've reached a leaf node
  if (is_leaf_node(node)) {
    return;
  }

  // We need to add strings here the proper way... :(
  // TODO optimize this
  char *new_prefix = malloc(strlen(prefix) + 2);
  strcpy(new_prefix, prefix);
  strcat(new_prefix, (const char*) &node->val);

  // DFS returns completions in order
  TST_find_completions(node->leftChild, prefix, completions);
  TST_find_completions(node->eqChild, new_prefix, completions);
  TST_find_completions(node->rightChild, prefix, completions);

  free(new_prefix);
}

// Wrapper function to manage output
void TST_get_completions(Node* root, char* word) {
  if (*word){
    root = TST_getLastNode(root, word);
  }

  List* completions = List_get_empty_list();

  TST_find_completions(root, word , completions);
  List_print_list(completions);
  List_clear_list(completions);
}
