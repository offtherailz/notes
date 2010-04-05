% Ruby notes
% Peter Aronoff
% 2009-01-04

# My general notes on Ruby

## Useful methods on numbers:

	number.times { ...code... }
	number1.upto(number2) { ...code... }
	number1.downto(number2) { ...code... }
	number1.step(number2, number3) { ...code... }

The first three are pretty obvious: do the code number times, count up to
number 2 starting from number 1 and count down to number 2 starting from
number 1. The last is pretty cool: starting at number 1 go up to number 2,
using number 3 as the step. Example:

	0.step(20, 2) { |number| puts number }

This produces 0,2,4,6,8,10,12,14,16,18,20. Note also that the return result is
0. This is true for all of these: they return the number that you call the
method on.

## Arrays:

Ways to make an array - 

	array = [1, 2, 3, 4]
	array = ["foo", "bar", "bizz", "buzz"]
	array = %w[foo bar bizz buzz]
	array = %w/foo bar bizz buzz/

You can also create an array with a range or a block - 

	array = Array.new # => Creates an empty array
	array = Array.new(5) # Creates an array with 5 elements, all with nil
	array = Array(10) { |x| x *= 2 } # [0, 2, 4, 6, 8, 10, 12, 14, 16, 18]

Access items in the array - 

	array[0]    # => 0
	array.at(0) # => 0 - slightly faster?
	array[-1]   # => 18
	array.first # => 0
	array.last  # => 18
	array.index 4   # => 2 - Finds first match
	array.rindex 8  # => 4 - Finds last match
	array[0, 4] # => 0, 2, 4, 6 - You give start and how many, like slice
	array.slice(0, 4) # => 0, 2, 4, 6 - Speaking of which, there's slice
	array[0..4] # => 0, 2, 4, 6, 8 - Two dots is inclusive
	array[0...4] # => 0, 2, 4, 6 - Three dots is exclusive
	array.include? 4 # => true
	array.include? 9 # => false

Join arrays; set operations -

	a = [0, 2]
	b = [4, 6]
	c = a + b   # => [0, 2, 4, 6]
	c << a      # => [0, 2]
	c.concat(a) # => Ditto

The concat method creates a new array, but << adds items to the array. Also,
if you chain << calls with multiple arrays, the result is an array of arrays,
not a flat array.

	c << a << b # => [[0, 2], [4, 6]]

	c & a       # Intersection: only preserves elements common to both arrays
	c - a       # Difference: removing any duplicates
	c | a       # Union: joins the two and removes duplicates

Useful methods on arrays - 

	array.clear # => Empties the array back to nada
	array.select # => Like grep in Perl, run a block to select items
	array.map   # => Also called collect, like Perl's map function
	array.delete("item") # => Delete "item" if found, returns nil otherwise
	array.delete_at(5) # => Delete the item at index 5
	array.delete_if { |x| x % 2 != 0 } # => Delete all odd numbers
	array.flatten # => Flatten a multi-dimensional array

## Hashes:

Ways to make hashes -

	hash = { 1 => nil, 2 => nil, 3 => 'foo' }
	hash = Hash[ 1, nil, 2, nil, 3, 'foo' ]

Note that symbols (:foo) make especially good hash keys.

To get a value, enter the hash's name and use the key as the index:

	hash[1] # => nil

To get all the values or keys or both, use keys, values or each

	hash.keys # => 1, 2, 3
	hash.values # => nil, nil, 'foo'
	hash.each # => Returns an enumerator - use in a block, really

To check for or get at specific items, use some of these:

	hash.values_at 1, 2 # => nil, nil
	hash.index 3 # => 'foo' - index only works on one item

[]= can add an item or change an items value

	hash[4] = 'bar' # => Adds a key and value (4 => 'bar')
	hash[3] = 'baz' # => Changes the value for the existing key 3

To sort by value or do any fancier sort, use a block

	hash.sort { |a,b| a[0] <=> b[0] } # => Regular alpha sort on keys
	hash.sort { |a,b| a[1] <=> b[1] } # => Regular alpha sort on values
	hash.sort { |a,b| b[1] <=> a[1] } # => Reverse alpha sort on values

Clear a hash with clear and delete key-value pairs with delete

	hash.clear # => Fresh and new
	hash.delete(1) # => Delete the key-value pair if key 1 is found

You can also use delete_if with a block

	hash.delete_if { |k,v| some logic here for k and v }

You can also replace the contents of a hash using replace

	hash.replace( { 1 => 'foo" } ) # Now the whole array is that one k-v pair

Finally, convert a hash to an array with to_a

	hash.to_a

Case/when

	fruit = "orange"
	case fruit
	  when "orange"
	    color = "orange"
	  when "apple"
	    color = "green"
	  when "banana"
	    color = "yellow"
	  else
	    color = "unknown"
	end

But you can make it shorter:

	fruit = "orange"
	color = case fruit
	  when "orange"
	    "orange"
	  when "apple"
	    "green"
	  when "banana"
	    "yellow"
	  else
	    "unknown
	end

Since the last item evaluated is the result, you can simply use that to assign
whatever gets evaluated last into the 'color' variable.

A trick to get even numbers:

	nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	evens = nums.select { |x| x[0] == 0 }

The 0th index of a number (number[0]) grabs the least significant bit of the
number. If it's 0, the number is even.

You can check the class of an object using an equality test or instance_of?

	o = 'foo'
	o.class == String     # => true
	o.instance_of? String # => true

Note that `instance_of?` doesn't do inheritance. Use `is_a?` for checking parent
classes as well:

	o = 1
	o.instance_of? Fixnum  # => true
	o.instance_of? Numeric # => false
	o.is_a? Numeric        # => true
	o.is_a? Comparable     # => also true - works for Mixins as well as parents

## Equality in Ruby

Equality in Ruby is complex, to say the least. There are a number of different
tests, and they differ in subtle ways.

The topmost test is equal?, which is defined in the Object class. This method
tests whether two objects have the same object id. By convention: subclasses
do not override this method. DON'T TOUCH IT!!!

Next up is ==, which at the Object level is identical to equal?, but which
many subclasses redefine to make more useful to the specific kind of object at
hand.

Two examples:

	a = 'foo'
	b = 'foo'
	a.equal? b # => false
	a == b     # => true - the String class uses == to test string equality

	a = 1
	b = 1.0
	a.equal? b # => false
	a == b     # => true - Numeric tests two numbers, even a Fixnum and a Float
	           #           for numeric equality

The eql? method begins in Object as a synonym for equal?, but many subclasses
redefine it as a slightly stricter version of ==.

	a = 1
	b = 1.0
	a.equal? b # => false - checking for object identity
	a == b     # => true - type conversion, numeric equality
	a.eql? b   # => false - no type conversion

The final method is === which the Object class defines as identical to == but
which many subclasses override. For example, the Range class uses === to test
whether a value falls within a range, and Regexp uses === to test whether a
string matches a regular expression.

You rarely use === per se, but it is the default test in a case...when block.
As a result, === is often known as the "case equality" operator.
