
#include <stdio.h>
#include <stdlib.h>

size_t getFileLength(FILE *fp)
{
    size_t filesize;
    fseek(fp, 0, SEEK_END);
    filesize = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return filesize;
}

char *readTextFile(FILE *fp, size_t count)
{
    char *buffer = (char *)malloc(sizeof(buffer) * count);
    fread(buffer, sizeof(char), count, fp);
    return buffer;
}

int main(int argc, const char **argv)
{
    if (argc == 2)
    {
        FILE *textFile;
        textFile = fopen(argv[1], "r");
        if (textFile != NULL)
        {
            size_t textFileLen = getFileLength(textFile);
            printf("%lu\n", textFileLen);
            char *data = readTextFile(textFile, textFileLen);
            for (size_t i = 0; i < textFileLen; i++)
            {
                if (data[i] != '\0')
                {
                    printf("%c", (unsigned char)data[i]);
                }
                else
                {
                    printf("\n");
                }
            }
            free(data);
            fclose(textFile);
        }
        return 0;
    }
    else
    {
        printf("Usage: <text file>\n");
    }
    return 1;
}
