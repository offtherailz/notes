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

## Chapter 8: Lambda the Ultimate

As the title suggests, Chapter 8 introduces higher-order functions:
functions that accept and return other functions as values.

They start with accepting a function as a value, using `rember-f` as an
example. `rember-f` is a function that receives three arguments:

+ A function with an equality test of some kind
+ An item to test for
+ A list to consider

The function `rember-f` then applies the test to all items in the list. The
return value is the original list minus anything that tests equal to the
item according to the given equality test. An example:

    (define rember-f
      (lambda (test? s l)
        (cond
          ((null? l) (quote ()))
          ((test? (car l) s) (cdr l))
          (else (cons (car l) (rember-f test? s (cdr l))))))))

    (rember-f = 5 '(4 5 6 7 6)) ; returns (4 6 7 6)

They then turn to returning a function as a value. Their example:

    (lambda (a)
      (lambda (x)
        (eq? x a)))

This is a function that accepts one argument, `a`, and returns the function,
`(lambda (x) (eq? x a))`.

They also mention that this is called "Currying", but the dreaded 'this'
problem pops up. It's not 100% clear to me what 'this' is here. So, to
clarify, the Currying is the process of taking a multi-argument function,
like `(eq? x a)`, and turning it into a series of functions, each of which
only receives exactly one argument. The wrapper function becomes
a single-use function for equality: you use it only to test if something is
`eq? a`.

Next they apply Currying to the rewrite of `rember-f`:

    (define rember-f
      (lambda (test?)
        (lambda (s l)
        (cond
          ((null? l) (quote ()))
          ((test? (car l) s) (cdr l))
          (else (cons (car l) ((rember-f test?) s (cdr l))))))))

Notice that nearly nothing changes. We make the first function a one
argument function, and we make its return value the inner `(lambda ...)`.
Other than that, we have to change the call to `rember-f` itself on the
last line, but that's it.

They then walk you through a sequence where you rewrite `insertL` as
`insertL-f` and `insertR` as `insertR-f`. In each case, you pass a `test?`
function the the outer function. The outer function applies the test and
then branches. If the test is true, it inserts an item to the left or
right. If the test is not true, it applies `cons (car l)` and the recurses
on the `(cdr l)`.

What they draw out of this is that the two functions differ *only in
a small area*, namely the what to do if the test is true. You can remove
this difference by abstracting away and passing a function in that does the
right `cons`. First they define two `seq` functions:

    (define seqL
      (lambda (new old l)
        (cons new (cons old l))))

    (define seqR
      (lambda (new old l)
        (cons old (cons new l))))

Note that when the functions are actually called `l` will not be the whole
outer list but rather `cdr l` of that larger list. But inside the
abstracted function, we don't need to care about that.

Once we have the two sequences, we can easily write a wrapper function that
accepts any sequence function as its one argument:

    (define insert-g
      (lambda (seq)
        (lambda (new old l)
          (cond
            ((null? l) (quote ()))
            ((eq? (car l) old) (seq new old (cdr l)))
            (else (cons (car l) ((insert-g seq) new old (cdr l))))))))

They reveal a nice side-effect while creating a `seq` function for `rember`
(removing an old item when it's found). If you have a function that doesn't
use of the arguments of a wrapper function, you can just pass `#f` there as
a placeholder.

    (define seqRem
      (lambda (new old l)
        l))

    (define rember
      (lambda (a l)
        (insert-g seqRem) #f a l))

All of this leads them to define The Ninth Commandment:

> Abstract common patterns with a new function.

The function `multirember&co` leads into collectors (a.k.a. continuations).
In such a function, as the recursion occurs values are accumulated in two
further lists, one for values that pass a test and one for values that fail
the test. This allows you to do things like remove all odd numbers from
a list and count how many evens (or odds) you have at the end.

    (define multirember&co
      (lambda (a lat k)
        (cond
          ((null? lat) (k (quote ()) (quote())))
          ((eq? (car lat) a)
           (multirember&co a (cdr lat)
                           (lambda (newlat seen)
                             (k newlat
                                  (cons (car lat) seen)))))
          (else
            (multirember&co a (cdr lat)
                            (lambda (newlat seen)
                              (k (cons (car lat) newlat) seen)))))))

The third parameter `col` is the collection or continuation function. The
trick is that each time recursion occurs, in either branch of the `cond`,
`col` is passed as well.

I'm having a very hard time following this, so let's try to walk through
a simple example.

+ a will be `'foo`, lat will be `'(foo b b)` and col will be `(lambda (x, y)
  length y)`

+ First call to `multirember&co` (original call)
    + 'a = 'foo
    + lat = '(foo b b)
    + k = k
        + Step one: is the list (foo b b) null? - #f
        + Step two: is the car of lat eq? to foo? - #t
+ Second call to `multirember&co` (from the `eq?` branch)
    + 'a = 'foo
    + lat = '(b b)
    + k = k-wrapped-once
        + Step one: is the list (b b) null? - #f
        + Step two: is the car of lat eq? to foo? - #f
+ Third call to `multirember&co` (from the `else` branch)
    + 'a = 'foo
    + lat = '(b)
    + k = k-wrapped-twice
        + Step one: is the list (b) null? - #f
        + Step two: is the car of lat eq? to foo? - #f
+ Fourth call to `multirember&co` (from the `else` branch)
    + 'a = 'foo
    + lat = '()
    + k = k-wrapped-thrice (!)
        + Step one: is the list () null? - #t
        + Step two: we've bottomed out: call k-wrapped-thrice and feed it
          two empty lists as its arguments.

So, this description is good, but the last part of the puzzle is what do
the various `k-wrapped` functions look like?

Here's the original `k` again:

    (lambda (x y) length y)

Here's `k-wrapped-once`:

    (lambda (newlat seen) (k newlat (cons 'foo seen))

Now we get the point of my naming scheme `k-wrapped-*`. The continuations
under `eq?` or `else` *wrap* the previous `k` in another lambda function.

Continuing, here's `k-wrapped-twice`:

    (lambda (newlat seen) (k-wrapped-once (cons 'b newlat) seen))

Finally, here's `k-wrapped-thrice`:

    (lambda (newlat seen) (k-wrapped-twice (cons 'b newlat) seen))

When we finally call `k-wrapped-thrice` -- because the original `lat` has
been emptied out -- the arguments for `newlat` and `seen` are empty lists.
That way, as the wrapped functions unwind, the items collected from
previous calls are `cons`-ed onto first the empty list and then onto
whatever lists are passed up in turn. So in this way, the wrapper functions
serve as the equivalent of accumlator arrays in a language like C or Ruby.
That helps to explain why Friedman and Felleisen call these collector
functions. (Continuation makes sense too, since these functions continue
the processing of the values passed along by the outermost function.)

Oh, and I forgot to mention: when we finally reach the call to the original
`k`, the second parameter will be `'(b b)`. So the ultimate return value of
my example will be the boring 2. :)

In addition to reading and re-reading *The Little Schemer*, the following
links helped me a great deal.

+ [Stackoverflow post 1](http://stackoverflow.com/q/7004636/26702)
+ [Stackoverflow post 2](http://stackoverflow.com/q/10692449/26702)
+ [Stackoverflow post 3](http://stackoverflow.com/q/10499514/26702)
+ [Unpacking multirember&co from TLS](http://www.michaelharrison.ws/weblog/?p=34)
