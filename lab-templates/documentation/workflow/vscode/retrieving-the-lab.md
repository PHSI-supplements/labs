# Retrieving the Lab using VS Code

We will place each coding assignment in a non-`main` branch so that adding a new assignment does not interfere with the assignment you're working on.
When you are ready to work on a coding assignment, notionally *FooLab*, you can retrieve the assignment from the Git server and merge it into your `main` branch:


## Prepare to Retrieve the Updates

- [ ] First, make sure you are on the `main` branch.
  You will find the current branch in the Status Bar at the bottom of VS Code.
  > ![A source control branching icon, with the word "main".](media/source-control-on-main.png)

- [ ] And make sure that you have committed any changes from your current work, so that your repository is ready to receive the *FooLab*.
  If the source control icon on the Activity Bar has a number, then you have uncommitted changes.
  > ![A source control branching icon with a "1" in a blue dot.](media/source-control-uncommitted-change.png)

  If it doesn't have a number, then all of your changes have been committed.
  > ![A source control branching icon without a blue dot.](media/source-control-no-uncommitted-changes.png)
  

## Fetch the Updates

- [ ] Next, retrieve the latest branches from the remote copy of your repository.
  Open the Command Palette and run **Git: Fetch**

- [ ] Confirm that you successfully fetched *FooLab*'s branch.
  Click on the Git status bar at the bottom of VS Code.
  The list of current branches will appear.
  You should see `origin/FooLab` in the list of branches.
  > ![A list of Git branches, including `main`, `origin/PokerLab`, and `origin/main`.](media/list-of-branches.png)

If you do not see `origin/FooLab`, look at [the `git fetch` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-fetch).


## Merge the Updates into `main`

Finally, merge the *FooLab* branch into your `main` branch.
- [ ] Make sure the branch shown in the Status Bar is still `main` before performing the merge.
- [ ] Open the Command Palette and run **Git: Merge**
  You will be presented with a list of unmerged branches.
- [ ] Select the `origin/FooLab` branch.  

Confirm that you successfully merged `origin/FooLab` into `main`.
There are two indicators.
- [ ] In the Source Control view, the **graph** will show a visual representation of the merge. 
  > ![Four commits. "Added name" and "Add PokerLab" are on different branches diverging from "Initial commit". The branches converge on "Merge remote-tracking branc..."](media/merge-on-git-graph.png)
- [ ] In the Explorer view, the list of files and directories will include the *FooLab* directory and the *FooLab-VSCode.code-workspace* file.
  > ![A list of files and directories. Among theme are "> PokerLab" and "{} PokerLab-VSCode.code-workspace".](media/explorer-view.png)

If the merge was not successful, look at [the `git merge` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-merge).
