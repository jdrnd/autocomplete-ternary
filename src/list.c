#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"


ListNode* get_list_node(const char* new_contents) {
  ListNode* newNode = (ListNode*)malloc( sizeof(ListNode) );
  char* contents = malloc(strlen(new_contents) + 1);
  strcpy(contents, new_contents);
  if (newNode == NULL) printf("Error with malloc");
  newNode->contents = contents;
  newNode->next = NULL;

  return newNode;
}



// Public

List* List_get_empty_list() {
  List* newList = (List*)malloc( sizeof(List) );
  if (newList == NULL) printf("Error with malloc");
  newList->head = get_list_node("");
  newList->tail = newList->head;

  return newList;
}

void List_add_to_list(List* list, const char* word) {
  ListNode* newNode = get_list_node(word);
  list->tail->next = newNode;
  list->tail = newNode;
}

void List_print_list(List* list) {
  ListNode* node = list->head;

  while (node) {
    puts(node->contents);
    node = node->next;
  }
}

void List_clear_list(List* list) {
  ListNode* node = list->head;
  ListNode* prev_node = list->head;

  while(node != NULL) {
    prev_node = node;
    node = node->next;

    free(prev_node->contents);
    free(prev_node);
  }
}
