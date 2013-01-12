# Programming in Lua 3rd Edition

## Chapter 7 Iterators and the Generic for

An iterator is any construction that makes it possible to travel over the
items in a collection in a regular way. (That is, it guarantees that you
hit every item or go in a specific order - if that's relevant, or stop when
the items have all been seen.) In Lua, functions normally represent
iterators. You call the function successively to retrieve item after item.

### Iterators and Closures

An iterator has to keep track of some information. It must know where it is
and where to go next. It also needs to know when to stop. Closures provide
a straightforward way to maintain this information. Closures hold onto
local variables from an enclosing environment. These variables can maintain
the state that the iterator needs. To create a closure, remember that you
must create the non-local variables. This means that a closure construction
normally involves two functions: the closure itself and a factory function
that produces the closure and initializes the non-local variables in
a reasonable way.

As an example, here's a simple iterator for a list. It's similar to the
builtin `ipairs`, except that it returns only values, not index positions:

    function values(t)
      local i = 0
      return function () i = i + 1; return t[i] end
    end

The function `values` here is the factory. It returns an inner function
which is the actual iterator. After the last element of the list, the
iterator will return `nil`. This is a good enough way to signal that the
iteration is over.

    t = {10, 20, 30}
    iter = values(t)
    while true do
      local element = iter()
      if element == nil then break end
      print(element)
    end

This shows how to use such an iterator manually. As you can see, it's clear
and simple, but a little verbose. That is you have to do a lot explicitly:

+ You must set up the iterator function.
+ You must create an endless loop.
+ You must call `iter` over and over and assign the return value to a local
  variable.
+ You must test that return value to see if it's `nil`.
+ You must manually break the endless loop, if the value is `nil`.

But luckily for us the generic `for` takes care of most of this by itself:

    t = {10, 20, 30}
    for element in values(t) do
      print(element)
    end

+ It maintains the iterator internally.
+ It keeps the variable declared in the top line local.
+ It calls the iterator for each new iteration.
+ It stops the loop when the iterator returns `nil`.

### The Semantics of the Generic for

The previous iterators cost you a new closure for each new loop. This is
usually fine, but in some cases, you might want less. If so, you may be
able to use the generic `for` itself to maintain much of the state you
need.

The generic `for` maintains three values for the life of the iteration:

+ The iterator function
+ An invariant state
+ A control variable

The full syntax for the generic `for` is as follows:

    for <var-list> in <exp-list> do
      <body>
    end

The `var-list` is one or more variable names, separated by commas, and
`exp-list` is one or more expressions, also separated by commas. Often the
expression list has only one element, namely a call to an iterator factory.
For example:

    for k, v in pairs(t) do print(k, v) end

Often the list of variables also has only one item. For example:

    for line in io.lines() do io.write(line, '\n') end

The first variable in the list is special: it is the 'control variable'. It
will never be `nil` during the loop. When the control variable is `nil`,
the loop ends.

To begin with, the `for` evaluates the expressions after `in`. These should
produce the three values neded by the `for` loop: the iterator function,
invariant state and control variable. As in a multiple assignment, only the
last (or only) element of the list can result in multiple values. And its
return values are adjusted to three. Anything extra is discarded; anything
missing is filled in with `nil`. (When using simple iterators, the factory
returns only the iterator function. The invariant state and control
variable start as `nil`.)

After initialization, the `for` begins to call the iterator function with
two arguments: the invariant state and the control variable. The `for` does
not care at all about the invariant state. But it passes that value from
the initialization step to the calls to the iterator function. This is how
we can sneak state in and create "stateless" iterators. The iterator
function should return values which the `for` loop can assign to the
variables in the var-list of the `for`. If the first value returned (the
control variable) is `nil`, the loop ends. Otherwise, the `for` executes
its body and then calls the iteration function again.

To spell this out in code, the following two are equivalent:

    for var_1, ..., var_n in <exp-list> do <block> end

    do
      local _iterator_function, _invariant_state, _control_var = <explist>
      while true do
        local var_1, ..., var_n = _iterator_function(_invariant_state,
                                                     _control_var)
        _var = var_1
        if _var == nil then break end
        <block>
      end
    end

