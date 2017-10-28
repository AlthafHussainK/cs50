#include<stdio.h>
#include<cs50.h>

int main(void)
{
   printf("Minutes: ");
   int n = get_int();
   int bottles;
   bottles = n * 12;

   printf("Bottles: %i\n", bottles);
}