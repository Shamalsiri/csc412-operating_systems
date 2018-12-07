#include <stdio.h>
#include <stdlib.h>	//	for malloc & calloc
#include <string.h>	//	for memcpy
#include <libgen.h>

#include "imageIO_TGA.h"

int main(int argc, char * argv[])
{

  /*
  * Check to see if there the correct number of arguments is entered
  * Store the arguments in local variable and cast argunments that should be int
  */
  if (argc == 7)
  {
    char * inputPath = argv[1];
    char * outputPath = argv[2];
    int xCoord = atoi(argv[3]);
    int yCoord = atoi(argv[4]);
    int width = atoi(argv[5]);
    int height = atoi(argv[6]);

    ImageStruct image = readTGA(inputPath);

    /*
    *  Use the basename function of the libgen.h file to get he file fName
    *  Edit the file name of the to include " [cropped].tga" at the end of the file name
    * Append the new file name to the output path
    */
    char* fileName = basename(inputPath);
    char fName[strlen(fileName) - 3]; //-3 for tga
    for(int i =0; i < (strlen(fName)-1); i++)
    {
      fName[i]=fileName[i];
    }
    strcat(fName, " [cropped].tga");
    strcat(outputPath, fName);

    /*
    * Check for out of bound errors:
    * including invalid X and Y coordinate
    * out of bound width and height inputs
    */
    if (xCoord < 0 || xCoord > image.width)
    {
      fprintf(stderr,"X Coordinate Out of Bound: X coordinate must be between 0"
      " and orignal image width: %d\n", image.width);
    }
    else if (yCoord < 0 || yCoord > image.height)
    {
      fprintf(stderr,"Y Coordinate Out of Bound: Y coordinate must be between 0"
      " and orignal image Height: %d\n", image.height);
    }
    else if ((xCoord + width) > image.width)
    {
      fprintf(stderr,"Out of Bound: X coordinate + width cannot exceed orignial"
      " orginal image width: %d\n", image.width);
    }
    else if((yCoord + height > image. height))
    {
      fprintf(stderr,"Out of Bound: Y coordinate + height cannot exceed orignial"
      " orginal image height: %d\n", image.height);
    }
    /*
    * Create a blank/black with the proper crop dimensions
    * Copy individual pixels within the crop region from the orignal picture
    * to the blank crop image
    * write the crop file to the output path
    */
    else
    {
      ImageStruct crop = newImage(width, height, RGBA32_RASTER, 1);
      ImageStruct* copy = &image;
      ImageStruct* copy2 = &crop;
      int *raster1 = (int*)(copy->raster);
      int *raster2 = (int*)(copy2->raster);
      int startPos = (image.width * yCoord) + xCoord;
      int index = 0;
      for(int i = 0 ; i < height; i++ )
      {
        for(int pos = startPos; pos < (startPos + width); pos++ )
        {
          raster2[index] = raster1[pos];
          index++;
        }
        startPos = startPos + image.width;
      }
      writeTGA(outputPath, &crop);
    }

  }
  /*
  * If invalid number of arguments is entered,
  * Print a error message with the proper form.
  */
  else
  {
    fprintf(stderr,"Invalid format: %s <PathToTGAFile> <X-coordinate>"
    " <Y-coordinate> <Width> <Height> <PathToOutputDirectory>\n", argv[0]);
  }

  return 0;
}
