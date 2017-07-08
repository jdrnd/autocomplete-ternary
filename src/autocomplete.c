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

void TST_insert(Node* root, const char* word){
  char letter;
  Node* prevNode = root;
  Node* currNode = root;

  letter = *word;

  if (letter == '\0') return; // empty string
  if (root == NULL) return;

  while (letter != '\0') {
    prevNode = currNode;

    if (!currNode->eqChild) {
      // No child, set next letter as child
      currNode->eqChild = TST_getNewNode(letter);
      currNode = currNode->eqChild;
      ++word;
    }
    else {
      if (letter > currNode->val){
        if (!currNode->rightChild) {
          currNode->rightChild = TST_getNewNode(letter);
          currNode = currNode->rightChild;
          ++word;
        }
        else if (letter == currNode->rightChild->val) {
          currNode = currNode->rightChild;
          ++word;
        }
        else {
          currNode = currNode->rightChild;
        }
      }
      else if (*word < currNode->val) {
        if (!currNode->leftChild) {
          currNode->leftChild = TST_getNewNode(letter);
        }
        else if (letter == currNode->leftChild->val) {
          currNode = currNode->leftChild;
          ++word;
        }
        else {
          currNode = currNode->leftChild;
        }
      }
      else {
        // letter == currNode->val
        // We already know currNode->eqChild exists
        if (letter == currNode->eqChild->val) {
          currNode = currNode->eqChild;
          ++word;
        }
        else {
          currNode = currNode->eqChild;
        }
      }
    }
    letter = *word;
  }
  // set end of word flag
  currNode->isEndOfWord = true;
}

Node* TST_getLastNode(Node* root, const char* word){
  if (root == NULL || *word == '\0') return false;
  Node* currNode = root;
  char letter = *word;

  while (*word != '\0') {
    if (currNode->eqChild && letter == currNode->eqChild->val){
      currNode = currNode->eqChild;
      ++word;
    }
    else {
      if (letter == currNode->val) {
        if (!currNode->eqChild) return NULL;
        currNode = currNode->eqChild;
      }
      else if (letter > currNode->val) {
        if (!currNode->rightChild) return NULL;
        currNode = currNode->rightChild;
        if (letter == currNode->val) ++word;
      }
      else {
        // letter < currNode->val
        if (!currNode->leftChild) return NULL;
        currNode = currNode->leftChild;
        if (letter == currNode->val) ++word;
      }
    }
    letter = *word;
  }

  if (currNode->isEndOfWord){
    return currNode;
  }
  else return NULL;
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
