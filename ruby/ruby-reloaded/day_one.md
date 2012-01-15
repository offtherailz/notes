# Ruby Reloaded (Day one: 20111205)

## Outline

+ Day One
  + Ruby Ecosystem
  + Code Style
  + REPLs
  + Core Class Tour
  + Ruby 1.9 Specifics
+ Day Two
  + TDD
  + Object Orientation Concepts and Design
  + Code Walking and Project Structure
  + Metaprogramming
  + Creating a DSL Library
  + Q&amp;A

## Sinatra (surprise extra)

Check out pstore (std lib?) for persistence; it's sort of like BerkeleyDB.

## Ecosystem

MRI 1.0, Christmas 1996 (Ruby itself and many Ruby-related libs are
released on the 25th).

MRI 1.6, First time systems appeared (Rails originally didn't use symbols).

MRI 1.8, released around 2003. (1.8.x is an interpreter.)

MRI 1.9.0, released Christmas 2007. 1.9 was originally meant be an unstable
development only release. (The 1.9 series is a virtual machine
implementation not just an interpreter.)

## Standard Library

Try running a program with `ruby -rprofile file.rb`.

Check out `require 'strscan'`.

## Code Style

+ 2 spaces for indentation, soft tabs
+ Provide rdoc-friendly comments
+ Curly braces versus do...end alternative: Use curly braces for functional
  (no side-effects) blocks; use do...end for side-effect blocks.
+ Bang methods are dangerous versions of non-bang methods

## REPLs

A REPL is a read-eval-print-loop. Ruby comes with one `irb` standard. Now
there is also `pry`.

## Core Classes

There's an actual method `.coerce` for numbers. You could monkey-patch
String to have it be coerced in mathematical operations.

Index a string by a string. This is useful for a test with less overhead
than a regex:

    x =~ /fox/
    x['fox']

The first returns `nil` on no match or start of match index on a match. The
second returns `nil` if there's no match or the string on a match.

Don't do this:

    Array.new(4, Hash.new) # Each item in the array is a ref to one hash

Instead do this:

    Array.new(4) { Hash.new } # Four different hashes

Enumerable is cool.
