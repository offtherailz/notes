<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css"
rel="stylesheet"></link>
# Chapter 7 - Basic Types

## Integer types

Integer types are whole numbers. They are one of C's two fundamental types
of numbers. (The other being floats which can have fractional parts.)
Integers can be divided into signed and unsigned. Signed and unsigned have
to do with bit-representation and storage.

A signed integer uses its leftmost bit to store the sign of the number as
a whole. That bit will be 0 if the number is positive (or zero) and 1 if
the number is negative. An unsigned number can only be positive, but it's
range is larger than a signed number (since it has an extra bit to work
with, in effect). By default, integers in C are signed.

C integers come in different sizes. The `int` type is usually 32 bits (16
on older machines). You can also have `long int` or `short int` if you need
larger numbers or want to conserve memory. All of these can be signed or
unsigned. The following six combinations are legal possibilities:

+ `short int`
+ `unsigned short int`
+ `int`
+ `unsigned int`
+ `long int`
+ `unsigned long int`

The order of specifiers doesn't matter: `unsigned short int` is the same as
`short unsigned int`. You can also omit the `int` in more complex names.
For example, `unsigned short` is equivalent to `unsigned short int`.

The exact range of values each type represents varies by machine. But the
C standard does demand a minimum range of values. However, for our purposes
it's enough to remember that `int` can't be shorter than `short int` (though
they may be the same), and `long int` can't be shorter than `int` (though
they may be the same). If you ever have a burning need to determine limits
on a particular machine, check the `limits.h` header for macros that will
show you those limits.

C99 added two new integer types `long long int` and `unsigned long long int`.
These are obviously even bigger than `long int` numbers.

### Integer constants

A constant is a number that appears in the text of a program (as opposed to
a number in a variable or the result of an expression). C constant integers
can appear in decimal, octal or hexadecimal. Decimal constants contain
digits between 0 and 9. They cannot begin with a zero. Octal digits are
0 through 7, and they _must_ begin with a zero. Hexadecimal constants
contain digits from 0 to 9 and letters between a and f. They always begin
with 0x. The letters in hexadecimals can be upper or lower case.

No matter how numeric constants are written, they are always stored in
binary. They are just alternative ways for us to write numbers in programs.
You can even mix representations in one expression: 10 + 015 + Ox20.

The type of a decimal constant is normally int. If the number becomes too
large, it will take the type long int and then unsigned long int, as
needed. You can force the compiler to treat a constant as a larger type by
adding 'L' (or 'l') and 'U' (or 'u').

    15L
    0355L
    0x7ffL
    15U
    0377U
    0x7ffL

You can combine 'L' and 'U'. Their order and case doesn't matter.

For the C99 long long type, you can add 'LL' (or 'll').

### Integer overflow

When you perform arithmetic on integers, the result may be too large to
represent. That is, if you multiply two numbers of type `int`, the result
may be too large to represent as an `int`. When this happens, it's called
'overflow'. The result of overflow for signed integers is undefined. The
result for unsigned integers is defined as the correct answer modulo 2n,
where n is the number of bits used to store the result. (This result is
effectively garbage anyhow, so I'm not especially concerned with defining
what kind of garbage it is.)

### Reading and writing integers

When reading or writing an unsigned int, use the format specifier 'u', 'o'
or 'x'. 'u' is for decimal notation, 'o' for octal and 'x' for
hexadecimal.

When reading or writing a short int, put the letter 'h' in front of 'd',
'o', 'u'or 'x'.

When reading or writing a long int, put the letter 'l' in front of 'd',
'o', 'u' or 'x'. For a long long int, put 'll' in front of 'd', 'o', 'u' or
'x'.

## Floating types

In addition to whole numbers, C provides a type for numbers with fractional
parts: floats. There are three floating types:

+ float - single-precision floating-point
+ double - double-precision floating-point
+ long double - extended-precision floating-point

The C standard doesn't specify the range of any of these types. Most
computers follow the specifications in IEEE Standard 754 (also known as IEC
60559).

In addition to the three types above (all known as 'real floating types'),
C99 provides a second type (known as 'complex types'). In the complex type,
there are three sub-types:

+ `float_Complex`
+ `double_Complex`
+ `long double_Complex`

### Floating constants

Floating constants can be written in a number of ways.

    57.0
    57.
    57.0e0
    57EO
    5.7e1
    5.7e+1
    .57e2
    570.e-1

