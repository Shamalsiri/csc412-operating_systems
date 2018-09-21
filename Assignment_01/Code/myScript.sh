#!/bin/bash
args=("$@") # store Arguments
elements=${#args[@]} # store the number of arguments

err1="Invalid argument list." #err msg 1
err2="Proper usage: myScript <path ot executable> m1 [m2 [m3 [...]]]" #err msg 2

if [ $elements -lt 2 ]; then # If there is no arguments or 1 argument
  echo $err1 # prints error message
  echo $err2
else # If the arguments include the path executable (exe) and list of ints
  path=$1
  if [ -x "$path" ]; then # check if the path is executable
    for ((i=1;i<$elements;i++)) # for loop that Call the exe with indiviual int
    do
      $path ${args[${i}]} #calls the exe with the int
    done
    for ((i=1;i<$elements;i++)) #for loop that pairs up the ints
    do
      for((j=i+1; j<$elements; j++))
      do
        $path ${args[${i}]} ${args[${j}]} #calls the exe with the paired 2 ints
      done
    done
  else # If path isn't executable, prints error msg
    echo $err1
    echo $err2
  fi
fi
