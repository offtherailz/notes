% Notes on Chapter 1 of WGR
% Peter Aronoff
% 2010-04-01

# Bootstrapping your Ruby literacy

## Three levels

The chapter considers Ruby from three angles:

> + The core language: design principles, syntax, semantics
+ The extensions and libraries that ship with Ruby, and the facilities for adding extensions of your own
+ The command-line tools that come with Ruby, with which you run the interpreter as well as some other important utilities (4).

## Methods and objects

> The whole universe of a Ruby program consists of objects and the messages that are sent to them (9).

Objects can appear in literal form (surrounded by quotes for strings, for example, or brackets for arrays) or in the form of variables. Every object can understand certain messages, and each message corresponds to a method. A method is a named function that the object can trigger or perform or respond to. Methods tend to appear after the dot operator, in forms like `[5,4,3,2,1].sort`.

We say that the message is "called" or "sent to the object." Black distinguishes between these two expressions in a subtle way. Although in general, you send an object a message and the object then performs the method that corresponds to the message, in some cases there is no such method. These cases are where we get into Ruby meta-programming.

Every object belongs to a specific, single class. However, class is less important in Ruby than an object and its methods. Objects can gain methods far beyond those of their originating class in Ruby. We don't so much worry about what kind of a thing a Ruby object is as what messages it can respond to.

## Ruby's installation details

You can always get information about where things are and how your version of Ruby was built, using the `Config::CONFIG` hash. In order to have access to this hash, `require rbconfig` in a script or irb. 

## Command-line flags

Most are as I would expect from Perl. However, `-v` oddly is not identical to `--version`. The short form gives the version of the interpreter and then runs any code or script that follows (with warnings).
