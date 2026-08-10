# When SSH Says Silly Stuff

Note: GitLab has its own [SSH troubleshooting page](https://docs.gitlab.com/user/ssh_troubleshooting/).

These suggestions are organized around the error condition.

- [The authenticity of host ... can't be established](#ssh-silliness-host-authenticity)
- [Permission denied (publickey)](#ssh-silliness-permission-denied)
- [`SSH_AUTH_SOCK` variable is not set](#ssh-silliness-ssh_auth_sock-variable-is-not-set-or-ssh-agent-is-not-running)
- [ssh-agent is running, but the key isn't loaded](#ssh-silliness-ssh-agent-is-running-but-the-key-isnt-loaded)
- [Inappropriate permissions on the key files](#ssh-silliness-inappropriate-file-permissions)
- [DNS/network failure](#ssh-silliness-dnsnetwork-failure)


## SSH Silliness: host authenticity

If you see something like
```text
The authenticity of host 'git.unl.edu (129.93.168.32)' can't be established.
ECDSA key fingerprint is SHA256:...
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```
This is not a failure.
This is a normal first-connection experience.
The safest thing to do is to [verify the host fingerprint](https://git.unl.edu/help/instance_configuration), but I think most people simply type `yes`. 


## SSH Silliness: permission denied

If you see something like
```text
Permission denied (publickey)
```
GitLab's documentation identifies a [half-dozen possible causes](https://docs.gitlab.com/user/ssh_troubleshooting/#error-permission-denied-publickey).
Some other possible causes include:
- The keypair doesn't exist. If
  ```bash
  ls ~/.ssh/id_ed25519 ~/.ssh/id_ed25519.pub
  ```
  shows that one or both files are absent, then try [generating a new keypair and copying the new public key to git.unl.edu](../first-time-setup/03-generate-ssh-keypair.md).
- The wrong public key was copied to GitLab -- from SSH's perspective, this is the same as GitLab's "Wrong private key being used" possible cause.
  The difference is your intent. Here, your fix is to copy the correct public key to GitLab.

A TA or the instructor can help you troubleshoot this issue.
- Does `~/.ssh/id_ed25519 exist?`
- Is its corresponding public key in git.unl.edu?
- Is `SSH_AUTH_SOCK` set / is ssh-agent running?
- Does `ssh-add -l` show `id_ed25519`?


## SSH Silliness: `SSH_AUTH_SOCK` variable is not set or ssh agent is not running

- **Linux** or **macOS**:<br>
  Run
  ```bash
  echo "$SSH_AUTH_SOCK"
  ssh-add -l
  ```
  If `SSH_AUTH_SOCK` is blank, the current shell does not have an ssh agent socket.
  If `ssh-add -l` says something like
  ```text
  Could not open a connection to your authentication agent.
  ```
  then it's certain that the shell cannot communication with an ssh agent.<br>
  Re-start ssh agent and re-add your private keys to the agent:
  ```bash
  eval "$(ssh-agent -s)"
  ssh-add
  ```
- **Windows**:<br>
  Run
  ```bash
  Get-Service ssh-agent
  ```
  If its `Status` is `Stopped`, then re-start ssh agent:
  ```bash
  Restart-Service ssh-agent
  ```


## SSH Silliness: ssh-agent is running, but the key isn't loaded

ssh-agent "forgets" the keys after being shut down and restarted -- such as when rebooting your computer.
If ssh agent is running and `SSH_AUTH_SOCK` is set, then run
```bash
ssh-add -l
```
If your private key isn't listed, then run `ssh-add` (without arguments) to load all of your private keys into ssh-agent, or `ssh-add <filename>` to load a specific private key.


## SSH Silliness: inappropriate file permissions

OpenSSH may refuse to use a private key that has too-generous file permissions.
The `~/.ssh/` directory should have `700` permissions, and private keys should have `600` permissions.
If the permissions need to be changed, use `chmod`.


## SSH Silliness: DNS/network failure

If you see something like
```text
ssh: Could not resolve hostname git.unl.edu: Name or service not known
```
or
```text
ssh: connect to host git.unl.edu port 22: Connection timed out
```
Then the problem isn't with SSH.
Assuming that you typed the correct hostname, then the problem is with the network.

