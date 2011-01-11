% Notes on *Programming in Haskell* by Graham Hutton
% Peter Aronoff
% 20101107

# Chapter 1

## 1.1 Functions

A function in Haskell is:

> a mapping that takes one or more arguments and produces a single result, and is defined using an equation that gives a name for the function, a name for each of its arguments, and a body that specifies how the result can be calculated in terms of the arguments

As an example: `triple x = x + x + x`

## 1.2 Functional programming

Functional is a *style* of programming where the basic method of computation is the application of functions to arguments. A functional programming language is one that supports and encourages this functional style.

## 1.3 Features of Haskell

+ Programs tend to be concise.
+ Haskell has a powerful type system.
+ Lists and list comprehension features are built right in and easy.
+ Recursion is a basic and natural way to loop in Haskell.
+ Haskell is a higher-order functional language. Functions are first-class citizens: a function can take a function as an argument or produce a function as a result.
+ Since Haskell functions are pure and without side effects, Haskell provides monads as a way of handling cases that require impure side effects.
+ Haskell uses lazy evaluation. No result is computed before it is needed. (This allows Haskell to work easily with infinite lists, for example.)
+ The purity of Haskell allows for a great deal of basic reasoning and proof for programs.

## 1.4 A historical survey of fp up to Haskell (skipped here)

## 1.5 A taste of Haskell

Hutton walks through a definition and explanation of quicksort in Haskell. His version looks like this:

    qsort [] = []
    qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
                   where
                        smaller = [a|a <- xs, a <= xs]
                        larger = [a|a <- xs, a > xs]
