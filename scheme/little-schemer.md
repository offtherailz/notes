# The Little Schemer

## Preface

> The goal of this book is to teach the reader to think recursively.

> Perhaps the best programming language to teach recursion is Scheme.

> there is a direct correspondence between the structure of Scheme programs
> and the data those programs manipulate.

## Chapter 1: Toys

An atom is a string of characters (letters, digits, special characters).
Some samples:

    atom
    1492
    *abc$

You can quote an atom with `quote atom` or `'atom`.

A list is a collection of S-expressions enclosed by parentheses or the null
list. The null list is special.

    ()
    (atom)
    (atom or turkey)
    ((atom or) turkey)

Since lists are themselves S-expressions, lists can have sub-lists.

The `car` of a list is the first item in the list. Note: The primitive `car`
is defined only for non-empty lists. The return value of `car` is a single
S-expression.

The `cdr` of a list is its tail, i.e. everything but its first item. The
`cdr` of a one-item list is the empty list. The return value of `cdr` is
a list.

The `cons` operation adds an S-expression to the front of a list. The
second argument to `cons` must be a list. The result of `cons` is a list.

The primitive `null?` returns true for the empty list and false for all
other lists. `null?` can only be called on lists.

The function `atom?` takes one argument -- any S-expression -- and it returns
true or false. True if the argument is an atom, and false otherwise. Scheme
itself lacks `atom?` so they define it as follows:

    (define atom?
        (lambda (x)
            (and (not (pair? x)) (not (null? x)))))

The function `eq?` takes two arguments, both of which must be non-numeric
atoms, and it returns whether they are the same or not. (Actually the notes
suggest that lists or numbers may be arguments to `eq?`, but no details
yet.)

## Chapter 2: Do It, Do It Again, and Again, and Again...

