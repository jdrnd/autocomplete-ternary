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

Node* TST_insert(Node* node, const char* word){
  // Add letter if it does not exist
  if (!node) {
    node = TST_getNewNode(*word);
  }

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

Node* TST_getLastNode(Node* node, const char* word){
  if (!node) return NULL;
  if (node->isEndOfWord && *word == '\0') return node;

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

bool TST_doesContain(Node* root, const char* word){
  Node* node = TST_getLastNode(root, word);

  if (!word || !*word || !node) return false;
  if (word[strlen(word)] != node->val) return false;
  if (!node->isEndOfWord) return false;

  return true;
}

const char* TST_getCompletions(Node* root, const char* word){
  // TODO use custom stack impilemtation to traverse the tree
  // TODO break out into .c and .h files
  return NULL;
}
