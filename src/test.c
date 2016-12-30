#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "autocomplete.c"

void runTests(){
  Node* root = TST_getNewNode('\0');

  TST_insert(root, "test");
  printf("%i\n", TST_doesContain(root, "test"));

  // TODO free memory used by tree
}
