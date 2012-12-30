# Chapter 12 - Pointers and Arrays

When a pointer refers to array elements, C can perform arithmetic (addition
and subtraction) on the pointers. This means that you can process an array
without using array subscripts - just through the use of pointers. In
addition, it turns out that arrays and pointers have a lot in common
already.

**NB**: One reason to suggest pointers over array subscripting is no longer
relevant. Pointers are *not* necessarily more efficient when using modern
compilers.

## Arrays and Pointers - Basics

You can make a pointer refer to an item in an array easily.

    int a[10], *p;
    p = &a[0];

The variable `p` now refers to the first item in the array. As such, you
can access `a[0]` via `*p`:

    *p = 5;

Now `a[0]` is initialized with a value of 5.

This is no different from anything in the previous chapter on pointers.

## Pointer arithmetic (aka, address arithmetic)

C supports three forms of pointer arithmetic:

+ Adding an integer to a pointer
+ Subtracting an integer to a pointer
+ Subtracting one pointer from another

These are the *only* forms of address arithmetic that C provides. We'll
look at each in turn.

## Adding an integer to a pointer

Assume the following definitions and operations:

    int a[10], *q, *p;
    p = &a[2];          /* p points to the third item in a. */
    q = p + 3;          /* q points to the sixth item in a. */
    p += 6;             /* p points to the ninth item in a. */

Adding an integer `j` to a pointer `p` returns a pointer to the element `j`
places after the one that `p` points to. If `p` refers to an element
`a[i]`, then `p + j` refers to `a[i + j]` (assuming that `a[i + j]`
exists).

## Subtracting an integer from a pointer

Assume the following definitions and operations:

    int a[10], *p, *q;
    p = &a[8];          /* p points to the ninth item in a. */
    q = p - 3;          /* q points to the sixth item in a. */
    p -= 6;             /* p points to the third item in a. */

If `p` points to array element `a[i]`, then `p - j` refers to `a[i - j]`,
again assuming that element exists.

## Subtracting one pointer from another

When one pointer is subtracted from another, the result is the distance
between the pointers, measured in array elements. For example:

    int a[10], *p, *q, i;
    p = &a[5];          /* p points to the sixth item in a. */
    q = &a[1];          /* q points to the second item in a. */
    i = p - q;          /* i gets the value 4. */
    i = q - p;          /* i gets the value -4. */

## Using pointers for array iteration

This is the big deal (TM) about pointers and arrays. Using pointers and
pointer arithmetic, you can process arrays without using subscripts.
Consider the following example:

    #define N 10
    ...
    int a[N], sum, *p;
    ...
    sum = 0;
    for (p = &a[0]; p < &a[N]; p++)
        sum += *p;

Look Ma, (nearly) no subscripts. (We can get rid of the remaining ones too.
Wait until the next section.)

Also, note that `&a[N]` is safe because thing will ever try to examine or
alter the value at that address.

Now, apparently, once upon a time, the primary argument in favor of
iterating over an array this way was speed. However, given compiler
advances, that's no longer necessarily true. In fact, in many cases,
subscripting may be faster (says K. N. King). Nevertheless, the pointer
iteration style is probably still very common because so many C programmers
got used to the idiom. So I should be able to recognize it, even if I never
write it (or rarely write it).

## Combining the *, ++ and -- operators

Now things get a little hairy. You can combine the indirection operator
with the pre-/post-increment/decrement operators. For example, the
following are equivalent, assuming `p` is a pointer to an item in `a`:

    a[i++] = j;
    *p++ = j;

The `++` operator takes precedence over `*`, so the compiler reads that as
`*(p++)`. The value of `p++` is `p` because we only increment *afterwards*.
So the value of the whole expression is `*p` and then `p` is incremented to
point to the next element in the array. This is great if you like brevity,
but awfully dense code.

You can change the order or operators for different effects. So, instead of
`*p++`, you could use `(*p)++`. There's a subtle difference in behavior.
The second version still has a value of `*p`, but after that value is
returned `*p` is incremented, *not* `p`. That is, the pointer doesn't
advance at all, but whatever it points to is incremented by one. Here's
a chart with a breakdown of possibilities:

    *p++ or *(p++)  Value is *p before increment; increment p after
    (*p)++          Value is *p before increment; increment *p after
    *++p or *(++p)  Increment p first; value is *p after increment
    ++*p or ++(*p)  Increment *p first; vlaue is *p after increment

Of these four, King says that `*p++` is most common although "all four
combinations appear in programs".

`--` and `*` combine in all the same ways as `++` and `*`.

## Using an array name as a pointer

