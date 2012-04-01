# The Little Book on CoffeeScript

## Preface

What are the advantages of CoffeeScript?

+ Succinct
+ Curated, good-parts version of JavaScript.
+ Extra syntactic sugar for classes, list comprehensions, etc.

What are some myths?

+ Debugging will be horrendous
+ Speed will suffer

What are some real disadvantages?

+ Compiling is another step in your workflow
+ New language; small community (but IRC is good)

## Trying CoffeeScript

You can try it most easily right in your browser at
[http://coffeescript.org][cs] by clicking the Try CoffeeScript tab. For
playing around, you can also use Jeremy Ashkenas's [script to compile cs
into js right in the browser][script].

    <script
    src="http://jashkenas.github.com/coffee-script/extras/coffee-script.js"
    type="text/javascript"></script>

    <script type="text/coffeescript">
      # CoffeeScript lives here
    </script

[cs]: http://coffeescript.org
[script]: http://jashkenas.github.com/coffee-script/extras/coffee-script.js

Finally, you can use the node tool to compile cs into js. Install it with
`npm` globally.

## CoffeeScript Syntax

NB: CoffeeScript is *not* a superset of JavaScript. (It can't be because it
has significant whitespace.) You can't compile JS using CoffeeScript, and
you can't mix the two languages together in a CS file.

### Some Basics

CoffeeScript has no semicolons, and the keywords `var` and `function` are
not used. Single line comments begin with a hash (as in Ruby), and
multiline comments are done with three hashes.

    # A boring comment

    ###
      Maybe this is more interesting, but maybe not.
    ###

Also, white space is significant in CoffeeScript. So in general, brackets
are replaced by a tab.

### Variables and Scope

As I mentioned earlier, there's no `var` in CoffeeScript. So how do we
handle variable scope? Well, CoffeeScript's attitude is simple: there are
no global variables. All of your code is wrapped in an anonymous function,
and all variable declarations are given a `var` in JavaScript. This makes
it impossible to accidentally create a global variable. However,
CoffeeScript also makes it a little extra work to create a global variable
- if you really need one. You can set such variables as properties on the
global object (`window` in browsers). But better is to use this
CommonJS-style code:

    exports = this
    exports.MyVariable = 'foo-bar'

In a root context, `this` is the global object. So this code makes it very
clear what global variables you want to create. (It also sets us up for the
CommonJS module pattern.)

### Functions

Functions are declared with an arrow -- `->` -- instead of the keyword
`function`. Multiline functions are indented (not in braces). The return
value is the value of the last expression implicitly. You only need the
`return` keyword if you want to return early. So here are a few simple
functions:

    foo = -> 'FOO!'
    bar = -> 'BAR!'

You can also pass arguments in parentheses before the arrow. CoffeeScript
supports default arguments and multiple arguments (using `...`):

    increment = (num, inc = 1) -> num + inc
    sum = (nums...) ->
      result = 0
      nums.forEach (n) -> result += n
      result

Splat arguments like `nums` above become an array of all the arguments
passed to the function. It's a real array, not the `arguments` object. You
can use it exactly as such without worrying about `Array.prototype.splice`
or the like.

### Function Invocation

Functions can be invoked with parens, `apply()` or `call()` -- just as in
JavaScript. But CoffeeScript will automatically call functions if they are
invoked with at least one argument. In such a case, parentheses are not
necessary (though they are allowed).

### Function Context and Binding

Since context changes so easily in JavaScript -- and in ways likely to trip
you up -- CoffeeScript makes it easy to bind a function to a desired
context. For example:

    this.clickHandler = -> alert("clicked")
    element.addEventListener("click", (e) => this.clickHandler(e))

If you use the thin arrow here, then `this` would refer to the element, not
to the local context. Using the fat arrow saves you from needing to use
`self = this` or the like.

### Object and Array Literals

