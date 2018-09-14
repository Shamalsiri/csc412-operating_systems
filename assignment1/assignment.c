#include<stdio.h>
#include<stdlib.h>
int gcd(int,int);

int main(int argc, char *argv[])
{
  int param1;
  int param2;

  if (argc == 1)
  {
    printf("Proper usage: prog m [n]\n");
  }
  else if (argc == 2)
  {
    param1 = atoi(argv[1]);

    if (param1 < 0)
    {
      printf("prog’s argument is not a strictly positive integer.\n");
    }
    else
    {
      printf("The list of divisors of %d is: ", param1);
      for(int i = 1; i <= param1; i++)
      {
        if(param1 % i == 0)
        {
          printf("%d", i);
          if(i != param1)
          {
            printf(", ");
          }
          else
          {
            printf(".");
          }
        }

      }
      printf("\n");
    }
  }
  else if (argc == 3)
  {
    param1 = atoi(argv[1]);
    param2 = atoi(argv[2]);
    if(param1 < 0)
    {
      printf("prog’s first argument is not a strictly positive integer.\n");
    }
    else if(param2 < 0)
    {
      printf("prog’s second argument is not a strictly positive integer.\n");
    }
    else
    {
      printf("The gcd of %d and %d is ", param1, param2);
      int denominator = gcd(param1, param2);
      printf("%d.\n", denominator);
    }
  }
  else
  {
    printf("Proper usage: prog m [n]\n");
  }

  return 0;
}

int gcd(int p1, int p2)
{
  if(p1 == 0 || p2 == 0)
  {
    return 0;
  }
  else if(p1 == p2)
  {
    return p2;
  }
  else if(p1 > p2)
  {
    return gcd(p1 - p2, p2);
  }
  else
  {
    return gcd(p1, p2 - p1);
  }
}
