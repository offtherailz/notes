% Notes on Chapter 4 of WGR
% Peter Aronoff
% 2010-04-03

# Modules and program organization

## Method lookup

When a method is called on an object, the method lookup chain runs like this:

+ Check class of object for method
+ Check if class of object mixes in an modules. If so, check those for method.
+ Check superclass of object for method.
+ Check if superclass of object mixes in any modules. If so, check for method.
+ Etc. all the way up the parent chain. If the method is never found, call `method_missing`.

If a class mixes in multiple modules, they are checked in _reverse order_ of inclusion. This means that the last module mixed-in will win. There is one caveat: you can't mix-in more than once. If you include M, N and then M again, N is the last mixed-in module, not M.