You can define object and array literals exactly as in JavaScript. However,
you can also leave off some of the noisier punctuation if you prefer.

    # standard
    object = { one: 1, two: 2 }
    # no braces are needed though
    object = one: 1, two: 2
    # actually, you can skip the commas too, for indented multiline defs
    object = 
      one: 1
      two: 2

    # Again, no braces
    User.create(name: 'John Smith')

Arrays can use white space instead of commas, but the brackets are still
required. Example:

    # standard
    array = [1,2,3]
    # multiline, no commas
    array = [
      1
      2
      3
    ]
    # trailing commas are fine
    array = [1,2,3,]

### Flow Control

Parentheses are optional with `if`. You can put an `if` condition on
a single line by adding a `then`.

    if true == true
      "We're ok"

    if true != true then "Panic"

CoffeeScript does not support the conditional operator. However, it does
support Ruby/Perl-style postfix conditionals.

    alert 'Too cold!' if heat < 5

You can replace the `!` negation operator with `not`. CoffeeScript also
provides `unless`, `is` (`===`) and `isnt` (`!==`)

### String Interpolation

CoffeeScript supports string interpolation like Ruby, using `#{...}` in
double quoted strings. You can also do multiline strings and heredocs:

    multiline = "This will be long.
    It will be really long. I can keep
    going as long as I like."

    heredoc = """
              Foo.
              Foo.
              Foo.
              """

### Loops and comprehensions

CoffeeScript provides a more modern `for` loop:

    for name in ['Roger', 'Roderick', 'Brian']
      alert "Release #{name}!"

You can easily get the current iteration index by adding a second argument:

    for name, idx in ['Roger', 'Roderick', 'Brian']
      alert "#{i}: Release #{name}!"

A postfix version is also provided:

    alert name for name in ['Sneezy', 'Dopey', 'Doc']

You can filter using `when`:

    alert name for name in ['Sneezy', 'Dopey', 'Doc'] when name[0] is 'D'

    # Works with regular order as well
    for name in ['Sneezy', 'Dopey', 'Doc'] when name[0] is 'D'
      alert name

If you want to iterate over the properties of an object (instead of the
items in an array), use `of` instead of `in`:

    names = 'sam': 'seaborn', 'donna': 'moss'
    alert "#{first} #{last}" for first, last of names

### Ranges and Arrays

You can create ranges in CoffeeScript using `..` or `...`. (The first form
includes the last number, the second excludes it.)

    [1..5] # => [1,2,3,4,5]
    [1...5] # => [1,2,3,4]

In addition, you can apply a range to an array, in which case it becomes
a `slice` call. You can also assign to an array slice. Also, since we can
slice strings just like arrays, this will all work on string slicing as
well.

One other goodie: you can easily check if an array contains an item with
`in`:

    words = ['foo', 'bar', 'ranks']
    if 'ranks' in words...

### Odds and Ends

CoffeeScript provides `@` as an alias to `this.`. So `@savior` refers to
`this.savior`. In addition, the language gives you `::` as an alias for
`prototype.`. So you can assign methods this way:

    User::first = -> @records[0]

CoffeeScript allows you to write `true` as `true`, `on` and `yes`. You can
write `false` as `false`, `off` and `no`. This can make for more legible
code:

    launch() if ignition is on
    let somethingRun() unless answer is no

Finally, CoffeeScript provides a helper to do existential checks: `?`. It
returns true unless a variable is `null` or `undefined`. Unlike JavaScript,
the empty string and 0 are *not* coerced to return false. You can use it in
a few ways.

    # Do the foo if brian is not null or undefined.
    foo() if brian?

    # Assign southern to velocity unless it's undefined or null; else 40.
    velocity = southern ? 40

    # If velocity is not null or undefined, leave it. Else assign it 40.
    velocity ?= 40

    # Try blackNight.getLegs(), and if it's not null, run kick on it.
    blackKnight.getLegs()?.kick()

