//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
#include <sys/syscall.h>

void mkdir_func(char* dir_path) {
    mkdir(dir_path);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        mkdir_func(argv[2]);
    }
    printf("mkdir not implemented.");
    return 0;
}
