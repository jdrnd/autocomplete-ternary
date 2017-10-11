// Private
typedef struct ListNode {
  const char* contents;
  struct ListNode* next;
} ListNode;

ListNode* get_list_node(const char* contents) {
  ListNode* newNode = (ListNode*)malloc( sizeof(ListNode) );
  if (newNode == NULL) printf("Error with malloc");
  newNode->contents = contents;
  newNode->next = NULL;

  return newNode;
}

typedef struct List {
  struct ListNode* head;
  struct ListNode* tail;
} List;

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
