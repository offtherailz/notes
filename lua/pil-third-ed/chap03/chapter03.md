# Programming in Lua 3rd edition

## Chapter 3 Expressions

Expressions denote values. Lua includes standard expressions: numeric
constants, string literals, variables, unary and binary operations and
function calls. It also includes some non-standard expressions: function
definitions and table constructors.

### Arithmetic operators

Lua has your standard arithmetic operators:

    + - * / ^ % and unary -

The exponentiation operator (`^`) is not _so_ standard, but we're glad to
have it.

### Relational operators

Lua has standard comparison and equality operators

    < > <= >= == ~=

You can use `==` and `~=` on any two values. If they are not of the same
type, they're not equal. Otherwise, they are compared according to their
types. Nil is equal only to itself. Tables and userdata are compared by
reference not by value.

You can only apply the order operators to two numbers or two strings.
Strings are compared by locale, so that's not completely portable.

### Logical operators

Lua provides `and`, `or` and `not`. All logical operators consider `false`
and `nil` to be false, and everything else to be true.

The `and` operator returns its first argument if it is false; otherwise it
returns its second argument. The `or` operator returns its first argument
if it is not false; otherwise it returns its second argument.

Both `and` and `or` use short-cut evaluation: they evaluate their second
operand only when necessary. This guarantees that things like the following
do not cause run-time errors:

    (type(v) == "table" and v.tag = "h1")

Two useful idioms:

+ `x = x or v` sets x to v only when x is not already set
+ `(a and b) or c` equivalent to C's `a ? b : c`, provided that b is not
  false.

In the second case, the parentheses are not needed since `and` binds more
tightly than `or`.

An example of the second idiom in use:

    max = (x > y) and x or y

The `not` operator always returns a boolean value.

### Concatenation

String concatenation is done with `..`. If any operand is a number, Lua
converts it to a string. Since strings are immutable, the concatenation
operation really creates a new string. So if you are doing a lot of them,
consider storing the substrings in a table and joining that way later.

### The Length Operator

The length operator `#` works on strings and tables. On strings, it returns
the number of bytes in the string. On tables, it returns the length of the
sequence represented by the table. (The author uses sequence in
a semi-technical way to describe a non-gappy array-like table indexed with
numbers, starting at 1 by convention in Lua.)

Idioms:

    a[#a] -- value of the last item in a
    a[#a] = nil -- remove the last item in a
    a[#a+1] = 'foo' -- append item to a

### Precedence

Operator precedence in Lua follows the table below, moving from higher to
lower priority:

    ^
    not # - (unary)
    * / %
    + -
    ..
    < > <= >= ~= ==
    and
    or

All binary operators are left associative, except for '^' and '..' which
are right associative.

### Table Constructors

Constructors are tables that create and initialize tables.

The simplest constructor is `{}` which creates an empty table.

You an also easily initialize a list:

    days = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
             "Friday", "Saturday" }

In such a case, `days[1]` gets the value "Sunday" and so on.

Lua offers sugar to initialize a record-like table:

    a = { x = 10, y = 20 }
    -- equivalent
    a = {}
    a.x = 10
    a.y = 20

The first version is faster, however, since Lua creates the table with the
right initial size immediately.

No matter how you create a table, you can always add and remove fields
later.

You can mix record-style and list-style initializations in one constructor:

    polyline = { color = "blue", thickness = 2,
                 {x = 0}, -- polyline[1]}
                 {x = 1}  -- polyline[2]
               }

As this example shows, you can also nest constructors and tables to produce
more complex structures.

The two basic constructor forms have limitations. You cannot initialize
fields with negative indices that way, nor use string indices that are not
proper identifiers in Lua. If you want something like that, you can use
a more general format:

    opnames = { ["+"] = "add", [i-20] = "foo" }

The syntax is less convenient, but the assignment is more flexible and
powerful. Both list-style and record-style constructors are really just
sugar for this form:

    {x = 0, y = 0} -- equivalent to {["x"] = 0, ["y"] = 0}
    {"r", "b", "g"} -- equivalent to {[1] = "r", [2] = "g", [3] = "b"}

You can always add a comma after the last entry. Nothing breaks. You can
also use semicolons (with no difference in meaning from a comma). The
author uses semicolons to delimit different sections in a constructor
(record section and list section).
