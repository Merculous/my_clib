
#include "io_utils.h"

size_t getSizeFromFileStream(FILE *stream)
{
    size_t size;
    fseek(stream, 0L, SEEK_END);
    size = (size_t)ftell(stream);
    fseek(stream, 0L, SEEK_SET);
    return size;
}

char *readDataFromFileStream(FILE *stream)
{
    size_t filesize = getSizeFromFileStream(stream);
    char *buffer = (char *)malloc(sizeof(char) * filesize);
    fread(buffer, sizeof(char), filesize, stream);
    return buffer;
}