#!/bin/bash

args=("$@")
elements=${#args[@]}

err1="Invalid Argument list."
err2="Proper usage: myScript <PathToDirectoryWithValid-TGA-Files> <OutputDirectory>"
if [ $elements -lt 2 ]; then # If there is no arguments or 1 argument
  echo $err1 # prints error message
  echo $err2
else
  gcc -ICode\ Handout/ dimensions.c Code\ Handout/imageIO_TGA.c Code\ Handout/rasterImage.c -o dimensions
  gcc -ICode\ Handout/ crop.c Code\ Handout/imageIO_TGA.c Code\ Handout/rasterImage.c -o crop
  gcc -ICode\ Handout/ rotate.c Code\ Handout/imageIO_TGA.c Code\ Handout/rasterImage.c -o rotate

  inputPath=$1
  outputPath=$2

  for file in $inputPath/*; do
    ./dimensions -v "$inputPath$(basename "$file")"
    ./rotate -l "$inputPath$(basename "$file")" $outputPath
done
fi
