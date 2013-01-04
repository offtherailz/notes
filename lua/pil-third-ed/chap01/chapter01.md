# Programming in Lua: 3rd edition

## Chapter 1 Getting Started

### Chunks

Every piece of code that Lua executes is called a 'chunk'. A chunk is
a sequence of commands or statements.

Lua does not require a semicolon to separate statements, but you can use
one if you want. The following four chunks are all valid and equivalent:

    a = 1
    b = a*2

    a = 1;
    b = a*2;

    a = 1; b = a*2;

    a = 1 b = a*2

A chunk can be a single statement or very large. Lua has no trouble with
large chunks. In general a chunk will contain a mixture of statements and
function definitions. (Note that function definitions are actually
assignments. See later chapters on functions.)

In addition to writing your code in a file, you can run the Lua interpreter
interactively. You can get to the interactive mode in two ways:

+ Run `lua` with no arguments, and you go right to interactive mode.
+ Run `lua -i prog`, and Lua runs the chunk in 'prog' and then starts in
  interactive mode.

While in interactive mode, Lua normally treats each line as a complete
chunk. However, if the interpreter can detect that a line is syntactically
incomplete, it will wait until it has a full chunk (say by waiting for an
'end'). But it is still usually easier to pull larger definitions into
a file.

You can get out of interactive mode by giving the interpreter EOF (Ctrl-D
or Ctrl-Z) or by using `os.exit` from the operating system library.

You can also use `dofile` to execute the contents of a file from the
interactive interpreter. This allows you to load up a batch of definitions
and test them easily.

### Some Lexical Conventions

Identifiers (names) in Lua can be any string of letters, digits and
underscores, not beginning with a digit. But you should avoid identifiers
starting with an underscore followed by one or more upper-case letters
(e.g. `_VERSION`). Lua reserves such variables for special uses. The
identifier `_` is often used for dummy variables.

Previous versions of Lua allowed letter to be defined by your locale.
However, 5.2 only accepts the ranges A-Z and a-z as letters for
identifiers.

You also cannot use any of the following reserved words as identifiers:

    and     break       do      else    elseif
    end     false       goto    for     function
    if      in          local   nil     not
    or      repeat      return  then    true
    until   while

Lua is case-sensitive. The following are all different identifiers: `and`,
`AND`, `And`, `AnD`. But don't do that.

Comments start with a double hyphen and run until th eend of the line. You
can also use block comments wich start with `--[[` and run until the next
`]]`. It's actually more complicated than that. Here's a good trick to
comment and uncomment pieces of code easily:

    --[[
    code you may want to comment out
    ...
    --]]

You can reactivate that block at any time by adding a third hypen to the
first line. Then `---[[` is a single-line comment as is `--[[`. The code
between those lines is executed normally.

### Global Variables

Global variables don't need declarations. Just use them. There's also no
error in using a non-initialized variable; all such variables have the
value `nil`. If you assign `nil` to a global variable, Lua act as though it
didn't exist. (In this way, you can theoretically help out garbage
collection, though I doubt this is often necessary or useful.)

### The Stand-Alone Inepreter

The stand-alone interpreter is a small program that makes it easy to use
Lua directly. If you start a file with a shebang line, Lua's interpreter
will ignore the first line. Thus, you can use Lua as a script interpreter.

The basic usage of the lua executable is this:

    lua [options] [script [args]]

Everything is optional. Calling the executable alone immediately goes into
interactive mode. The `-e` option allos you to enter code directly from the
command line. The `-l` option loads a library. The `-i` option sends you
into interactive mode after running any other arguments.

Within interactive mode, you can print the value of an expression by adding
a `=` at the start of the line, followed by the expression.

Before running any arguments, the interpreter looks for an environment
variable named `LUA_INIT_5_2` and then `LUA_INIT`. If there is such
a variable and it has `@filename` in it, the interpreter loads the
given file first. If the item is defined as just `filename`, the
interpreter treats the file as Lua code and runs it. You can use this
mechanism to preload modules, predefine essential functions, change your
prompt or path, etc.

Scripts can retrieve their arguments in the predefined global variable
`arg`. When a script runs, `arg` is created and loaded as follows. The
script's name is in index 0, its arguments in index 1, 2, etc. Options that
precede the script's name go into negative indices. For example:

    $ lua -e "sin=math.sin" script a b

    arg[-3] = "lua"
    arg[-2] = "-e"
    arg[-1] = "sin=math.sin"
    arg[0] = script
    arg[1] = a
    arg[2] = b

In general, scripts only use the positive indices.

Since Lua 5.1 scripts can also get their arguments using a vararg
expression (`...`).
