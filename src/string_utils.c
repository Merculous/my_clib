
#include <string_utils.h>

const unsigned char *convertUInt32ToASCII(const uint32_t value)
{
    static unsigned char buffer[sizeof(char) * sizeof(value) + sizeof(char)];
    memcpy(buffer, &value, sizeof(value));
    buffer[sizeof(char) * sizeof(value)] = '\0';
    static const unsigned char *bufferPointer = (const unsigned char *)buffer;
    return bufferPointer;
}