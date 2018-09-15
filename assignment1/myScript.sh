#!/bin/bash
args=("$@")
elements=${#args[@]}
echo $elements

if [ $elements -eq 0 ]; then
  echo Invalid argument list.
  echo Proper usage: myscript m1[m2 [m3 [...]]]
else
  for ((i=0;i<$elements;i++))
  do
    ./prog ${args[${i}]}
  done
  for ((i=0;i<$elements;i++))
  do
    for((j=i+1; j<$elements; j++))
    do
      ./prog ${args[${i}]} ${args[${j}]}
    done
  done
fi


arguments - parameters
