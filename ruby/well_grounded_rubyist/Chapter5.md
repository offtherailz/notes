% Notes on Chapter 5 of WGR
% Peter Aronoff
% 2010-04-05

# The default object (self), scope, and visibility

At any given time, there is one and only one current object or `self` in Ruby. There are, however, a number of different contexts, and the identify of `self` shifts according to what context you are in.

Context | Example | What object is self?
--------|---------|--------------------
Top level of program|Any code outside blocks|`main` (built-in default object)
Class definition| class C; self| The class object C
Module definition| module M; self| The module object M
Method definitions|1. Top level method|Whatever is `self` when the method is called
cont.|2. Instance method in class|An instance having that method called on it
cont.|3. Instance method in module|A. Individual object extended by M
cont.|cont.|B. Instance of class that mixes in M
cont.|4. Singleton method on specific object|obj


## Switching self

It's essential to know when and how the identify of `self` will change in Ruby code. When control passes to a new class or module, self switches to that class or module. In addition, when you enter an instance method defition or a singleton method (including a class method), self will change to be the object responding to that method (i.e., the instance or the class).

## Privileges of being self

The primary privilege of self is that it is the default sender of messages. What this means is that if you write `method_call` instead of `object_name.method_call`, then the implied object is `self`. In practice, this gets used most often (?) to call one instance method in a class from another instance method of the same class:

    class C
      def x
        puts "hello from C::x"
      end
      def y
        puts "In C::y, about to call x without an explicit receiver object"
        x
      end
    end

This all works out just right, as if by magic. When you instantiate an object of the class C and then call `foo.y` that instance is `self` when the method `y` is called. Hence, when the Ruby interpreter gets to the bare `x`, it interprets it as `self.x` and uses that instance of C as `self`. Magic.

The other key privilege of self is that whatever is self at any given time is the owner of all instance variables in that scope. The following example illustrates this idea:

    class C
      def show_var
        @v = "Hello, people of Earth!"
        puts @v
      end
      @v = "Goodbye, people of Earth!"
    end
    C.new.show_var

First, note that this would print "Hello, people of Earth!" rather than "Goodbye, people of Earth!" Second, the reason is that `@v` is two different items in this code. The first is an instance variable of an instatiation of C; the second is an instance variable of the _class_ rather than any specific instance of that class.

## Variable scope

B discusses three variable scopes: global, local and class variables. He does not discuss instance variables since, as he puts it, they are self-scoped, and he has already discussed that.

## Global scope

A global variable begins with a `$`, and it is available everywhere in your program. They never go out of scope, and their value is visible everywhere, no matter how deeply nested your classes and modules become. In addition to any globals that you might create, Ruby has a number of pre-defined globals (a la Perl). 

As tempting as they are to new programmers, globals are generally a bad idea. Initially, they seem great: you can create a few globals and then easily share information via the global between different classes and modules. However, this violates a basic principle of OOP and good programming: objects should encapsulate their data, and the pieces of your program should be loosely rather than tightly coupled. This makes your programs more flexible and safer. Safer because you avoid unintended changes to globals affecting the whole of your program.

## Local scope

Every part of every program is its own local scope, and as local scopes shift, you get a brand new supply of local variables. If you are in one local scope and set a variable `x` to the value `5`, that does not change the `x` from another local scope, which may have the value `foo`.

Here are the basic rules for where local scopes begin and end:

+ The top level is its own local scope
+ Every class of module definition block has its own local scope. This is true for nested classes or modules as well.
+ Every call to a method generates a new local scope, with all local variables reset to an undefined state.

## Constants and lookup

Constants are visibile everywhere, but unlike globals a single constant may have more than one value at a time. If for example we have a constant `X` with a value of `1` in class C, module M, then we can always get at that value via `C::M::X`. However, there may be another constant `X` inside class C but outside module M, and that may have a value of `2`. We get that via `C::X`. 

Note that constant lookup is a bit like pathnames: you can do a relative or non-relative description. If you are inside class C and module M, then X refers (relatively) to `C::M::X`. However, if there were another `X` inside main that you wanted to reach, you can always reach up to get it by prepending `::` to your variable name: `::X`.

## Class variables

Class variables, like instance variables and globals, look different. They have two at signs before the identifier: `@@total`. They can be useful if you need to share data among an entire class (rather than storing it instance by instance). An example of such a case might be a class variable `@@manufacturers` for a CoffeMaker class. Another favorite example is a `@@total` variable for something countable, like a Cars class.

Although they can be useful and seem tempting, they are also dangerous. They are dangerous because strictly speaking they don't belong to a single class. Class variables belong to any class below the class they start in in the class hierarchy. That allows for a lot of action at a distance and confusion. 

As an alternative, B suggests that you can maintain per-class state using instance variables that belong to classes.

    class Car 
      @@makes = [] 
      @@cars = {} 
      attr_reader :make 
      def self.total_count 
        @total_count ||= 0 
      end 
      def self.total_count=(n) 
        @total_count = n 
      end 
      def self.add_make(make) 
        unless @@makes.include?(make) 
          @@makes << make 
          @@cars[make] = 0 
        end 
      end 
      def initialize(make) 
        if @@makes.include?(make) 
          puts "Creating a new #{make}!" 
          @make = make 
          @@cars[make] += 1 
          self.class.total_count += 1 
        else 
          raise "No such make: #{make}." 
        end 
      end 
      def make_mates 
        @@cars[self.make] 
      end 
    end

What he does here is manually create setter and getter methods for the instance variable `@totalcount`. That instance variable belongs to the _class_ rather than an instance of that class. However, if you subclass Car (say with Hybrid, as in B's example), then the parent and child class will automagically keep track of their own totals separately. No muss, not too much fuss.
