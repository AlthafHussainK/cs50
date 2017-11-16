#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int u_a[26], l_a[26];
//int key = 25;


//get key from command-line argument
int main(int argc, string argv[])
{

    if(argc > 2 || argc == 1)
    {
        printf("Usage: ./caesar k\n");
        exit(1);

    }
    int key;
//turn key into integer
    key = atoi(argv[1]);


//alphabetical index
    for(int i = 0, n = 65; i < 26; i++)
    {
        u_a[i] = n;
        n++;
    }
    for(int i = 0, n = 97; i < 26; i++)
    {
        l_a[i] = n;
        n++;
    }

//prompt for plain text
    printf("plaintext: ");
    string p = get_string();

//store length of the input
    int len;
    len = strlen(p);

//declare output array
    int cipher_text[len];

    int c,f,u,l;

//iterate over plain text
    for(int i = 0; i < len; i++)
    {
        c = 0, f = 0;
        if(isupper(p[i]))
        {
            c = p[i];

            int mod, m;
            u = c;
            m = u % 65 + key;
            if(m > 25)
            {
                 mod = m % 26;
            }
            else
                mod = m;

            f = mod;

            cipher_text[i] = u_a[f];
        }

        else if(islower(p[i]))
        {
            c = p[i];

            int mod, m;
            l = c;
            m = l % 97 + key;
            if(m > 25)
            {
                 mod = m % 26;
            }
            else
                mod = m;

            f = mod;

            cipher_text[i] = l_a[f];
        }

        else
            cipher_text[i] = p[i];
    }


    printf("ciphertext: ");

    for(int i = 0; i < len; i++)
    {
        printf("%c", cipher_text[i]);
    }

printf("\n");
}

