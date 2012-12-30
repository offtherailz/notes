# Chapter 13 - Strings

## String literals

A string literal is a sequence of characters between double quotes:

    "This is a string."

Compare this with a character constant: a single character between single
quotes:

    'c'

## Escape sequences in string literals

String literals can contain the same escape sequences as character
constants. Examples: `\n`, `\b`, `\t`.

## Very long strings

If you need to write a very long string literal, you can run over the line
by using '\', as in shell scripts. Nothing can appear after the backslash.

This is fine, but it can mess up indentation since the next line must
continue at the beginning of the line. An alternative solution is to cheat
by using C's automatic concatenation of strings:

    printf("When you come to a fork in the road, take it.   \n"
           "--Yogi Berra");

## String literals and storage

C treats string literals in a surprising way: they are character arrays.
When the compiler sees a string literal of *n* characters, the compiler
sets aside *n* + 1 byes of memory for the string. This piece of memory will
hold all the characters in the string, plus a special character -- the null
character -- which marks the end of the string. The null character is
a byte where all the bits are zero. You represent it in code with `\0`.

Since strings are arrays, the compiler treats a string array as a pointer
of type `char *`. Both `printf` and `scanf` expect a value of `char *` as
their first argument.

You can do everything with a string literal that you could do with the type
`char *`. It can appear on the right hand of an assignment:

    char *p;
    p = "abc";

In the second line, C *does not* copy the string into `p`. It causes `p` to
refer to the first character of the string. You can also subscript a string
literal:

    char c;
    c = "abc"[1];

Now `c` has the value `b`.

## String literals versus character constants

A string literal with a single character is *not* the same thing as
a character constant. The string literal `"a"` is a pointer to a memory
location that contains the character `a`. The null character follows. The
character constant `'a'` is represented by an integer (the numerical code
for that character).

## String variables

C has no distinct string type. To store a string in a variable, you create
an array of characters to store the string. This causes various problems.

+ Hard to known if a specific array of characters is really a string or an
  actual array of characters.
+ Off by one errors result from the mandatory null char.
+ Any string functions we write must be careful about the extra null char.
+ No better way to determine the length of a string than to search
  character-by-character for the null char.

Nevertheless, this is what C does. Here's a standard way to store a string
up to 80 characters long.

    #define STR_LEN 80
    ...
    char_str[STR_LEN+1];

The extra 1 is to hold the `\0`. The actual string can be shorter than *n*
+ 1, but no longer. An array of `STR_LEN + 1` can store the empty string
all the way up to a string as long as `STR_LEN`.

You can initialize a string variable as you declare it:

    char date1[8] = "June 14";

That's a shortcut. You get to write the string literal, but the compiler
treats it as if you wrote this:

    char date[8] = {'J', 'u', 'n', 'e', ' ', '1', '4', '\0'};

Note that the `\0` is *automatically added* to the string.

If the string is shorter than the size you explicitly give it, extra null
characters are added at the end to fill the gap:


    char date2[9] = "June 14"; /* As if "June 14\0\0" */

If the initializing string is too long for the size you give, there will be
an error. However, there's an edge case. If the size is exactly long enough
for the string but not the null character, C will store it without the
final `\0`. This is a nightmare, since it's then useless for standard
string functions. Do not do this.

As with other arrays, you can omit the number if you initialize when you
declare the variable:

    char date3[] = "January 14th, 2012"; /* Look Ma, no counting. */

The length of the array is specified when the program is compiled. You
can't change the length later to accomodate a longer string.

## Character arrays versus character pointers

Examine the following:

    char date[] = "June 14";
    char *date = "June 14";

The first declares `date` to be an array. The second declares `date` to be
a pointer. We can use either version of the two in many cases. In
particular, any function that expects to be passed a character array or
character pointer (like `printf` or `puts`) will accept both.

However, they are not the same in all respects.

+ In the array version, you can change the characters stored in `date`. In
  the pointer version, `date` refers to a string literal. String literals
  cannot be changed.
+ In the array version, `date` is the name of an array. In the pointer
  version, `date` is a pointer variable. It starts out referring to one
  literal string, but you could make it point to other strings during the
  execution of the program.

## Reading and writing strings

Writing a string is easy; reading a string is somewhat more difficult since
you have to be careful about the size of the string and the variable that
will hold it.

You can write strings using `printf` or `puts` (as well as other functions,
e.g. `fprintf`):

    char str[] = "This is fun.";
    printf("%s\n", string);
    puts(str);

The `puts` function automatically inserts a newline character after the
string it receives as a parameter.

