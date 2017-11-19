#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  printf("Name: ");
  string s = get_string();
  int t = 0;

  for (int n = 0, l = strlen(s); n < l; n++)
  {
    if (s[n] == ' ')
    {
      t = n+1;
    }
    else
    {
      if(n == t)
      {
        printf("%c", toupper(s[n]));
      }
    }
  }
  printf("\n");
}
