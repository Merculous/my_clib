
#include <stdio.h>
#include <stdint.h>

#include "string_utils.h"

void printAllStringsFromCharBuffer(char *buffer, size_t bufferSize)
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

char *convertUInt32ToASCII(uint32_t value)
{
    size_t bufferLen = sizeof(value) + sizeof(char);
    char *buffer = (char *)malloc(sizeof(char) * bufferLen);
    memcpy(buffer, &value, bufferLen);
    buffer[bufferLen] = '\0';
    return buffer;
}