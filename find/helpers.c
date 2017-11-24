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
    // searching algorithm
    if(n < 1)
    {
        return false;
    }

    //int t = 0;
    int start = 0, end = n-1, middle;
    while(start <= end)
    {

        middle = (start + end) / 2;
        if(values[middle] == value)
        {
            return true;
            exit(0);
        }
        else if(value > values[middle])
                start = middle + 1;
        else
                end = middle - 1;

    }
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
    // sorting algorithm
    int i;
    for(i = 0; i < n-1; i++)
    {
      for(int j = 0; j < n-1 - i; j++)
        if(values[j] > values[j+1])
          swap(&values[j], &values[j+1]);
    }

}
