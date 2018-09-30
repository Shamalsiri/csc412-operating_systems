// Libraries included
#include<stdio.h>
#include<stdlib.h>

// Define the helper method/function
int gcd(int,int);

/*
* Main funciton,
* It has two parameters argc of type int and argv a pointer to a char array
* If there is one argument it will prints a list of divisors
* If there is two arguments it will prints the greatest common denominator
*/
int main(int argc, char *argv[])
{
  int param1;
  int param2;
  char *a

  if (argc == 1) // If no arguments, prints error message
  {
    printf("Proper usage: %s m [n]\n",argv[0]);
  }
  else if (argc == 2) //If there is 1 argument
  {
    param1 = atoi(argv[1]); // Convert char[] to an int

    if (param1 < 0) // If the int is a negative number, prints error message
    {
      printf("prog’s argument is not a strictly positive integer.\n");
    }
    // If the int is 0, print the divisor as 0.
    // Any words (non- numbers) would be considered 0 here
    else if(param1 == 0)
    {
      printf("The list of divisors of %d is: %d\n", param1, param1);
    }
    else // If the int is a positive number, list of divisors will be printed
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
  else if (argc == 3) // If there is 2 arguments
  {
    param1 = atoi(argv[1]); // convert argv[1] to int
    param2 = atoi(argv[2]); // convert argv[2] to int

    if(param1 < 0) // If the first argument is negative, prints error message
    {
      printf("prog’s first argument is not a strictly positive integer.\n");
    }
    // If the second argument is negative, prints error message
    else if(param2 < 0)
    {
      printf("prog’s second argument is not a strictly positive integer.\n");
    }
    else // If both arguments are postive, GCD is calculated
    {
      printf("The gcd of %d and %d is ", param1, param2);
      // Call the helper method that calculates the gcd
      int gcdenominator = gcd(param1, param2);
      printf("%d.\n", gcdenominator);
    }
  }
  else // If there is more than 2 arguments, prints error message
  {
    printf("Proper usage: prog m [n]\n");
  }

  return 0;
}

/*
* Helper Method (Recursive)- takes 2 ints as parameters
* Calculate the Greated Common Denominator
* Returns the gcd of type int
*/
int gcd(int p1, int p2)
{
  if(p1 == 0 || p2 == 0) // if one or both parameters are 0
  {
    return 0;
  }
  else if(p1 == p2) // if the paramters are the same
  {
    return p2;
  }
  else if(p1 > p2) // If the first parameter is larger than the second
  {
    return gcd(p1 - p2, p2); // recursive call to the method
  }
  else // If the second argument is larger than the first
  {
    return gcd(p1, p2 - p1); //recursive call to the method
  }
}
