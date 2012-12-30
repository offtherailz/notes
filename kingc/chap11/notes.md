# Chapter 11 - Pointers

In most computers, main memory is divided into 8-bit bytes. Each byte has
a unique address. A executable contains code (machine instructions which
correspond to statements in the C program) and data (variables in the
original C program). Each variable occupies one or more bytes of memory. If
a variable occupies more than one byte of memory, the address of the first
byte is said to be its address.

A pointer variable is a variable designed to hold one of those memory
addresses. So if `p` is a pointer and `i` is an integer variable, we can
create and connect those two as follows:

    int i;
    int *p;
    i = 0;
    p = &i;

Here we see two new operators at work:

+ The address operator: `&`
+ The indirection operator: `*`

The indirection operator is used when declaring pointers. A pointer
declaration must also include a type. A pointer to an int and a pointer to
a double would be declared differently.

    int *int_ptr;
    double *double_ptr;

Pointer variables can be declared along with other variables in one line:

    int i, j, a[10], *p, *q;

That line declares two ordinary int variables, an array of 10 ints, and two
pointers to int.

After declaring a pointer variable, we must initialize it. Otherwise it
points to nothing in particular. This is where the address operator comes
into play:

    int i, *p;
    i = 0;
    p = &i;

You can also initialize a pointer variable at the same time that you
declare it:

    int i;
    int *p = &i;
    /* Even more briefly... */
    int i, *p = &i;

## Relationship of `*` and `&`

The two operators are inverse. Apply `&` to a variable, and you get
a pointer to the variable; `&` returns the address of the variable. Apply
`*` to a pointer gets you back to the original variable; `*` returns the
value of the variable.

## `*` has many meanings and uses

The indirection operator shows up in pointer declarations, but not just
there. Once you've declared a pointer and connected it to an address (using
`&`), you can use `*` in other ways.

On the one hand, `*` returns the value of the variable - say for assignment
to something else:

    int i, j, *p;
    i = 4;
    p = &i;
    j = *p - 1; /* j is now 3. */

In addition, you can use `*p` as an lvalue:

    *p = 3; /* Now i itself is 3. */

## Caution!

Never apply the indirection operator on a pointer that isn't initialized
(that you haven't explicitly set to some address). It causes undefined
behavior.

    int j, *p;

    j = *p; /* Bad, very very bad */

## Pointer to pointer assignment

You can use the assignment operator to copy pointers, if they have the same
type.

    int i, *p, *q;
    p = &i; /* One way to assign a value to a pointer. */
    q = p;  /* Another way to assign a value to a pointer. */

Notice that in the second assignment, we use neither the address operator
nor the indirection operator. That makes sense because we are assigning
*the pointer itself* to another pointer. We don't need the address
operator, because that's for getting the address of a variable. Here we
don't want to assign the address *of p* to q. We also don't need the
indirection operator because that's for getting the value of the address
that a pointer references. But here we don't want to assign the value *p
points to* to q.

Don't confuse the following:

    /* Pointer assignment */
    q = p;

    /* Assigning the value in p's address to q's address */
    *q = *p;

## Pointers as function arguments

Pointers have many uses, but one thing they are good for is imitating
call-by-reference semantics. Normally, when you call a function in C, the
variables are called by value. That means you get a copy of the variable's
value inside the function. Anything you do to the variable in the function
does not affect the calling context's variable. This is often a good thing
(it protects us from unexpected changes), but sometimes we want to directly
affect some variable. In such a case, we can use pointers.

To use pointers as function arguments, we must do two things. First,
declare the function to expect pointer arguments. Second, pass in a pointer
not a regular variable when calling the function. An example follows:

    /* The declaration... */
    void decompose(double x, long *int_part, double *frac_part);
    /* Later */
    long i;
    double d;

    /* The call... */
    decompose(3.14159, &i, &d);

    /* The definition of decompose... */
    void decompose(double x, long *int_part, double *frac_part)
    {
        *int_part = (long) x;
        *frac_part = x - *int_part;
    }

Notice that we use `&` in the call to `decompose` and `*` both in the
declaration of the function and inside the function.

Note that "needing a pointer" doesn't necessarily imply that you will need
(or use) `&`. Example:

    int i, *p;
    p = &i;
    scanf("%d", p);

The last line is perfectly valid. `scanf` needs a pointer, and it gets one.
Since `p` contains the address of `i`, we use it directly. In fact, if we
used `&p`, it would mean something very different. It would mean "the
address of the pointer p". But that's not what we want at all, in this
case.

## Using `const` to protect arguments

Often a function that takes pointers as arguments will modify those
variables, but not always. If you want to define a function that accepts
pointer arguments, but *does not want* to modify the related variables, you
can use `const`:

    void f(const int *p);

The compiler will then detect any attempt to alter `*p` inside the
function.

## Pointers as return values

In addition to using pointers as function parameters, you can return
a pointer from a function.

    int *max(int *a, int *b)
    {
        if (*a > *b)
            return a;
        else
            return b;
    }

    int *p, i, j;
    ...
    p = max(&i, &j);

Take a good look at that. Make sure you're clear about when and why you use
`*a`, `&a` or `a` (for whatever variable - not just 'a').

Be careful never to return a pointer to a variable that has gone out of
scope:

    int *f(void)
    {
        int i;
        ...
        return &i;
        /* Boom. i won't exist when f returns. */
        /* So this pointer is broken. */
    }

## A note about `*`

The `*` symbol has two distinct jobs in relation to pointers. In
a declaration, the `*` simply indicates that the item is *a pointer* to
whatever type. It is **not** the indirection operator in a declaration.
Otherwise, it is the indirection operator. In that use, it returns the
value that the pointer refers to.

    int *p; /* Declaration: * is not the indirection operator. */
    *p = 4; /* Statement: * is the indirection operator. */
    j = *p; /* Statement: * is the indirection operator. */
