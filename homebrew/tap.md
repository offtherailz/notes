# brew tap

The `brew tap` command is powerful, but has a few subtleties worth
describing.

tl;dr `brew tap` allows you to add unofficial Github repos to the list of
formulas that `brew` tracks, updates and installs from. When naming tap
repos and formulas, however, there are a few gotchas to beware of.

## The command

+ If you run `brew tap` with no arguments, it will list the currently
  tapped repositories. Example:

        $ brew tap
        homebrew/dupes
        telemachus/desc
        telemachus/vim

+ If you run `brew tap` with a single argument, `brew` will attempt to
  parse the argument into a valid 'username/repo' combination. If the
  argument is a valid name, then `brew tap` will attempt to clone the
  repository and symlink all its formulae. (See below for what it means to
  be a 'valid name'.) After that, `brew` will be able to work on those
  formulae as if there were in mxcl's canonical Homebrew repository. You
  can install and uninstall them with `brew [un]install`, and the formulae
  are automatically updated when you run `brew update`. (See below for
  a few exceptions on names and installation.)

+ In you run `brew tap --repair`, then `brew` will check for dead symlinks
  and relink all valid formulae across all your taps.

## Naming conventions and limitations

`brew tap username/repo` employs some shortcuts and has some limitations.

+ If your repo is named `homebrew-something`, then the `homebrew-` is
  optionally ignored.

  That is, `brew tap username/homebrew-foobar` is functionally equivalent
  to `brew tap username/foobar`. In the case of a repository with such
  a name, you can `tap` or `untap` it with or without explicitly adding the
  `homebrew-` portion of the repository's name.

+ The name of the repository (other than the optional 'homebrew-') is
  checked against a regular expression. The details of the regular
  expression don't matter, but what does matter is that it creates some
  limitations on what `brew tap` considers a legal name.

  In a nutshell, your repository name can only contain letters, numbers and
  the underscore. In particular, you can't use a hypen (again, except for
  the optional 'homebrew-'). This causes some potentially frustrating `brew
  tap` errors:

        $ brew tap telemachus/foo-bar
        Error: Invalid usage

## Formula duplicate names

If your tap contains a formula that is also present in master, that's fine,
but it means that you must install it explicitly.

For example, you can create a tap for an alternative `vim` formula, but in
that case when you install from there you must run the command with a more
explicit installation target:

    brew install vim                 # installs from mxcl master
    brew install username/repo/vim   # installs from your custom repo
