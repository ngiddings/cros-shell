//
// Created by connor on 2/20/24.
//
#include <stdio.h>
#include <unistd.h>

#include "command.h"
#include "utility.h"
#include <string>

#define INPUT_MAX 128
#define HISTORY_MAX 10
char HISTORY[HISTORY_MAX];

/**
 * Main loop for the terminal.
 * 1. Print the prompt including current fs location
 * 2. Get the userinput using fgets into input
 * 3. Convert char input into string input_str
 * 4. Create a new command object and parse the input into the object.
 * 5. Call the run() method on the command object if parsed successfully.
 * 6. Flush input
 */
int main()
{

  // stuff from utility.h
  clear();
  PRINT_BANNER();
  //

  while (1)
  {
    // user input and file system location
    int parse_status, run_status;
    char input[INPUT_MAX], cwd[128];

    // get the current fs location and print a prompt
    getcwd(cwd, sizeof(cwd));
    printf("\033[32m%s\033[0m$ ", cwd);
    if (!fgets(input, sizeof(input), stdin)) {
      // if something is wrong with stdin, we're screwed.
      continue;
    }

    // get user input as a string and check for empty input
    std::string input_str(input);

    // BLANK INPUT
    if (input_str.size() <= 1)
    {
      continue;
    }

    // printf("%s", input);

    // parse the new command
    Command command;
    parse_status = command.parse(input_str);
    if (parse_status < 0) {
      printf("\033[1;31mUnrecognized command..\n\033[0m");
      continue;
    }

    run_status = command.run();
    if (run_status < 0) {
      printf("\033[1;31mUnexpected failure running command..\n\033[0m");
    }

    // flush input
    // scanf("%*[^\n]%*1[\n]");
    // getchar();
  }
}
