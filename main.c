#include <stdio.h>
#include<string.h>
#include "lexer.h"

char buff[200];
int main(int argc, char *argv[]) {
    if(argc!=2)
    {
        printf("Invalid number of arguments\n");
        return 1;
    }
    if(strstr(argv[1],".c")==NULL)
    {
        printf("Invalid source file type please enter .c file\n");
        return 1;
    }
    get_token(argv[1],buff);
    return 0;
}
