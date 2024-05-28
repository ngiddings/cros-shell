//
// Created by connor on 2/7/24.
// functions similarly to linux ls
//

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ls(char* dir_path) {
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        fprintf(stderr, "Error opening directory: %s\n", dir_path);
        exit(1);
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        char dir[100];
        getcwd(dir, sizeof(dir));
        ls(dir);
    } else {
        for (int i = 1; i < argc; i++)
            ls(argv[i]);
    }
    return 0;
}