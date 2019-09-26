    The purpose of this program is to be used a rudimentary shell program in the 
Linux nvironment. The main function of this program is to show a very simple 
example of how a shell operates, and to help illustrate how the inner workings of a 
more complex shell(bash, csh) program might act. The program should accept and execute
all shell commands that are already in the  path /usr/bin. This program will exit 
when keyword “exit” is entered into the command promp regardless of case.
	This project comes with a make file to easily use with the program. The “make” 
command will compile, link and build the executable. The “make run” command will run 
make and then run the executable. The "makle clean" will remove all object files and 
remove the executable, and the “make debug” command will "make" and run the program 
with the -Debug tag to print the value of the argument count, input/output redirect 
values, if process needs to be ran in the backround, and all argument vectors to 
better help with debugging and/or understanding the program and/or shells in general .