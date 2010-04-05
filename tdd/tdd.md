% Notes on TDD
% Peter Aronoff
% 2009-11-28

## My notes on test driven development

### The basic cycle of work

+ Red: write a short, specific test that fails.
+ Green: make the test pass; write whatever code you must to do so.
+ Refactor: remove duplication and generally improve the code you wrote in step two.

This makes sense to me, but it's fucking hard. I find it very hard to break down all of what I want to do into specific, small tests. Also, in the case of filesystem or network operations, it's very hard to know what to test and how to proceed. 

### Beck's three methods for quickly getting to green

+ Fake it: Stick in constants; then gradually replace them with variables until done.
+ Use the obvious implentation: write the right code, if it's obvious.
+ Triangulation: generalize only when you have two or more examples. In this scenario, we delay refactoring - if no design or solution (other than a quick bad one) suggests itself - until further examples help to clarify the problem.

### From _Ruby Best Practices_ 

+ Keep test cases atomic. Don't bundle all tests into one test case.
+ Check exceptions (both that the right ones are raised and that others are not).
+ Use `rake` to automate tests. Run all tests every time you make changes in order to catch any problems between pieces of the application.
