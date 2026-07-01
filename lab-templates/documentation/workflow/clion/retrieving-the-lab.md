# Retrieving the Lab using CLion

We will place each coding assignment in a non-`main` branch so that adding a new assignment does not interfere with the assignment you're working on.
When you are ready to work on a coding assignment, notionally *FooLab*, you can retrieve the assignment from the Git server and merge it into your `main` branch:


## Prepare to Retrieve the Updates

- [ ] First, make sure you are on the `main` branch.
  You will find the current branch at the top of CLion's window.
  > ![A source control branching icon, with the word "main".](media/source-control-on-main.png)

- [ ] And make sure that you have committed any changes from your current work, so that your repository is ready to receive the *FooLab*.
  If the Commit view shows that there are changed files, then you have uncommitted changes.
  > ![A screenshot with "Commit" at the top. A line says "Changes 1 file".](media/source-control-uncommitted-change.png)

  If the Commit view doesn't show any changed files, then all of your changes have been committed.
  > ![A screenshot with "Commit" at the top. A line says "Changes".](media/source-control-no-uncommitted-changes.png)
  

## Fetch the Updates

- [ ] Next, retrieve the latest branches from the remote copy of your repository.
  From CLion's menu, select **Git** ⇒ **Fetch**

> ⓘ **Note**
>
> The first time that CLion access the Git server during a session, you may be prompted to approve SSH Key Access.
> If you are:
> - [ ] Click the "Allow" button
>
> > ![A popup "Provide SSH Key Access. The process on the backend is requesting an SSH key." There are 'Allow' and 'Deny' buttons.](media/approve-key-forwarding.png)

- [ ] Confirm that you successfully fetched *FooLab*'s branch.
  Click on the current branch dropdown at the top of CLion's window.
  The list of current branches will appear.
  You should see `Remote` ⇒ `origin` ⇒ `FooLab` in the list of branches.
  > ![A list of Git branches, including `Local/main`, `Remote/origin/main`, and `Remote/origin/PokerLab`.](media/list-of-branches.png)

If you do not see `origin/FooLab`, look at [the `git fetch` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-fetch).


## Merge the Updates into `main`

Finally, merge the *FooLab* branch into your `main` branch.
- [ ] In the current branch dropdown, select **FooLab** ⇒ **Merge 'origin/FooLab' into 'main'**
  > ![The list of Git branches from the previous step. PokerLab has been expanded, and a list of possible actions are shown. "Merge 'origin/PokerLab' into 'main'" is highlighted.](media/merge-into-main.png)

Confirm that you successfully merged `origin/FooLab` into `main`.
There are two indicators.
- [ ] The Git view will show a visual representation of the merge. 
  > ![Five commits. "Added name" and "Add PokerLab" are on different branches diverging from "Initial commit". The branches converge on "Merge remote-tracking branc..."](media/merge-on-git-graph.png)
- [ ] The Project view will include the *FooLab* directory.
  > ![A list of files and directories. Among theme is "> PokerLab".](media/project-view.png)

If the merge was not successful, look at [the `git merge` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-merge).
