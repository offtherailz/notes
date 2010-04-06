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
