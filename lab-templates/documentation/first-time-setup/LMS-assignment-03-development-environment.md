# The Development Environment

For most of the semester, the target platform will be the nuros.unl.edu Linux server.
You have the option of writing your software on your personal computer and then uploading it to Nuros for testing,
but IDE's remote development tools have matured enough that most students find it more convenient to configure their IDE for remote development on Nuros.
That is, your files will be in your home directory on Nuros; your IDE will connect to your Nuros account to access the files; building and testing the files will take place on Nuros automatically.


## Secure Shell Terminal

You can reasonably expect that when you're using your IDE for remote development, its built-in terminal emulator will also connect to Nuros.
There will be a couple of labs that may be easier to use a more conventional terminal emulator to SSH into Nuros.

### From Mac or Linux

If your personal computer (or the lab computer you're using) is a Mac or a Linux box,
the simplest option is to open a terminal window on your computer and type
```
ssh USERNAME@nuros.unl.edu
```
where *username* is your UNL username.
See the "Working Remotely" section of [The School of Computing's Support FAQ](https://computing.unl.edu/faq/),
specifically "Connecting to cse.unl.edu and other Unix servers with SSH from...", for instructions.

-  Instead of using *cse.unl.edu* as the Host Name, use *nuros.unl.edu*.
-  Instead of using your SoC username and password, use your UNL username and password.

### From Windows

If your personal computer (or the lab computer you're using) is a Windows machine,
you can launch an SSH session from a Windows terminal window in the same manner as for Mac and Linux, though this seems to be a less-popular option than using PuTTY.

If you choose to use PuTTY, see the "Working Remotely" section of [The School of Computing's Support FAQ](https://computing.unl.edu/faq/),
specifically "Connecting to cse.unl.edu and other Unix servers with SSH from Windows" for instructions.

-  Instead of using *cse.unl.edu* has the Host Name, use *nuros.unl.edu*.
-  Instead of using your SoC username and password, use your UNL username and password.


## Transferring Files

If you do your development remotely, you shouldn't need to transfer files between your local computer and Nuros.
If you find that you do need to do so, you can reasonably expect that when you're using your IDE for remote development, you can drag-and-drop from the IDE's "files" pane to your local computer's file manager.
You may, however, prefer a standalone application to transfer files.

### scp

If you're comfortable working with the command line, the `scp` command has very much the same basic use of the `cp` command, except that you specify the remote host.
Coping files from your computer to the server:
```
scp FILE-1 FILE-2 ... FILE-N USERNAME@nuros.unl.edu:FILEPATH
```
copies the files from your local computer to the *filepath* on the *nuros.unl.edu* Linux server, where *filepath* is relative to your home directory.
Or, working the other direction:
```
scp USERNAME@nuros.unl.edu:FILE FILEPATH
```
copies *file* from the remote server to *filepath* on your local computer.
Just as with *cp*, you can use the `-r` argument to copy directories:
```
scp -r pokerlab USERNAME@nuros.unl.edu:.
scp -r USERNAME@nuros.unl.edu:pokerlab .
```

### FileZilla

FileZilla is a very popular drag-and-drop option.
See the "Working Remotely" section of [The School of Computing's Support FAQ](https://computing.unl.edu/faq/),
specifically "How do I access my home directory from off campus from Windows?"
(Despite the name of that particular FAQ, FileZilla is also available for non-Windows systems.)

-  Instead of using *cse.unl.edu* has the Host Name, use *nuros.unl.edu*.
-  Instead of using your SoC username and password, use your UNL username and password.


## Editing Files

### Vim or Emacs

If you prefer to use Vim or Emacs, we assume that you will either work from the command line on Nuros and are otherwise sufficiently comfortable with your editor that you will need little guidance in configuring it.

### VS Code

[VS Code](https://code.visualstudio.com/) is a very popular IDE.
You will need to install some plugins:
- [ ] [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack), which includes
    - C/C++ <!-- https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools -->
    - CMake Tools <!-- https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools -->
    - C/C++ UI Themes <!-- https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-themes -->
- [ ] [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh)
- [ ] [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

<!--

[//]: # (TODO: It looks like this will require some server-level downloads, and sysadmin might not appreciate that. CLion will have to wait until we switch to Docker)

### CLion

[CLion](https://www.jetbrains.com/clion/) is second in popularity only to VS Code; price may be a factor for that.
JetBrains has long offered a free academic license for its professional-grade products (that involved leaping through a few hoops),
but JetBrains recently made CLion free for any noncommercial use, which should greatly simplify the process if you wish to use CLion.
You will need to install a plugin:
- [ ] [PlatformIO](https://www.jetbrains.com/help/clion/platformio.html)

-->

### Other IDEs

You may use another IDE if you wish; however, you are responsible for configuring it.

When we issue the Cow Pi hardware kits (or before that), you will want to install the [PlatformIO plugin](https://platformio.org/install/integration) for your IDE or the [command-line PlatformIO Core](https://platformio.org/install/cli).
