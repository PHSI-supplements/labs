# Connection to Nuros

After the TAs have placed the URL for your Git repository in the comments of the "git.unl.edu username" Canvas assignment, navigate to that URL in your web browser to confirm that you have access.

- Locate the `Code ᵛ` button and click it to get its dropdown menu.
  Copy the **"Clone with SSH"** link.
- Using a Secure Shell (SSH) terminal, connect to your account on nuros.unl.edu. 
  Optionally create a directory for CSCE 231 and use `cd` to navigate to that directory.
- Clone your Git repository:
  ```
  git clone git@git.unl.edu:csce231/...
  ```
  where *git@git.unl.edu:csce231/...* is the "Clone with SSH" link that you copied.
- After the clone is complete, test your ability to make an edit and send the change to git.unl.edu.
  - Use `cd` to navigate in your local copy of your repository.
  - Use a text editor such as Vim or Nano to edit the top-level *README.md* file:
    ```shell
    vim README.md
    ```
    or
    ```shell
    nano README.md
    ```
  - Locate the "Student" section near the top:
    > ```
    > ## Student
    > 
    > - Name:
    > - Lab Section:
    > ```
  - Fill in your name and your lab section.
  - Save the file and exit the editor.
  - Stage the file for a commit:
    ```shell
    git add README.md
    ```
  - Commit the change:
    ```shell
    git commit
    ```
    An editor will open (probably Vim or Nano, possibly an editor outside the terminal).
    Type a descriptive commit message, such as "Added my name to README".
    Save and close the editor.
  - Push the commit to git.unl.edu:
    ```shell
    git push
    ```
  - Refresh the web browser that you have opened to your git.unl.edu repository.
    You should see your commit message above the list of files, and you should see your changes in the README.md file.
- Finally, run these three commands so that we can see that you can connect to Nuros and have successfully cloned your repository and made a commit:
  ```
  cat /etc/hostname
  whoami
  ls
  git log
  ```

---

On the Canvas page for this assignment:
- Click on the `Submit Assignment` button in the upper-right corner. This will make a text entry field appear at the bottom of the page.
- Copy/paste the responses to the `cat`, `whoami`, `ls`, and `git log` commands into the text entry field, and click on the new `Submit Assignment` button.

---

You can now return to the last section of [Setting Up Your CSCE 231 Development Environment](https://canvas.unl.edu/courses/209782/pages/setting-up-your-csce-231-development-environment).
