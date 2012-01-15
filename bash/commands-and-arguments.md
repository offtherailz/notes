# BashGuide @ Greg's Wiki

## Commands and Arguments

### How Bash handles input

Bash reads commands from input (a terminal or a file), and each line is
a command to Bash. A command is a piece of work - something to do. Bash
divides the lines into words, and the division is on whitespace (spaces or
tabs). Normally, the first word of each command is the name of the command
to run, and the rest of the words are arguments to that command. The
arguments may be options, switches, filenames or whatever.

The amount or type of whitespace between parts of a command are irrelevant.
The following are all identical:

    echo This     is  silly
    echo This is silly

On the one hand, this is convenient, but in some cases you may want to
preserve the specific whitespace. In such a case, pass the words to Bash
quoted. Then Bash will see the quoted string as _one_ argument and not
touch the inner whitespace.

To be clear, it's the shell and not `echo` that ignores the whitespace. The
command `echo` never sees the whitespace (as such). The shell does its
division of the arguments and then passes them along to the command. So in
the first example, `echo` receives 'This', 'is' and 'silly' as its three
arguments. Then it prints them with a single space between each one.
(That's its default behavior.) In the other case, `echo` receives only one
argument, 'This     is  silly'. When there is only one argument, `echo`
simply prints it to STDOUT as is.

### Types of commands

Bash recognizes a number of different types of commands: aliases,
functions, builtins, keywords and executables. In a nutshell:

+ An alias is a simple way of creating shortcuts for long, complex
  commands. They are not able to do very much (e.g. no parameters).
+ A function is like a small script. They can take arguments and create
  local variables.
+ A builtin is a command that Bash does itself rather than calling.
  Examples are `cd` and `echo`.
+ A keyword is similar to a builtin, except that they also have special
  parsing rules. (I might also say a keyword is part of the language of the
  shell itself, while a builtin is more like an added special function.)
+ An executable or application is a program that can be executed by
  referring to its full pathname (e.g., /bin/ls) or just its name (assuming
  the item is on your path and has the right permissions).

Finally, a script is simply a sequence of commands kept in a file. Once
you've put it all together as you want, you can run the whole sequence as
one thing by placing it into a script.
