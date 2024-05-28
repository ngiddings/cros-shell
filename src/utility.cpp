//
// Created by connor on 2/21/24.
//
#include "utility.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

std::vector<std::string> split_string(std::string &str,
                                      const std::string &delimiter) {
  size_t pos = 0;
  std::vector<std::string> parsed_input;
  if (str.find(delimiter) != std::string::npos) {
    while ((pos = str.find(delimiter)) != std::string::npos) {
      std::string token = str.substr(0, pos);
      if (token.size() > 0) {
        parsed_input.push_back(token);
      }
      str.erase(0, pos + delimiter.size());
    }
  }
  if (str.size() > 0)
    parsed_input.push_back(str);
  return parsed_input;
}

int cd(const char *str) {
  if (chdir(str) != 0) {
    printf("Unable to find path.\n");
    return -1;
  }
  return 0;
}

void PRINT_BANNER() {
  printf("\033[32m________  ________  ________  ________\n\033[0m");
  printf("\033[32m|\\   ____\\|\\   __  \\|\\   __  \\|\\   ____\\\n\033[0m");
  printf("\033[32m\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|_\n\033[0m");
  printf("\033[32m \\ \\  \\    \\ \\   _  _\\ \\  \\\\\\  \\ \\_____  \\\n\033[0m");
  printf("\033[32m  \\ \\  \\____\\ \\  \\\\  \\\\ \\  \\\\\\  \\|____|\\  \\\n\033[0m");
  printf("\033[32m   \\ \\_______\\ \\__\\\\ _\\\\ \\_______\\____\\_\\  \\\n\033[0m");
  printf("\033[32m    \\|_______|\\|__|\\|__|\\|_______|\\_________\\\n\033[0m");
  printf("\033[32m                                  \\|_________|\n\033[0m");
  printf("\033[32m    \"Powered by terminal gremlins and questionable memory accessing.\"\n\n\033[0m");

  printf("Input a command or use '\033[34mhelp\033[0m' for some ideas\n");
}

void clear() {
  printf("\033[H\033[J");
}