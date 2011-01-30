# How to create and run Perl programs

## File naming conventions

They use '.pl' as a standard suffix. Many people do, and some (stupid) editors rely on this to know if something is a Perl program. I prefer not to use suffixes like this if I can avoid it. Instead, I name the scripts for what they do (or however I want) and give them a proper shebang. It mostly works out the same, however, so you can do what you like.

## Shebang line conventions

They use `#!/usr/bin/perl`, but I much prefer `#!/usr/bin/env perl`. Using `env` allows *me* to control my choice of Perl interpreter however I like. This is especially important if you are using perlbrew which will store *none* of your perls at /usr/bin.


## Little notes

+ Always use the `warnings` pragma not `-w` unless you are using a version of Perl earlier than 5.6. By the way, you shouldn't be using a version of Perl earlier than 5.6.
+ Use line comments. Block comments with POD are a pain. Use editor macros.
+ `__END__` can be useful to block out large chunks of something.
+ You should *always* enable `strict`. One easy way to do this is `use strict;`, but if you are running 5.10.x or higher, you can just use that specific version of Perl. That enables strictness and also enables any new features for that version of Perl (like `say` for example). It does, however, limit the environments under which your script will run. If you're in control of you environments, I think it's a good idea. The following all work:
        use v5.6.1;
        use 5.6.1;
        use 5.006_001; # More backwards compatible, according to perldoc -f use
+ To enable features from your Perl version at the command line, use `-E` instead of `-e`.
        perl -e 'say "hello, world!"' # fails, hard
        perl -E 'say "hello, world!"' # works, well
+ Use `diagnostics` instead of `warnings` while developing a program for verbose messages.

