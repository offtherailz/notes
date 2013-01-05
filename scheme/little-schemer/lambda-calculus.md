# The Lambda Calculus

## History

Lorenzo Church developed the lambda calculus in 1936. He was studying
computation and the idea of what was computable. The lambda calculus is
a mathematical system to help in that study. What Church came up with is
equivalent to Alan Turing's Turing machine, though he discovered it
independently. Church wanted to create a formal system for all of
mathematics, but he gave up on that goal.

## Introduction

The lambda calculus is a functional language. It is based on the theory of
mathematical functions. In the lambda calculus, you express all
computations in terms of functions. Because of a few advantages, the lambda
calculus can serve as a model for purely functional languages:

+ Treats functions and data uniformly
+ Has very few side effects
+ Simple but concise notation

## Syntax

The two most essential features of the lambda calculus:

+ Function definition or lambda abstraction
+ Function application or lambda application

Context free grammar for the lambda calculus:

    <expression>    :=  <name> | <function> | <application>
    <function>      :=  λ <name>.<expression>
    <application>   :=  <expression><expression>
    <name>          :=  a | b | c | ... | Z

A name (or variable) is be a simple letter, such as `x` or `y`. An
expression can be surrounded by parentheses for clarity. The following are
equivalent:

    E
    (E)

The only keywords in the language are 'lambda' and '.' (The lambda is
sometimes written as 'λ' or '\'.)

Function application associates from the left. Consider this expression:

    E1 E2 E3 ... En

Application would proceed as if it were this:

    (...((E1 E2) E3)...En)

## An example function: identity

Here is the identity function in the lambda calculus:

    λx.x

The identifier after the lambda is the name of the function. The expression
after the point (here just a single letter) is the function's body.

Functions can be applied to expressions:

    (λx.x)y

The parentheses are there for clarity. That is the identity function
applied to y. You evaluate a function application by substituting the value
of the argument `x` (here `y`) into the body of the function definition.

    (λx.x)y = [y/x]x = y

The notation `[y/x]` means that all occurences of `x` are substituted by
`y` in the expression to the right.

The names of arguments in function definitions are not important. They are
merely placeholders. So the following are all equivalent ways of expressing
the identity function.

    (λz.z) ≡ (λy.y) ≡ (λt.t) ≡ (λu.u)

## Free and bound variables

In the lambda calculus, all names are local to definitions. In the function
`λx.x`, the `x` is bound since the `x` in the body is preceded by `λx`.
A name not preceded by a `λ` is a free variable. Some examples:

    (λx.xy)
    (λx.x)(λy.yx)

In the first example, the `x` is bound and the `y` is free. In the second,
the `x` in the first body is bound to the first `λ`. The `y` in the second
body is bound to the second `λ`, and the `x` in the second body is free.
The `x` in the second body is completely independent from the `x` in the
first expression.

Sources:

+ [Lambda Calculus Tutorial][lct]

[lct]: http://classes.soe.ucsc.edu/cmps112/Spring03/readings/lambdacalculus/project3.html
