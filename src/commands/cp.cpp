//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
#include <stdlib.h>

void cp(char* src_file_name, char* dest_file_name, bool overwrite) {
    FILE* src_file = fopen(src_file_name, "r");
    if (src_file == NULL) {
        fprintf(stderr, "Error opening src file: %s\n", src_file_name);
        exit(1);
    }

    FILE* dest_file = fopen(dest_file_name, "r");
    if (dest_file != NULL) {
        fclose(dest_file);
        if (!overwrite) {
            fclose(src_file);
            return;
        }
    }

    dest_file = fopen(dest_file_name, "w");
    if (dest_file == NULL) {
        fprintf(stderr, "Error opening dest file: %s\n", dest_file_name);
        fclose(src_file);
        exit(1);
    }

    int ch;
    while ((ch = fgetc(src_file)) != EOF) {
        fputc(ch, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: cp <flags> <src file> <dest file1> <dest file2> ...\n");
    } else {
        int i          = 1;
        char* flags    = argv[1];
        int size       = sizeof(flags);
        bool overwrite = false;
        if (flags[0] == '-') {
            i++;
            for (int j = 1; j < size; j++) {
                switch (flags[j]) {
                    case 'o':
                        overwrite = true;
                        break;
                    default:
                        break;
                }
            }
        }

        for (int j = i + 1; j < argc; j++)
            cp(argv[i], argv[j], overwrite);

        return 0;
    }
}
