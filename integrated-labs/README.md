# CSCE 231 Lab Assignments

We will place the assignments and starter code for most of the labs in this directory.

## Table of Contents

- [Retrieving the Lab](#retrieving-the-lab)
- [Reading the Assignment](#reading-the-assignment)
- [How Long will the Lab Take?](#how-long-will-the-lab-take)
- [Typical Lab Directory Structure](#typical-lab-directory-structure)
- [Configuring, Compiling, and Testing](#configuring-compiling-and-testing)
- [Turning in the Completed Lab](#turning-in-the-completed-lab)

## Retrieving the Lab

The first lab, PokerLab, is available at the start of the semester.
We will place subsequent labs in branches so that doing so does not cause any confusion while you're finishing up another assignment.
When you are ready to work on the next lab, notionally *FooLab*, you can retrieve the assignment and starter code:

- First, make sure that you're on the `main` branch (you should be, but double-check) and that you have no uncommitted changes.
  ```bash
  git checkout main
  git status
  ```
  - If you get a *fatal: not a git repository* error, then navigate to your repository's directory and try again.
  - If `git status` does not say *nothing to commit, working tree clean*, then commit your changes (or stash them if you prefer) before continuing.
- Make sure the local copy of the `main` branch is up-to-date with the remote (this should be the case, but double-check).
  ```bash
  git pull
  ```
- Retrieve the *FooLab* branch and merge it into your `main` branch (replace `FooLab` with the actual, correct name).
  ```bash
  git fetch origin FooLab
  git merge --no-ff origin/FooLab
  ```
  There shouldn't be any merge conflicts, but if there are, and if you cannot resolve them yourself, then talk with a TA or the professor.

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
 ├── LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt  # used to indicate if you're exercising late days
 ├── README.md                              # Assignment front matter 
 ├── build/...                              # Will appear after you configure the project
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
```bash
cmake --preset=default
```
If you're working on your personal computer, run the command:
```bash
cmake --preset=personal-computer
```
or, if you need to specify a particular compiler:
```bash
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
```bash
cmake --build build
```
or, to build a specific target:
```bash
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
```bash
build/foolab
```

### Testing the Program

In general, there are no automated tests provided with the labs.
We expect you to test your own code.
Most labs' driver code is designed to facilitate this: provide your inputs, and the driver code will show you the actual output and compare it with the expected output.

We do, however, provide an automated test.
Most labs have particular constraints that require you to write your code in a way that will help you attain the learning objectives.
We provide an automated test that checks for violations of the assignment's constraints.

If you're using an IDE, there should be controls to run the test.
In VS Code, you can also select this command from the command palette:
```
CMake: Run Tests
```

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```bash
ctest --test-dir build --output-on-failure
```

Any constraint violations will result in a failed test, and `--output-on-failure` will show you what the constraint violations are.

## Turning in the Completed Lab

Some parts of some labs require you to provide answers on Canvas.
Be sure to have those completed before the assignment is due.

You turn in the code simply by pushing your completed lab to your repository.
You *should* make a habit of committing successful changes along the way, but at a minimum, push your completed code before the assignment is due.
If you are exercising one or more late days, be sure to also edit and push LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt.

If you're working from the command line, then navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```bash
git add .                                   # will stage both src/ directory and LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt
git commit                                  # will open an editor for you to provide a commit message
git push
```

