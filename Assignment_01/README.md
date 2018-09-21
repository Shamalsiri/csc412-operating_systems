# Programing Assignment 1 #

***Attention:*** The following document is a summation (and excerpts) of the Assignment 1 hand out provided by Professor Herve

## Objectives ##
- Setup the environment that you are going to use for all assignments this semester;
- Learn some simple Unix commands (if you were not already familiar with Unix/Linux);
- Get started with C programming and bash scripting;
- Make sure that you follow properly assignment specifications.

### 1. Setting up the Environment ###
- Step 1:
  - Install the latest version of Ubuntu into a Virtual Machine
  - **Take a screenshot of the settings of the Ubuntu virtual machine that you just created. Name the screenshot file step1.pdf**  
- Step 2:  
  - Create a new folder using the `mkdir` command  
  - Move to that folder using the `cd` and printout the path this (current) working directory by using the `pwd` command.
  - **Take a screenshot of the terminal after you executed the `pwd` command. Name the screenshot file step2.pdf**  
- Step 3:  
  - Redirect the current working directory to the file using the `>` operator: `pwd > path.txt`
  - You can view the content of the file either by typing `pr path.txt` or `more path.txt`
  - **Take a screenshot of the terminal showing the content of the *path.txt* file after you executed the commands listed in this subsection. Name the screenshot file step3.pdf**  
- Step 4:  
  - Create a new (empty) text file with the terminal command `touch`
  - Verify in the *GUI* explorer that the file has indeed been created
  - **Take a screenshot of the terminal and GUI explorer that you have completed this step in the assignment. Name the screenshot file step4.pdf**
- Step 5:  
  - Use the text editor (*vi/vim, nano, emacs*) of your choice to open a next text file, type in the customary line "Hello World!" and save the file.
  - **Take a screenshot of open editor window. Name the screenshot file step5.pdf**
- Step 6:  
  - Display your recent history by typing the command `history`  
  - **Take a screenshot showing that you have experimented with the history features of Unix. Name the screenshot file step6.pdf**
- Step 7: Save your command `history` to a file named *history.txt*, edit this file to add a first line containing your name. Save the *history.txt* file.

### 2.  A Little C Program ###

#### 2.1 Computation #####

 Your program will take either one or two strictly positive integer arguments. If the program was launched with a single argument, then you should compute and output the list of all divisors of the argument. For example, if your executable is named `prog` and is launched from the console with the command  

`./prog 36`

Then your program should produce the following output:

*The list of divisors of 36 is: 1, 2, 3, 4, 6, 9, 12, 18, 36.*

If the program was launched with two arguments, then your program should compute and output the gcd of these two numbers.For example, if your executable is named `prog` and is launched from the console with the command

`./prog 36 60`

Then your program should produce the following output:

*The gcd of 36 and 60 is 12.*

#### 2.2 Data validation and error reports ####

You should check the argument(s) of your program and report an eventual error using one of the following messages (again assuming that you built an executable named `prog`): *  
 * prog launched with no argument.  
   Proper usage: prog m [n]     
 * prog launched with too many arguments.  
   Proper usage: prog m [n]  
 * prog’s argument is not a strictly positive integer.  
 * prog’s first argument is not a strictly positive integer.  
 * prog’s second argument is not a strictly positive integer.*  

Needless to say, the name of the executable should not be hard-coded in your C program.  

### 3. Simple *bash* Script

Write a bash script that launches an executable, multiple times.

#### 3.1 The Script ####

The *script* should take as arguments a path for the executable of the divisor program, as well as a list of strictly positive integers. Then the *script* should do the following:

*  Launch the divisor program for each of the integer arguments, to get the list of divisors of that number.
*  Launch again the divisor program for each pair of arguments (ignoring order, so if you called `./prog 20 12`, don’t call `./prog 12 20`, to compute the gcd of these two numbers.)

#### 3.2 Output of the Script ####

When the numerical arguments to your script are all strictly positive integers, then the entire output is provided by the divisor program. For example, if your C executable is named `prog` and is in the same directory as the bash script, and then your script is launched with the command

  `sh ./myScript.sh ./prog 36 10 37`

then the output should be:  

*The list of divisors of 36 is: 1, 2, 3, 4, 6, 9, 12, 18, 36.  
The list of divisors of 10 is: 1, 2, 5, 10.  
The list of divisors of 37 is: 1, 37.  
The gcd of 36 and 10 is 2.  
The gcd of 36 and 37 is 1.  
the gcd of 10 and 37 is 1.*  

On the other hand, if any the script was launched with an invalid argument list, your script should simply terminate and report:

*Invalid argument list.  
Proper usage: myScript <path to executable> m1 [m2 [m3 [...]]]*

## Organization ##

All the screenshots, named as specified earlier, should go into a folder/directory named Screenshots, while the C program and the script should go into a folder named Code. These two folders and the history.txt file should be placed into a folder named Assignment 01. Compress this folder into a zip archive and upload the archive to your submit folder before the submission deadline.

*** Reminder: *** Use of any solutions found in this repository for academic assignments/purposes will be considered **Plagiarism.**
