# Install Git

If Git is already installed on your computer, you can skip to [Verify Your Installation](#verify-your-installation).


## Windows

- [ ] Visit https://git-scm.com/downloads.
- [ ] Download and run the Windows installer.
- [ ] Unless instructed otherwise, accept the default installation options.
- [ ] When the installation is complete, open **PowerShell**.


## macOS

### Option 1: Install Git Through Xcode Command Line Tools (recommended)

- [ ] Open **Terminal**.
- [ ] Run:
  ```bash
  git --version
  ```
- If Git is not installed, macOS will prompt you to install the Xcode Command Line Tools.
  - [ ] Follow the prompts to complete the installation.

### Option 2: Install Git Directly

1. Visit https://git-scm.com/downloads.
2. Download and install Git for macOS.
3. Open **Terminal** when the installation completes.


## Linux

If you're running Linux on your laptop, it's likely that Git is already installed.

- Confirm that Git is already installed.
  - [ ] Open a terminal window.
  - [ ] Run:
    ```bash
    git --version
    ```
- [ ] If git is not installed (`git: command not found`), then install it using your installation's package manager.
  - apt (*e.g.*, Ubuntu)
    ```bash
    sudo apt update
    sudo apt install git
    ```
  - dnf (*e.g.*, Fedora)
    ```bash
    sudo dnf install git
    ```
  - Arch Linux
    ```bash
    sudo pacman -S git
    ```


## Verify Your Installation

- [ ] Open a terminal and run:
  ```bash
  git --version
  ```

- You should see output similar to:
  ```text
  git version 2.51.0
  ```

The exact version number may be different.


## Configure Your Name and Email Address

It is a good idea to configure your default "global" name and email address;
however, you do not need to do so for this course.

If you choose to configure your git "global" information:
- [ ] Run these commands, replacing the placeholders with your own information:
  ```bash
  git config --global user.name "YOUR HUMAN NAME"
  git config --global user.email "USERNAME@example.com"
  ```
- [ ] Verify the configuration:
  ```bash
  git config --global --list
  ```
  - You should see your name and email address in the output.
