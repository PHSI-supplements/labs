# Turning in the Completed Lab using the Terminal

Some parts of some labs require you to provide answers on Canvas.
Be sure to have those completed before the assignment is due.

You turn in the code by pushing your completed lab to your Git repository.
You *should* make a habit of committing successful changes along the way, but at a minimum, push your completed code before the assignment is due.

> ⓘ **Note**
> 
> If you are exercising one or more late days, worked with a lab partner, or consulted external references, 
> then update `submission_metadata.json` before committing and pushing your work.

- [ ] Use `cd` to navigate to the *FooLab* directory (the same directory that has CMakeLists.txt).
- Run the commands:
  ```bash
  git add .                                   # stages all changes in the lab directory, including the src/ directory and the submission_metadata.json file
  git commit
  ```
  An editor should open for you to provide a commit message.  
  If it does not, see [the `git commit` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-commit).

- [ ] Send the updates to git.unl.edu:
  ```bash
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
  If you see something different, see [the `git push` troubleshooting steps](../../troubleshooting/git.md#git-grumpiness-git-push).

- [ ] Refresh your repository in your web browser and confirm that your most recent commit appears and that the files you changed contain your latest work.

Once your changes have been pushed to the Git server, no further action is required unless the assignment also includes questions to be answered on Canvas.
