#include<stdio.h>

int main(void)
{
    char alphabets[52];

    for(int i = 0, ln=65; i < 52; i++)
    {
        if(ln == 91)
            ln = 97;
        alphabets[i] = ln;
        ln++;
    }
    
    printf("%s\n",alphabets);
}