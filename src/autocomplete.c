#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

void TST_insert(Node* node, const char* word){
  if (node->val == *word) ++word;

  if (*word == '\0') {
    node->isEndOfWord = true;
    return;
  }

  printf("%c", *word);

  if (!node->eqChild) {
    node->eqChild = TST_getNewNode(*word);
    TST_insert(node->eqChild, word);
  }
  else if (*word == node->val || node->eqChild->val == *word) {
    TST_insert(node->eqChild, word);
  }
  else if (*word < node->val) {
    if (!node->leftChild){
      node->leftChild = TST_getNewNode(*word);
    }
    TST_insert(node->leftChild, word);
  }
  else if (*word > node->val) {
    if (!node->rightChild) {
      node->rightChild = TST_getNewNode(*word);
    }
    TST_insert(node->rightChild, word);
  }
}

Node* TST_getLastNode(Node* node, const char* word){
  if (!node) {
    return NULL;
  }

  if (*word == '\0') {
    return node;
  }

  // If next letter is a direct descendant, recures to that node and advance the word pointer
  if (node->eqChild && node->eqChild->val == *word){
    return TST_getLastNode(node->eqChild, ++word);
  }
  else if (node->leftChild && node->leftChild->val == *word) {
    return TST_getLastNode(node->leftChild, ++word);
  }
  else if (node->rightChild && node->rightChild->val == *word) {
    return TST_getLastNode(node->rightChild, ++word);
  }
  // If next letter is not a descendant, recurse to the correct child node without advancing the word pointer
  else if (*word < node->val) {
    return TST_getLastNode(node->leftChild, word);
  }
  else if (*word == node->val) {
    return TST_getLastNode(node->eqChild, word);
  }
  else { // *word > node->val
    return TST_getLastNode(node->rightChild, word);
  }
}

bool TST_doesContain(Node* root, const char* word){
  Node* node = TST_getLastNode(root, word);

  if (!word || !*word || !node) return false;
  if (word[strlen(word) - 1] != node->val) return false;
  if (!node->isEndOfWord) return false;

  return true;
}

const char* TST_getCompletions(Node* root, const char* word){
  // TODO use custom stack impilemtation to traverse the tree
  // TODO break out into .c and .h files
  return NULL;
}
