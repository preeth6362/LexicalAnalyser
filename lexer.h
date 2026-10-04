#ifndef LEXER_H
#define LEXER_H
#include<stdio.h>

#define MAX_KEYWORDS 32

typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CHAR_CONSTANT,
    INT_CONSTANT,
    STRING_LITERALS,
    UNKNOWN
} TokenType;

void get_token(char *str,char *buff);
TokenType isOperator(char ch,FILE *fptr,char *buff);
TokenType isString(char ch,FILE *fptr,char *buff);
TokenType isSpecial(char ch,int *s,FILE *fptr,char *buff);
TokenType isCHAR_Constant(char ch,FILE *fptr,char *buff);
TokenType isKeyword(char ch,FILE *fptr,char *buff);
TokenType isINT_Constant(char ch,FILE *fptr,char *buff);
int checkBinary(char ch,FILE *fptr,int i,char *buff);
int checkHex(char ch,FILE *fptr,int i,char *buff);
int checkOct(char ch,FILE *fptr,int i,char *buff);
int checkFloat(char ch,FILE *fptr,int i,char *buff);

#endif
