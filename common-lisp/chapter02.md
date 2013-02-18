# Chapter 2: Lists

## Combinations of car and cdr

+ On its own `car` gets the initial element of a list
+ On its own `cdr` gets the rest of a list (i.e. everything but the `car`)

You can create combinations of `car` and `cdr` at will, up to four letters
deep. Here is how they work:

+ You can always write the same thing with explicit `car` and `cdr`
  combinations, but it's longer.
+ An example:

        (cadr '(fee fie foe fum)); => fie, the car of the cdr
        (car (cdr '(fee fie foe fum))); => Same thing, but more writing

+ Note that the order of operations is the reverse of what you write. That
  is, we write (and pronounce) them "left to right", but the order of
  operations is "right to left" as we work though the nested parentheses of
  the longer version.
+ As I said above, Common Lisp provides built-in versions of all
  combinations of `car` and `cdr` up to four As and Ds deep. It also
  provides built-in definitions of `first` through `tenth` if you prefer
  that version.

## car and cdr of nested lists

Imagine you have this list `((blue cube) (red pyramid))`, and you want to
get at `pyramid`, but you can't immediately see how to write a combination
of `car` and `cdr` to do it. Here's a way to do it:

+ `c?dr   => ((red pyramid))`
+ `c?adr  => (red pyramid)`
+ `c?dadr => (pyramid)`
+ `cadadr => pyramid`

In effect, you build up the combination backwards. Again, this makes sense
because backwards means 'according to the order of operations'.

Now an exercise. Write down tables to get at each element in this nested
list: `(((fun)) (in the) (sun))`.

+ To get at `fun`:
    + `c?ar   => ((fun))`
    + `c?aar  => (fun)`
    + `caaar  => fun`
+ To get at `in`:
    + `c?dr   => ((in the) (sun))`
    + `c?adr  => (in the)`
    + `caadr  => in`
+ To get at `the`:
    + `c?dr   => ((in the) (sun))`
    + `c?adr  => (in the)`
    + `c?dadr => (the)`
    + `cadadr => the`
+ To get at `the`:
    + `c?dr   => ((in the) (sun))`
    + `c?ddr  => ((sun))`
    + `c?addr => (sun)`
    + `caaddr => sun`

## car and cdr of nil

The `car` and `cdr` of `nil` are `nil`. In other Lisp dialects, if you try
to take the `car` or `cdr` of `nil` or the empty list, you get an error.
But Common Lisp simply has it return `nil`. I can imagine this is useful
for recursion.

Since `first`, `second` and so on are defined in terms of `car` and `cdr`,
they exhibit the same behavior. They return `nil` when used on an empty
list.

In addition, the `cdr` of a one-item list is `nil` as well.
