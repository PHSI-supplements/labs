# Clone Your Repository

After the TAs have placed the URL for your Git repository in the comments of the "git.unl.edu Username" Canvas assignment, navigate to that URL in your web browser to confirm that you have access.

- [ ] Locate the `Code ᵛ` button and click it to get its dropdown menu.
  Copy the **"Clone with SSH"** link.
- [ ] Decide where on your computer's file system you want your CSCE 231 repository to be stored.
  In your terminal window, use the `cd` command to navigate to that location.
- [ ] Clone your Git repository:
  ```bash
  git clone git@git.unl.edu:csce231/...
  ```
  where *git@git.unl.edu:csce231/...* is the "Clone with SSH" link that you copied.

  > ⚠️ **A Common Mistake**
  > 
  > If you are prompted
  > ```text
  > Username for 'https://git.unl.edu':
  > ```
  > Then you inadvertently copied the "Clone with HTTPS" link.
  > *You **must** use the "Clone with SSH" link.*


## Verify the Remote Repository

- [ ] After cloning, run the command:
  ```bash
  git remote -v
  ```

  You should see output similar to:
  ```text
  origin  git@git.unl.edu:csce231/your-repository.git (fetch)
  origin  git@git.unl.edu:csce231/your-repository.git (push)
  ```

## Configure Your Name and Email Address

For this course, you need to configure your name and email address for the Git repository, even if you previously set your global name and email address.
This is because we're going to run the labs in a "container," which has its own Git configuration that is separate from the one on your computer.
By storing your name and email address in the repository itself, Git will use the correct information whether you commit from your computer or from inside the container.

These may be the same as your global name and address;
however, your name *must* be recognizable as you, and your email address *must* be your UNL email address.
(For example, if Canvas lists you as "Stuart Dent", then "Stuart Dent", "Stu Dent", or "S Dent" are all acceptable names.
Nicknames or handles such as "Awesome CodeMaestro" are not.)

- [ ] Run these commands, replacing the placeholders with your own information:
  ```bash
  git config user.name "YOUR HUMAN NAME"
  git config user.email "USERNAME@huskers.unl.edu"
  git config commit.gpgsign false
  ```
- [ ] Verify the configuration:
  ```bash
  git config --show-origin --get user.name
  git config --show-origin --get user.email
  git config --show-origin --get commit.gpgsign
  ```
  These should show the values you provided, along with "file:.git/config".
  If the file is something like "file:/Users/sdent3/.gitconfig" then the repository-specific values were not set.

> ⓘ **Note**
>
> `git config commit.gpgsign false` disables the option to cryptographically sign your commits for this repository.
> This simplifies setting up the Docker container in an upcoming task.
> 
> If you have your "global" Git configuration set to cryptographically sign your commits, and if you want to preserve that option for this repository, then see Dr. Bohn for additional information.
> 
> If you don't know what I'm talking about, don't worry about it.


## Verify That You Can Commit and Push

[//]: # (TODO: revise the following instructions to work with Windows, too -- from what I read, it sounds like Git for Windows uses vim as the default editor -- does it install it? -- if so, we can just say "use vim" and move on, I guess)

After the clone is complete, test your ability to make an edit and send the change to git.unl.edu.

- [ ] Use `cd` to navigate into your local copy of your repository.
- Use a text editor of your choice to edit the top-level *README.md* file.
  - [ ] Locate the "Student" section near the top:
    > ```markdown
    > ## Student
    > 
    > - Name:
    > - Lab Section:
    > ```
  - [ ] Fill in your name and your lab section.
  - [ ] Save the file and exit the editor.
- [ ] Stage the file for a commit:
  ```bash
  git add README.md
  ```
- [ ] Commit the change:
  ```bash
  git commit -m "Added my name to README"
  ```

  > ⓘ **Note**
  > 
  > Without the `-m` argument, `git commit` launches an editor, typically Vim, for you to add your commit message.
  > Using the `-m` argument is convenient for short, one-line commit messages.
  > 
  > Learning to use Vi-family editors such as Vim can be valuable throughout your career, and not just for writing commit messages.
  > Learning to use Vim is not an objective of this course, but we encourage you to run
  > ```bash
  > vimtutor
  > ```
  > when you have the time to do so.

- [ ] Push the commit to git.unl.edu:
  ```bash
  git push
  ```
- [ ] Refresh the web for your repository.
  You should see:
  - Your commit message, authored by you, above the list of files, and
  - Your changes in the README.md file.


- [ ] Show a TA the web view of your repository.