The letter 'e' or 'E' (case doesn't matter) can be used to indicate an
exponent. A '+' or '-' can appear after the 'E' or 'e'.

By default, floating constants are stored as double-precision numbers. If
you want to force a constant to be consider a float or long double, use the
letter 'F' or 'f', 'L', or 'l' (case doesn't matter) after the number.

### Reading and writing floating-point numbers

The base specifiers are 'e', 'f' and 'g'. 'e' is for exponential format
with a default of 6 digits after the decimal point. 'f' is for fixed
decimal format, again with a default of 6 digits after the decimal point.
'g' will use either exponential or fixed decimal format, depending on the
number's size. In the case of 'g', a number before it specifies the maximum
number of digits to show, not digits after the decimal point. Also, 'g'
won't show trailing zeroes. And if there are no digits after the decimal
point, 'g' won't display the decimal point.

To read double floats, put the letter 'l' in front of 'e', 'f' or 'g'. The
'l' is _not needed_ when writing (using `printf`), only when reading.
`printf` can already handle floats or doubles with 'e', 'f' and 'g'. (C99
allows you to use 'l' with 'e', 'f' and 'g' and `printf`, but the 'l' is
meaningless.)

To read or write long doubles, put the letter 'L' in front of 'e', 'f' or
'g'.

## Character types

The last basic type is `char`: the character type. The values of type
`char` vary widely from one machine to another, depending on their base
character sets.

A variable with type `char` can be assigned any single character in the
machine's set. **NB**: Character constants are put in single quotes; double
quotes surround strings. A one-character string is still a string.

    letter = 'a'; /* letter better be type char */
    string = "a"; /* string better be type char [] or char * */

### Operations on characters

C treats characters as small integers. In ASCII for example character codes
range from 0 to 127. An 'a' has the value 97, and 'A' has the value 65. In
fact, character constants have the type `int` rather than `char`. You can
use this to interesting effects.

    char ch;
    int i;

    i = 'a';        /* i is now 97 */
    ch = 65;        /* ch is now 'A' */
    ch = ch + 1;    /* ch is now 'B' */
    ch++;           /* ch is now 'C' */

Characters can also be compared just like numbers. Here's a quick and
simple way to check for lowercase letters and convert them to uppercase.

    if ('a' <= ch && ch <= 'z')
            ch = ch - 'a' + 'A';

This is arguably too clever, but it's common, so it's worth getting used
to. Unfortunately, it's also a bit unportable since it relies on the fixed
distance between 'a' and 'A', 'b' and 'B' etc. For some character sets,
this will be a problem.

Another potential problem with treating characters as numbers is that you
can write things like `'a' * 'b' / 'c'`, and the compiler can't catch the
error.

### Signed and unsigned characters

The C standard doesn't specify whether ordinary `char` is a signed or an
unsigned type. Compilers vary in how they treat it. (Unsigned chars have
values from 0 to 255; signed have values from -128 to 127.) Usually it
doesn't matter, but if it _does_ matter for your application, specify the
type in the declaration.

    signed char ch;
    unsigned char uch;

In C89, character types, integer types and enumerated types are all known
as 'integral types'. C99 doesn't use this term. Instead, it extends the
meaning of 'integer type' to include characters and enumerated types. C99's
`_Bool` type is also condidered to be an unsigned integer type.

## Arithmetic types

Integers and floats are known as 'arithmetic types'. Again, C89 and C99
differ in their exact categorization of all this.

+ C89
    + Integral types
        + char
        + Signed integer types
        + Unsigned integer types
        + Enumerated types
    + Floating types
+ C99
    + Integer types
        + char
        + Signed integer types (both standard and extended)
        + Unsigned integer types (both standard and extended)
        + Enumerated types
    + Floating types
        + Real floating types
        + Complex types

## Escape sequences

Usually a character constant is one characer in single quotes. However,
there are some special characters that can only be written in another way.
In addition, you can write any character using numerical codes.

The traditional character escapes are well known non-printing characters:

    '\n'
    '\t'
    '\r'

And so on.

In addition, _any_ character can be written numerically, using an octal or
hexadecimal sequence.

+ Octal

        \033
        \33

+ Hexadecimal

        \x1b
        \x1B

## Reading and writing characters using `scanf` and `printf`

The `%c` conversion specifier allows you to use `scanf` and `printf` to
read and write single characters. `scanf` doesn't skip white-space
characters before reading a character. If you want to skip initial
white-space do this:

    scanf(" %c", &ch);

Remember that an initial space for `scanf` means "zero or more initial
white-space characters".

## Reading and writing characters using `getchar` and `putchar`

Simpler and faster than `scanf` and `printf` for single characters are
`getchar` and `putchar`. `getchar` actually returns an int, so usually the
variable that will hold its return value is declared as type int. (This
helps to find EOF, for example.)

Because `getchar` directly returns the character it reads, it provides
certain C idioms:

    while ((ch = getchar()) != '\n')
            ;

That skips everything to the end of a line. Or to skip blanks:

    while ((ch = getchar()) != ' ')
            ;

At the end of that loop, `ch` will hold the first nonblank character.

**NB**: Beware of mixing calls to `scanf` and `getchar`. Since `scanf` will
often leave behind characters it peeks at, you may get results you don't
want.

    printf("Enter an integer: ");
    scanf("%d", &i);
    printf("Enter a command: ");
    command = getchar();

The call to `getchar` will end up reading first anything `scanf` left
behind. Here it might be letters or a new-line not read after the integer.

## Type conversion

C allows you to mix types more generously than the computer itself. That
is, the machine cannot normally add, say, a 16-bit integer and a 32-bit
integer or a 32-bit integer and a 32-bit float. C allows this via implicit
conversions. The programmer can also force explicit conversions as
necessary or for greater clarity.

### The usual arithmetic conversions

The basic rule is to convert operands to the "narrowest" type that will
safely accomodate both values. The narrower (smaller) type is promoted to
the wider type. So an integer added to a float becomes a float added to
a float.

Here are simple charts of promotions.

+ If either operand is a floating type:

    float -> double -> long double

+ If neither is a floating type

    int -> unsigned int -> long int -> unsigned long int

**NB**: Comparing signed and unsigned ints can lead to problems since the
unsigned int will lose its sign. If it was negative, that can't be
represented in the signed int. Weird, bad shit happens. Don't do it.

### Conversion during assignment

The usual conversions don't apply to assignment statments. Instead, the
expression on the right side is converted to the type of the variable on
the left side. Simple, but dangerous. Information _can_ be lost. Because of
conversions like this, it's a good idea to use 'f' at the end of
a floating-point constant. Otherwise, the compiler may take it as a double
and issue a warning during assignment.

### Implicit conversions in C99

C99's system is somewhat different from C89. C99 gives each integer type an
"integer conversion rank":

1. long long int, unsigned long long int
2. long int, unsigned long int
3. int, unsigned int
4. short int, unsigned short int
5. char, signed char, unsigned char
6. `_Bool`

C99 uses "integer promotions" rather than C89's integral promotions.
Convert any type of rank less than unsigned int and int to an int (if all
values will fit there) or to unsigned int (if all values won't fit there).

+ If either operand is a floating type: as before
+ If neither is a floating type:
    + First perform integer promotions on both operands. If they are now of
      the same type, stop. Otherwise, use the following rules.
    + If they are both signed or both unsigned, convert to one with lesser
      integer conversion rank to the type of the greater rank.
    + If unsigned operand has rank greater or equal to the rank of the
      signed operand, convert the signed to the unsigned's type.
    + If the signed type can represent all the vlues of the unsigned
      operand, convert the unsigned operand to the signed operand's type.
    + Otherwise, conver both operands to the unsigned type corresponding to
      the type of the signed operand.

Also, any arithmetic type can be trivially converted to `_Bool`:

    + 0 if the original value is 0
    + 1 otherwise

### Casting

C offers a way to force conversions via casts. A cast has this syntax:

    ( type-name ) expression

For example:

    float f, frac_part;
    f = 3.149;
    frac_part = f - (int) f;

You can also use a cast to document a conversion that is implicit and would
happen even without the cast:

    i = (int) f; /* f is converted to an int then assigned to i */

Also, a cast allows you to overrule the compiler and force it to do
conversions that we want, in the way we want.

    float quotient;
    int dividend, divisor;

    quotient = dividend / divisor;

As written, this will do integer division and _then_ store the result as
a float. But we (almost certainly) want to do floating division to get
a more precise answer. This will do that:

    quotient = (float) dividend / divisor;

You don't need to cast both numbers because of regular implicit conversions
(a float divided by an int already promotes the int to a float). However,
you can cast both if you like:

    quotient = (float) dividend / (float) divisor;

In addition, you can use a cast to prevent possible overflows:

    long i;
    int j = 1000;
    i = j * j;

The problem there is that `j * j` will be done as integer multiplication
first, then converted to a long for assignment. But on some machines, an
int is too small to store the result of the multiplication. This cast fixes
the problem:

    i = (long) j * j;

## Type definitions

You can use `#define` to make a macro for a Boolean type: `#define BOOL
int`. But there's a better way: a type definition.

    typedef int Bool;

Note that the name of the new type comes _last_. The capital letter isn't
required, but it's a convention that some C programmers follow. (For all
user-defined types?)

After you've created a type with typedef, you can use it like any other
type in declarations.

    Bool flag; /* Just like int flag */

### Advantages of type definitions

They can make the program clearer.

    typedef float Dollars;
    Dollars cash_in, cash_out;

K argues this is more informative than `float cash_in, cash_out;`. I'm not
really seeing it yet, but ok.

ALso, they make the program easier to modify. If later, you want dollars to
be doubles, you only change one line -- the type definition.

### Type definitions and portability

Type definitions also improve portability. If you want to store some
quantity in ints (for speed and space), but you need the range 0-50,000,
you create a Quantity type. Then if you _must_ switch to longs, you adjust
the type definition. (**NB**: You would also need to change associated
things like `printf` and `scanf`.)

The C library itself uses `typedef` to name types that may vary from
implementation to implementation. These names often end in `_t`. For
example, `size_t` or `ptrdiff_t`.

## The `sizeof` operator

The `sizeof` operator determines how much memory is required to store
values of a particular type.

    sizeof(type-name)

For example, `sizeof(char)` is always 1. But `sizeof(int)` can vary.

`sizeof` can also be applied to constants, variables and expressions:

    sizeof(i)
    sizeof('c')
    sizeof(i + j)

Printing the result of a `sizeof` operation can be tricky, because the
result is implementation defined. In C89, cast the result to unsigned long:

    printf("Size of int: %lu\n", (unsigned long) sizeof(int));

In C99, you can use the `z` specifier, followed by `u` for an unsigned
integer:

    printf("Size of int: %zu\n", sizeof(int));

