# Discrete Mathematics for Computing

## Chapter 1

### Formal definition for algorithm

His definition of an algorithm (page 2):

> a finite sequence of steps for performing a task, such that:
>
> + each step is a clear and unambiguous instruction that can be executed in
    a finite time;
> + the sequence in which the steps are to be executed is clearly defined;
> + the process is guaranteed to stop after a finite number of steps have
    been executed.

In general an algorithm will take various inputs and yield some output,
though this is not strictly required. He also points out that an algorithm
will usually have some purpose.

### Basic pseudocode conventions

In order to describe algorithms somewhat formally without worrying about
the details of any particular programming language, he uses an artificial
pseudocode. (I don't know if it's his invention or widely used.)

Here's his first example, then a short discussion of its features:

> The area of a circle with radius r is Pi * r ** 2. The algorithm is as
> follows:
> 
> 1. Input r {r is the radius of the circle}
> 2. area <- pi * r ** 2
> 3. Output area

+ The steps are numbered. Sub-steps are numbered as 1.1, 1.1.1 and so on.
+ Anything between {} are comments
+ Assignment is shown with `<-`

### Control structures

He also introduces a handful of control structures for the pseudocode.

+ For (assignment) to (limit) do... (For-do)
+ If (test) then... (If-then)
+ If (test) then...else... (If-then-else)
+ While (test) do... (While-do)
+ Repeat...until (test)... (Repeat-until)
