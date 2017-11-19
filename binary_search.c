#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Enter 2 argumnets\n");
        exit(0);
    }

    int item = atoi(argv[1]);

    int numbers[] = {6, 7, 8, 10, 11, 14, 15, 17, 19, 22, 23, 25};

    int n = sizeof(numbers) / sizeof(int) , start = 0, middle = 0;
    int end = n-1;

    while(start <= end)
    {
        middle = (start + end) / 2;
        if(numbers[middle] == item)
        {
            printf("Found in array\n");
            exit(1);
        }
        else
        {
            if(item > numbers[middle])
                start = middle + 1;
            else
                end = middle - 1;
        }
    }
    if(start > end)
        printf("Not found in array\n");
}