#include "test.c"
#include "autocomplete.h"

int main(void){
  char command;
  char input[20];

  Node* root = (Node*)NULL;
  root = TST_seed_from_file(root, "dictionary.txt");

  while (true) {


    puts("Press t to run tests, e to exit, or w to enter a word to complete:");
    command = getchar();

    if (command == 't') runTests();
    else if (command == 'w') {
      puts("Enter word to get completions for: ");
      scanf("%s", &input);
      TST_get_completions(root, input);
    }
    else if (command == 'e'){
      break;
    }

    // Clear input buffer
    fseek(stdin,0,SEEK_END);
  }
  TST_clear(root);
}
