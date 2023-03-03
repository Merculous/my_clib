
#include <stdlib.h>

#include "img3.h"

int main(int argc, const char **argv)
{
    if (argc == 2)
    {
        FILE *textFile;
        textFile = fopen(argv[1], "r");
        if (textFile != NULL)
        {
            parseImg3(textFile);
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
        printf("Usage: <img3>\n");
        return 1;
    }
}