# Programming in Lua 3rd edition

## Chapter 6 More about Functions

Last chapter was the introduction to functions in Lua. This chapter is the
more advanced material. Functions in Lua are first-class values with proper
lexical scoping.

First-class values: A Lua function is a value with the same rights as more
everyday values like numbers or strings. You can store functions in
variables (both global and local); you can store functions in tables; you
can pass functions to functions as arguments; and you can return functions
as return values from functions.

Lexical scoping: Functions can access variables of their enclosing
functions. Lua properly contains the lambda calculus. It supports proper
closures.

Lua functions, like all other values, are anonymous. They do not have
names. A function name like 'print' is merely a variable that holds the
function. You can manipulate these variables like any other variables.

The normal syntax to create functions is actually syntactic sugar:

    function foo(x) return x*2 end
    -- Really that's this
    foo = function(x) return x*2 end

A function definition is actually a statement (an assignment to be
specific). You can consider `function (x) body end` to be a constructor,
like `{}` is a table constructor. You generally give a function a name, but
you don't have to. You can use them anonymously.

A common example is `table.sort`. This function accepts a table as an
argument and a function as an optional argument. The function tells
`table.sort` *how* to sort the given table. The sort function will receive
two arguments, and it must return whether the first is greater than the
second. This allows you to sort tables in any way you can describe in
a function. An example:

    network = {
      {name = "grauna", IP = "210.26.30.24"},
      {name = "arraial", IP = "210.26.30.23"),
      {name = "lua", IP = "210.26.30.25"}}
    }

    table.sort(network, function(a,b) return (a.name > b.name) end)

A function that accepts another function as an argument is a higher-order
function.

### Closures

A function enclosed in another function has full access to the local
variables from the enclosing function. This is lexical scoping. This sounds
obvious, but many languages do not support it.

    names = {"Peter", "Paul", "Mary"}
    grades = {Mary = 10, Paul = 7, Peter = 8}
    table.sort(names, function(name1, name2)
      return grades[name1] > grades[name2]
    end)

    function sortbygrades(names, grades)
      table.sort(names, function(name1, name2)
        return grades[name1] > grades[name2]
      end)
    end

In the second function, notice that the inner, anonymous function accesses
the parameter `grades` which is local to the enclosing function. Inside the
anonymous function, `grades` is neither a global nor a local variable. The
term used in Lua now is 'non-local variable'. (An older name is 'upvalue'.)

Why is this such a big deal? Since functions are first-class values, they
can escape the original scope of their variables.

    function newCounter()
      local i = 0
      return function()
               i = i + 1
               return i
             end
    end

    c1 = newCounter()
    print(c1()) -- 1
    print(c1()) -- 2

    c2 = newCounter()
    print(c2()) -- 1
    print(c1()) -- 3
    print(c2()) -- 2

`c1` and `c2` are distinct closures over the same function. Each contains
its own, independent version of `i`. (The author points out that the actual
value in Lua is the closure, not the function. He describes the function as
a 'prototype for closures'. I'm not 100% sure what this means, frankly.)

Closures are useful in many contexts. First, you can pass them as arguments
to higher-order functions. Second, you can use them to write functions that
create functions, like `newCounter`. Closures are also useful for
callbacks.

Another valuable use for closures is that they allow you to redefine
functions in Lua easily, even predefined ones from the environment. You
often need to keep the original function and only tweak it slightly. This
is easy in Lua:

    oldSin = math.sin
    math.sin = function(x)
      return oldSin(x*math.pi/180)
    end
    -- more cleanly
    do
      local oldSin = math.sin
      local k = math.pi/180
      math.sin = function(x)
        return oldSin(x*k)
      end
    end

The old version is now in a *private* variable. The only way to access it
is through the new version. This technique makes it very easy to create
secure environments, a.k.a 'sandboxes'. He gives an example of hiding
`io.open` in cases where the program might run external code fed to us by
users.

### Non-Global Functions

Since functions are first-class values, we can store them in local as well
as global variables.

First, we can store them in table fields. Most Lua libraries use this as
a way to package the code they provide:

    Lib = {}
    Lib.foo = function(x, y) return x+y end
    Lib.goo = function(x, y) return x-y end

There are two other ways you can do this:

    Lib = {
        foo = function(x, y) return x+y end
        goo = function(x, y) return x-y end
    }

    Lib = {}
    function Lib.foo(x, y) return x+y end
    function Lib.goo(x, y) return x-y end

When you store a function in a local variable, you get a local function.
The function is restricted in scope. This is very useful for modules, since
it allows you to have private helper functions that you don't export (and
that the user cannot reach directly, even if she knows the name of the
function).

Lua provides the following as sugar for `local function = ...`:

    local function f(params)
      body
    end

In order to ensure that this works out for recursive functions, this
expands to the following:

    local f -- forward declaration
    f(params)
      body
    end

This way, you can call `f` from within `f`. However, this will not work if
you have indirectly recursive functions. In that case, you must give
explicit forward declarations:

    local f, g
    function g()
      whatever
      f()
      whatever
    end
    function f()
      whatever
      g()
      whatever
    end

Make sure not to write `local function` before `f` or `g` later. Otherwise,
Lua will create a new local variable, and the global one will remain
undefined.

### Proper tail calls

Lua does tail-call elimination. A tail call is a goto  in the form of
a call. A tail call happens when a function calls another as its last
action, so that the calling function has nothing else to do. For example:

    function f(x) return g(x) end

After `f` calls `g`, it has nothing further to do. That means there's no
need to return to `f` when `g` ends. That in turn means that the program
doesn't need to keep any information about `f` in the stack. After `g`
returns, control can leap immediately to the point after `f` was called. If
a language takes advantage of this and doesn't use any extra stack space
when using a tail call, we say that language does tail-call elimination.
Lua does it.

Because tail calls use no stack space, the number of nested tail calls that
a program can make is unlimited. For example:

    function foo(n) if n > 0 then return foo(n-1) end end

This program will never overflow the stack, no matter the value of `n`.

Some things that might look like a potential for tail-call elimination are
not. All the following fail:

    function f(x) g(x) end -- Missing 'return'; f must discard results of g
    -- also bad
    return g(x) + 1 -- Must do the addition
    return x or g(x) -- Must adjust to one result
    return (g(x)) -- Must adjust to one result

In Lua, only a call with this form is a tail call:

    return func(args)

However, both `func` and its arguments can be complex expressions. Lua
evaluates them once, before the call and then does elimination. The
following *is* a tail call:

    return x[i].foo(x[j] + a*b, i+j)
