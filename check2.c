#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

TokenType isINT_Constant(char ch,FILE *fptr,char *buff)
{
    if(isdigit(ch))
    {
        int i=0;
        buff[i++]=ch;
        if(buff[0]=='0')
        {
            ch=getc(fptr);
            if(checkBinary(ch,fptr,1,buff)==1)return INT_CONSTANT;
            else if(checkHex(ch,fptr,1,buff)==1)return INT_CONSTANT;
            else if(checkOct(ch,fptr,1,buff)==1)return INT_CONSTANT;
            else if(isalpha(ch))
            {
            buff[i++]=ch;
            while((ch=getc(fptr))!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return INT_CONSTANT;
            }
            else 
            {
                if (ch != EOF) {
                    fseek(fptr, -1, SEEK_CUR);
                }
                buff[i] = '\0';
                printf("%s\t\t\tInteger Constant\n", buff);
                return INT_CONSTANT;
            }
        }
        else
        {
            while((ch=getc(fptr))!=EOF)
            {
                if(isdigit(ch))
                buff[i++]=ch;
            else if(ch=='.')
            {
                if(checkFloat(ch,fptr,1,buff)==1)return INT_CONSTANT;
            }
            else if(isalpha(ch))
            {
            buff[i++]=ch;
            while((ch=getc(fptr))!=EOF)
            {
                if(!isalnum(ch))
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return INT_CONSTANT;
            }
            else
            {
            fseek(fptr,-1,SEEK_CUR);
            break;
            }  
            }
            buff[i]='\0';
            printf("%s\t\t\tInteger Constant\n",buff);
            return INT_CONSTANT;
        }
    }
    else return UNKNOWN;
}

int checkBinary(char ch,FILE *fptr,int i,char *buff)
{
if(ch=='b' || ch=='B')
{
    buff[i++]=ch;
    while((ch=getc(fptr))!=EOF)
    {
        if(isalpha(ch))
        {
            buff[i++]=ch;
            while(ch=getc(fptr)!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return 1;
        }
        else if(isdigit(ch))
        {
            if(ch=='0'||ch=='1')
            buff[i++]=ch;
            else
            {
                buff[i++]=ch;
                while((ch=getc(fptr))!=EOF)
                {
                    if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                    {
                        fseek(fptr,-1,SEEK_CUR);
                        break;
                    }
                    buff[i++]=ch;
                }
                buff[i]='\0';
                printf("%s\t\t\tError:Invalid integral constant\n",buff);
                return 1;
            }
        }
        else
        {
            fseek(fptr,-1,SEEK_CUR);
            break;
        }
    }
    buff[i]='\0';
    printf("%s\t\t\tInteger Constant(Binary)\n",buff);
    return 1;
}
else return 0;
}
int checkHex(char ch,FILE *fptr,int i,char *buff)
{
    if(ch=='x' || ch=='X')
    {
        buff[i++]=ch;
        while((ch=getc(fptr))!=EOF)
        {
            if(isxdigit(ch))
            buff[i++]=ch;
            else if(isalpha(ch))
            {
            buff[i++]=ch;
            while(ch=getc(fptr)!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return 1;
            }
            else
            {
            fseek(fptr,-1,SEEK_CUR);
            break;
            }
        }
        buff[i]='\0';
        printf("%s\t\t\tInteger Constant(HexaDecimal)\n",buff);
        return 1;
    }
    else return 0;
}
int checkOct(char ch,FILE *fptr,int i,char *buff)
{
    if(isdigit(ch))
    {
        buff[i++]=ch;
        while((ch=getc(fptr))!=EOF)
        {
            if(isdigit(ch))
            buff[i++]=ch;
            else if(isalpha(ch))
            {
            buff[i++]=ch;
            while(ch=getc(fptr)!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return 1;
            }
            else
            {
            fseek(fptr,-1,SEEK_CUR);
            break;
            }
        }
        buff[i]='\0';
        printf("%s\t\t\tInteger Constant(Octal)\n",buff);
        return 1;
    }
    else return 0;
}
int checkFloat(char ch,FILE *fptr,int i,char *buff)
{
    buff[i++]=ch;
    while((ch=getc(fptr))!=EOF)
    {
        if(isdigit(ch))
        buff[i++]=ch;
        else if(ch=='.')
        {
            buff[i++]=ch;
            while((ch=getc(fptr))!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return 1;
        }
        else if(ch=='f'||ch=='F'||ch=='l'||ch=='L')
        {
            buff[i++]=ch;
            ch=getc(fptr);
            if(isdigit(ch))
            {
            buff[i++]=ch;
            while((ch=getc(fptr))!=EOF)
            {
                if(ch==' '||ch=='\n'||ch=='\t'||ch==';'||ch==EOF)
                {
                    fseek(fptr,-1,SEEK_CUR);
                    break;
                }
                buff[i++]=ch;
            }
            buff[i]='\0';
            printf("%s\t\t\tError:Invalid integral constant\n",buff);
            return 1;
            }
            else
            {
                fseek(fptr,-1,SEEK_CUR);
                break;
            }
        }
        else
        {
            fseek(fptr,-1,SEEK_CUR);
            break;
        }
    }
    buff[i]='\0';
    printf("%s\t\t\tInteger Constant(Float)\n",buff);
    return 1;
}