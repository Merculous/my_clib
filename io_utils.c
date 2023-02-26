
#include <stdlib.h>

#include "io_utils.h"

size_t getSizeFromFileStream(FILE *stream)
{
    size_t size;
    fseek(stream, 0L, SEEK_END);
    size = (size_t)ftell(stream);
    fseek(stream, 0L, SEEK_SET);
    return size;
}

char *readTextFromFileStream(FILE *stream)
{
    size_t filesize = getSizeFromFileStream(stream);
    char *buffer = (char *)malloc(sizeof(char) * filesize);
    fread(buffer, sizeof(char), filesize, stream);
    return buffer;
}

void printAllStringsFromBuffer(char *buffer, size_t bufferSize)
{
    for (size_t i = 0; i < bufferSize; i++)
    {
        if (buffer[i] != '\0')
        {
            printf("%c", (unsigned char)buffer[i]);
        }
        else
        {
            printf("\n");
        }
    }
}