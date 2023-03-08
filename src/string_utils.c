
#include "string_utils.h"

void printAllStringsFromCharBuffer(unsigned char *buffer, uint32_t bufferSize)
{
    for (uint32_t i = 0; i < bufferSize; i++)
    {
        if (buffer[i] != '\0')
        {
            printf("%c", buffer[i]);
        }
        else
        {
            printf("\n");
        }
    }
}

const unsigned char *convertUInt32ToASCII(const uint32_t value)
{
    static unsigned char buffer[sizeof(value) + sizeof(char)];
    memcpy(buffer, &value, sizeof(value));
    buffer[sizeof(value) + sizeof(char)] = '\0';
    static const unsigned char *bufferPointer = (const unsigned char *)buffer;
    return bufferPointer;
}