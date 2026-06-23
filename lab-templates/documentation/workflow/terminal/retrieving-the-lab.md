# Retrieving the Lab using the Terminal

We will place each coding assignment in a non-`main` branch so that adding a new assignment does not interfere with the assignment you're working on.
When you are ready to work on a coding assignment, notionally *FooLab*, you can retrieve the assignment's instructions and starter code:


## Prepare to Retrieve the Updates

First, make sure your repository is ready to receive the *FooLab* and that you are on the `main` branch.
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
If you see something different, see [the `git status` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-status).


## Fetch the Updates

Next, retrieve the latest branches from the remote copy of your repository:
```shell
git fetch origin
```
If there are no new branches to retrieve, then there will be no output.
If the instructor has added a new assignment, then you should see something like this:
```
From git.unl.edu:csce231/spring2026/your-repo.git
* [new branch]      FooLab     -> origin/FooLab
```
If you see something different, see [the `git fetch` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-fetch).


## Merge the Updates into `main`

Finally, merge the *FooLab* branch into your `main` branch.
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

If you see something different, see [the `git merge` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-merge).
