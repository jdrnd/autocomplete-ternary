/*
Defines a singly-linked list of strings used for storing
autocompletion results
*/

#ifndef LIST_H
#define LIST_H


typedef struct ListNode {
  char* contents;
  struct ListNode* next;
} ListNode;

ListNode* get_list_node(const char* new_contents);


typedef struct List {
  struct ListNode* head;
  struct ListNode* tail;
} List;

List* List_get_empty_list();
void List_add_to_list(List* list, const char* word);
void List_print_list(List* list);
void List_clear_list(List* list);

#endif
