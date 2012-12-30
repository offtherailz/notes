# Chapter 15 - Writing Large Programs

Up until now, all the programs have been relatively small. However, typical
programs involve more than one source file. In this chapter, King gets
modular.

## Source files

A C program can be divided up among any number of source files. He gives
a long-ish example of a calculator program for Reverse Polish notation. You
might put the "get a token" functions into `token.c` and the stack handling
functions in `stack.c` and so on.

Splitting a program up into multiple files may seem annoying or complicated
at first, but it brings advantages.

+ Grouping related things brings clarity.
+ Each source file can be compiled separately---a big time-saver if the
  program is large and gets re-compiled often.
+ Reusing functions becomes easier. You might use `stack.c` for some other
  program. It needs stacks but has nothing to do with calculators.

## Header files

Once we divide up a program, though, we have some problems. How do the
functions from different files call each other? How can external variables
be available to functions in another file? How do files share macro
definitions or type definitions?

The answer to all of this is `#include`. We put information we want to
share out into header files (they end in `.h` by convention), and then use
`#include` to bring them into other files. (**NB**: The C standard uses the
term "source file" for both `.c` and `.h` files, but King uses "source
file" only for `.c` files.)

## The `include` directive

The `#include` directive has two main forms. The first is used for header
files from C's standard library. The second is used for all other header
files, including ones we write ourselves.

    #include <filename>
    #include "filename"

The difference has to do with the paths that are searched and in what order
they are searched. In the first case, only the directory or directories
where system header files are searched (e.g. `/usr/include`). In the second
case, search the current directory and then search the standard locations.

In addition, however, you can alter the paths to search by a command-line
option using `-I` or by tweaking environment variables in makefiles or the
like.

You can put path information in an include, but it's a good idea to limit
that to relative path names (at most).

There is a third form of `#include` directive. In this case, you can use
preprocessing tokens.

    #if defined(IA32)
            #define CPU_FILE "ia32.h"
    #elif defined(IA64)
            #define CPU_FILE "ia64.h"
    #endif
    ...
    #include CPU_FILE

## Sharing macros definitions and type definitions

Large programs often use the same macro or type definitions in multiple
files. This is a good place to use a shared header file.

    # In the header
    #define BOOL int
    #define TRUE 1
    #define FALSE 0
    ...
    # In a source file
    #include "mybool.h"
    ...
    # Or with a typedef
    #define TRUE 1
    #define FALSE 0
    typedef int Bool;

## Sharing function prototypes

It's a bad idea to call a function defined in another file without the
compiler first seeing the function's prototype. (In C99, it's prohibited
even.) So another use for headers is to place function prototypes.

One practice is to name the header file and source file the same basic
thing. Definitions go into the source file, and prototypes (declarations)
go into the header. However, don't put prototypes in the header for
functions that are _only_ used in the one file. (That is, leave them
private, so to speak.) The source file that defines a function should
_also_ include its own header in order to ensure that the definition
matches the prototype.

## Sharing variable definitions

External variables can be shared among files just as functions are shared.
But it requires a little extra care and a new keyword: `extern`. We must
also now distinguish between declaring a variable and defining it.
Declaring a variable is stating it's type and name. Defining it means
setting aside space for it. Normally a statement like `int i` _both_
declares and defines a variable. However, with `extern` that's not so.

If a variable will be shared among many files, you can put it into a header
and then use `extern` in the source files that include that header.

    # In the header
    int i; /* Declares and defines i. Space is set aside for it. */
    # In the source file
    extern int i; /* Declares without defining. No new space set aside. */

## Nested includes

One header can pull in other headers via `#include`. In the past,
C programmers disliked nested includes like this, but it has become more
common (maybe under the influence of C++?).

## Protecting header files

Doubly including a header can be a problem. First, it leads to double
compilation. Second, if there are type definitions, there will be
a compilation error. To protect agains this, you can do something like the
following:

    #ifndef BOOLEAN_H
    #define BOOLEAN_H

    #define TRUE 1
    #define FALSE 0
    typedef int Bool;

    ...
    #endif

Now the file will skip everything if it's included more than once.

## Error directives in header files

You can use error directives in header files as a way to bail out of
compilation under certain conditions.

    #ifndef __STDC__
    #error This header requires a Standard C compiler
    #endif

## Building a multiple-file program

Building a program out of more than one file involves the same basic steps
as a program in one file: compiling and linking.

+ Compiling: each file gets compiled separately. For each one, the compiler
  produces an object file.
+ Linking: All the object files made in the last step are put together by
  the linker. The linker also adds in code for library functions. The
  result is an executable.

You can do this all pretty easily with `gcc` in one step:

    gcc -o justify justify.c line.c word.c

However, this is annoying to type and duplicates effort if only one of the
files has changed. To simplify things, you want a makefile.

    justify: justify.o word.o line.o
            gcc -o justify justify.o word.o line.o

    justify.o: justify.c word.h line.h
            gcc -c justify.c

    word.o: word.c word.h
            gcc -c word.c

    line.o: line.c line.h
            gcc -c line.c

Each of the four groups is a rule. The first line is a 'target', followed
by the files it depends on. The next line is a command that specifies how
to rebuild the target (after a change in one of the dependencies).

## Errors during linking

Sometimes an error will pop up during linking rather than compilation. You
may see messages like "undefined symbol" or "undefined reference". In such
a case, here are some things to check:

+ Misspellings between files
+ Missing files
+ Missing libraries (here check both for missing `#include` directives and
  you may need an option on the command line like `-lm`)

## Rebuilding a program

Quick version: If you use `gcc` you have to track what you need to rebuild
and what object files you can reuse. Make takes care of this for you. Use
make.

## Defining macros outside a program

C compilers allow you to specify the value of a macro at compile-time. For
example, `gcc` offers the `-D` option. Case in point:

    gcc -DDEBUG=1 foo.c

Many compilers also support a `-U` option to undefine macros at
compile-time.