Up until now, we've initialized a pointer to an array this way: `p
= &a[0]`. But that is actually unnecessary. `a` itself *is* a pointer to
the first element in the array. Moreover, pointer arithmetic works on array
names. So we could do the following:

    int a[10];
    *a = 7;         /* Store 7 in a[0]. */
    *(a + 1) = 12;  /* Store 12 in a[1]. */

More generally, `a+i` is the same as `&a[i]` (both are pointers to element
`i` of `a`) and `*(a+i)` is the same as `a[i]` (both represent element `i`
itself).

**NB**: This all means that *array subscripting* is itself a form of
pointer arithmetic. (This is *why* subscripts start with 0. `*a` == `*(a
+ 0)`.)

Going back to the sum loop above, we can rewrite it as follows:

    for (p = &a[0]; p < &a[N]; p++)
        sum += *p;

    for (p = a; p < a + N; p++)
        sum += *p;

Also note that although an array name can be used as a pointer, you can't
assign it a new value. The following won't work:

    /* Try to find the address of the first 0 in a. */
    while (*a != 0)
        a++;

If you want to do something like this, you need another variable:

    p = a;
    while (*p != 0)
        p++;

## Array arguments (revisted)

When an array name is passed to a function, it is always treated as
a pointer. This has some important consequences:

+ Normally a parameter given to a function is protected from change because
  it is copied (pass by value). However, an array is not protected. If you
  want to protect it, you can add `const` in the function's declaration.
  Then the compiler will protect you: `inf f(const int a[])`.
+ There is no performance penalty for passing even enormous arrays to
  functions. Only the pointer is really passed. There's no copying of large
  amounts of data.
+ An array parameter can be declared as a pointer, instead of as an array.
  These two are equivalent:

        int f(int *a);
        int f(int a[]);

  **NB**: This is only true for parameters, not for variable declaration.
+ You can pass a function an array slice, in a roundabout way. If you want
  a function only to work through a portion of an array, pass a starting
  point and the number of elements to iterate over:

        f(&b[5], 10);

  That will start at `b[5]` instead of `b[0]` and look at ten items. (This
  trick could come in handy for optimizing sort algorithms, for example.)

## Pointers and multidimensional arrays

Multidimensional arrays are stored as a series of rows. But internally,
they're not multidimensional at all: they're just one series of rows. This
means that you can avoid nested `for` loops when iterating over them:

    int a[NUM_ROWS][NUM_COLS];
    ...
    /* Nested for loops */
    int row, col;
    for (row = 0; row < NUM_ROWS; row++)
        for (col = 0; col < NUM_COLS; col++)
            a[row][col] = 0;
    /* Pointer instead of nested loops */
    int *p;
    for (p = &a[0][0]; p <= &a[NUM_ROWS - 1][NUM_COLS - 1]; p++)
        *p = 0;

The second method is obviously much shorter. It's also probably harder to
read if you're not familiar with the idiom.

## Processing a single row of a multidimensional array

It's easy to process one row of a multidimensional array.

    p = a[i]; /* Equivalent to p = &a[i][0]; */

    int a[NUM_ROWS][NUM_COLS], *p, i;
    for (p = a[i]; p < a[i] + NUM_COLS; p++)
        *p = 0;

## Processing a single column of a multidimensional array

It's *not* easy to process one column of a multidimensional array. He shows
how to do it, and I think I get it, but ouch.

    int a[NUM_ROWS][NUM_COLS], (*p)[NUM_COLS], i;
    ...
    for (p = &a[0]; p < &a[NUM_ROWS]; p++)
        (*p)[i] = 0;

He declares `p` to be a pointer to an array of length `NUM_COLS`. Since the
pointer is to the whole array, `p++` advances you to the next row. So if
`i` is 2, then you will work down the third column for however many rows
you have.

**NB**: The parentheses are required in both places above. The first tells
the compiler to treat `(*p)[NUM_COLS]` as a declaration of a pointer to an
array length `NUM_COLS` whose members are ints. Without the parentheses, it
would see a declaration of an array of pointers instead of a pointer to an
array. The second expression tells the compiler we want to assign something
to the zeroth element of `(*p)`. `*p[i]` would refer to the same thing as
`*(p[i])`, aka `p[i]`.

I think I understand this, but also think there must be an easier way. What
about this?

    int a[ROWS][COLS], *p, i, j;

    /* Initialize all members of a to 5. */
    for (p = &a[0][0]; p <= &a[ROWS-1][COLS-1]; p++) {
        *p = 5;
    }

    /* Iterate over one column, changing its value to 0. */
    for (p = &a[0][3]; p <= &a[ROWS-1][ROWS-1]; p += COLS) {
        *p = 0;
    }

## Using the name of a multidimensional array as a pointer

The name of a multidimensional array can be used as a pointer, just as the
name of any array. But you have to be careful about what it means:

    int a[NUM_ROWS][NUM_COLS];

In such a case, `a` is *not* a pointer to `a[0][0]`. It's a pointer to
`a[0]`. From the standpoint of C, `a` is not a two-dimensional array, but
a one-dimensional array whose elements are one-dimensional arrays. When you
use `a` as a pointer, it is a pointer to an integer array of length
`NUM_COLS` -- `int (*)[NUM_COLS]`. That means you can simplify the previous
code for processing a column from a multidimensional array:

    for (p = a; p < a + NUM_ROWS; p++)
        (*p)[i] = 0;
