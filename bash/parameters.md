# BashGuide @ Greg's Wiki

## Parameters

The guide describes parameters as "a sort of named space in memory you can
use to retrieve or store information".

There are two types of parameters: variables and special parameters. The
special ones are read-only and Bash sets them for you. You create and
update variables as you like. (Variable names can contain letters, digits
and underscores, but can't start with a number.)

The assignment syntax for a variable cannot contain spaces, and in an
assignment, the variable should not have a `$` sigil:

    varname=vardata

To use the data in the variable, you use parameter expansion. This
substitutes the value of the variable for its name. But after that happens,
the shell may still do additional manipulations with the result. So, for
example - and very importantly, word splitting happens after parameter
expansion. Thus, you will (almost?) always want to put double quotes around
parameter expansion:

    rm $foo   # bad, since $foo may expand to This is not a love song.mp3
    rm "$foo" # good

(**NB** The `$` in a parameter expansion is _not_ part of the variable's
name as it is in Perl. It's syntax that tells the shell to replace the name
of the variable with its value. The name is `whatever`, but the value is
something else.)

### Some important special parameters

+ `0` The name, or path, of the script (not always reliable)
+ `1,2...` Arguments passed to the script or function, in order. These only
  have individual names up to 9.
+ `*` All the words of all the positional parameters. If in double quotes,
  it expands to _a single string_ with all the positional parameters
  separated by the first character of the IFS variable.
+ `@` All the words of all the positional parameters. If in double quotes,
  it expands to a list of all the positional parameters as individual
  words. (Thus you can loop over this but not over `*`.)
+ `#` The number of positional parameters that are currently set.
+ `?` The exit code of the last executed command.
+ `!` The PID of the last executed command.
+ `$` The PID of the current shell.
+ `_` The last argument of the last command.

### Some useful builtin variables

+ `BASH_VERSION` A string version number for Bash
+ `HOSTNAME` The long or short form of your machine's hostname
+ `PPID` PID of the parent process of the shell
+ `PWD` Present working directory
+ `RANDOM`  A pseudo-random number between 0 and 32767
+ `UID` The id number of the current user (Not reliable for authentication)
+ `COLUMNS` Column count of the terminal's width
+ `LINES` Row count of your terminal's height
+ `HOME` Current user's home directory
+ `PATH` Colon-separated list of directories to search for commands
+ `PS1` The shell's prompt string
+ `TMPDIR` Name of the directory used by the shell for temporary files

### Variable types

Bash is not typed, but there are different types of variables.

+ Array (`declare -a`) An array of strings
+ Associative array (`declare -A`) A hash of strings (Bash 4.0 or higher)
+ Integer (`declare -i`) A number for arithmetic evaluation
+ Read only (`declare -r`) A variable that cannot be modified or unset
+ Export (`declare -x`) The variable will be inherited by subshells or
  child processes.

Instead of `declare -i` for integers, most people use `let` or `(())` to
indicate arithmetic operations. And you rarely see arrays explicitly
declared with `declare -a`. It is enough to say `array=(  )`.

### Parameter expansion

If you want to use a variable's value as part of a larger string, you will
often need to surround the variable name with `{}` to make clear where it
ends.

    foo=bar
    echo "I have three $bars"     # won't work, no such variable as 'bars'
    echo "I have three ${bar}s"   # works great

In addition, parameter expansion can modify the string that is substituted.

+ `${param:-word}` If 'param' is unset or null, use the expansion of
  'word'. Otherwise, use 'param'.
+ `${param:=word}` If 'param' is unset or null, assign 'word' to 'param'
  and then expand it.
+ `${param:+word}` If 'param' is null or unset, substitute nothing.
  Otherwise, use the alternate value 'word'.
+ `${param:offset:length}` Substring expansion: expands up to 'length'
  characters of 'param', starting at character 'offset'. The string is
  indexed starting at zero. If 'length' is omitted, go all the way to the
  end. If 'length' is negative, count back from the end of the string. If
  you omit 'length', you must also omit the final colon.
+ `${#param}` The length of characters of 'param' is substituted.
+ `${param#pattern}` The 'pattern' is matched against the start of
  'param'. The expansion is 'param' minus the shortest match of 'pattern'.
+ `${param##pattern}` As above, but now the expansion is 'param' minus the
  _longest_ match of 'pattern'.
+ `${param%pattern}` The 'pattern' is matched against the end of 'param'.
  The expansion is 'param' minus the shortest match of 'pattern'.
+ `${param%%pattern}` As above, but the expansion is 'param' minus the
  _longest_ match of 'pattern'.
+ `${param/pattern/replacement}` The first match of 'pattern' is replaced
  with 'replacement'.
+ `${param//pattern/replacement}` As above, but every match of 'pattern' is
  replaced with 'replacement'.
