
#include <img3.h>

int main(int argc, const char **argv)
{
    if (argc == 2)
    {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (fp != NULL)
        {
            parseImg3(fp);
            fclose(fp);
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