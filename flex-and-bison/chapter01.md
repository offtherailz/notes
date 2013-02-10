# flex & bison

## Chapter 1: Introducing Flex and Bison

Flex and Bison help build programs that deal with structured input.
Initially, they were intended for making compilers, but they have many
other uses as well.

### Lexical Analysis and Parsing

Parsers in the 1950s were largely ad hoc. After a lot of study in the
1960s, syntactical analysis became much better understood. A key insight
was to divide the work into two parts: lexical analysis (also called lexing
or scanning) and syntax analysis (also called parsing).

Scanning divides input into meaningful chunks, called tokens. Parsing works
out how the tokens connect.

As an example, look at this C code:

    alpha = beta + gamma;

A scanner would divide this into the tokens 'alpha', 'equal sign', 'beta',
'plus sign', 'gamma' and 'semicolon'. The parser then works out that 'beta
+ gamma' is an expression and assigns the result of that expression to
'alpha'.

### Regular Expressions and Scanning

Scanners look for patterns of characters in their input. These patterns are
regular expressions. A flex program essentiall contains a list of regular
expressions and instructions saying what to do when input matches them. THe
instructions are known as actions. A flex-generated scanner reads through
its input, maching against all the regular expressions and performing
appropriate actions on matches. (Flex translates the regular expressions
into deterministic finite automata internally. This means that they are
highly efficient: they match just as fast against 100 patterns as one.)

### Our First Flex Program

As an example, here's a `wc` clone:

    %{
    int chars = 0;
    int words = 0;
    int lines = 0;
    %}

    %%

    [^ \t\n\r\f\v]+ { words++; chars += strlen(yytext); }
    \n { chars++; lines++; }
    . { chars++; }

    %%

    main(int argc, char **argv)
    {
        yylex();
        printf("%8d%8d%8d\n", lines, words, chars);
    }

A flex program contains three sections, separated by '%%'. The first
section contains declarations and option settings. The second is a list of
patterns and actions. The third is C code that is copied to the generated
scanner. It's usually small routines related to the code in the actions
triggered by the matches.

In the declaration section, any code inside of `%{` and `%}` is copied
verbatim near the beginning of the generated C source. Here it just sets up
variables for characters, words and lines.

The second section has a pattern at the start of each line, followed by
C code to execute when the pattern matches. The C code can be one statement
or a multiline block in braces. The patterns *must* be at the start of the
line. Any line that starts with whitespace is taken by flex to be code to
copy into the generated C program.

Note that in the first match `yytext` is an automatic variable. In an
action, yytext will point to the intput text that the pattern just matched.

The C code in the final section calls `yylex`. This is flex's scanner
routine. Then it prints results.
