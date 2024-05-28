//
// Created by connor on 2/7/24.
// functions similarly to linux ls
//
#include <stdio.h>

void echo(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        printf("Usage: echo <prompt>\n");
    else
        echo(argc, argv);
    return 0;
}