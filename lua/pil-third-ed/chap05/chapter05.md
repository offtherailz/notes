# Programming in Lua 3rd edition

## Chapter 5 Functions

Functions are the main way to abstract statements and expressions in Lua.
Functions can do something, or they can return a value. The first kind of
function is like a statement, and the second an expression. (Some languages
call the first type procedures or subroutines.)

Lua functions take their arguments inside parentheses. If you have no
arguments, you still need to add the empty parentheses to signal the call.
There is one special case: if a function has a single argument which is
either a literal string or a table constructor, then the parentheses are
optional:

    print "hello world"
    dofile 'a.lua'
    f{x = 10, y = 20}

Lua also offers syntactic sugar for object-oriented calls. The colon
operator in an expression like `o:foo(x)` is a shorter way to write
`o.foo(o, x)`. The colon operator automatically adds `self` (in effect)
as a first argument.

Lua programs can use functions defined in Lua or in C (or any language used
by the host application).

Function definition has a simple syntax:

    function add(a)
      local sum = 0
      for i=1, #a do
        sum = sum + a[i]
      end
      return sum
    end

Parameters are local variables, initialized with the values given when the
function is called. You can always call a function with more or less
parameters than the definition. Lua adjusts the number of arguments just as
it does in multiple assignment. Extra arguments are discarded; missing
parameters get the value `nil`.

This can be useful for setting default arguments:

    function incCount(n)
      n = n or 1
      count = count + n
    end

### Multiple Results

Lua functions can return multiple results. An example is `string.find`. It
locates a pattern in a string. It returns two indices when it finds the
pattern: the index of the character where the pattern begins, and the index
of the character where it end. You use multiple assignment to get both
results:

    s, e = string.find("hello Lua users", "Lua")
    -- s = 7, e = 9

To write a function that returns multiple results, simply list them after
return in the function call. Note that Lua always adjusts the number of
results from a function to the circumstances of the call. If you call
a function as a statement, all results are discarded. When you call
a function as an expression, Lua keeps only the first result. You get all
results only when the call is the last (or only) expression in a list of
expressions. These lists appear in four constructions in Lua:

+ multiple assignments
+ arguments to function calls
+ table constructors
+ return statement

Note that a function call produces exactly one result if it is *not* the
last element in a list. This is true even if the function itself is written
to return multiple results. Finally, you can always force a call to return
exactly one result by enclosing it in an extra pair of parentheses.

A special function with multiple returns is `table.unpack`. It takes an
array argument, and returns as results all elements from the array,
starting at index 1. This method uses the length operator, so it only works
on proper sequences. (That is, arrays starting at index 1 with no gaps.)

Although `table.unpack` is written in C, here is a recursive version
written in Lua:

    function unpack(t, i, n)
      i = i or 1
      n = n or #t
      if i <= n then
        return t[i], unpack(t, i+1, n)
      end
    end

### Variadic Functions

Lua functions can receive a variable number of arguments. Here's a simple
example:

    function add(...)
      local s = 0
      for i, v in ipairs{...} do
        s = s+v
      end
      return s
    end

The three dots in the parameter list indicate that the function is
variadic. Lua can access these extra arguments inside the function using
the three dots as an expression. The expression `...` is called a vararg
expression. It behaves like a multiple return function, returning all extra
arguments of the current function. Here's a multi-value return function:

    function id(...) return ... end

Here's a way to create an internal printf-like function:

    function printf(fmt, ...)
      return io.write(string.format(fmt, ...))
    end

Variadic functions can have any number of fixed parameters before the
variadic part. Lua assigns the first arguments to these parameters. The
rest, if any, go as extra arguments.

To iterate over the extra arguments, you can use the expression `{...}`. If
the extra arguments can contain valid nils, then you need to do something
else. In Lua 5.2, you can use `table.pack`. This receives any number of
arguments, and returns a new table with all its arguments, just like
`{...}`. But it also adds an extra field `n`. That field is the total
number of arguments. Here's an example:

    function nonils(...)
      local args = table.pack(...)
      for i=1, args.n do
        if arg[i] == nil then return false end
      end
      return true
    end

When the extra arguments cannot be nil, `{...}` is cleaner and faster than
`table.pack`. Prefer it if you can.

### Named Arguments

Lua's argument passing is positional. Arguments match parameters in
function calls by positions. If you want to imitate named argument calling,
however, you can pack all the arguments into a table, and use the table as
the argument's sole parameter.

    function rename(arg)
      return os.rename(arg.old, arg.new)
    end

This sort of thing is useful when you have a function with many parameters,
and most of them are optional.
