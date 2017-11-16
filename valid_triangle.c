#include<stdio.h>
#include<cs50.h>

bool valid_triangle(float a, float b, float c);

int main()
{
    float a, b, c;
    scanf("%f%f%f", &a, &b,&c);
    int v = valid_triangle(a,b,c);
    printf("%d\n", v);

}

bool valid_triangle(float a, float b, float c)
{
    if(a <= 0 || b <= 0 || c <= 0)
        return false;

    if((a + b <= c) || (b + c <= a) || (a + c <= b))
        return false;

    else
        return true;
}