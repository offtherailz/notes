# Chapter 14 - The Preprocessor

## How the preprocessor works

The preprocessor's behavior is controlled by preprocessing directives.
These appear in lines beginning with a '#' character. Two very common
directives are `#define` an `#include`.

The `#define` directive defines a macro -- a name that represents something
else. When the preprocessor sees a `#define`, it stores the name of the
macro together with its expansion. When the macro is used later in the
program, the preprocessor replaces the macro by its defined value.

The `#include` directive tells the preprocessor to open a particular file
and include its contents as part of the program being compiled.

## Preprocessing directives

+ Main types
    + Macro definition: `#define` defines a macro; `#undef` removes one
    + File inclusion: `#include` brings in a specified file
    + Conditional compilation: `#if`, `#ifdef`, `#ifndef`, `#elif`,
      `#else`, and `#endif` allow blocks of text to be included or
      excluded, depending on testable conditions
+ Less common types
    + `#error`
    + `#line`
    + `#pragma`

Some general rules that apply to all directives.

+ They begin with a `#` symbol.
+ Any number of spaces and horizontal tabs can separate tokens in
  a directive.
+ Directives always end at the first new-line character, unless explicitly
  continued. To continue onto the next line, you use a backslash, as in
  shell scripting.
+ Directives can appear anywhere in a program. Although `#define` and
  `#include` generally appear at the start of a file, other directives can
  show up later, even in the middle of function definitions.
+ Comments can appear on the same line as a directive.

## Macro definitions

Macro definitions can be simple (also known as 'object-like') or
parameterized.

### Simple macros

The definition of a simple macros has this form:

    #define identifier replacement-list

The replacement-list is any sequence of preprocessing tokens. These can
include identifiers, keywords, numeric constants, character constants,
string literals, operators and punctuation.

**NB**: A common error is to put an assignment operator inside a macro
definition. This is *wrong*. Don't do it.

    #define N = 100 /* Uh oh... */
    ...
    int a[N];       /* Boom: becomes int a[= 100]; */

By the same logic, don't end a macro definition with a semicolon. You would
get a problem in exactly the same way.

Simple macros are used mostly for defining what K and R call "manifest
constants".

    #define STR_LEN 80
    #define TRUE 1
    #define FALSE 0
    #define PI 3.14159
    #define CR '\r'
    #define MEM_ERR "Error: not enough memory"

Using macros in this way brings several benefits.

+ Programs are easier to read without magic numbers in particular. But an
  orderly use of macros for strings and characters can help in similar
  ways.
+ Programs are easier to modify. If you need to change that memory error's
  wording later and it appears in a hundred places, a macro will save work.
+ It helps to prevent typos or inconsistencies.

There are also some trickier or less common uses for simple macros.

+ Make minor changes to the syntax of C:

        #define BEGIN {
        #define END }
        #define LOOP for (;;)

+ Rename types:

        #define BOOL int

+ Control condition compilation:

        #define DEBUG

The first two aren't great ideas. Changing C syntax makes things harder for
others who want to read your code. Renaming types can be done better with
type definitions.

### Parameterized macros

A parameterized macros (or a function-like macro) allows you to use macros
in more powerful ways.

    #define identifier(x1, x2, ..., xn) replacement-list

**NB**: In such a macro, space is not allowed between the identifier and
the left parenthesis. Otherwise, the preprocessor will take the macro as
a simple one.

You can use these to make mini-functions or to stand in for little bits of
code that get annoying to type. However, they bring pros and cons.

+ Pros
    + The program may be a little faster. C99 inline functions can match
      this improvement.)
    + Macros are "generic". You can write a max to handle ints, longs,
      doubles, floats, etc. (See cons.)
+ Cons
    + Compiled code will often be larger.
    + Macros are "generic". No type-checking, no automatic casting, as in
      functions. (See pros.)
    + You can't have a pointer to a macro.
    + A macro may evaluate its arguments more than once. Thus arguments
      with side-effects (`i++`) can cause really hard to find bugs.

## Special operators

You can use `#` or `##` in macros for special effects. The `#` operator
turns a macro argument into a string literal. It can appear only in the
replacement list of a pareterized macro. (The operation here is known as 'stringization'.)

Here's one use for that in debugging:

    #define PRINT_INT(n) printf(#n " = %d\n", n)
    ...
    PRINT_INT(i/j);
    /* The above becomes printf("i/j" " = %d\n", i/j); and by automatic
       concatenation, it will output i/j = 5. */

The `##` operator can paste two tokens together to form a single token.
(The operation is known as "token-pasting".) If one of the operands is
a macro parameter, the pasting occurs after the macro has been replaced by
the argument given.

    #define MK_ID(n) i##n
    ...
    int MK_ID(1), MK_ID(2), MK_ID(3);
    /* The above becomes int i1, i2, i3; */

