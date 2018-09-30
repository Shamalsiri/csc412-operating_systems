#include<stdio.h>
#include<stdlib.h>

int main(int argv, char *argc[])
{
  char *s = argc[0];
  char *sub;
  int length = sizeof(s) / sizeof(*char);

  printf("%c\n", s[0]);
  printf("%d\n",length);

  for(int i =0; i< length; i++)
  {
    printf("%c\n",s[i]);
  }
  return 0;
}