You can read strings using `scanf` or `fgets`. (He goes through `gets`, but
I'm going to avoid that.)

    scanf("%s", str);
    fgets(str, sizeof(str), stdin);

`scanf` skips initial whitespace, but stops reading as soon as it sees
whitespace after a string. So you can't read a whole line of words with
spaces between them. `fgets` reads until it gets to a new-line or until it
gets to `sizeof(str) - 1`. `fgets` will store a newline character if it has
room for one. `scanf` is unsafe, but you can specify how many characters to
read in the formatting. (E.g. `scanf("%80s", str)`.)

## Reading strings character by character

Since both `scanf` and `gets` have issues and lack flexibility, many
C programmers write their own input functions. This is fine, and you can
easily read a character at a time in C. However, you must be aware of some
key questions:

+ Should the function skip white space before beginning to store the
  string?
+ What character stops the function from reading? A newline? Any white
  space character? Something else?
+ Is the character that causes reading to stop stored in the string?
+ What should the function do if the string its reading is too long to
  store?

## Accessing the characters in a string

Since strings are stored as arrays, you can always easily use subscripting
(or pointers) to get at individual characters. This allows you to easily do
things like, e.g., count spaces in a string:

    int count_spaces(const char *s)
    {
            int count;
            count = 0;

            while (*s != '\0') {
                    if (*s == ' ') count++;
                    *s++;

            }

            return count;
    }

In this case, we declare the string `s` to be constant since we know we
don't want to change it. In addition, we use `char *s` -- a pointer --
rather than `char s[]` -- an array. Either declaration can work. It's up to
you to choose which you prefer. The advantage of the pointer is that it
spares us from having to use a separate integer variable to subscript the
array.

Some FAQ about array versus pointers in the function declaration:

+ Is it better to use array operations or pointer operations to get at
  characters?

  Either is potentially fine, and you can even mix them.
  Many C programmers lean towards pointers, so you should be ready to see
  them in other code, but neither is necessarily better.

+ Should a string parameter be declared as an array or as a pointer?

  It almost doesn't matter. The compiler treats an array parameter as if it
  were declared as a pointer anyhow. You can use whichever makes more sense
  to you.

+ Does the declaration of the parameter affect what arguments are legal to
  pass into the function?

  No. Whichever parameter you declare, you can pass in an array name,
  a pointer to an array or a string literal.

  ## Using the C string library

In C, you can't compare, copy or concatenate strings directly. To do so,
you need the functions in `string.h`.

Here are some of the key functions the library includes:

+ `strcpy(char *copy, char *original)` copies the string in original into
  copy. Returns a pointer to the copy. The original isn't altered, so it is
  declared as `const`. Thus, you can use a string literal there.

  **NB**: `strcpy` does no bounds-checking. If the copy is too small to
  hold the original, the behavior is undefined. To compensate for this,
  there is also `strncpy`. This function takes a third parameter to
  specify the maximum size string to copy. Thus, you limit the danger.
  However, this function is slower. Also, it *still* has the problem that
  if the copy has enough room for the entire original except for the null
  character, the copy will be left without a null char. Thus, here's
  a safer way to use `strncopy`:

        strncopy(copy, original, sizeof(copy)-1);
        copy[sizeof(copy)-1] = '\0';

+ `strnlen(const char *s)` finds the length of the string. Returns the
  length as an item of `size_t`: you can treat this as an `int` for all
  normal purposes. The number returned does not include the final null
  character.

+ `strcat(char *target, char *original)` appends the string in `original`
  to `target`. It returns `target` -- a pointer the resulting string. As
  with `strcpy`, this function does no bounds checking and is potentially
  unsafe. Again, like `strcpy`, `strcat` has a safer version that takes
  a third parameter to specify the limit to concatenate: `strncat`.

+ `strcmp(str1, str2)` compares the two strings. Returns 0 if they are
  equal, less than 0 if `str1` is smaller than `str2` and more than 0 if
  `str1` is greater than `str2`. For the purposes of the comparison, less
  than or greater than cares about the numerical codes that represent the
  characters in the string. For ASCII characters, some important
  properties:

    + The characters in the sequences A-Z, a-z and 0-9 have consecutive
      codes.
    + All uppercase letters are less than all lowercase letters.
    + Digits are less than letters
    + Spaces are less than all printing characters.

## String idioms

Start with something like the following to search for the end of a string
(say to get the length of a string):

    size_t n;

    for (n = 0; *s != '\0'; s++)
            n++;

The test `*s != '\0'` is the same as `*s != 0`, because the integer value
of the null character is 0. But testing `*s != 0` is the same as testing
`*s`. Both are true if `*s` is not equal to 0. So we could do something
like this:

    size_t n = 0;

    while (*s++)
            n++;

This is shorter, but not necessarily faster. Alternatively, he offers this
-- which he says may be faster, depending on compiler:

    const char *p = s;

    while (*s)
            s++;
    return s - p;

Two idioms he offers:

    while (*s)
            s++;

    while (*s++)
            ;

The first leaves `s` pointing at the null character. The second leaves `s`
pointing just past the null pointer.

Here's a very explicit and long strcat function followed by a short and
idiomatic one:

    char *strcat(char *s1, const char *s2)
    {
            char *p = s1;

            while (*p != '\0')
                    p++;

            while (*s2 != '\0') {
                    *p = *s2;
                    p++;
                    s++;
            }

            *p = '\0';

            return s1;
    }

    char *strcat(char *s1, const char *s2)
    {
            char *p = s1;

            while (*p)
                    p++;

            while (*p++ = *s2++)
                    ;

            return s1;
    }

This gives us our string copying idiom:

    while (*p++ = *s2++)
            ;

How does this work? Well, it assigns the value of the pointer `s2`
reference to `p`. The *return value* is whatever got assigned. Thus, when
we assign `\0` the test is false, and the loop ends. Since the assignment
happens *before* the test, however, the assignment gets done, and the
resulting string is null-terminated (as it should be).

## Arrays of strings

Programs often must work with arrays of strings. You can declare these in
two ways:

    char planets[][8] = { "Mercury", "Venus", "Earth", "Saturn" };

    char *planets[] = { "Mercury", "Venus", "Earth", "Saturn" };

An advantage of the second method is that each one of the sub-arrays can be
its own length. This means no wasted storage space for all the strings that
are shorter than seven characters. (There is space taken to store the
pointers, but presumably that's less than in an array storing sentences of
varying lengths.)

However you declare and initialize the array of strings, you can get at
individual strings by subscripting the outermost array or by using
a pointer to a pointer. Compare:

    int i;
    for (i = 0; i < argc; i++)
            printf("%s\n", argv[i]);

    char **p;
    for (p = &argv[0]; *p != NULL; p++)
            printf("%s\n", *p)
