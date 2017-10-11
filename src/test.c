#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "autocomplete.h"

Node* test_insertion_and_basic_containment(Node* root) {
  puts("Running insertion and basic containment tests");
  root = TST_insert(root, "test");
  assert(TST_doesContain(root, "test"));

  root = TST_insert(root, "joel");
  assert(TST_doesContain(root, "joel"));

  root = TST_insert(root, "testing");
  assert(TST_doesContain(root, "test"));
  assert(TST_doesContain(root, "testing"));

  assert(!TST_doesContain(root, "notword"));
  assert(!TST_doesContain(root, "testin"));

  puts("Insertion and containment tests passed");
  return root;
}

Node* test_dictionary_insertion(Node* root) {
  puts("Running dictionary insertion tests");
  TST_seed_from_file(root, "dictionary.txt");


  assert(TST_doesContain(root, "abastardize"));
  assert(!TST_doesContain(root, "abastardiz"));
  assert(!TST_doesContain(root, "abasta"));
  assert(TST_doesContain(root, "a"));

  assert(TST_doesContain(root, "indispensabilities"));
  assert(TST_doesContain(root, "indispensability"));
  assert(!TST_doesContain(root, "indispensabi"));

  assert(TST_doesContain(root, "trigs"));
  assert(TST_doesContain(root, "zyzzyvas"));

  puts("Dictionary insertion tests passed");
  return root;
}

void runTests(){
  puts("\n\nRunning Tests..");

  Node* root = (Node*)NULL;

  // TODO free memory used by tree
  root = test_insertion_and_basic_containment(root);
  root = test_dictionary_insertion(root);

  TST_clear(root);
  puts("All tests passed! \n\n");
}
