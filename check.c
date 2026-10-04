#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue","signed","unsigned","goto","auto","extern",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct","long","short","register","enum",
    "typedef","union","volatile"
};
static const char* operators1 = "+-*/%=!<>|&^";
static const char* operators2[] = {"++","--","<=",">=","==","!=","&&","||","+=","-+","/=","*=","%=","&=","^=","|=",">>","<<"};
static const char* specialCharacters = ",;{}()[]";

char stack[1000];

TokenType isOperator(char ch,FILE *fptr,char *buff)
{
    if((strchr(operators1,ch))!=NULL)
    {
            int j,i=0;
            buff[i++]=ch;int single=1;
            while((ch=getc(fptr))!=EOF)
            {
            if((strchr(operators1,ch))!=NULL)
            {
            single=0;
            buff[i++]=ch;
            }
            else
            {
            fseek(fptr,-1,SEEK_CUR);
            break;
            }
            }
            if(single)
            {
                printf("%c\t\t\tOperator\n",buff[0]);
                return OPERATOR;
            }
            buff[i]='\0';
            for(j=0;j<18;j++)
            {
                if(strcmp(buff,operators2[j])==0)
                break;
            }
            if(j<18)
            printf("%s\t\t\tOperator\n",buff);
            else
            printf("%s\t\t\tError:invalid operator\n",buff);
        return OPERATOR;
    }
    else
    return UNKNOWN;
}
TokenType isString(char ch,FILE *fptr,char *buff)
{
    if(ch=='"')
        {
            int i=0;buff[i++]=ch;
            while((ch=getc(fptr))!='"')
            {
                if(ch=='\n'||ch==EOF)
                {
                    buff[i++]='\0';
                    printf("%c%s\t\t\tError: missing \" character\n",ch,buff);
                    return STRING_LITERALS;
                }
            buff[i++]=ch;
            }
            buff[i]='"';
            buff[i+1]='\0';
            printf("%s\t\t\tString literal\n",buff);
            return STRING_LITERALS;
        }
        else
        return UNKNOWN;
}
TokenType isSpecial(char ch,int *s,FILE *fptr,char *buff)
{
    if(strchr(specialCharacters,ch)!=NULL)
        {
            if(ch=='[')stack[++*s]=']';
            if(ch=='(')stack[++*s]=')';
            if(ch=='{')stack[++*s]='}';
            if(ch==']'||ch==')'||ch=='}')
            {
                if((*s)!=-1 && stack[*s]==ch)
                (*s)--;
                else
                {
                printf("%c\t\t\tError:invalid order of brackets\n",ch);
                return SPECIAL_CHARACTER;
                }
            }
            printf("%c\t\t\tSpecial Character\n",ch);
            return SPECIAL_CHARACTER;
        }
        else
        return UNKNOWN;
}
TokenType isCHAR_Constant(char ch,FILE *fptr,char *buff)
{
    if(ch==39)
    {
        int i=0;
        buff[i++]=ch;
        while((ch=getc(fptr))!=EOF)
        {
            if(ch=='\n')
            {
                buff[i++]='\0';
                printf("%c%s\t\t\tError: missing ' character\n",ch,buff);
                return CHAR_CONSTANT;
            }
            else if(ch==39)
            {
                buff[i++]=ch;
                break;
            }
            buff[i++]=ch;
        }
        buff[i]='\0';
        if(strlen(buff)>4)
        {
            printf("%s\t\t\tError:invalid character constant\n",buff);
            return CHAR_CONSTANT;
        }
        if(strlen(buff)==4)
        {
            if(buff[1]=='\\')
            {
                if(buff[2]=='0'||buff[2]=='a'||buff[2]=='b'||buff[2]=='t'||buff[2]=='n'||buff[2]=='v'||buff[2]=='f'||buff[2]=='r')
                {
                    printf("%s\t\t\tcharacter constant\n",buff);
                    return CHAR_CONSTANT;
                }
                else
                {
                    printf("%s\t\t\tInvalid character constant\n",buff);
                    return CHAR_CONSTANT;
                }
            }
            else
            {
              printf("%s\t\t\tInvalid character constant\n",buff);
              return CHAR_CONSTANT;  
            }
        }
        else if(strlen(buff)==3)
        {
            printf("%s\t\t\tcharacter constant\n",buff);
            return CHAR_CONSTANT;
        }
        else
        {
            printf("%s\t\t\tInvalid character constant\n",buff);
            return CHAR_CONSTANT;
        }
    }
    else
    return UNKNOWN;
}
TokenType isKeyword(char ch,FILE *fptr,char *buff)
{
    if(isalpha(ch))
    {
        int start=ftell(fptr);
        int i=0,j;
        buff[i++]=ch;
        while((ch=getc(fptr))!=EOF)
        {
            if(isalnum(ch))
            buff[i++]=ch;
            else
            {
                fseek(fptr,-1,SEEK_CUR);
                break;
            }
        }
        buff[i]='\0';
        for(j=0;j<32;j++)
        {
            if(strcmp(keywords[j],buff)==0)
            break;
        }
        if(j<32)
        {
        printf("%s\t\t\tKeyword\n",buff);
        return KEYWORD;
        }
        else
        {
         fseek(fptr,start,SEEK_SET);   
        return UNKNOWN;
        }
    }
    else
    return UNKNOWN;
}