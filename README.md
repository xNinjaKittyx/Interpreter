#Interpreter
Interpreter written in C++ to interpret lines of code and execute it.


#Syntax
In this current state, it only reads from top to bottom some lines of code.
```
display - displays whatever you want. Separate different strings and variables with commas.
EX: display "The volume of the cylinder is ", 3.14 * radius * radius * height;

read - take input. Please take note that this is implicit, and does not require a declaration.
read radius; //This will initiate the variable radius, and store whatever the user put into it.

while, if, else statements work just like they usually do in C++.

You can also declare variables implicitly.
EX: number = 2; //Initiate the variable number with the value 2.
```

#Example Code

```

while (1 == 1)
{
display "";
display "************************************************";
display "Want to determine whether n is a prime?";
display "What is your value of n this time? ";
read n;
display "************************************************";
display "";

if ( n < 2 )
    primeStatus = 0;

else
    primeStatus = 1;

candidate = 2;
while (candidate < n)
{
    if ((n % candidate) == 0)
	    primeStatus = 0;

	candidate = candidate + 1;
}

if (primeStatus == 1)
    display n, " is a prime";

else
    display n, " is NOT a prime.";
}

```
