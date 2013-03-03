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

## cons

The `cons` function creates cons cells. It takes two inputs; it returns
a pointer to a new cons cell whose `car` points to the first input and
whose `cdr` points to the second. `cons` stands for construct.

We can say, as a shorthand, that `cons` adds an item to the front of the
list. But internally, `cons` is more basic than this. Here is what `cons`
really does:

1. Create one new cons cell.
1. Make the new cons cell point to the head of the second input.
1. Return a pointer to the new cons cell.

Thus, in effect, `cons` returns a cons cell chain one longer than the
second input. But this is almost a side effect. `cons` itself doesn't know
anything about lists or the front of a list.

## cons and the empty list

If you `cons` something onto `nil`, you get a list of one element:

    (cons 'frob '())
    (cons 'frob nil) ;; Same as above

In printed notation, consing something onto `nil` is equivalent to throwing
an extra pair of parentheses around it.

    (cons '(phone home) nil) ; => ((phone home))

## Building nested lists with cons

If the first input to `cons` is a nonempty list, the result will be
a nested list. That is a list with more than one level of cons cells.

## cons can build lists from scratch

You can use successive `calls` to cons to build a list from scratch. Simply
`cons` the first item onto `nil` and the rest of the items onto the
resulting list of each last `cons` call.

## Symmetry of cons and car/cdr

Given a list x, if you know the `car` of x and the `cdr` of x, you can use
`cons` to work out the whole list.

More formally:

    x = (cons (car x) (cdr x))

But this only holds for nonempty lists. If the original x is `nil`, then
this doesn't work. (Can you see why? If you use `cons` on `nil` and `nil`,
you don't get `nil`. Instead you get `(nil)`.)

## List

It is common to want to take a bunch of inputs and make a new list from
them. Lisp provides `list` to do just that. It takes any number of inputs
and returns a new cons cell chain ending in `nil`. The new cell chain has
as many cells as there are inputs.

What `list` really does is create a new cons cell for each input. Then it
fills in the `car` pointers with references to the input values. Then it
fills in the `cdr` pointers to form a chain. Finally, `list` returns
a pointer to the first cell.

`cons` and `list` are very different. `cons` makes a single new cons cell.
`list` makes a new cons cell for each input. We can think of `list` as
expanding into a chain of calls to `cons`.

## Replacing the first element of a list

You can easily replace the first element of a list by `cons`-ing the new
item onto the `cdr` of the original list. This doesn't actually "create
a new list". Instead it simply creates a new cons cell with the new item
and return a pointer to that item. That item's `cdr` points to the *second*
item in the previous list. Hence it's all just simple pointer manipulation.

## (Advanced Topics) Unary Arithmetic with Lists

Lists can be used to do unary (base one) artithmetic. In a unary numeric
system, numbers are simply marks or tally symbols. One mark is one, two
marks is two, and so forth. Zero is no marks. (Negative numbers are ignored
for now.)

He proposes to use X as the tally symbol. Unary numbers can therefore be
written as lists of Xs.

+ 0 is NIL
+ 1 is (X)
+ 2 is (X X)
+ 3 is (X X X)

The function `REST` can be used to subtract 1 in unary, since `(REST
'(XXX))` would yield `(X X)`. (Note that this breaks down if you apply
`REST` to NIL. It returns simply NIL. Negative numbers are ignored for now.)

The function `LENGTH` converts unary numbers to regular integers.

## (Advanced Topics) Nonlist Cons Structures

A proper list is a cons cell chain ending in `NIL`. When you write or see
lists in parentheses notation, the convention dictates that you leave out
the final `NIL`. But it's there.

    * * ----------> * * ----------> * * ----------> NIL
    |               |               |
    |               |               |
    |               |               |
    A               B               C

However, there are cons cell structures that are not proper lists because
their chains don't end in `NIL`. For example:

    * * ----------> * * ----------> * * ----------> D
    |               |               |
    |               |               |
    |               |               |
    A               B               C

In parenthesis notation, these two lists are as follows:

    (A B C)
    (A B C . D)

If a list does not end in `NIL`, then Lisp prints a period (dot) before the
final, non-`NIL` element in the list. Such a list is called a 'dotted list'
as opposed to a proper list (which by definition ends in `NIL`).

You can produce a dotted pair using `cons`:

    (cons 'a 'b); => (a . b)
