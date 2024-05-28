//
// Created by connor on 2/12/24.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search(char *token, char *file_name, bool verbose)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        exit(1);
    }

    char line[1024]; // assuming max line length is 1024 chars
    int line_number = 1;

    if (verbose)
    {
        printf("%s:\n", file_name);
        printf("%s occurences:\n", token);
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *occurrence = strstr(line, token);
        while (occurrence != NULL)
        {
            if (verbose)
                printf("  line: %d, index: %d %s", line_number, occurrence - line + 1, line);
            else
                printf("%d %d %s", line_number, occurrence - line + 1, line);
            occurrence = strstr(occurrence + 1, token);
        }
        line_number++;
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Usage: search <flags> <token> <file1> <file2> ...\n");
    }
    else
    {
        int i = 2;
        char *flags = argv[1];
        int size = sizeof(flags);
        bool verbose = false;
        if (flags[0] == '-')
        {
            i++;
            for (int j = 1; j < size; j++)
            {
                switch (flags[j])
                {
                case 'v':
                    verbose = true;
                    break;
                default:
                    break;
                }
            }
        }

        char *token = argv[i - 1];
        for (; i < argc; i++)
            search(token, argv[i], verbose);
    }
    return 0;
}
