# Programming in Lua 3rd edition

## Chapter 8 Compilation, Execution, and Errors

Lua is *not* exactly an interpreted language. In fact, Lua always
precompiles the source code to an intermediate form before running it.
(This is actually not uncommon: other interpreted languages do the same.)
For I, "the distinguishing feature of interpreted languages is not that
they are not compiled, but that is is possible (and easy) to execute code
generated on the fly" (page 71). `dofile` is a big part of this process for
Lua.

### Compilation

When `dofile` was mentioned earlier, it was as a primitive function to run
chunks of Lua code. However, the function `loadfile` really does the brunt
of the work. `loadfile` compiles a chunk and returns the compiled chunk as
a single function. Also, unlike `dofile`, `loadfile` does not raise errors.
It just returns error codes. If you wrote `dofile` in Lua, it might look
like this:

    function dofile(filename)
      local f = assert(loadfile(filename))
      return f()
    end

`dofile` uses `assert` to raise an error if `loadfile` fails.

`dofile` is convenient for simple things, but `loadfile` is more powerful
and flexible. First, the user can choose how (or if) to handle errors.
Also, if you need to run a file more than once, `loadfile` is cheaper. It
only compiles the file once, and then you can call the returned function as
often as you like.

There is also a function `load` that reads a chunk from a string instead of
a file. (In Lua 5.1, this function was named `loadstring`)

    f = load("i = i + 1")
    i = 0
    f(); print(i) --> 1
    f(); print(i) --> 2

This function is powerful but expensive. You can usually figure out
a simpler way to do things. If, however, you want a quick hackish
`dostring`, that is a load-and-fire from a string function, you can call
the result of `load` directly:

    load(s)()

If there's an error, however, you will get a message like "attempt to call
a nil value" since `load` returns `nil` on error. For a better error
message, you could do this:

    assert(load(s))()

Note that `load` doesn't compile with lexical scoping, so you may see odd
results if you are trying to depend on scope for variable values. `load` is
most often used to run external code.

The load functions never raise errors and they have no side effects. They
only compile the chunk to an internal representation and return the result
as an anonymous function. Don't make the mistake of thinking that loading
a chunk defines a function. In Lua, function definitions are assignments.
That means that they happen at runtime, not at compile time. An example:

    -- file 'foo.lua'
    function foo(x)
      print(x)
    end

    f = loadfile('foo.lua')
    print(foo) -- nil - foo doesn't exist until f is _called_
    f()
    foo('ok') -- prints 'ok'

### Precompiled code

You can precompile code with `luac`. You can use this to save a precompiled
form of a Lua program. Precompiled code is not necessarily smaller, but it
loads faster. It also freezes development at a specific point.

    luac -o program.lc prog.lua

You can also use the `-l` option which causes `luac` to print out the
opcodes that the compiler generates for a chunk.

In addition to the required first argument, `load` accepts three more
arguments.

+ The second is a name for the chunk, used only in error messages
+ The third controls what kind of chunks can be loaded: 't' textual chunks
  only, 'b' binary chunks only, 'bt' (the default) both binary and textual
  chunks.
+ The fourth argument specifies an environment

### C Code

C provides a way to dynamically link C code in some operating system
environments. You use `package.loadlib`. This function takes two arguments:
a full path to the library and the name of a function to load from the
library.

    local path = '/usr/local/lib/lua/5.1/socket.so'
    local f = package.loadlib(path, 'luaopen_socket')

`loadlib` doesn't call the function. It returns it as a Lua function which
you can then call as you want. If there is any error loading the file or
function, `loadlib` returns `nil` plus an error messsage.

Rather than `loadlib`, you will usually use a higher-level function to load
C libraries, namely `require`. Details about `require` will come in later
chapters.

### Errors

When an error happens, Lua ends the current chunk and returns to the
calling application. Errors occur under a number of conditions. For
example:

+ Adding values that aren't numbers
+ Calling values that aren't functions
+ Indexing values that aren't tables

You can also explicitly raise an error, using the `error` function with an
error message as an argument. This is a good way to signal errors in your
code:

    print 'Enter a number: '
    n = io.read('*n')
    if not n then error('Invalid input!') end

This sequence is so common that Lua has a built-in function to simplify it:
`assert`:

    print 'Enter a number: '
    n = assert(io.read('*n'), 'Invalid input!')

The `assert` function returns the value of the first argument, if it is
non-false. If it is false, then `assert` raises an error and passes its
optional second argument as the error's message.

If a function runs into an unexpected situation (an exception), it can do
two basic things:

+ Return an error code (for example, `nil`)
+ Raise an error by calling `error`

There's no rule about when to do what. But I gives guidelines:

+ If an exception is easily avoided, it should raise an error.
+ Otherwise, it should return an error code.

As an example fo the first, he mentions calling `sin` on a table. It's easy
to check for a problem with this before or after the call:

    -- after
    local res = math.sin(x)
    if not res then -- error?
      <error code>
    end

    -- before
    if not tonumber(x) then -- x is not a number?
      <error code>
    end

But often you don't check either argument to `sin` or result of call. If
the argument is not a number, something is wrong with your program. As
such, calling `sin` on something that isn't a number raises an error.

But in the case of `io.open`, there's no easy way to check for an exception
before calling the function. (Because in many systems, the only way to know
if a file exists is by trying to open it.) So in this case, if `io.open`
fails because the file doesn't exist or the permissions are wrong, it
returns `nil` plus an error message as a string. That way you can handle
this error however you like.

    local file, msg
    repeat
      print 'Give me a file name: '
      local name = io.read()
      if not name then return end
      file, msg = io.open(name, 'r')
      if not file then print(msg) end
    until file

If you don't want to handle things so much, but still want to be safe, you
just wrap the call in `assert`:

    file = assert(io.open(name, 'r'))

This is a common idiom in Lua. If the call fails, you get an error plus
base message from `assert`:

    file = assert(io.open('no-file', 'r'))
    -- stdin:1: no-file: No such file or directory

### Error Handling and Exceptions

Often, you don't need to do error handling in Lua. The application program
handles errors. However, if you do want to handle errors internally, you
should use the `pcall` function to encapsulate your code.

`pcall` calls its first argument in protected mode. It catches errors while
the function is running. If there are no errors, `pcall` returns `true`
plus any values returned by the cal. Otherwise, it returns `false` plus the
error message.

The error message doesn't have to be a string: `pcall` will return any Lua
value that you pass to `error`:

    local status, err = pcall(function () error({code=121}) end)
    print(err.code)

Using `error` and `pcall`, you can create exception handling in Lua. You
throw an exception with `error` and catch one with `pcall`. The error
message identifies the error.

### Error Messages and Tracebacks

You can use any value as an error message, but usually they are strings. In
the case of an internal error, Lua generates the error automatically.

When the error message is a string, Lua tries to add some information about
where the error happened. The location error gives the filename (or
'stdin') and the line where the error happened.

You can pass a second argument to `error` - a number which gives the level
where the error should be reported. 1 is your function. Add 1 for each
level up the chain that you want to go.

    function foo(str)
      if type(str) ~= 'string' then error('String expected', 2) end
      <regular code>
    end

In addition to where the error occurred, you often want more information.
Since `pcall` destroys part of the stack, it removes your ability to build
a traceback of the error. If you want a traceback, therefore, you have to
build it before `pcall`. Lua provides `xpcall` to help with this. In
addition to the function to call, `xpcall` takes a message handler
function. If an error occurs, Lua calls this second function before the
stack unwinds, so that it can use the debug library to gather information
about the error. The debug library will get more attention in Chapter 24.
