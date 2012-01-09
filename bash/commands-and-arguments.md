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
functions, builtins, keywords and executables.
