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

  while (*word != '\0') {

    letter = *word;
    prevNode = currNode;

    if (letter < currNode->val){
      if (currNode->leftChild == NULL){
        currNode->leftChild = TST_getNewNode(letter);
      }
      currNode = currNode->leftChild;
    }
    else if (letter == currNode->val){
      if (currNode->eqChild== NULL){
        currNode->eqChild = TST_getNewNode(letter);
      }
      currNode = currNode->eqChild;
      ++word;
    }
    else {
      // letter > val
      if (currNode->rightChild == NULL) {
        currNode->rightChild = TST_getNewNode(letter);
      }
      currNode = currNode->rightChild;
    }

  }
  // set end of word flag
  currNode->isEndOfWord = true;
}

bool TST_doesContain(Node* root, const char* word){
  if (root == NULL || *word == '\0') return false;
  Node* currNode = root;

  size_t len = strlen(word);
  int i = 0;

  while (*word != '\0') {
    printf("%c\t%c\n", currNode->val, *word);

    if (*word > currNode->val){
      if (currNode->rightChild != NULL){
        currNode = currNode->rightChild;
      }
      else {
        return false;
      }
    }
    else if (*word < currNode->val) {
      // char < node's val
      if (currNode->leftChild != NULL){
        currNode = currNode->leftChild;
      }
      else {
        return false;
      }
    }
    else {
      // Values are equal
      ++i;
      if (currNode->eqChild != NULL){
        currNode = currNode->eqChild;
        ++word;
      }
      else {
        if (i == len && currNode->isEndOfWord) return true;
        else return false;
      }
    }
  }
  if (i == len && currNode->isEndOfWord) return true;
  else return false;
}
