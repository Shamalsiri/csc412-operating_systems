#include <stdio.h>
#include <stdlib.h>	//	for malloc & calloc
#include <string.h>	//	for memcpy
#include <libgen.h>

//#include "imageIO_TGA.h"
#include "imageIO_TGA.h"

void rotateImage180(ImageStruct* image, ImageStruct* rotate);
void rotateLeft(ImageStruct* image, ImageStruct* rotate1);
void rotateRight(ImageStruct* image, ImageStruct* rotate2);

/*
* Copy arguments to variable
* Read the original image given
*/
int main(int argc, char* argv[])
{
  char *rotation = argv[1];
  char *inputPath = argv[2];
  char *outputPath = argv[3];
  int countL = 0;
  int countR = 0;
  ImageStruct image = readTGA(inputPath);

/*
* Create the file name of the new image to:
* ""<orignal file name> [rotated].tga"
*/
  char* fileName = basename(inputPath);
  char fName[strlen(fileName) - 3]; //-3 for tga
  for(int i =0; i < (strlen(fName)-1); i++)
  {
    fName[i]=fileName[i];
  }
  strcat(fName, " [rotated].tga");
  strcat(outputPath, fName);

/*
* Simplify the rotation argument
*
*/
  for(int i = 0 ; i < strlen(rotation); i++)
  {
    if(rotation[i] == 'L' || rotation[i] == 'l')
    {
      countL++;
    }
    else if(rotation[i] == 'R' || rotation[i] == 'r')
    {
      countR++;
    }
  }

  int result = countL - countR;

  if((result % 4) == 0)
  {
    writeTGA(outputPath, &image);
  }
  else if((result % 3 ) == 0)
  {
    if(result < 1)
    {
      ImageStruct rotate1 = newImage(image.height, image.width, RGBA32_RASTER, 1);
      rotateLeft(&image, &rotate1);
      writeTGA(outputPath, &rotate1);
      free(rotate1.raster);
    }
    else
    {
      printf("rotate right, Function not working\n");
    }
  }
  else if ((result % 2) == 0)
  {
    ImageStruct rotate = newImage(image.width, image.height, RGBA32_RASTER, 1);
    rotateImage180(&image, &rotate);
    writeTGA(outputPath, &rotate);
    free(rotate.raster);
  }
  else
  {
    if(result < 1)
    {
      printf("rotate right! Function not working\n");
    }
    else
    {
      ImageStruct rotate1 = newImage(image.height, image.width, RGBA32_RASTER, 1);
      rotateLeft(&image, &rotate1);
      writeTGA(outputPath, &rotate1);
      free(rotate1.raster);
    }
  }

  //ImageStruct rotate2 = newImage(image.height, image.width, RGBA32_RASTER, 1);
  //rotateRight(&image, &rotate2);
  //writeTGA("./check3.tga", &rotate2);
  //free(rotate2.raster);

  //writeTGA("./check.tga", &rotate);
  free(image.raster);

  return 0;
}

/*
* DOESN'T WORK
* Attempted to create a new picture that is rotated 90 degrees to the right by
* Copying the top left most pixel to the top right most pixel in the new image and
* second top left pixel below the top right most pixel in the new image
*/
void rotateRight(ImageStruct* image, ImageStruct* rotate)
{
  int* raster1 = (int*)(image->raster);
	int* raster2 = (int*)(rotate->raster);

  unsigned int rotateStartPos = ((rotate->width) * (rotate->height)) - rotate->width;
  for (unsigned int i = 0; i < image->height; i++)
  {
    unsigned int rotateCopyPosition = rotateStartPos;
    for(unsigned int j = 0; j < image->width; j++)
    {
      unsigned int currentPos = (image->width * i) + j;
      raster2[rotateCopyPosition] = raster1[currentPos];
      rotateCopyPosition = rotateCopyPosition + rotate->width;
    }
    if(rotateStartPos + 1 != 24)
    {
      rotateStartPos = rotateStartPos + 1;
    }

  }
}

/*
* Attempted to create a new picture that is rotated 90 degrees to the left by
* Copying the top left most pixel to the bottom left most pixel in the new image and
* Top right pixel at the top left most pixel in the new image
*/
void rotateLeft(ImageStruct* image, ImageStruct* rotate)
{
  int* raster1 = (int*)(image->raster);
	int* raster2 = (int*)(rotate->raster);

  unsigned int rotateStartPos = (rotate->width) - 1;

  for (unsigned int i = 0; i < image->height; i++)
  {
    unsigned int rotateCopyPosition = rotateStartPos;
    for(unsigned int j = 0; j < image->width; j++)
    {
      unsigned int currentPos = (image->width * i) + j;
      raster2[rotateCopyPosition] = raster1[currentPos];
      rotateCopyPosition = rotateCopyPosition + rotate->width;
    }
    rotateStartPos = rotateStartPos - 1;
  }
}

/*
* Following code is re-used. The orignal code can be found in the main.c file the professor
* presented when assigning the assignment to class
* rotating an image is the same as mirroring from the top 
*/
void rotateImage180(ImageStruct* image, ImageStruct* rotate)
{
	int* raster1 = (int*)(image->raster);
	int* raster2 = (int*)(rotate->raster);

	unsigned int effectiveWidth  = image->bytesPerRow / image->bytesPerPixel;

	for (unsigned int i=0, mirrorI=image->height-1; i<image->height; i++, mirrorI--)
	{
		for (unsigned int j=0; j<image->width; j++)
		{
  		raster2[i*effectiveWidth + j] = raster1[mirrorI*effectiveWidth + j];

		}
	}
}
