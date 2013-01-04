# Programming in Lua 3rd edition

## Chapter 2 Types and Values

Lua is dynamically typed. There are no type definitions, and each value
carries its own type.

There are eight basic types in Lua:

+ nil
+ boolean
+ number
+ string
+ userdata
+ function
+ thread
+ table

The `type` function yields the type name of any given value (as a string).

A variable's type isn't defined or predefined; it can hold any type, and it
can switch at any time.

### Nil

Nil is a type with only one value, `nil`. The `nil` value is different from
every other value in Lua. It represents a kind of non-value or the absence
of any useful value. Global variables are `nil` by default, and you can
assign `nil` to a variable to delete it.

### Booleans

There are two boolean values, `true` and `false`. But you can use any value
in a Lua condition. Conditional tests consider `false` and `nil` as false,
and everything else is true. Note that `0` and the empty string are true in
Lua.

### Numbers

The number type represents real (double-precision floating-point) numbers.
There is no integer type in Lua. Any integer up to `2**53` has an exact
representation, and there will be no rounding error unless you go beyond
this limit. But of course fractional numbers can have problems with
representation. Also numbers may have a finite representation in decimal
but an infinite representation in binary. This can lead to trouble. For
example 12.7-20+7.3 is not exactly zero when you compute it with doubles.
That's because both 12.7 and 7.3 don't have finite binary representations.

You can write numeric constants with an optional decimal part, plus an
optional decimal exponent. Examples:

    4   0.4     4.57e-3     0.3e12      5E+20

You can also write hexadecimal constants, prefixed by 0X or 0x. Since 5.2,
hexadecimal constants can also have a fractional part and a binary exponent
(prefixed by 'p' or 'P'). Examples (with decimal representation in
parentheses):

    0xff (255)  0X1A3 (419) 0x0.2 (0.125)   0x1p-1 (0.5) 0xa.bp2 (42.75)

### Strings

Strings are a sequence of characters. Lua handles strings in such a way
that you can store binary data in a string. You can also store Unicode
strings in any representation (UTF-8, UTF-16, etc.). The standard string
library doesn't offer explicit support for Unicode, but it's easy to handle
UTF-8 strings in Lua (details later, in Chapter 21).

Strings in Lua are immutable. You don't change a character inside one; you
create a new string, even if that's transparent to you at the time. Lua
automatically performs memory management on strings. Lua can handle very
large strings efficiently. You can get the length of a string using the `#`
prefix operator:

    a = 'hello'
    length = #a

### Literal strings

You can delimit literal strings with single or double quotes as you like.
The standard backslash escapes are available in Lua. You can also specify
a character in Lua using escape sequences `\ddd` or `\xhh`. In the first
case you use up to three decimal digits (prefix with 0 to prevent
ambiguity), and in the second you use `\x` and two hexadecimal digits.

### Long strings

You can also delimit strings by matching double square brackets. This kind
of literal can go for many lines, but they don't interpret escape
sequences. This form of string also ignores an initial newline (if it's the
very first character). This is useful for writing strings that contain
larger pieces of code or markup.

If the string itself contains brackets, you can add any number of equal
signs between the two opening brackets. Then only a matching bracket
+ equal-signs + bracket will close the string. This same trick can be used
with comments. In this way, you can easily comment out code that contains
already commented-out sections.

You shouldn't use long strings with arbitrary characters. Instead use
quotes and encode the escapes in decimal or hex. If you have a long string
in such a situation, you can use `\z` at end of line, starting in Lua 5.2.
If will cause the interpreter to skip all subsequent character until the
next non-space item is found. Example:

    data = "\x00\x01\x02\x03\x04\x05\x06\x07\z
            \x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"

The `\z` there causes that `\x08` to appear immediately after `\x07` in the
resulting string.

### Coercions

Lua does automatic conversion between numbers and strings at run time,
though they now regret this design decision. Don't do it. Instead use
`tonumber` and `tostring` and explicitly convert as needed.

### Tables

The table type implements associative arrays. These associative arrays can
be indexed with numbers, strings or any value of the language except nil.

Tables are the only data structuring mechanism built into Lua. They can
represent arrays, sets, records easily. Lua also uses tables internally to
represent packages and objects. For example, `os.exit` refers to the `exit`
function in the `os` module. That module is stored as a table.

Tables are neither values nor variables in Lua; they are objects. A table
is a dynamically allocated object; a program manipulates only references to
the table. You don't need to (and can't) declare a table. Tables can only
be created using a constructor expression. The simplest constructor
expression is `{}`; it creates an empty table. Tables themselves are always
anonymous in Lua. Like global variables, table fields evaluate to `nil`
when they're not initialized. You can also assign `nil` to a table field to
delete it.

For records, you use the field name as an index. Lua provides a syntactic
sugar for this:

    a = {}
    a["x"] = 10 -- same as below
    a.x = 10    -- same as above

Don't confuse `a["x"]` with `a[x]`. The first indexes the table with the
string 'x'. The second uses the value of the variable `x` as the index.

You can get the size of a table with `#`. However, if the table can have
valid nils or it is a mixed table (indexes by string and by number), then
you have to be more complicated.

### Functions

Lua treats functions as first-class values. You can store them in
variables, pass functions to arguments, and return functions from results.
In addition, Lua has good support for functional-style programming,
including nested functions with lexical scoping. Lua can also call
functions written in C.

### Userdata and Threads

Userdata allows you to store arbitrary C data in a Lua variable. Within
Lua, userdata has only the predefined operations of assignment and
equality. You can use userdata to represent new types. Lua's own I/O
library represents open files using userdata.

They don't discuss threads here. They will in Chapter 9, when they discuss
coroutines.
