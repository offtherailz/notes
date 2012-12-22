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
