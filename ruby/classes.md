% Classes in Ruby
% Peter Aronoff
% 2009-09-28

Generally speaking, a class in OO software is a blueprint or a factory for objects (nouns but also abstract types). It bundles and defines the potential attributes (adjectives) and methods (verbs) of object instances (tokens, nouns).

In Ruby, you define a class using the `class` keyword in a block. The name of the class should have a capital letter:

	class Whale
	  # Stuff here about the Whale class
	end

Classes can inherit (only singly), in which case, you define the class like so:

	class Whale < Mammal
	  # Stuff here about the Whale class
	end

When a new object is created, you can set its original state using the built-in `initialize` method. This method is special: it's private, and you call it using `new`. For example:

	class Whale < Mammal
	  def initialize(length, weight, color)
	    @length = length
		@weight = weight
		@color = color
	  end
	end

	enoch = Whale.new('13 feet', '2000 pounds', 'white')

Note two things about this. First, as Dave Thomas points out, 

> this is the pattern you want to aim for. Your `initialize` method sets up an environment for your object, leaving it in a usable state. Other methods then use that state (*Programming Ruby 1.9*, 39).

Second, `@` indicates an instance variable which is available to all the methods of a given object. The instance variables of a given object define that object's state at any given point in execution. Thomas distinguishes instance variables like this from 'attributes' which present a public face for the information in an instance variable.

In order to have a true attribute, you need to create an accessor. Theoretically, you could do it by hand:

	class Whale < Mammal
		def initialize
		  # As before
		end

		def weight
		  @weight
		end
	end

But it's easier to simply use `attr_` methods to create accessors. There are three available:

- `attr_reader` creates a getter method
- `attr_writer` creates a setter method
- `attr_accessor` creates a combined method for setter or getter

It's rare to want a write-only accessor, so the two most commonly seen are `attr_reader` and `attr_accessor`. Here's an example both creating and using them:

	class Whale < Mammal
	  attr_reader		:color
	  attr_accessor		:length, :weight

	  def initialize(length, weight, color)
	    @length = length
		@weight = weight
		@color = color
	  end
	end

	enoch = Whale.new('13 feet', '2000 pounds', 'white')

	puts enoch.color
	puts enoch.length
	enoch.weight = '2050 pounds'
	puts enoch.weight

In Ruby, you can also trivially create virtual attributes. A virtual attribute is an externally visible state of your object instance which is *not* a pointer to an instance variable. It feels as though it is, to the user, but the implementation hides the details. Here is a random example:

	class Whale < Mammal
	  attr_reader		:name, :nickname

	  def initialize(name)
	    @name = name
	  end

	  def nickname
	    name + 'ito'
	  end
	end

	enoch = Whale.new(enoch)
	puts "His nickname is #{enoch.nickname}."
