//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
#include <unistd.h>

int pwd() {
    char cwd[128];
    getcwd(cwd, sizeof(cwd));
    return printf("%s\n", cwd);
}

int main() {
    pwd();

    return 0;
}
