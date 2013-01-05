# Programming in Lua 3rd Edition

## Chapter 4 Statements

Lua supports both traditional and non-traditional statements. Traditional
Lua statements include assignment, control structures and procedure calls.
Non-traditional statements in Lua include multiple assignments and local
variable declarations.

### Assignment

Assignment is the basic way to change the value of a variable or a table
field.

    a = 'hello'
    t.n = t.n + 1

Lua also allows multiple assignment, which assigns a list of values to
a list of variables in one step. Both lists are comma separated.

    a, b = 10, 2*x

In a multiple assignment, Lua first evaluates all values and only then
executes the assignments. So you can use multiple assignment to swap
values:

    x, y = y, x
    a[i], a[j] = a[j], a[i]

Lua always adjusts the number of values to the number of variables. If the
list of values is shorter than the list of variables, the extra variables
get the value `nil`. If the list of values is longer, the extra values are
silently discarded.

Multiple assignment is not faster or better than single for simple
assignments. It *is* useful, however, for swapping and collecting multiple
return values from a signle function.

### Local Variables and Blocks

Lua supports local variables. You create a local variable with the `local`
statement:

    j = 10 -- global variable
    local i = 1 -- local variable

Unlike globals, local variables have a scope limited to the block where
they are declared. A *block* is the body of a control structure, the body
of a function or a chunk (the file or string where the variable is
declared). You can use `do...end` to create and control scope more
precisely.

Local variables are good style. They avoid cluttering the global
environment, and access to locals is faster than to globals. Also, locals
disappear when their scope ends, and this helps the garbage collector do
its job.

Lua treats local-variable declarations as statements. You can write a local
declaration anywhere you can write a statement. The scope goes from the end
of the declaration to the end of the block. Declarations can include an
initial assignment. Extra values work just as in a conventional assignment.
Unassigned local variables are also initialized with the `nil` value.

A common Lua idiom is this:

    local foo = foo

This preserves the value of the global foo, and it speeds up access to foo
in the local block or chunk. Lua is happy to let you declare locals
wherever you wish. You don't need to do them all up front.

### Control Structures

Lua provides a small and conventional set of control structures: `if`,
`while`, `repeat` and `for`. All control structures require an explicit
terminator: `end` for `if`, `for` and `while` and `until` for `repeat`.

The condition expression of a control structure can result in any value.
`false` and `nil` are falsey, and everything else is truthy.

#### if then else

An `if` statement tests its condition and executes its `then`-part or its
`else`-part accordingly. The `else`-part is optional.

    if a < 0 then a = 0 end
    if a < b then return a else return b end
    if lines > MAXLINES then
      showpage()
      line = 0
    end

To write nested `if` statements, you can use `elseif`. It's just like an
`else` followed by an `if`, but it avoids the need for multiple `end`s.
Because Lua lacks a switch statement, chains using `elseif` are relatively
common.

#### while

A `while` loop repeats its body while a condition is true. Lua first tests
the condition in the `while` loop. If the condition is false, then the loop
never runs. Otherwise, the body is executed, the test is run again and the
process continues.

    local i = 10
    while i > 0
        print("Still counting down...")
        i = i - 1
    end
    print ("Blastoff!")

#### repeat

A `repeat-until` statement repeats its body until its condition is true.
This statement does the test *after* the body, so it always executes at
least once.

    -- print the first non-empty input line
    repeat
      line = io.read()
    unline line ~= ''
    print(line)

Unlike many languages, in Lua the scope of a local variable declared inside
the loop of a `repeat` statement includes the condition:

    local sqr = x/2
    repeat
      sqr = (sqr+x/sqr)/2
      local error = math.abs(srq^2-x)
    until error < x/1000        -- error still visible in the condition

The `for` statement has two variants: the numeric for and the generic for.

#### Numeric for

A numeric `for` has the following syntax:

    for var = exp1, exp2, exp3 do
       <stuff>
    end

The loop will execute 'stuff' for each value of var from exp1 to exp2,
using exp3 as a step. The third expression is optional. When it's not
present, Lua defaults to a step of 1.

Typical examples:

    for i = 1, f(x) do print(i) end
    for i = 10, 1, -1 do print(i) end
    for i = 1, math.huge do
      <stuff>
      if test then break end
    end

The last example shows how to get a loop that is for all intents and
purposes endless. If you do this, remember to `break` somewhere inside.

In a `for` loop, each of the three expressions are evaluated only once,
before the loop starts. The control variable is automatically local to the
`for` statement. If you need the variable after the loop ends, save it into
another variable. Also, never change the value of the control variable in
the body of the statement. The effect is unpredictable. If you want to end
the loop early, do so by using `break`.

#### Generic for

The generic `for` traverses all the values returned by some iterator
function:

    for k, v in pairs(t) do print(k, v) end

The `pairs` function is a built-in iterator that gets all the keys and
values out of a hash-like table.

Although it looks simple, generic `for`s are very powerful. The standard
library provides several useful ones: `io.lines`, `pairs`, `ipairs`,
`string.gmatch` and more.

You can also write your own iterators easily. This will be the subject of
Chapter 7.

As with the numeric `for`, the loop variables are local to the body of the
statement, and you should never assign to them directly.

#### break, return and goto

The `break` and `return` statements allow you to jump out of a block. The
`goto` statement allows you to jump nearly anywhere.

Use the `break` statement to end a loop. It breaks the innermost loop
(`for`, `repeat` or `while`) that contains it. It cannot be used other than
in a loop. After `break`, control resumes from immediately after the broken
loop.

A `return` statement returns results from a function or simply finishes the
function. There is an implicit `return` at the end of every function, so if
your function returns no value, you can leave the `return` implicit.

As a matter of syntax, `return` can only appear as the last statement of
a block. If you *must* write a `return` in the middle of a block, wrap it
in a `do` block.

`goto` obviously gets a bad rap. But, says our author, the statement is
powerful and can improve code if used wisely. The syntax is conventional:
use the reserved word `goto` followed by a label. A label name is any valid
identifier in the call. But when placing the label in the code, you write
`::label::`. The colons are to make programmers think twice before using
a `goto`.

In Lua, `goto` is restricted. You can't jump into a block, since labels
follow the usual visibility rules. (A label outside a block is not visible
within that block.) You cannot jump out of a function. (The first rule
already means that you cannot jump *into* a function.) Third, you cannot
jump into the scope of a local variable.

As examples of good, simple uses for `goto` are to simulate a construction
that Lua lacks, such as `continue` or multi-level break or `redo`.

    while some_condition do
      ::redo::
      if some_other_condition then goto continue
      elseif yet_another_condition then goto redo end
      <code>
      ::continue::
    end

A detail about scoping: the scope of a local variable ends on teh last
*non-void* statement of the block where the variable is defined. Labels are
considered void statements. Here's an example where this matters:

    while some_condition do
      if some_other_condition then goto continue end
      local var = something
      -- some code here
      ::continue::
    end

The scope of `var` does not include the `continue` label since var's scope
ends right above the `::continue::` label (because it is a void statement).

The author mentions state machines as a good use of `goto`. He gives two
examples: checking input for an even number of zeros and a maze/room game.