The `##` operator isn't very common. King comes up with the following
example for it:

    #define GENERIC_MAX(type)       \
    type type##_max(type x, type y) \
    {                               \
            return x > y ? x : y;   \
    }
    ...
    GENERIC_MAX(float)
    /* The above yields float float_max(float x, float y) { etc. }

## General properties of macros

+ A macro's replacement list can contain invocations of other macros.
+ The preprocessor only replaces entire tokens, not portions of tokens. The
  preprocessor ignores macro names that are embedded in identifiers,
  character constants and string literals.
+ A macro definition normally remains in effect until the end of a file.
  Macros defined inside functions do *not* have local scope. They are valid
  for the rest of the file.
+ A macro can't be defined twice unless the new definition is identical to
  the old one. There can be differences in spaces, but the tokens in the
  replacement list and the parameters (if any) must be the same.
+ Macros can be undefined by `#undef`. After a macro has been undefined, it
  can be redefined differently.

## Parentheses in macros

Here's how to decide when to use extra parentheses in macro definitions.

1. If the macro's replacement list contains an operator, always enclose the
   list in parentheses.

        #define TWO_PI (2*3.149159)

2. If the macro has parameters, put parentheses around each parameter every
   time it appears in the replacement list.

        #define SCALE(x) ((x)*10)

## Creating longer macros

You can use the comma operator to create longer macros.

    #define ECHO(s) (get(s), puts(s))

Since the comma operator can only join expressions (not statements), this
method has limits. If you must join statements, you can use a `do` loop
where the condition is false:

    #define ECHO(s)          \
            do {             \
                    gets(s); \
                    puts(s); \
            } while (0)

Then when you use `ECHO` you follow it with a semicolon. That semicolon
completes the `do` statement.

This can allow you to create more powerful, complex macros, but don't abuse
it.

## Predefined macros

C offers a number of useful predefined macros:

    __LINE__
    __FILE__
    __DATE__    /* Mmm dd yyyy Dec 20 2012 */
    __TIME__    /* hh:mm:ss 22:18:43 */
    __STDC__    /* 1 if the compiler conforms to C standard (C89 or C99) */

## Empty macro arguments

C99 allows any or all of the arguments to a macro call to be empty. The
regular number of commas must appear, however. Whether or not this is
useful depends on the macro.

    #define ADD(x,y) (x + y)
    ...
    i = ADD(j, k);
    i = ADD(,k);    /* Becomes i = (+k) */

You can use empty macro arguments with `#` and `##` as well.

## Macros with a variable number of arguments

In C99 macros can take an unlimited number of arguments. The main use is
passing those arguments to a function that accepts a variable number of
arguments, like `printf` or `scanf`.

    #define TEST(condition, ...) ((condition) ? \
      printf("Passed test: %s\n", #condition) : \
      printf(__VA_ARGS_))

## The __func__ identifier

C99 also provides an identifier `__func__` for every function. It behaves
like a string variable that stores the name of the currently executing
function. It's useful for debugging.

    #define FUNCTION_CALLED() printf("%s called\n", __func__);
    #define FUNCTION_RETURNS() printf("%s returns\n", __func__);

You can also pass `__func__` to another function to let it know the name of
the calling function. (None of this has anything to do with the
preprocessor. King put it here since so much of the preprocessor has to do
with debugging.)

## Conditional compilation

### The `if` and `endif` directives

The preprocessor allows you to define directives that are conditional.

    #define DEBUG 1
    ...
    #if DEBUG
    printf("Value of i: $d\n", i);
    ...
    #endif

When the preprocessor hits the `#if` directive, it evaluates the constant
expression. If that is zero, the lines between `#if` and `#endif` are
removed from the program during preprocessing. Otherwise, they are
included. Either way, the `#if` and `#endif` don't make it into the program
itself.

The `#if` directive treats undefined identifiers as macros that have the
value 0. So if you just leave out a definition for `DEBUG`, it is false by
default. This might come in handy, but I would probably rather be explicit.

### The `defined` operator

The `defined` operator returns 1 if the identifier is a currently defined
macro. Otherwise, it yields 0.

    #if defined(DEBUG)

Since `defined` only tests if the macro is _defined_, not if it has
a specific value, this allows you to set a macro more simply:

    #define DEBUG
    ...
    #if defined(DEBUG)
    ....
    #endif

### The `ifdef` and `ifndef` operators

The preprocessor also provides two operators to make testing for whether
a macro is defined or not simpler.

    #ifdef macro /* Same as #if defined(macro) */
    #ifndef macro /* Same as #if !defined(macro) */

### The `elif` and `else` directives

You can also use `#elif` and `#else` to have branches for a conditional
compilation.

    #if defined(WIN32)
    ...
    #elif defined(MAC_OS)
    ...
    #elif defined(LINUX)
    ...
    #endif

### Uses of conditional compilation

+ Debugging
+ Programs that are portable to several machines or operating systems
+ Programs to be compiled with different compilers
+ Providing a default definition for a macro
+ Temporarily disable code that contains comments (since comments can't
  nest)
+ Protecting header files against multiple inclusion

## Miscellaneous directives

### The `error` directive

The `#error` directive allows you to print out a short message as needed.
The directive is normally used in conjunction with conditional compilation,
and in extreme circumstances. Some compilers will immediately terminate
compilation when one is triggered.

    #if INT_MAX < 100000
    #error int type is too small
    #endif

Another use might be in the `#else` portion of a complex condition - if
nothing suitable is found.

    #if defined(WIN32)
    ...
    #elif defined(MAC_OS)
    ...
    #elif defined(LINUX)
    ...
    #else
    #error No operating system match found
    #endif

### The `line` directive

The `#line` directive allows you to alter the way that program lines are
numbered. You can also use it to make the compiler think it's reading the
program from a file with a different name.

    #line n
    /* n should be an integer between 1 and 32627 (2147483647 in C99) */
    #line n "file"

Use of these directives will change the value of `__LINE__` and `__FILE__`.

These two forms of the `#line` directive are rarely used by programmers
directly. They are used by programs that generate C code as output. For
example, `yacc` uses them.

### The `pragma` directive

The `#pragma` directive allows you to request special behavior from
a compiler. For example:

    #pragma data(heap_size => 1000, stack_size => 2000)

What commands are available to set (and how to set them) is entirely
dependent on the compiler. The preprocessor must ignore any `#pragma`
directive that includes an unrecognized command. It won't emit any error
messages in such a case.
