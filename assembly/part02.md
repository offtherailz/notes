# [Assembly Language Primer for Hackers][alpfh]

[alpfh]: http://www.worldofhacker.com/Article-Assembly-Language-Primer-For-Hackers-Part-1-System-Organization

## Part 2

Compile demo program with `gcc -ggdb`. There will be a warning about `gets`.

Then run the program, and while it's waiting for the `gets` call, `ps` to see
the the process number.

Although the program will be laid out in the identical way every time it
runs, the 2.6 kernel randomizes the memory placement of the segments in
order to prevent certain buffer overflow attacks.

This randomization can be turned off by switching the value in
`/proc/sys/kernel/randomize_va_space` from 1 to 0.
