# Simply Scheme

## Chapter 4: Defining Your Own Procedures

As an example:

    (define (square x)
      (* x x))

The definition has four parts:

+ The keyword `define` which says we are defining something
+ Inside parentheses, the procedure name and any arguments it takes. Note
  that you don't use commas here between arguments.
+ The body of the procedure. This is an expression whose value is the
  function's return value.

### Special forms

`define` is a special form. (Technically, `define` is a keyword, and the
entire expression `(define ()...)` is a special form. But people use
'special form' in both ways.) Normally, an expression is a function call.
In that case, Scheme evaluates all the sub-expressions and then applies the
procedure to the argument values. However, in the case of special forms,
Scheme doesn't evaluate all the sub-expressions. Each special form has its
own evaluation rule. In the case of `define`, no part of the definition is
evaluated.

### Functions and Procedures

We can distinguish between a procedure and a function. A function is
a connection between some values you have and a new value: values go in and
values come out. A procedure is the recipe by which a computer can work out
a result. Two equations can describe different processes but compute the
same function. For example:

    (define (f x)
      (+ (* 3 x) 12))

    (define (g x)
      (* 3 (+ x 4)))

They also note that in real life you don't necessarily need a procedure to
represent a function. You can represent a function by a table or a graph,
for example.

### Argument Names versus Argument Values

When we define a procedure, we give a name for each argument. The name is
simply a stand-in for a value which will be provided when the function is
actually called. The technical label for the abstract name is 'formal
parameter', though people may say 'formal' or 'parameter' alone. The
technical term for the actual value is 'actual argument'. In a call like
`(square (+ 5 9))`, we can also distinguish between the 'actual argument
expression' -- `(+ 5 9)` and the 'actual argument value' -- 14.

### Procedure as Generalization

If we want to average two numbers, we can do that in Scheme:

    (/ (+ 17 25) 2)

But even better is to write a function that averages *any* two numbers:

    (define (average x y)
      (/ (+ x y) 2))

Now we can just write `(average 17 25)`. There are multiple gains here.
First, the next time we will solve the problem quicker. Second, we can
focus on the problem and its solution, rather than on its method or the
details for how to get to the end. By creating new functions, we add new
items to the list of things we can do without too much thinking. That's
good. (Not that thinking is bad, but you don't want to think through
everything, every time. It would be exhausting, and you would get far less
done.)

### Composability

The great thing about functions is that you can put them together in
arbitrarily complex ways. Whether a function is primitive or defined by
a user, you can then use that function on its own or in order to produce
a value for another function. Go nuts.

### The Substitution Model

When a procedure is called, Scheme carries out the process in its body in
the following manner. First, it makes a copy of the body with the arguments
in place of the formal parameters. Then Scheme evaluates the body. If the
body itself involves further procedures, this goes on in multiple steps.
