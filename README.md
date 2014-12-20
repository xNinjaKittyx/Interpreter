Interpreter
===========

Interpreter written in C++ to interpret lines of code and execute it.


In this current state, it only reads from top to bottom some lines of code.

Here is the syntax that it is able to understand

display - displays whatever you want. Separate different strings and variables with commas.
EX: display "The volume of the cylinder is ", 3.14*radius*radius*height;

read - take input. Please take note that this is implicit, and does not require a declaration.
read radius; //This will initiate the variable radius, and store whatever the user put into it.

while, if, else statements work just like they usually do in C++.

You can also declare variables implicitly.
EX: number = 2; //Initiate the variable number with the value 2.
