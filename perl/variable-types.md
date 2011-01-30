# Variables and data types in Perl

## What's a variable?

In a nutshell, a variable is a name you give to store data. You can imagine a variable as a label for a box. You point to a particular box by picking out the right label. Once you know what you're talking about, it's easy to get at the items in that particular box.

Another way to think of it is that variables are the 'nouns' of Perl. They are the things you manipulate in your programs.

## Variable names

Variable names can contain alphanumeric characters and underscores. A legal variable name cannot begin with a number. So `1cool_dude` is not legal. Standard Perl style dictates camel case multi-word variables. Only use full uppercase for constants.

Unlike many langagues, Perl uses specific punctuation symbols to indicate the type of a variable. The technical name for the symbols is 'sigils'.
