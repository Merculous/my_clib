
#include <io_utils.h>

uint32_t getSizeFromFileStream(FILE *stream)
{
    uint32_t size;
    fseek(stream, 0, SEEK_END);
    size = (uint32_t)ftell(stream);
    fseek(stream, 0, SEEK_SET);
    return size;
}

int8_t *readDataFromFileStream(FILE *stream)
{
    uint32_t streamSize = getSizeFromFileStream(stream);
    int8_t *buffer = (int8_t *)malloc(sizeof(*buffer) * streamSize);
    fread(buffer, sizeof(int8_t), streamSize, stream);
    return buffer;
}