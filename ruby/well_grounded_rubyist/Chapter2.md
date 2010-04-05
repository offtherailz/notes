% Notes on Chapter 2 of WGR
% Peter Aronoff
% 2010-04-02

# Objects, methods, and local variables

## Objects before classes

B repeats that objects are primary in Ruby - even before classes. Although any given object will (and must) belong to some class, what an object can do is more important than its ancestor chain. And since Ruby is so dynamic, an object's ancestry doesn't determine what it can do. 

## A nuance about return values and the return keyword

Every method returns a value. If you don't use the keyword `return` explicitly, Ruby returns the last evaluated expression in the method. This means that often you can omit the word return and count on Ruby to do the right thing. However, there are two cases where you do need to say `return` explicitly:

+ If you return early in the method (perhaps after certain tests come out a certain way)
+ If you return a list _not_ packaged explicitly as an array

The problem is that `a, b, c` isn't valid all by itself. So you can't build up three values that way and then end a method with just a bare, comma-separated list of the variables. Instead, you need to explicitly say `return a, b, c` or `[a, b, c]`. In either case, the return value takes the shape of an array of items.

## Boolean methods

Ruby has three special built-in values: `true`, `false`, and `nil`. Any expression or method can be used that returns `false` or `nil` comes out false in a boolean context; any other value comes out true. Although there are methods that are specifically made to be boolean tests, anything can do in a pinch.

By convention, methods that are meant to be boolean tests end in a question mark in Ruby. For example `File.file?(item)` returns true if `item` is a file and false otherwise.

## Important helper methods - nota bene

Since Ruby is so dynamic - has B mentioned that a few hundred times already? - you can never quite tell what methods an object can respond to. Or at least, it isn't always guaranteed that you can tell. Thus, Ruby has a built-in method of all objects that can help you check. The parameter should be a symbol or string, and the return value will be true or false:

    object.respond_to?(method)
    # for example
    'hello'.respond_to?(:to_i)
    # => true


In addition, Ruby has a built-in method `send` that allows you to send arbitrary methods to objects - if you are getting them in a way that doesn't allow you to know what to call in advance. It looks as you would expect: `object.send(method)`. Again, the parameter should be a string or a symbol.
