# Advanced uses of pointers

Previous uses of pointers:

+ As a function argument, so that the function can alter the variable (in
  Chapter 11)
+ With arrays to perform pointer arithmetic and process arrays (in Chapter
  12)

Two new uses of pointers:

+ Dynamic storage allocation
+ Pointers to functions

## Dynamic storage allocation

C data structures are normally fixed in size. Arrays are normally set at
compile time. (In C99, a variable-length array can be set at run time, but
it's still _set_ after that.) But a fixed-size structure can be a problem.
We might choose too small a size (and blow up or have to bail out during
a run), or choose too large a size and waste space. But C does support
dynamic storage allocation during program execution. This allows you to
design data structures that grow (or shrink) as needed. Although all types
of data can use dynamic storage allocation, it's most common with strings,
arrays more generally and structures.

### Memory allocation functions

There are three essential functions (all declared in `stdlib.h`) for
allocation of memory:

+ `malloc` - Allocates a block of memory but doesn't initialize it
+ `calloc` - Allocates a block of memory and clears it
+ `realloc` - Resizes a previously allocated block of memory

`malloc` is most common. It's also more efficient than `calloc`.

When you request a block of memory, the function has no idea what type of
data will be stored in the block later. So it can't return a normal type
like `int` or `char`. Instead, it returns a value of type `void *`. Such
a value is a generic pointer -- effectively just a memory address.

### Null pointers

When a memory allocation function is called, there's always a chance that
it will fail to locate a block of memory large enough for the request. If
that happens, the functions returns a null pointer. A null pointer is
a pointer to nothing. It's a special value that can be distinguised from
any valid pointer. After storing the allocation function's return value,
_always_ check for null pointers. (Cf. opening a file and making sure you
actually have an open file to work with.)

The null pointer is represented by a macro `NULL`. You use that to test the
function's return value.

    p = malloc(10000);
    if (p == NULL) {
            /* Allocation failed. Do something to handle that. */
    }

You can also combine the test and the allocation:

    if ((p = malloc(10000)) == NULL) {
            /* Allocation failed. Do something to handle that. */
    }

Since pointers return true or false directly (like numbers) in C, you can
even skip the explicit test against `NULL`. The result of `if (p)` will be
true for any pointer other than `NULL`. So to test if a pointer is `NULL`,
you could just write `if (!p)`.

The `NULL` macro is defined in seven headers (one is C99 only):

+ locale.h
+ stddef.h
+ stdio.h
+ stdlib.h (which gives us `malloc`, `calloc`, and `realloc`)
+ string.h
+ time.h
+ wchar.h (C99 only)

## Dynamically allocated strings

Dynamic storage allocation is very common with strings since it can be hard
to decide in advance how long a string-holding array needs to be.

### Using `malloc` to allocate memory for a string

Here is `malloc`'s prototype:

    void *malloc(size_t size);

`malloc` allocates a block of `size` bytes and returns it. `size_t` is an
unsigned integer type defined in the C library. For these purposes, we can
think of it as like an integer.

Using `malloc` for strings is easy since C guarantees that a `char`
requires one byte of storage. To make space for a string of n characters,
you'd write:

    /* p should be of type char * */
    p = malloc(n + 1);

You don't need to cast the return value of `malloc`, but some people prefer
to be (over?) explicit:

    p = (char *) malloc(n + 1);

The extra one byte of space is for the final '\0' character.

The memory block you get from `malloc` is not initialized or cleared in any
way. One way to initialize it is to use `strcpy`:

    strcpy(p, "whatever");

### Using dynamic storage allocation in string functions

Dynamic storage allocation makes it possible to write functions that return
pointers to new strings -- strings that didn't exist before the function
was called. For example, C's stdlib doesn't have a function to concatenate
two strings without changing either one. But it's easy to write your own.

    char *concat(const char *s1, const char *s2)
    {
            char *result;
            result = malloc(strlen(s1) + strlen(s2) + 1);

            if (result == NULL) {
                    printf("Error: malloc failed in concat\n");
                    exit(EXIT_FAILURE);
            }
            strcpy(result, s1);
            strcat(result, s2);

            return result;
    }

## Dynamically allocated arrays

Dynamically allocated arrays share the same benefits as dynamically
allocated strings. C allows you to allocate space for an array during
execution and then access the array through a pointer to its first element.
Instead of using `malloc`, `calloc` is sometimes used, since it initializes
the memory that it allocates. The `realloc` function allows you to make an
array larger or smaller as needed during execution.

### Using `malloc` to allocate storage for an array

Allocating storage for an array with `malloc` is very much like what we saw
with strings. The one wrinkle is that space will not necessarily be one
byte per item. You can use the `sizeof` operator to calculate the space
needed.

    int *a;
    /* At some point, we determine the value for n. */
    a = malloc(n * sizeof(int));
    ...
    /* You could also use pointer arithmetic to iterate over the array. */
    for (i = 0; i < n; i++)
            a[i] = 0;

### The `calloc` function

The `calloc` function is a variant of `malloc`. It has the following
prototype:

    void *calloc(size_t nmemb, size_t size);

`calloc` allocates space for `nmemb` members, each of which is `size` bytes
long. Like `malloc`, it returns a null pointer if the space isn't
available. But unlike `malloc`, `calloc` also initializes the array by
setting all bits in it to 0.

You can use `calloc` to allocate space for any object (not just an array).
For example:

    struct point { int x, y; } *p;
    ...
    p = calloc(1, sizeof(struct point));

This initializes `p` as a pointer to a point struct whose `x` and `y`
members are already set to 0.

### The `realloc` function

After allocating memory, we might find out later that we have too much or
too little space. This is where `realloc` comes in handy. The `realloc`
function has the following prototype:

    void *realloc(void *ptr, size_t size);

When `realloc` is called, `ptr` must point to a memory block obtained by
a previous call to `malloc`, `calloc` or `realloc`. The `size` parameter
represents the new size of the block. This new size can be larger or
smaller than the original one. `realloc` doesn't require that `ptr` point
to memory that's being used as an array, but in practice it usually does.

Make sure to use `realloc` only on a pointer previously initialized by
`malloc`, `calloc` or `realloc`. Otherwise, the behavior of `realloc` is
undefined.

The C standard lays out the following rules for `realloc`:

+ When it expands a memory block, `realloc` does not initialize the bytes
  that are added.
+ If `realloc` can't expand the block as requested, it returns a null
  pointer; the data in the old memory block is unchanged.
+ If `realloc` is called with a null pointer as its first argument, it
  behaves like `malloc`. (**NB**: This could come in handy.)
+ If `realloc` is called with 0 as its second argument, it frees the memory
  block.

But the C standard does not specify _how_ `realloc` works. We expect it to
be as efficient as possible. This implies that it shouldn't move the memory
block unless it must. Shrinking should never need to move the block;
expanding a block will sometimes require moving it and copying as needed.

**NB**: After calling `realloc`, you should update all (other?) pointers to
the memory block, since it's possible that the call to `realloc` moved the
memory elsewhere. (Not true for shrinking, right?)

## Deallocating storage

`malloc` and the other memory allocation functions get memory blocks from
the heap. Calling these functions too many times -- or asking them for
excessively large amounts of memory -- can exhaust the heap.

In addition, a program may allocate blocks of memory and then lose track of
them. The space that is lost is garbage. A program that leaves garbage
behind has a memory leak. C provides no automatic garbage collection.

    p = malloc(...);
    q = malloc(...);
    p = q;

After the last line, the memory that was originally allocated for `p` is
garbage. There's no way to reach it. It cannot be used. But it's not free
for further allocation from the heap.

### The `free` function

Here is the prototype for `free` (from stdlib.h):

    void free(void *ptr);

It's dead easy to use `free`. Just pass it a pointer to a memory block that
we no longer need.

    p = malloc(...);
    q = malloc(...);
    free(p)
    p = q;

The argument to free must be a pointer returned by one of the memory
allocation functions or a null pointer. If you use it on a pointer to any
other kind of object (like a variable or array), the behavior is undefined.

### The "dangling pointer" problem

Although `free` is great -- since it allows programmers to reclaim memory
for the heap -- it has its own danger. It can create dangling pointers.
A dangling pointer is a pointer that no longer refers to a valid memory
address. If you try to use such a pointer, the behavior is undefined -- and
bad.

    char *p = malloc(4);
    ...
    free(p);
    ...
    strcpy(p, "abc"); /* Boom */

What can make dangling pointers especially hard to find is that several
pointers may refer to the same block of memory. If you call `free` on _any_
of them, _all_ the pointers are left dangling. You can no longer use _any_
of them safely.
