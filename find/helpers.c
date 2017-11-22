/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(n < 1)
    {
        return false;
    }
    int start = 0, end = 0, middle;
    while(start <= end)
    {
        middle = (start + end) / 2;
        if(values[middle] == value)
        {
            return true;
            exit(1);
        }
        else
        {
            if(item > values[middle])
                start = middle + 1;
            else
                end = middle - 1;
        }
    }
    if(start > end)
        return false;

}

/**
 * Sorts array of n values.
 */
void swap(int *x, int *y)
 {
   int temp = *x;
   *x = *y;
   *y = temp;
 }
 
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    int i, j;
    for(i = 0; i < n-1; i++)
    {
      for(int j = 0; j < n-1 - i; j++)
        if(array[j] > array[j+1])
          swap(&array[j], &array[j+1]);
    }
    return 0;
}
