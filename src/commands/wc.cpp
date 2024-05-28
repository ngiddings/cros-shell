//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
#include <stdlib.h>

void wc(char *file_name, bool show_chars, bool show_bytes, bool show_words, bool show_lines)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        exit(1);
    }

    int lines = 1;
    int words = 0;
    int characters = 0;
    int bytes = 0;

    if (show_chars || show_words || show_lines)
    {
        int in_word = 0;
        int ch = 0;

        while ((ch = fgetc(file)) != EOF)
        {
            characters++;

            if (ch == '\n')
            {
                lines++;
            }

            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f')
            {
                in_word = 0;
            }
            else if (in_word == 0)
            {
                in_word = 1;
                words++;
            }
        }
    }

    if (show_bytes)
    {
        if (fseek(file, 0, SEEK_END) != 0)
        {
            fprintf(stderr, "Error reading file: %s\n", file_name);
            exit(1);
        }

        bytes = ftell(file);
        if (bytes == -1)
        {
            fprintf(stderr, "Error reading file: %s\n", file_name);
            exit(1);
        }
    }

    fclose(file);

    printf("%s:\n", file_name);
    if (show_bytes)
        printf("    bytes: %d\n", bytes);
    if (show_chars)
        printf("    characters: %d\n", characters);
    if (show_words)
        printf("    words: %d\n", words);
    if (show_lines)
        printf("    lines: %d\n", lines);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("Usage: wc <flags> <file1> <file2> ...\n");
    }
    else
    {
        int i = 1;
        char *flags = argv[1];
        int size = sizeof(flags);
        bool show_chars = false;
        bool show_bytes = false;
        bool show_words = false;
        bool show_lines = false;
        if (flags[0] == '-')
        {
            i++;
            for (int j = 1; j < size; j++)
            {
                switch (flags[j])
                {
                case 'c':
                    show_chars = true;
                    break;
                case 'b':
                    show_bytes = true;
                    break;
                case 'w':
                    show_words = true;
                    break;
                case 'l':
                    show_lines = true;
                    break;
                default:
                    break;
                }
            }
        }

        for (; i < argc; i++)
        {
            if (!show_chars && !show_bytes && !show_words && !show_lines)
                wc(argv[i], show_chars, show_bytes, true, show_lines);
            else
                wc(argv[i], show_chars, show_bytes, show_words, show_lines);
        }
    }
    return 0;
}
