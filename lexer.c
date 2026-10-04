#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

/*
    Keywords, identifiers, char constant, integral constants, float constant, operators, special char, string literal
*/
void get_token(char *str,char *buff)
{
    FILE *fptr=fopen(str,"r");
    if(fptr==NULL)
    {
        printf("error opening file\n");
        return;
    }
    char ch;
    int s=-1;
    while((ch=getc(fptr))!=EOF)
    {
        int i=0;
        if(isOperator(ch,fptr,buff)==OPERATOR)continue;
        else if(isString(ch,fptr,buff)==STRING_LITERALS)continue;
        else if(isSpecial(ch,&s,fptr,buff)==SPECIAL_CHARACTER)continue;
        else if(isINT_Constant(ch,fptr,buff)==INT_CONSTANT)continue;
        else if(isCHAR_Constant(ch,fptr,buff)==CHAR_CONSTANT)continue;
        else if(isKeyword(ch,fptr,buff)==KEYWORD)continue;
        else if(isalpha(ch)||ch=='_')
        {
            buff[i++]=ch;
            while((ch=getc(fptr))!=EOF)
            {
                if(isalnum(ch)||ch=='_')
                buff[i++]=ch;
                else
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
            }
            buff[i]='\0';
            printf("%s\t\t\tIdentifier\n",buff);
        }
        else if(ch!=' '&&ch!='\n'&&ch!='\t'&&ch!='\r')
        {
            printf("%c\t\t\tError: stray character\n",ch);
        }
    }
    if(s!=-1)
    {
        printf("Error brackets order dont match\n");
    }
}





