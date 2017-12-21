#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int num;
    struct node *next;
}
node;

void print(node *n)
{
    while( n != NULL)
    {
        printf("%d\n", n -> num);
        n = n -> next;
    }
}

int main(void)
{
    node *head = malloc(sizeof(node));
    node *sec = malloc(sizeof(node));
    node *third = malloc(sizeof(node));

    head -> num = 10;
    head -> next = sec;

    sec -> num = 20;
    sec -> next = third;

    third -> num = 30;
    third -> next = NULL;

    print(head);

    free(head);
    free(sec);
    free(third);

    return 0;
}
