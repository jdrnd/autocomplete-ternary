#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "autocomplete.c"

void runTests(){
  printf("%s", "Running Tests..");

  Node* root = (Node*)NULL;

  root = TST_insert(root, "test");
  assert(TST_doesContain(root, "test") == true);

  root = TST_insert(root, "joel");
  assert(TST_doesContain(root, "joel") == true);

  root = TST_insert(root, "testing");
  assert(TST_doesContain(root, "test") == true);
  assert(TST_doesContain(root, "testing") == true);

  assert(TST_doesContain(root, "notword") == false);
  assert(TST_doesContain(root, "testin") == false);

  // TODO free memory used by tree
}
