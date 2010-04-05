% Notes on Chapter 3 of WGR
% Peter Aronoff
% 2010-04-02

# Organizing objects with classes

## An odd point about setter methods, syntactic sugar and return values

Normally in Ruby, the return value of a method is - well - whatever it returns. However, methods that make use of the `item=(foo)` syntactic sugar are an important exception. Those methods allow you to define methods and then call them in ways that appear to be assignments rather than method calls. Because they look like assignments so completely, their return value, as in the case of assignments, becomes the value of the item assigned through the method. This is so, even if you explicitly return some other value in the method definition:

    class Foo
      def weird=(x)
        @x = x
        return 'foo'
      end
    end
    f = Foo.new
    f.weird = 6 # => 6 *not* 'foo'

I can't at the moment imagine this biting me, but it's worth noticing.

## Class methods

Classes are objects, and just like other objects, they have methods. It's important to remember where these methods might come from. In a nutshell, class methods come from one of three places:

+ From their class
+ From their superclass or ancestor chain
+ From any singleton methods that they have defined for them

As an example, `new` as a method is the first type of method. It belongs to the Class class, and this it comes from the class that all methods belong to. Methods like `attr_accessor` come from the parent chain. The Class class has Module as its superclass, and that's where the `attr` methods (among others are defined). Finally, you can always create singleton methods for your own classes as needed. B gives the example of defining a `most_expensive` method for his Ticket class. It makes sense for this to be a class method since no one instance has access to the prices of all the other tickets.

## Constants

Class names are (generally) constants, and you can also define constants within classes. Some key things to keep in mind about constants:

+ They must begin with a capital letter
+ They're not really constant. You can redefinine them, and in general that will just get you a warning from the interpreter. (If you extend or even redefine parts of a class itself, you don't even get a warning.)
+ If you create a constant within a class, it is available outside the class by using the `::Constant` notation. For example, the Math module defines pi. You get this item by referring to `Math::PI`. This is completely distinct from instance variables which cannot be directly accessed outside of a class.
    
    

