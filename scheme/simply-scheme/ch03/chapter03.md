# Simply Scheme

## Chapter 3: Expressions

In the REPL, Scheme reads what you type and *evaluates* it. This chapter
will help explain what it means to evaluate something.

What you type is called an 'expression'. An expression can be a single
value (e.g. 26) or something more complex in parentheses. The first kind of
expression is called an atom or atomic expression. The second kind is
called a compound expression. It is compounded out of multiple smaller
expressions. You can also call the expressions within a compound expression
subexpressions.

Compound expressions tell Scheme to do a procedure. Other names for this
are calling the procedure, invoking it or applying it.

In order to understand expressions, you must already understand (some)
expressions. What? Well, a compound expression contains expressions. So the
only way to understand it is to understand what it contains. This might
seem viciously circular, but the understanding stops when we reach atomic
expressions. An atomic expression like 4 is self-evaluating, for example.

### Little People

They introduce a metaphor of people inside the computer to explain how
evaluation works. Take this mathematical expression:

    (- (+ 5 8) (+ 2 4))

Alonzo hires Alice to do the subtraction. She can subtract, but she needs
numbers to work with. She asks Alonzo for her numbers. He looks into the
expression and hires two more people to compute the sub-expressions that
are additions. Bernie, the first addition specialist, also wants numbers.
Alonzo sees the numbers 5 and 8, so he hands these to Bernie. Bernie
returns 13. Cordelia, the second addition specialist, wants numbers. Alonzo
hands her 2 and 4; she returns 6. Alonzo now hands 13 and 6 to Alice. She
returns 7, and the expression is evaluated completely.

A few points of detail. Alonzo can keep straight about what is an argument
to what because of the parentheses and their grouping. Second, when
talking, it sounds like Bernie does his addition before Cordelia does hers.
However, this is left for implementations to determine. Cordelia may do her
work first, or they may do the work in parallel on a multi-core computer.
What matters is only that the sub-expressions must be evaluated *before*
the outer expression is evaluated. But the order of sub-expressions is not
dictated by Scheme.

### Digression on order of evaluation from SICP

Since they haven't introduced variables yet, they don't get into the issue
of normal-order evaluation versus applicative-order evaluation. Imagine we
have the following definitions:

    (define (square x) (* x x))

    (define (sum-of-squares x y) (+ (square x) (square x)))

    (define (f a) (sum-of-squares (+ a 1) (* a 2)))

Now let's imagine we want to evaluate this. First we will use the method
that Scheme actually follows. In this method (applicative-order evaluation),
the interpreter first evaluates the operator and operands and then applies
the resulting procedure to the resulting arguments. For the following
examples, we will evaluate the expression `(f 5)`.

First we retrieve the body of `f`:

    (sum-of-squares (+ a 1) (* a 2))

Then we replace the formal parameter by the argument 5:

    (sum-of-squares (+ 5 1) (* 5 2))

Now we have a combination with two operands (the sub-expressions) and one
operator (sum-of-squares). We must evaluate the operator to get the
procedure we need to apply, and we must evaluate the operands to get the
arguments.

We can reduce the sub-expressions:

    (sum-of-squares 6 10)

Now we apply the sum-of-squares operation to those:

    (+ (square 6) (square 10))

Using the definition of square, that reduces to:

    (+ (* 6 6) (* 10 10))

By multiplication that reduces to:

    (+ 36 100)

Finally yielding 136.

Under this model, the interpreter first evaluates the operator and operands
and then applies the procedure. But an alternative model would not evaluate
the operands until their values were needed. This method would just keep
substituting operand expressions until we were down to expressions with
only primitive operators. Then the evaluation would proceed.

So let's do it again:

    (f 5)

    (sum-of-squres (+ 5 1) (* 5 2))

    (+ (square (+ 5 1)) (square (* 5 2)))

    (+ (* (+ 5 1) (+ 5 1) (* (* 5 2) (* 5 2))))

Now reductions:

    (+ (* 6 6) (* 10 10))

    (+ 36 100)

    136

The answer is the same, but we get there by a different route. In
particular, `(+ 5 1)` and `(* 5 2)` are evaluated twice in this version.

This second method -- fully expand then reduce -- is known as 'normal-order
evaluation', in contrast to 'applicative-order evaluation' -- evaluate the
arguments and then apply.
