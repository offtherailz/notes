# Git course 2011-05-23

## Big pickup in corporate/enterprise use of Git

Git has gone from being the domain of the cool kids to big business and corporate usage as well.

## History

+ Started as Bash scripts
+ Moved to C later
+ Linus's joke about how he named 'git' - after himself.
+ Did not invent DVCS - history into the 90s
+ Biggest remaining candidates - Mercurial and Git (both 2005)

## Installation

+ All good here

## Configuration

    git config --global user.name "My Name"
    git config --global user.email "name@host.com"

    # List current config
    git config --global --list

    git config [--local | --global | --system]
    # --local $PWD/.gitconfig
    # --global $HOME/.gitconfig
    # --system /usr/local/x/git/x.x.x/etc/config
    git config --global core.excludesfile "~/.filename"

    git commit -v # Show diff when I get to commit message
    git diff --staged
    git diff HEAD
    git diff --diff-filter=M # Filter for modifications
    git diff -w # No whitespace diffs
    git diff --color-words # Diff on words and color

    git status # Yup
    git status -s # Show short status
    git status -u # More detail for new directories

    git log
    git log --stat # Show filenames plus numbers
    git log -p # Show patch form of changes
    git log --diff-filter=A # Filter on diff
    git log --pretty=raw # Not sure
    git log -3
    git log --stat -M
    git log --stat -C # Show renames in history
    git log --stat -C --find-copies-harder # ZOINKS!

    rm <FILES>   # Just through your OS
    git add -u . # Picks up deletes, too!
    mv <FILE1> <FILE2> # Through OS
    git add -A . # Picks up moves, too!

## Remotes

Remotes are bookmarks. The default name for a repo you clone from is 'origin'.

Both local and remote branches exist on *my* machine. Branches that are on *other* machines are upstream.

All remotes are peers to Git. Nothing in Git distinguishes or ranks remotes.

## Branches

    git branch foo
    git branch foo #hash # Mark a starting point for a branch
    git checkout branch_name
    git checkout -b foo
    git branch -d foo
    git branch -D foo

## Merging

## Stashing

    git stash # Hide local uncommitted changes; revert to HEAD
    git pop   # Get the local changes back
    git pop stash@{0}
    # Applies changes but doesn't pop - good for applying to many branches
    git stash apply
    git stash branch... # Look this up later
    git reset --hard # Discard changes, staged and unstaged

## Rebase

    git checkout featurebranch
    git rebase master
    git checkout master
    git merge featurebranch


    git pull --rebase # Pull changes, but don't merge commit; use fast-forward
    # If there's a merge:
    ## (1) Manually fix conflict
    ## (2) git add the file
    ## (3) git rebase --continue

## Undo in git

    git clean # purges untracked files
    git clean -fd # purges untracked files and directories

    git revert #hashtag # undo a commit surgically

    git commit --amend  # repopen a commit to fix commit message

    git reset --hard # Reset HEAD, working copy and index
    git reset --soft # Reset HEAD, but not index or working copy

## reflog

    git reflog # a log of what you did - places you can reset to


## Random

+ Git default port 9148?
