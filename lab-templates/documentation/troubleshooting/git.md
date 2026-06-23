# When Git Gets Grumpy

[//]: # (TODO: should we &#40;*can* we&#41; provide IDE versions of these instructions? If not, explain why here.)
[//]: # (TODO: be prepared to address interplay between containerization and git)

- [`git status`](#git-grumpiness-git-status)
- [`git fetch`](#git-grumpiness-git-fetch)
- [`git merge`](#git-grumpiness-git-merge)
- [`git commit`](#git-grumpiness-git-commit)
- [`git push`](#git-grumpiness-git-push)
- [`git pull --ff`](#git-grumpiness-git-pull---ff)
- [`git pull --rebase`](#git-grumpiness-git-pull---rebase)


## Git Grumpiness: `git status`

You tried to make sure your repository is ready to receive the *FooLab*.
```shell
git status
```
You expected to see something like this:
```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```
But you saw something different.
- If you get a *fatal: not a git repository* error, then `cd` into your repository's directory and try again.
- If it does not say *On branch main*, then switch back to the main branch:
  ```shell
  git checkout main
  ```
- If it does not say *Your branch is up to date with 'origin/main'*, then update it:
  ```shell
  git pull --ff
  ```
- If it does not say *nothing to commit, working tree clean*, then commit your changes before continuing.
  (You *can* stash changes instead, but do that only if you know how to re-apply them later, or if you are intentionally abandoning all changes since your last commit.)

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Retrieving the Lab"](#retrieving-the-lab)


## Git Grumpiness: `git fetch`

You attempted to retrieve the FooLab branch.
  ```shell
  git fetch origin FooLab
  ```
You expected to see something like this:
  ```shell
  From git.unl.edu:csce231/fall2025/your-repo
  * branch            FooLab     -> FETCH_HEAD
  ```
But you saw something different.
If the error is:
- *fatal: couldn't find remote ref FooLab*, then  
  either the instructor hasn’t released this lab yet, or you mistyped the branch name.
  Double-check spelling and capitalization.
  To check whether the branch exists on the remote:
  ```shell
  git ls-remote --heads origin FooLab
  ```
  You can list *all* remote branches with:
  ```shell
  git ls-remote --heads origin
  ```
- *ssh: Could not resolve hostname git.unl.edu: Name or service not known*, or  
  *ssh: connect to host git.unl.edu port 22: Connection timed out*, then  
  this is a connectivity problem.
  Check the network.
- *Permission denied (publickey)*, or
  *fatal: Could not read from remote repository* (**without** timeouts/DNS errors), then
  this is usually a login/SSH key issue.
  A TA or the instructor can help you troubleshoot this issue.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Retrieving the Lab"](#retrieving-the-lab)


## Git Grumpiness: `git merge`

You attempted to merge the *FooLab* branch into your `main` branch.
```shell
git merge --ff origin/FooLab
```
You expected to see a message like:
```
Updating abc1234..def5678
Fast-forward
# or
Merge made by the 'ort' strategy.
FooLab/README.md   | 10 ++++++++++
FooLab/src/main.c  | 42 ++++++++++++++++++++++++++++++++++++++++++
...
```
But you saw something different.
- If you get an error like:<br>
  *fatal: Not something we can merge*, or<br>
  *fatal: Not a valid object name: 'origin/FooLab'*, or<br>
  *fatal: 'origin/FooLab' does not point to a commit*, then
  the branch name is wrong or the branch was not fetched correctly.
  Double-check the capitalization and try again.
- If you get a message about *untracked working tree files would be overwritten by merge*, then
  you have files in your working directory that conflict with the lab.
  Move, rename, or remove them, then try again.
- If Git reports *Automatic merge failed; fix conflicts and then commit the result*, then you have a merge conflict that Git cannot resolve automatically:
    1. Open the conflicting files -- Git marks the conflicting lines with `<<<<<<<`, `=======`, and `>>>>>>>`.
    2. Edit the file(s) to keep the correct code.
    3. Mark each file's conflicts as resolved as you go:
       ```shell
       git add path/to/conflicted-file
       ```
    4. Once all conflicts are resolved:
       ```shell
       git commit
       ```
  Save and close the editor to complete the merge.
- If you see *Already up to date*, then the lab has already been merged (or there was nothing new to add).
  You can continue.
- If you get an error saying *fatal: refusing to merge unrelated histories*, let a TA or the instructor know — this indicates something unusual in your repository setup.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Retrieving the Lab"](#retrieving-the-lab)


## Git Grumpiness: `git commit`

You attempted to stage and commit files:
```shell
git add .
git commit
```
You expected the editor should open for you to provide a commit message, but it didn't.
- If `git commit` exits with *nothing to commit, working tree clean*, then either you forgot to run `git add`, or there were no changes to stage when you ran `git add`.
  Run `git status` to see what (if anything) is changed.
- If the screen changed but looks "stuck," then Git has probably opened a text editor in the terminal (often Vim or Nano) and is waiting for you to type a commit message.
  Type a short message describing your changes, then save and exit the editor
- If you see *Aborting commit due to empty commit message*, then the editor was closed without you having entered a commit message.
  Run `git commit` again and include a commit message.
- If an editor opened outside the terminal, then switch to that window to enter your commit message.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Turning in the Completed Lab"](#turning-in-the-completed-lab)


## Git Grumpiness: `git push`

You attempted to send the updates to git.unl.edu:
```shell
git push
```
You expected to see a message that is something like this:
```
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 12 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (5/5), 2.21 KiB | 2.21 MiB/s, done.
Total 5 (delta 0), reused 0 (delta 0), pack-reused 0
To git.unl.edu:csce231/fall2025/your-repo.git
   abc1234..def5678  main -> main
```
But you saw something different.
- If you see
  ```
  Everything up-to-date
  ```
  then there was nothing new to push. This is not an error.
- If you received the message
  ```
  To git.unl.edu:csce231/fall2025/your-repo.git
  ! [rejected]        main -> main (fetch first)
  error: failed to push some refs to 'To git.unl.edu:csce231/fall2025/your-repo.git'
  hint: Updates were rejected because the remote contains work that you do
  hint: not have locally. This is usually caused by another repository pushing
  hint: to the same ref. You may want to first integrate the remote changes
  hint: (e.g., 'git pull ...') before pushing again.
  hint: See the 'Note about fast-forwards' in 'git push --help' for details.
  ```
  Then the message tells you exactly what is wrong (*the remote* copy of your repository *contains work that you do not have locally*)
  and how to fix it (`git pull ...`)
    - If you're new to Git, I recommend using
      ```shell
      git pull --ff
      ```
      which will highlight merge conflicts for you. If you're more comfortable with Git, you may use
      ```shell
      git pull --rebase
      ```
      Regardless of which command you use, be sure to check that your code still compiles and functions correctly before re-running `git push`.
- If you saw one of these errors:
    - *ssh: Could not resolve hostname git.unl.edu: Name or service not known*, or
    - *fatal: Could not read from remote repository*, or
    - *ssh: connect to host git.unl.edu port 22: Connection timed out*, then  
      this is a connectivity problem.
      Check the network.
- If you see network-related errors such as: *ssh: Could not resolve hostname git.unl.edu: Name or service not known*, or  
  *ssh: connect to host git.unl.edu port 22: Connection timed out*, then  
  this is a connectivity problem.
  Check the network.
- If you see authentication errors such as: *Permission denied (publickey)*, or
  *fatal: Could not read from remote repository* (**without** timeouts/DNS errors), then
  this is usually a login/SSH key issue.
  A TA or the instructor can help you troubleshoot this issue.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Turning in the Completed Lab"](#turning-in-the-completed-lab)


## Git Grumpiness: `git pull --ff`

You retrieved changes from the remote copy of your repository with:
```shell
git pull --ff
```
and expected to see something similar to:
```
Updating abc1234..def5678
Fast-forward
 src/main.c | 10 ++++++++++
 1 file changed, 10 insertions(+)
```
Or possibly:
```
Updating abc1234..def5678
Auto-merging src/main.c
Merge made by the 'ort' strategy.
 src/main.c | 2 ++
 1 file changed, 2 insertions(+)
```
But instead you saw something different.
- If you saw:
  ```
  Already up to date.
  ```
  then there were no new changes to pull.
  This is not an error.
- If you saw
  ```
  error: Your local changes to the following files would be overwritten by merge:
      src/main.c
  Please commit your changes or stash them before you merge.
  Aborting
  ```
  then you have uncommitted changes in the local copy of your repository.
  Stage (`git add ...`) and commit (`git commit`) the changes, or stash (`git stash`) them if you prefer.
- If you saw something similar to:
  ```
  Auto-merging src/main.c
  CONFLICT (content): Merge conflict in src/main.c
  Automatic merge failed; fix conflicts and then commit the result.
  ```
  then some of the changes in the remote copy overlap with changes in the local copy,
  and Git could not resolve them automatically.
    1. Open the conflicting files -- Git will mark the conflicting lines with `<<<<<<<`, `=======`, and `>>>>>>>`.
    2. Edit the file(s) to keep the correct code.
    3. Mark them resolved:
       ```shell
       git add path/to/conflicted-file
       ```
    4. Once all conflicts are resolved:
       ```shell
       git commit
       ```
  This completes the merge.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.


## Git Grumpiness: `git pull --rebase`

You retrieved changes from the remote copy of your repository with:
```shell
git pull --rebase
```
and expected to see something similar to:
```
First, rewinding head to replay your work on top of it...
Applying: Add new function to src/main.c
Applying: Rename variable in src/xyzzy.c
```
But instead you saw something different.
- If you saw an error like
  ```
  Cannot rebase: You have unstaged changes.
  Please commit or stash them.
  ```
  (or any other message that says you have uncommitted changes),
  then you have uncommitted changes in the local copy of your repository.
  Stage (`git add ...`) and commit (`git commit`) the changes, or stash (`git stash`) them if you prefer.
- If you saw something similar to:
  ```
  First, rewinding head to replay your work on top of it...
  Applying: Add new function to src/main.c
  Using index info to reconstruct a base tree...
  CONFLICT (content): Merge conflict in src/main.c
  error: could not apply 3f2a1bc... Add new function to src/main.c
  Resolve all conflicts manually, mark them as resolved with
  "git add <file>", then run "git rebase --continue".
  ```
  then there is a conflict while replaying commits.
    1. Open the conflicting file -- Git will mark the conflicting lines with `<<<<<<<`, `=======`, and `>>>>>>>`.
    2. Edit the file to keep the correct code.
    3. Mark it resolved and continue the rebase:
       ```shell
       git add path/to/conflicted-file
       git rebase --continue
       ```
    4. Repeat the process for any additional merge conflicts.

  If you get stuck and want to cancel the rebase and return to where you started:
  ```shell
  git rebase --abort
  ```

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.
