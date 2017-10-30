#include<stdio.h>


int main(void)
{
    int h;
//Taking input from user
    do
    {
        h = 0;
        printf("Height: ");
        scanf("%d", &h);
    }
    while (h < 0 || h > 23); //checks the height is acceptable or not

//prints a double half-pyramid
    for (int i = 0; i < h; i++)
    {
        for (int m = h; m > i + 1; m--)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf(" ");
        for (int j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                printf(" ");
            }
            printf("#");
        }

        printf("\n");
    }

}