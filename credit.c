#include<stdio.h>
#include<stdlib.h>
#include<cs50.h>

int main(void)
{
//Stage 1
    //Input
    long long ccn;
    printf("Number: ");
    //scanf("%lld", &ccn);
    ccn = get_long_long();

    //digit count
    long long copy = ccn;
    int count = 0;
    while(copy > 0)
    {
      copy /= 10;
      count++;
    }

    //validity check
    if(count != 13 && count != 15 && count != 16)
    {
      printf("INVALID\n");
      exit(0);
    }

//stage 2
    int ccna[count];
    copy = ccn;
    //digit to array
    for(int i = count-1; i >= 0; i--)
    {
      ccna[i] = copy % 10;
      copy /= 10;
    }

    //multiplication
    int sum = 0;
    for(int i = 1; i < count; i += 2)
    {
      int c;
      c = ccna[i] * 2;
      if(c > 9)
      {
        int s = 0;
        s = s + c % 10;
        c = c / 10;
        s = s + c % 10;
        sum = sum + s;
      }
      else
        sum = sum + c;
    }
    //sum of digits
    for(int i = 0; i < count; i += 2)
    {
      sum = sum + ccna[i];
    }

//Stage 3
    //Validity check
      if(sum % 10 == 0 && (ccna[0] == 3 && (ccna[1] == 4 || ccna[1] == 7)))
      {
        printf("AMEX\n");
      }

      else if (ccna[0] == 4) {
        printf("VISA\n");
      }
      else if(ccna[0] == 5 && (ccna[1] == 1 || ccna[1] == 2 || ccna[1] == 3 || ccna[1] == 4 || ccna[1] == 5))
      {
        printf("MASTERCARD\n");
      }
      else
      {
        printf("INVALID\n");
      }

}
