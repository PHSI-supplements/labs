# CSCE 231 Lab Assignments

We will place the assignments and starter code for most of the coding assignments in this repository.

## Student

- Name: 
- Lab Section: 

## Table of Contents

- [Retrieving the Lab](#retrieving-the-lab)
- [Reading the Assignment](#reading-the-assignment)
- [How Long will the Lab Take?](#how-long-will-the-lab-take)
- [Typical Lab Directory Structure](#typical-lab-directory-structure)
- [Configuring, Compiling, Running, and Testing](#configuring-compiling-running-and-testing)
- [Turning in the Completed Lab](#turning-in-the-completed-lab)
- [When Git Gets Grumpy](#when-git-gets-grumpy)
  - [Git Grumpiness: `git status`](#git-grumpiness-git-status)
  - [Git Grumpiness: `git fetch`](#git-grumpiness-git-fetch)
  - [Git Grumpiness: `git merge`](#git-grumpiness-git-merge)
  - [Git Grumpiness: `git commit`](#git-grumpiness-git-commit)
  - [Git Grumpiness: `git push`](#git-grumpiness-git-push)
  - [Git Grumpiness: `git pull --ff`](#git-grumpiness-git-pull---ff)
  - [Git Grumpiness: `git pull --rebase`](#git-grumpiness-git-pull---rebase)

## Retrieving the Lab

We will place each coding assignment in a non-`main` branch so that adding a new assignment does not interfere with the assignment you're working on.
When you are ready to work on a coding assignment, notionally *FooLab*, you can retrieve the assignment's instructions and starter code:

- First, make sure your repository is ready to receive the *FooLab* and that you are on the `main` branch.
  ```shell
  git status
  ```
  You should see something like this:
  ```
  On branch main
  Your branch is up to date with 'origin/main'.
  
  nothing to commit, working tree clean
  ```
  The important parts are that you are on `main` and that your working tree is clean.
  If you see something different, see [the corrective steps below](#git-grumpiness-git-status).
- Next, retrieve the latest branches from the remote copy of your repository:
  ```shell
  git fetch origin
  ```
  If there are no new branches to retrieve, then there will be no output.
  If the instructor has added a new assignment, then you should see something like this:
  ```
  From git.unl.edu:csce231/spring2026/your-repo.git
  * [new branch]      FooLab     -> origin/FooLab
  ```
  If you see something different, see [the corrective steps below](#git-grumpiness-git-fetch).
- Finally, merge the *FooLab* branch into your `main` branch.
  ```shell
  git merge --ff origin/FooLab
  ```
  If everything is clean, you should see one of two types of messages.
  - If Git can fast-forward through the merge, you will see:
    ```
    Updating abc1234..def5678
    Fast-forward
    FooLab/README.md   | 10 ++++++++++
    FooLab/src/main.c  | 42 ++++++++++++++++++++++++++++++++++++++++++
    ...
    ```
  - If Git needs to perform an explicit merge, you will see:
    ```
    Updating abc1234..def5678
    Merge made by the 'ort' strategy.
    FooLab/README.md   | 10 ++++++++++
    FooLab/src/main.c  | 42 ++++++++++++++++++++++++++++++++++++++++++
    ...
    ```
    and a new commit will be created for the merge.
  
  If you see something different, see [the corrective steps below](#git-grumpiness-git-merge).

## Reading the Assignment

The README.md file in each lab's directory has the front matter for the assignment, including links to each page of the assignment.
The bottom of each page (including README.md) has navigation links to move forward or backward in the assignment.

## How Long will the Lab Take?

A good rule of thumb is to pay attention to how many points the lab is worth.
- **10 points** - except for PokerLab, a 10-point assignment is designed to be finished during lab time.
  - PokerLab is a different beast -- the lab itself can easily be finished during lab time, but the time to set up your development environment may throw that off.
- **20 points** - about half of the class will finish during lab time.
- **30-40 points** - we do not expect anybody to finish during lab time.
- **50+ points** - a multi-week lab
  - You should not expect to be able to start a multi-week lab the day before it's due and still be able to finish it.

## Typical Lab Directory Structure

```
FooLab/
 │
 ├── CMakeLists.txt                         # configuration file
 ├── CMakePresets.json                      # configuration file
 ├── submission_metadata.json               # used to indicate if you're exercising late days, had a lab partner, or consulted external references
 ├── README.md                              # Assignment front matter
 ├── build/...                              # Will appear after you configure the project
 ├── data/...                               # Files that are neither code nor documentation (not present in all assignments)
 ├── doc/...                                # The pages describing the assignment's tasks
 ├── src/...                                # The source code
 └── test/...                               # Constraint Check Tests
```

## Configuring, Compiling, Running, and Testing

### Configuring the Project

If you're using an IDE, open the project in the *FooLab* directory (the same directory that has CMakeLists.txt).
It should configure the project for you.
If you're working on your personal computer instead of Nuros, you may be prompted to identify the compiler you'll use.

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt).
If you're working on Nuros, run the command:
```shell
cmake --preset=default
```
If you're working on your personal computer, run the command:
```shell
cmake --preset=personal-computer
```
or, if you need to specify a particular compiler:
```shell
cmake --preset=personal-computer -DCMAKE_C_COMPILER=/path/to/the/compiler
```

### Compiling the Project

If you're using an IDE, there should be a "Build" button.
In VS Code, you can also select one of these commands from the command palette:
```
CMake: Build                                # Builds all targets
CMake: Build Target                         # Build a specific target
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
cmake --build build
```
or, to build a specific target:
```shell
cmake --build build --target foolab
```

### Running the Program

If you're using an IDE, there should be a "Run" button.
In VS Code, you can also select one of these commands from the command palette:
```
CMake: Run Without Debugging
CMake: Debug
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
build/foolab
```

### Testing the Program

We expect you to test your own code.
Most labs' driver code is designed to facilitate this: provide your inputs, and the driver code will show you the actual output and compare it with the expected output.

We do, however, provide one automated test.
Most labs have particular constraints that require you to write your code in a way that will help you attain the learning objectives.
We provide an automated test that checks for violations of the assignment's constraints.

[//]: # (TODO: Build a "test recorder" to turn student tests into automated tests for regression testing)

If you're using an IDE, there should be controls to run the test.
In VS Code, you can also select this command from the command palette:
```
CMake: Run Tests
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
ctest --test-dir build --output-on-failure
```

Any constraint violations will result in a failed test, and `--output-on-failure` will show you what the constraint violations are.

## Turning in the Completed Lab

Some parts of some labs require you to provide answers on Canvas.
Be sure to have those completed before the assignment is due.

You turn in the code simply by pushing your completed lab to your repository.
You *should* make a habit of committing successful changes along the way, but at a minimum, push your completed code before the assignment is due.
If you are exercising one or more late days, be sure to also edit and push submission_metadata.json.

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the commands:
```shell
git add .                                   # will stage both src/ directory and submission_metadata.json
git commit
```
An editor should open for you to provide a commit message.  
If it does not, see [the corrective steps below](#git-grumpiness-git-commit).

Send the updates to git.unl.edu:
```shell
git push
```
You should see a message that is something like this:
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
If you see something different, see [the corrective steps below](#git-grumpiness-git-push).

---

## When Git Gets Grumpy

### Git Grumpiness: `git status`

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

### Git Grumpiness: `git fetch`

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

### Git Grumpiness: `git merge`

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

### Git Grumpiness: `git commit`

You attempted to stage and commit files:
```shell
git add .
git commit
```
You expected the editor should open for you to provide a commit message, but it didn't.
- If `git commit` exits with *nothing to commit, working tree clean*, then either you forgot to run `git add`, or there were no changes to stage when you ran `git add`.
  Run `git status` to see what (if anything) is changed.
- If the screen changed but looks "stuck," then Git has probably opened a text editor in the terminal (often Vim or Nano) and is waiting fo ryou to type a commit message.
  Type a short message describing your changes, then save and exit the editor
- If you see *Aborting commit due to empty commit message*, then the editor was closed without you having entered a commit message.
  Run `git commit` again and include a commit message.
- If an editor opened outside the terminal, then switch to that window to enter your commit message.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Turning in the Completed Lab"](#turning-in-the-completed-lab)

### Git Grumpiness: `git push`

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
- If you see netowrk-related errors such as: *ssh: Could not resolve hostname git.unl.edu: Name or service not known*, or  
    *ssh: connect to host git.unl.edu port 22: Connection timed out*, then  
    this is a connectivity problem.
    Check the network.
- If you see authentication errors such as: *Permission denied (publickey)*, or
  *fatal: Could not read from remote repository* (**without** timeouts/DNS errors), then
  this is usually a login/SSH key issue.
  A TA or the instructor can help you troubleshoot this issue.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.

[Back to "Turning in the Completed Lab"](#turning-in-the-completed-lab)

### Git Grumpiness: `git pull --ff`

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

### Git Grumpiness: `git pull --rebase`

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
