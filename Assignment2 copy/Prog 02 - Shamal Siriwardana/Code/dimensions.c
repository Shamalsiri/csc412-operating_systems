#include <stdio.h>
#include <stdlib.h>	//	for malloc & calloc
#include <string.h>	//	for memcpy

//#include "imageIO_TGA.h"
#include "imageIO_TGA.h"

/*
* This program takes a tga file with a modifier to dispay specific dimension of the file
*/
int main(int argc, char *argv[])
{
  char * inputPath;
  char * modifiers;
  ImageStruct image;
  int isSame; // Might not need

  /*
  * Prints a error message if the number of arguments is 1
  */
  if (argc == 1)
  {
    fprintf(stderr, "Invalid format: %s <modifiers> <PathToTGAFile>\n", argv[0]);
  }
  else if (argc == 2)
  {
    /*
    * Split the argument to the modifier and the path
    */

    inputPath = argv[1];
    if(inputPath[0] == '-')
    {
      int i = 1;
      char modi[4];
      modi[0] = '-';
      while(inputPath[i] == 'v' || inputPath[i] == 'h' || inputPath[i] == 'w')
      {
        modi[i] = inputPath[i];
        i++;

      }
      modi[i] = '\0';
      char input[strlen(inputPath) - strlen(modi)];
      memcpy(input, &inputPath[strlen(modi)], strlen(inputPath));
      input[strlen(inputPath) - strlen(modi)] ='\0';

      if(!strcmp(modi,"-"))
      {
        fprintf(stderr,"Invalid modifier\n");
        return 0;
      }

      image = readTGA(input);

      /*
      * Check for the proper modifer and perform it's function
      */

      if(!strcmp(modi,"-v"))
      {
        printf("width:%d, height: %d\n", image.width, image.height);
      }
      else if (!strcmp(modi,"-w"))
      {
        printf("%d\n", image.width);
      }
      else if(!strcmp(modi,"-h"))
      {
        printf("%d\n", image.height);
      }
      else if(!strcmp(modi,"-vh") || !strcmp(modi,"-hv"))
      {
        printf("height: %d\n", image.height);
      }
      else if(!strcmp(modi,"-vw") || !strcmp(modi,"-wv"))
      {
        printf("width: %d\n", image.width);
      }

    }
    else
    {
      inputPath = argv[1];
      image = readTGA(inputPath);
      printf("%d %d\n", image.width, image.height);
    }
  }
  /*
  * For 2 arguments, take the modifer and
  * check for the proper function and perform it
  */
  else if (argc ==3)
  {
    modifiers = argv[1];
    inputPath = argv[2];

    image = readTGA(inputPath);

    if (!strcmp(modifiers,"-v"))
    {
      printf("width:%d, height: %d\n", image.width, image.height);
    }
    else if (!strcmp(modifiers,"-w"))
    {
      printf("%d\n", image.width);
    }
    else if (!strcmp(modifiers,"-h"))
    {
      printf ("%d\n", image.height);
    }
    else if (!strcmp(modifiers,"-vh") || !strcmp(modifiers,"-hv"))
    {
      printf("height: %d\n", image.height);
    }
    else if (!strcmp(modifiers,"-vw") || !strcmp(modifiers,"-wv"))
    {
      printf("width: %d\n", image.width);
    }
    else
    {
      fprintf(stderr,"Invalid modifier\n");
      return 0;
    }

  }
  else
  {
    fprintf(stderr, "Invalid format: %s <modifiers> <PathToTGAFile>\n", argv[0]);
  }
  return 0;
}
