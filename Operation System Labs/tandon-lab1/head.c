#include "types.h"
#include "stat.h"
#include "user.h"
#define STDIN "_stdin"

char buf[512];


void print_help()
{
    printf(1, "Usage: head [OPTION]... [FILE]...\nPrint the first 10 lines of each FILE to standard output.\nWith more than one FILE, precede each with a header giving the filename.\nPossible arguments are:\n\n\t-NUM\t\tprint the first NUM lines of each file;\n");
    exit();
}

void print_error(uint err, char* s)
{
    switch(err)
    {
    case(0):
        printf(2, "head: invalid option %s\nTry 'head --help' for more information\n", s);
        break;
    case(1):
        printf(2,"head: invalid number of lines: %s\n", s);
        break;
    case(2):
        printf(2, "head: cannot open '%s' for reading: No such file or directory\n", s);
        break;
    default:
        printf(2, "head: error\n");
    }
    exit();
}

void head(int fd, int n)
{
    int i, r, l=0;


    while((r = read(fd, buf, sizeof(buf))) > 0 && l < n)
    {
        for(i = 0; i < r && l < n; i++)
        {
            printf(1, "%c", buf[i]);
            if(buf[i] == '\n')
                l++;
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    int i, n = 10;
    char *c;
    short flag = 0;

    for(i = 1; i < argc; i++)
    {
        strcpy(buf, argv[i]);
        if(buf[0]=='-')
        {
            if(buf[1] == '-')
            {
                c = buf;
                c += 2;
                if(strcmp(c, "help") == 0)
                    print_help();
                else
                    print_error(0, argv[i]);
            }
            else
            {
                c = buf
                c += 1
                if(atoi(c) == 0)
                    print_error(1, c);
                n = atoi(c);
            }
        }
        else
        {
            flag = 1;
            if((fd = open(argv[i], 0)) < 0){
                print_error(2, argv[i]);
                exit();
            }
            head(fd, n);
            if(i+1 < argc)
                printf(1, "\n");
        }
    }
    if(flag == 0)
    {
        head(0, n);
        exit();
    }
    exit();
}
