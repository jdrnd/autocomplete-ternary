#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "autocomplete.c"

void runTests(){
  Node* root = TST_getNewNode('\0');

  TST_insert(root, "test");
  printf("%i\n", TST_doesContain(root, "test"));

  TST_insert(root, "joel");
  printf("%i\n", TST_doesContain(root, "joel"));

  TST_insert(root, "testing");
  printf("%i\n", TST_doesContain(root, "testing"));

  printf("%i\n", TST_doesContain(root, "notword"));
  printf("%i\n", TST_doesContain(root, "testin"));

  // TODO free memory used by tree
}
