# AVL Database

## Overview

This project is a command-line Student Database (using an AVL Tree).

## Features

You can use the following commands:

- ADD (last name, first name) (Student Grade)
- PRINT
- RPRINT
- REMOVE (last name, first name)
- LOOKUP (last name, first name)
- HELP
- EXIT

The database uses tree balancing to make add, remove, and lookups take less than log(n) time. However, prints will take n time since we are traversing the entire tree. 

n = number of students.

## Example

``` 
What would you like to do?
Options:
ADD (last name, first name) (Student Grade)
PRINT
RPRINT
REMOVE (last name, first name)
LOOKUP (last name, first name)
EXIT

blah
error: term blah unknown. Please try again.

ADD Block, Billy 100
Added Block, Billy with grade: 100

PRINT
Block, Billy 100

LOOKUP Block, Billy
Block, Billy has grade: 100

REMOVE Block, Billy
Removed: Block, Billy

RPRINT


EXIT
```

## Running the Program

I used MSVC to compile my project; however, I believe you should also be able to run the project on Linux using gcc or clang.

## Why I built this?

This was my final project in my Data Structures course. It oppened my eyes to the data structures that databases use.