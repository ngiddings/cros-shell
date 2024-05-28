//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
int main() {
    printf("Commands:\n");
    printf("    joke\n");
    printf("    echo <prompt>\n");
    printf("    ls <directory>\n");
    printf("    cd <path>\n");
    printf("    pwd\n");
    printf("    search <flags> <token> <file1> <file2> ...\n");
    printf("        -v: verbose\n");
    printf("    wc <flags> <file1> <file2> ...\n");
    printf("        -b: byte count\n");
    printf("        -c: character count\n");
    printf("        -w: word count\n");
    printf("        -l: line count\n");
    printf("    cp <flags> <src file> <dest file1> <dest file2> ...\n");
    printf("        -o: overwrite file\n");
    return 0;
}
