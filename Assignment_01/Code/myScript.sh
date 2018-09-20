#!/bin/bash
args=("$@") # store Arguments
elements=${#args[@]} # store the number of arguments

err1="Invalid argument list." #err msg 1
err2="Proper usage: myScript <path ot executable> m1 [m2 [m3 [...]]]" #err msg 2

if [ $elements -eq 0 ]; then # If there is no arguments, prints error message
  echo $err1
  echo $err2
elif [ $elements -eq 1 ]; then # If the argument is only the path to executable,
  echo $err1 # prints error message
  echo $err2
else # If the arguments include the path executable (exe) and list of ints
  path=$1
  for ((i=1;i<$elements;i++)) # for lookp that Call the exe with indiviual ints
  do
    $path ${args[${i}]}
  done
  for ((i=1;i<$elements;i++)) #for loop that pairs up the ints
  do
    for((j=i+1; j<$elements; j++))
    do
      $path ${args[${i}]} ${args[${j}]} #calls the exe with the paired 2 ints
    done
  done
fi
