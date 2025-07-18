# raz-b
A simple utility for splitting text files into multiple parts with a specified number of lines.
> Wrote this to automate some repetitive work. Yes, I know the code sucks - PRs welcome! :D

>I got carried away with something and plan to make a file processor out of it. I'll update the REAMDE file sometime 

## Description
The program allows you to:

View files in the current directory

Select a file to split

Specify the number of lines per output file

Automatically generate split files

## Usage
Compile the program:

```sh
g++ -std=c++17 raz-b.cpp -o raz-b  
```
Run the program:

```sh
./raz-b 
``` 
Enter the desired number of lines per output file

Select a file from the list by its number

The program will create files in the format copy1_original.txt, copy2_original.txt, etc.

## Features
The first and last lines of the original file are preserved in each output file

Supports all text files in the current directory

Simple console-based interface

## Requirements
A C++17-compatible compiler

Standard filesystem library (std::filesystem)
