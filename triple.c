#include<stdio.h>

int triple(int a);

int main(void)
{
    int foo = 4;
    //foo = triple(foo);
    printf("%d\n", triple(foo));
}

int triple(int a)
{
    return a *= 3;
}