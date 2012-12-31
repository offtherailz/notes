# Simply Scheme

## Chapter 1

The book will use Scheme to teach "some big ideas in computer science. The
ideas are mostly about *control of complexity*".

One example is *abstraction*. As a small example they mention that after
solving part of a large problem, you can give the partial answer a name.
Afterwards, you can use that named mini-program as if it were an atom,
built into the computer. This allows you to forget about -- or hide away --
certain details as you work.

### The REPL

When in the REPL, you type a request to Scheme, and Scheme prints the
answer. You can start with simple values, like `6`, and Scheme will echo it
back to you. But if you want Scheme to do something, you enclose it in
parentheses. The parentheses tell scheme to carry out a procedure. (Their
initial definition for 'procedure' is "something that Scheme knows how to
do".) Inside the parentheses, the first item tells Scheme what procedure to
use; the rest of the items are arguments. Examples:

    (+ 4 7 8)
    (word 'comp 'uter)

Built-in procedures are called 'primitive'; new procedures that we write
are called 'compound' procedures.

### Example: Combinations from a Set

    ; Produce combinations of a given size from a set
    (define (combinations size set)
      (cond ((= size 0) '(()))
            ((empty? set) '())
            (else (append (prepend-every (first set)
                                         (combinations (- size 1)
                                                       (butfirst set)))
                          (combinations size (butfirst set))))))
    (define (prepend-every item lst)
      (map (lambda (choice) (se item choice)) l))
