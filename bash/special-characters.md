# BashGuide @ Greg's Wiki

## Special Characters

When working in Bash, some characters have a non-literal meaning. These
metacharacters are especially important and potentially confusing. Here's
the key thing to remember: the shell evaluates the characters and works out
their meanings, but it does not (usually) pass them on as-is to other
commands. So _the shell_ sees and interprets them, not the subsequent
commands.


+ Whitespace - a space, tab or newline is a word delimiter. The first word
  of each command is treated as the command name. Later words are arguments
  to the command.
+ $ - The expansion character is used in substitutions, including parameter
  expansion, command and variable substitution.
+ Single quotes: this type of quote mark protects the text within the
  quotes from _any_ kind of expansion by the shell. Word-splitting isn't
  done, and special characters are no longer special.
+ Double quotes: this type of quotes prevents word-splitting, but
  substitutions still occurs.
+ # - Comments start at this symbol and continue until the next newline.
  The shell does not process comments.
+ ; - You can use the command separator to put multiple commands on
  a single line.
+ \ - The backslash prevents the next character from being special. It
  works outside quotes and within double quotes, but not within single
  quotes.
+ ~ - An alias for the current user's home directory. Also in expressions
  like `~john` it means John's home directory.
+ `<` and `>` are redirection characters. The modify the input and output
  of a command.
+ | - The pipe sends the output of the command on the left to the input of
  the command on the right.
+ `[[ ]]` The expression inside the double brackets is evaluated as
  condition. This form is a Bashism, and it has some advantages over the
  single bracket form.
+ `{ }` The commands inside the braces are treated as though they were one
  command.
+ ` ` or $( ) provide command substitution. The command inside is run first
  and its standard output is replaced in the larger command.
+ ( ) - Subshell execution means the command is run in a new shell, and
  side-effects (e.g. changing directories) have no effect on the parent.
+ (( )) - Arithmetic commands go in double parentheses. This is a Bashism.
+ $(( )) - Arithmetic substitution is like the double parentheses alone,
  except that now the result is placed into the larger command.


tl;dr - The shell sees these special characters, interprets them, and then
they are usually replaced in the command by their meaning.
