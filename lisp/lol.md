# Land of Lisp

## Chapter 4: Making decisions with conditions

### Truth and falsity in Lisp

In Lisp an empty list evaluates as false. This allows easy recursion over
lists. When you reach the empty list, the recursion will bottom out. No
danger of infinite loops.

    (defun my-length (list)
        (if list
            (1+ (my-length (cdr list)))
            0))

    (my-length '(list with four symbols))

Not only does an empty list evaluate to false, but in Common Lisp it is the
*only* false value. However, there are form expressions in Lisp that are
all the empty list:

+ `'()`
+ `()`
+ 'nil
+ nil

Note that Scheme and Common Lisp differ over this. Scheme does not treat an
empty list and false as the same thing. (Not sure of the details here.)

### Basic if conditions in Lisp

The conditional in Lisp is a special form. Only one of the expressions
after the `if` is evaluated (lazy evaluation). This means you can get away
with things that you couldn't otherwise:

    (if (oddp 5)
        'odd-number
        (/ 1 0))

Normally only one thing can be done in each branch of a conditional.
However, if you really want to cram more in, you can use `progn` to push
extra commands into a branch. Note that only the last expression is
considered for the return value, regardless of the rest.

    (defvar *number-was-odd* nil)

    (if (oddp 5)
        (progn (setf *number-was-odd* t)
                'odd-number)
        'even-number)

### Alternatives to if: when and unless

As an alternative to `progn` in an `if`, you can use `when` or `unless`.
With `when` all the enclosed expressions are evaluated when the condition
is true. With `unless` all the enclosed expressions are evaluated when the
condition is false. However, `when` and `unless` don't do anything when the
condition evaluates in the opposite way. They simply return `nil` in that
case.

    (defvar *number-was-odd* nil)

    (when (oddp 5)
        (setf *number-was-odd* t)
        'odd-number)

    (unless (oddp 4)
        (setf *number-is-odd* nil)
        'even-number)

(There's a typo on page 56. The return value of `*arch-enemy*` should be 
'USELESS-OLD-JOHNNY'.)

### Alternatives to if: cond and case

In addition to `if`, `when` and `unless`, Lisp also has `cond` and `case`
conditionals. The `cond` allows for multiple branches and for multiple
actions in each branch. Its syntax is a bit noisy though. The case form is
simpler, but it limits the test to `eq` checks.

    (cond ((eq person 'henry) (setf *arch-enemy* 'stupid-lisp-alien)
                              '(curse you lisp alien - you ate my pudding))
          ((eq person 'johnny) (setf *arch-enemy* 'useless-old-johnny)
                              '(i hope you choke on the pudding johnny))
          (t                  '(why you eat my pudding stranter?)))

    (case person
          ((henry)    (setf *arch-enemy* 'stupid-lisp-alien)
                      '(curse you lisp alien - you ate my pudding))
          ((johnny)   (setf *arch-enemy* 'useless-old-johnny)
                      '(i hope you choked on my pudding johnny))
          (otherwise  '(why you eat my pudding stranger?)))

### Unexpected conditions: and and or

In addition to the proper conditionals, the shortcut evaluation of `and`
and `or` means that you can use them as conditionals.

    (and *file-modified* (ask-user-about-saving) (save-file))

    (if *file-modified*
        (if (ask-user-about-saving)
            (save-file)))

Since the first version might be a bit obscure and the second a bit
verbose, you can compromise:

    (if (and *file-modified*
              (ask-user-aboue-saving))
        (save-file))

### Returning values other than true from a boolean

Since anything other than `nil` or an empty list is true, many boolean
functions return more useful values instead of just returning `t`. For
example:

    (member 1 '(3 4 1 4 5))
    (1 4 5)

The `member` function returns the tail of the list.

### Equality testing in Lisp

Lisp, like Ruby, has lots of ways to test equality:

+ `eq`
+ `equal`
+ `eql`
+ `=`
+ `string-equal`
+ `equalp`

A simple rule of thumb for comparisons is this:

+ Compare symbols with `eq`.
+ Compare everything else with `equal`.

Comparing symbols with `eq` is fast and does the job. On the other hand,
`equal` is very flexible. It tests whether two things are isomorphic, and
it seems to generally "do what you want"(TM). You can even compare a list
with a `cons` of a list with the same contents, and it will say they're the
same.

`eql` is similar to `eq`, but you can use it for numbers and characters as
well as symbols.

`equalp` is similar to `equal`, but it handles some difficult cases. You
can use it to compare strings case insensitively, and it will consider
integer and floating point versions of a number the same.

The others are specialized comparisons. `=` is for numbers, `string-equal`
for strings and `char-equal` for characters. Note that `string-equal` is
case insensitive, and `=` considers pairs like 1 and 1.0 to be equal. In
both these cases, `equal` differs.
