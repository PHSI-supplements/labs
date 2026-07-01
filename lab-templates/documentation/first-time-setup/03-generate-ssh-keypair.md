# Configure SSH Authentication for your git.unl.edu Account

- [ ] Generate an SSH keypair by running the command
  ```bash
  ssh-keygen -t ed25519 -C "CSCE 231"
  ```
  When asked what file to save it in, press ENTER to accept the default.  
  When prompted for a passphrase, you may set one up, or you can press ENTER to use no passphrase.

That will create a public key and a private key that together form a cryptographic keypair, stored in your `~/.ssh/` directory.
You will use the keypair to let git.unl.edu know that messages from you are authentic.

> ⓘ **Public vs Private Keys**
> 
> The file ending in .pub is your **public key** and may be shared with the Git server.
> Do not share the file without the .pub extension, as that is your **private key**.
> 
> You can read more about [public-key cryptography](https://en.wikipedia.org/wiki/Public-key_cryptography) if you like.

- Copy the *public* key
  - [ ] Run the command
    ```bash
    cat ~/.ssh/id_rsa.pub
    ```
  - [ ] Highlight the output, and copy it to your computer's clipboard.
- Add the public key into your git.unl.edu account
  - [ ] In git.unl.edu's web interface, click on your avatar to get a drop-down menu, and select "Edit profile" (alternatively, from your account page, there is an "Edit profile" in the upper-right corner)  
    ![A dropdown menu suspended from a photograph. Highlighted on the dropdown menu is "Edit profile".](media/git-edit-profile.png)
  - [ ] In the left-side menu, select "SSH Keys".
  - [ ] Paste the public key that you copied into the "Key" field, and click "Add key"
- [ ] Confirm that you can now authenticate with git.unl.edu by running the command
  ```bash
  ssh -T git@git.unl.edu
  ```
