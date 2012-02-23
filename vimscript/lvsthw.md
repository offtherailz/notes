# Notes on [Learn Vimscript the Hard Way][lvsthw]

[lvsthw]: http://learnvimscriptthehardway.stevelosh.com/

## Echoing Messages

You can print output using `echo` or `echom`. The difference is that
messages printed with `echom` are saved and can be recalled with the
`messages` command at a later time. Thus, `echom` can be especially good
for debugging messages.

## Setting Options

Vim has a huge number of options that you can set. Options have two main
types: boolean ('on' or 'off') or options with values. An example of
a boolean option is `number`; it's either set - in which case you see
numbers - or it's not - in which case you don't see numbers.

Many (all?) boolean options can be toggled with a bang command. So `:set
number!` flips the number state into its opposite, whatever it's set to
currently. You can also check what an option is set to by adding a `?`.

Options with values are what you would expect. An example is `numberwidth`.
You don't just turn it on or off. Instead, you set it to some value. For
example, `:set numberwidth=10`.

You can set more than one option with a single `:set` command. For example,
`:set number numberwidth=6`. (Note: no commas.)

## Basic Mapping

You can map keys to other keys or commands, using `map`. Note that comments
are _not ok_ inside of mapping settings.

## Modal mapping

Instead of using just `map` generically, you can map keys only for specific
modes using `nmap`, `vmap` and `imap`. These apply to normal mode, visual
mode and insert mode, respectively.

## Strict Mapping

Normal mappings in Vim take other mappings into account by default. This
means things can get ugly fast. So, it is often a better idea to use the
`nore` forms:

    nnoremap
    inoremap
    vnoremap

## Leader and Local Leader

In addition to mapping keys to commands, you can map sequences of keys to
commands. In particular, it is helpful to be able to choose one general
prefix key. Then any custom mappings are done as `<prefix>key command`. The
prefix is your leader. Vim's default leader is '\'. You can reset this with
`let mapleader = "whatever"`. Then in mappings, you can say things like
this: `nnoremap <leader>d dd`.

In addition to the global leader, there is also a local leader. The local
leader takes effect only for specific filetypes.
