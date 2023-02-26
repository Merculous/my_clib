
#include <stdio.h>
#include <stdlib.h>

#include "io_utils.h"

int main(int argc, const char **argv)
{
    if (argc == 2)
    {
        FILE *textFile;
        textFile = fopen(argv[1], "r");
        if (textFile != NULL)
        {
            size_t textFileSize = getSizeFromFileStream(textFile);
            char *textFileData = readTextFromFileStream(textFile);
            printAllStringsFromBuffer(textFileData, textFileSize);
            free(textFileData);
            fclose(textFile);
            return 0;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        printf("Usage: <text file>\n");
        return 1;
    }
}