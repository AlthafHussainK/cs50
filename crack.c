#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define _XOPEN_SOURCE

char *crypt(const char *key, const char *salt);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        exit(0);
    }

    char key4[5], key3[4], key2[3];
    char salt[2];

    strncpy(salt,argv[1],2);

    char alphabets[52];
    for(int i = 0, ln=65; i < 52; i++)
    {
        if(ln == 91)
            ln = 97;
        alphabets[i] = ln;
        ln++;
    }

    int n = 52;

    //key 2
    for(int i = 0; i < n; i++)
    {
        key2[0] = alphabets[i];
        for(int j = 0; j < n; j++)
        {
            key2[1] = alphabets[j];
            key2[2] = '\0';

            if(strcmp(argv[1], crypt(key2, salt)) == 0)
            {
                printf("%s\n", key2);
                exit(1);
            }
        }
    }

    //key 3
    for(int i = 0; i < n; i++)
    {
        key3[0] = alphabets[i];
        for(int j = 0; j < n; j++)
        {
            key3[1] = alphabets[j];
            for(int k = 0; k < n; k++)
            {
                key3[2] = alphabets[k];
                key3[3] = '\0';

                if(strcmp(argv[1], crypt(key3, salt)) == 0)
                {
                    printf("%s\n", key3);
                    exit(1);
                }
            }
        }
    }

    //key 4

    for(int i = 0; i < n; i++)
    {
        key4[0] = alphabets[i];
        for(int j = 0; j < n; j++)
        {
            key4[1] = alphabets[j];
            for(int k = 0; k < n; k++)
            {
                key4[2] = alphabets[k];
                for(int l = 0; l < n; l++)
                {
                    key4[3] = alphabets[l];
                    key4[4] = '\0';

                    if(strcmp(argv[1], crypt(key4, salt)) == 0)
                    {
                        printf("%s\n", key4);
                        exit(1);
                    }

                }
            }
        }
    }
}