### Stateless Iterators

A stateless iterator doesn't keep any state of its own. This means that you
can reuse it in multiple loops without having to create new closures for
each one. An example is `ipairs`. If we wrote it in Lua, it might look like
this:

    local function iter(a, i)
      i = i + 1
      local v = a[i]
      if v then
        return i, v
      end
    end

    function ipairs(a)
      return iter, a, 0
    end

When the `for` loop initializes, it gets three values: the `iter` function
as iterator, `a` as invariant state and zero for the initial value of the
control variable. Then the `for` calls `iter(a, 0)` which results in `1,
a[1]` -- assuming `a[1]` is not `nil`. This continues until the first `nil`
element in `a`.

A similar stateless iterator is `pairs`. It uses `next` which is
a primitive function in Lua. `next(t, key)` where `key` is a key in the
table `t` returns a next key-value pair (as two values). You kick it off
with `next(t, nil)` which returns a first pair. When there are no more
pairs to return, `next` returns `nil`. You can actually use `next` directly
without involving `pairs` in order to iterate over a hash-like table in
Lua:

    for k, v in next, t do
      <loop body>
    end

In any case, here's how you could write `next` in Lua:

    function pairs(t)
      return next, t, nil
    end

### Iterators with Complex State

Sometimes you need more state than would fit into two variables (invariant
state and control variable). The easy way is to use closures. As an
alternative, though, you could put all the state the iterator needs into
a table and then use that table as the invariant state for the iteration.
(Also, the table itself remains invariant even if you change the values
stored in it. That allows you to do useful work with the table while still
having a true invariant item.) An iterator that uses a table this way tends
to ignore the second variable provided by the generic `for` -- the iterator
variable -- because it has everything it needs in the invariant state.

Here's an example of an iterator that grabs all words from a file:

    local iterator -- forward declaration

    function allwords()
      local state = {line = io.read(), pos = 1}
      return iterator, state
    end

    function iterator(state)
      while state.line do
        local s, e = string.find(state.line, "%w+", state.pos)
        if s then
          state.pos = e + 1
          return string.sub(state.line, s, e)
        else
          state.line = io.read()
          state.pos = 1
        end
      end
      return nil
    end

Ierusalimschy recommends you prefer iterators in the following order:

+ Stateless: keep all state in the two `for` variables
+ Closures
+ Tables (? he really doesn't seem to recommend this at all)
+ Coroutines --- most powerful, but a little more expensive

### True Iterators

So far all of our iterators do not iterate. The `for` loop actually
iterators. Our iterators are actually generators: they generate values and
eventually emit `nil` when out of items.

However, it is possible to build true iterators in Lua. In such a case, you
don't use a loop. You just call the iterator with an argument that says
what the iterator should do each iteration (i.e. a block argument as in
Ruby). In Lua, this would mean feeding the (true) iterator a callback
function to call inside the loop. Here's the `allwords` iterator again, in
this style:

    function allwords(callback)
      for line in io.lines() do
        for word in string.gmatch(line, "%w+") do
          callback(word)
        end
      end
    end

    -- An example call of allwords(callback):
    allwords(print)

    -- An example using an anonymous function as the callback:
    local count = 0
    allwords(function (w)
      if w == 'hello' then count = count + 1 end
    end)
    print(count)

    -- Here's that in the previous table/closure style:
    local count = 0
    for w in allwords() do
      if w == 'hello' then count = count + 1 end
    end
    print(count)

In earlier versions of Lua, true iterators were popular, since the language
lacked the `for` construct. How do they compare now? They have about the
same overhead: one function call per iteration. The true iterator is easier
to write (coroutines can get us this ease as well). But the generator style
is more flexible. (Imagine iterating over two files, for example.) Also,
the generator style allows you to use `break` and `return` inside the
iterator's body. With a true iterator, the `return` would return from the
callback function, not from the function doing the iteration. Overall
Ierusalimschy prefers generators.
