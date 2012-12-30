# Chapter 8 - Arrays

**NB**: I didn't take notes on this chapter when I first read it, so the
notes here are (very) incomplete. Mostly that's because I'm good with
arrays. But I do want notes on one section, so I'm writing them up now.

## Using the sizeof operator with arrays

The `sizeof` operator can determine the size of an array in bytes. You can
also use `sizeof` to determine the size of individual elements in an array.
Put these two together, and you can work out the length of an array.

    sizeof(a) / sizeof(a[0])

You could use this in a `for` loop as an example:

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)

But this may produce a warning for the test expression. The problem is that
i is (almost certainly) an int, but the return value of `sizeof` is
`size_t` (an unsigned type). In this case, the comparison is safe since
both values are guaranteed to be nonnegative. To prevent the warning, we
can add a cast:

    for (i = 0; i < (int) sizeof(a) / sizeof(a[0]); i++)

Now at this point, a macro would make this easier:

    #define A_SIZE(a) ((int) (sizeof(a) / sizeof(a[0])))
    ...
    for (i = 0; i < A_SIZE(a); i++)