To walk us through recursion, the authors define two new functions, `lat?`
and `member?`. The first returns true if a list is a list of atoms. The
second returns true if a given atom is a member of a given list.

    (define lat?
      (lambda (l)
        (cond
          ((null? l) #t)
          ((atom? (car l)) (lat? (cdr l)))
          (else #f))))

They recommend that all functions that accept an argument of a list use
`null? list` as the base case. Here they check the `car` of each sublist to
see if it's an atom. Then they call `lat?` itself again on the `cdr` of the
same sub-list. If any `car` is not an atom, the function returns false.
Otherwise, we reach the base case -- the null list -- and return true.

    (define member?
      (lambda (a lat)
        (cond
          ((null? lat) #f)
          (else (or (eq? (car lat) a)
                    (member? a (cdr lat)))))))

First check if `lat` is empty. If it is then `a` is not a member (trivially).
Otherwise, check if the `car` of `lat` is `a` or whether `a` is a member of
the `cdr` of `lat`. So we keep trying the first item and then recursing on
the tail until we hit the empty list.

## Chapter 3: Cons the Magnificent

They walk through creating the function `rember`. The function takes two
arguments, an atom and a list. It removes the first instance of the atom
(if found) and returns the rest of the list.

+ Test for the empty list. If the list is empty, return an empty list.
+ Check if the `car` of the list (which we now know is not empty) is equal
  to the atom.
    + Use `cond` to ask questions about the list. The syntax is this:
        (cond
            (predicate return-value)
            (predicate return-value)...)
    + Use `eq?` to test the equality of atoms.
    + If `car lat` is equal to the given atom, then return `cdr lat`.
    + If `car lat` is not equal to the atom, then call `rember a` on the
      `cdr` of the original list.

> The First Commandment: (preliminary) Always ask `null?` as the first
> question in expressing any function (over lists, I'm assuming).

They then switch to multi versions of functions. The trick to
a multi-remove or a multi-replace, is that you need to add the result of
the first operation to the recursion. To to this, they introduce The Second
Commandment:

> Use `cons` to build lists.

Then while building up a function `firsts` -- which returns the first item
from a series of lists -- they introduce The Third Commandment:

> When building a list, describe the first typical element, and then `cons`
> it onto the natural recursion.

Example for `firsts`

    (firsts '((a b) (c d) (e f))) ; result is (a c e)

+ The typical element is `a`, `c` or `e`. That is, `(car (car l))`
+ Take that and `cons` it onto the natural recursion as so:

        (cons (car (car l)) (firsts (car l)))
              ^^^^^^^^^^^^^ ^^^^^^^^^^^^^^^^
              Typical elem  Natural recursion

Finally, while introducing `multiinsertL`, they introduce The Fourth
Commandment:

> Always change at least one argument while recurring. It must be changed
> to be closer to termination. The changing argument must be tested in the
> termination condition: when using `cdr`, test termination with `null?`.

## Chapter 4: Numbers Games

We move from textual atoms to numbers now. Numbers are still atoms.
Negative numbers and floats are also atoms, but the book considers only
nonnegative integers.

They immediately introduce two new functions -- `add1` and `sub1`.

    (define add1
      (lambda (n)
        (+ n 1)))

    (define sub1
        (lambda (n)
          (- n 1)))

We need to add these to Scheme. They also introduce `zero?` which is built
in.

Using these three as primitives, they want us to define a function `o+`.
Here it is now:

    (define o+
      (lambda (x y)
        (cond
          ((zero? x) y)
          (else (add1 (o+ y (sub1 x)))))))

They point out that `zero?` takes the place of `null?` as the base case,
and that `add1` takes the place of `cons`. `cons` builds lists, and `add1`
builds numbers, as they put it.

Next is `o-` which defines subtraction in terms of `zero?` and `sub1`.


    (define o-
      (lambda (x y)
        (cond
          ((zero? y) x)
          (else (sub1 (o- x (sub1 y)))))))

They next introduce tuples. A tuple is a list of numbers, e.g. `(1 2 3)`.
The next job is to build a function `addtup` that adds all those numbers.

+ Use `o+` instead of `cons` to build up the final reasult.
+ The terminal condition when building lists returns `()`. The terminal
  condition here -- when building a number -- should return 0.
+ The natural terminal condition is `null? tup`. That's the same as working
  on lists, since we are removing one item at a time (using `car`) and then
  recursing over the `cdr` of the tuple.
+ Just as `cons` builds lists, `addtup` builds a number by totaling all the
  numbers in a tuple.

This leads them to revise The First Commandment:

> When recurring on a list of atoms, `lat`, ask two questions about it:
> `(null? lat)` and else.
> When recurring on a number, `n`, ask two questions about it: `(zero? n)`
> and else.

Here is `addtup`:

    (define addtup
      (lambda (tup)
        (cond
          ((null? tup) 0)
          (else (o+ (car tup) (addtup (cdr tup)))))))


In the process of writing `o*`, a multiplication function for two numbers,
they also revise The Fourth Commandment:

> Always change at least one argument while recurring. It must be changed
> to be closer to termination. The changing argument must be tested in the
> termination condition: when using `cdr`, test termination with `null?`
> and when using `sub1`, test termination with `zero?`

Here is `o*`:

    (define o*
      (lambda (x y)
        (cond
          ((zero? y) 0)
          (else (o+ x (o* x (sub1 y)))))))

After introducing the multiplication function, they introduce The Fifth
Commandment:

> When building a value with +, always use 0 for the value of the
> terminating line, for adding 0 does not change the value of an addition.
>
> When building a value with *, always use 1 for the value of the
> terminating line, for multiplying by 1 does not change the value of
> a multiplication.
>
> When building a value with `cons`, always consider () for the value of
> the terminating line.

## Chapter 5: *Oh My Gawd*: It's Full of Stars

They now introduce functions that work on lists of atoms or lits with
arbitrarily-nested sub-lists as well. The first trick here is to check if
the `car` is an atom (using `atom?`). If it's not recurse down the `car`
itself until we hit an atom. All else is like the last chapter.

The first example is a function to remove an item wherever it appears in
a list or sub-lists:

    (define rember*
      (lambda (a lat)
        (cond
          ((null? lat) (quote ()))
          ((atom? (car lat))
                  (cond
                    ((eq? a (car lat))
                     (rember* a (cdr lat)))
                    (else (cons (car lat)
                                (rember* a (cdr lat))))))
          (else (cons (rember* a (car lat))
                      (rember* a (cdr lat)))))))

They then go through the similar `insertR*` which inserts some atom to the
right of another atom in arbitrarily nested S-expressions. That leads to
the final version of The First Commandment:

> When recurring on a list of atoms, `lat`, ask two questions about it:
> `(null? lat)` and else.
> When recurring on a number, `n`, ask two questions about it: `(zero? n)`
> and else.
> When recurring on a list of S-expressions, `l`, ask three questions about
> it: `(null? l)`, `(atom? (car l))`, and else.

After talking over what makes `*` functions special (they recur on the
`car` and the `cdr` of a list, and they ask three questions), the authors
revise The Fourth Commandment for the last time as well.

> Always change at least one argument while recurring. When recurring on
> a list of atoms, `lat`, use `(cdr lat)`. When recurring on a number, `n`,
> use `(sub1 n)`. And when recurring on a list of S-expressions, `l`, use
> `(car l)` and `(cdr l)` if neither `(null? l)` nor `(atom? (car l))` are
> true.
>
> It must be changed to be closer to termination. The changing argument
> must be tested in the termination condition:
>
> when using `cdr`, test termination with `null?` and
> when using `sub1`, test termination with `zero?`.

In the course of writing and rewriting a number of equality-testing
functions, the authors post The Sixth Commandment:

> Simplify only after the function is correct.

### Equality?

At this point, we have written three functions to test equality, and we're
using two more that are primitives. Let's take a look and review.

+ Built-ins
    + = x y       ; Compares two numerical values
    + eq? x y     ; Compares pointers not values
    + eqv? x y    ; Compares identity of objects
    + equal? x y  ; Compares values and can handle lists, atoms, chars, etc.
+ Ours
    + eqan? x y   ; Compares two items, atoms or numbers They use eq? or =.
                    I'm not sure why they don't just use equal?
    + eqlist? x y ; Compares two lists
    + my-equal x y; Compares two of anything using eqan? and eqlist?

## Chapter 6: Shadows

While discussing a function `value`, they introduce The Seventh
Commandment:

> Recur on the subparts that are of the same nature:
>    * On the sublists in a list.
>    * On the subexpressions of an arithmetic expression.

Then soon after, they introduce The Eighth Commandment:

> Use help functions to abstract from representations.
