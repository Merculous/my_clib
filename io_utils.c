
#include "io_utils.h"

uint32_t getSizeFromFileStream(FILE *stream)
{
    uint32_t size;
    fseek(stream, 0, SEEK_END);
    size = (uint32_t)ftell(stream);
    fseek(stream, 0, SEEK_SET);
    return size;
}

char *readDataFromFileStream(FILE *stream)
{
    uint32_t streamSize = getSizeFromFileStream(stream);
    char *buffer = (char *)malloc(sizeof(char) * streamSize);
    fread(buffer, sizeof(char), streamSize, stream);
    return buffer;
}