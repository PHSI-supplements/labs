# BombLab

[//]: # (Original BombLab © Bryant & O'Hallaron, heavy edits © Bohn)

---

## Rebuild the Docker Image

> 🛑 **Before You Go Further** 🛑
> 
> After you have retrieved the BombLab assignment from git.unl.edu: 
> - [ ] Double-check that Docker is running
> - [ ] Close any running instances of the course container
>   ```bash
>   docker compose down
>   ```
> - [ ] **[Rebuild the course container Docker image](../documentation/first-time-setup/06-build-course-container.md)**
>   ```bash
>   docker compose build
>   ```
> 
> There are two reasons you need to rebuild the Docker image,
> - The *compose.yaml* file has an update to adjust the security settings for the container's OS, so that the OS's security settings don't interfere with an upcoming assignment.
> - The *Dockerfile* file has an update to add the `dos2unix` utility to Windows users [manage line breaks](doc/04-tips.md#dos-line-breaks-versus-unix-line-breaks).
> 
> There are a couple of other "quality of life" updates to the Docker image, too.
> - Ensures CLion has the PlatformIO plugin while connected to the container.
> - SSH configuration settings will persist between sessions.
> 
> ---
> 
> 👍 **Optional**
> 
> You may wish to suppress the warning about the connection to git.unl.edu not being quantum-safe.
> 
> - [ ] In a terminal window, launch the course container
>   ```bash
>   docker compose run --rm csce231
>   ```
> - [ ] In the container, run this command
>   ```bash
>   printf "Host git.unl.edu\n    WarnWeakCrypto no-pq-kex\n" > ~/.ssh/config
>   ```
> 


We now return you to your regularly-scheduled assignment. 💣

---

In this assignment, you will gain greater familiarity with assembly code by stepping through a disassembled program and seeing how it accesses registers and memory, and how it transforms data.

> ❗️ **Important**
>
> The instructions are written assuming you will run the bomb in the course container.
> Specifically, the bomb should run on any x86-64 processor or AAarch64 processor running Linux, but we know it runs in the course container.
> The bomb will not run in a Windows or macOS operating system.

> ❗️ **Important**
>
> When you initially configure the project,
> CMake will detect your system's environment and will provide the architecturally-appropriate "bomb".
>
> ---
>
> The *submission_metadata.json* file includes an "environment" object:
> ```
>  "environment": {
>    "architecture": "@ARCH@",
>    "os": "@OS@"
>  },
> ```
> CMake will replace the placeholder values with the actual values for your system.
> We will use this information to determine which assembly code file we should grade.
> **Please do not manually edit the "environment" object.**
> You may edit the other values as before.

This assignment is worth 50 points.


## Front Matter

### Submission Deadline

This assignment is due **the week of October 19, before the start of your lab section**.
Your completed assignment must be pushed to git.unl.edu before it is due.

If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [submission_metadata.json](submission_metadata.json) file and including the update with your code.

### Collaboration Rules

During your scheduled lab time, you may, **but are not required to**, form a partner group of 2 students.
When necessary, there may be a group of 3 students.
During your scheduled lab time, and until the end of your lab day, you may discuss problem decomposition and solution design with your lab partner.
After your scheduled lab day, you may discuss concepts and syntax with other students, but you may discuss solutions only with the professor and the TAs.
Sharing code with or copying code from another student or the internet is prohibited.

If you work with a lab partner, be sure to:
- Add your partner to [submission_metadata.json](submission_metadata.json),
- Commit your code (including submission_metadata.json) at the end of lab, and
- Commit your code at the end of the day if you continue to work with your partner after lab.

### Generative AI Rules

You may use the CodeHelp.app "virtual TA" for help, and
you may use "Oscar the AI Tutor" built into the course's textbook.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents


- [Getting Started](doc/01-getting-started.md)
- [Defusing a Bomb](doc/02-defusing-a-bomb.md)
- [Partial Source Code](doc/03-bomb.c.md)
- [Turn-In and Grading](doc/05-grading.md)


### Learning Objectives

After successful completion of this assignment, students will be able to:
- Disassemble machine code
- Recognize program structures in assembly code
- Trace the execution of assembly language programs

### Assignment Summary

In this assignment, your task is not to write code.
Instead, your task is to understand code and how it transforms data.
You likely will spend much time observing data progress through a disassembled program -- 
and you will use your new understanding to find the inputs to get functions to complete successfully. 


---

|                 |                              |       [➡️](doc/01-getting-started.md)        |
|:---------------:|:----------------------------:|:--------------------------------------------:|
|                 |                              | [Getting Started](doc/01-getting-started.md) |
