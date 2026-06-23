# Assignment Structure

## Reading the Assignment

The README.md file in each lab's directory has the front matter for the assignment, including links to each page of the assignment.
The bottom of each page (including README.md) has navigation links to move forward or backward in the assignment.

[//]: # (TODO: Markdown preview from various sources, and index.html)


## How Long will the Lab Take?

A good rule of thumb is to pay attention to how many points the lab is worth.
- **10 points** - except for PokerLab, a 10-point assignment is designed to be finished during lab time.
    - PokerLab is a different beast -- the lab itself can easily be finished during lab time, but the time to set up your development environment may throw that off.
- **20 points** - about half of the class will finish during lab time.
- **30-40 points** - we do not expect anybody to finish during lab time.
- **50+ points** - a multi-week lab
    - You should not expect to be able to start a multi-week lab the day before it's due and still be able to finish it.


## Typical Lab Directory Structure (Linux-Native Code)

```
FooLab/
 │
 ├── CMakeLists.txt                         # configuration file
 ├── CMakePresets.json                      # configuration file
 ├── submission_metadata.json               # used to indicate if you're exercising late days, had a lab partner, or consulted external references
 ├── README.md                              # Assignment front matter
 ├── build/...                              # Will appear after you configure the project
 ├── data/...                               # Files that are neither code nor documentation (not present in all assignments)
 ├── doc/...                                # The pages describing the assignment's tasks
 ├── src/...                                # The source code
 └── test/...                               # Constraint Check Tests
```


## Typical Lab Directory Structure (Cow Pi Code)

```
FooLab/
 │
 ├── platformio.ini                         # configuration file
 ├── rename_uf2.py                          # post-processing file
 ├── submission_metadata.json               # used to indicate if you're exercising late days, had a lab partner, or consulted external references
 ├── README.md                              # Assignment front matter
 ├── build/...                              # Will appear after you configure the project
 ├── data/...                               # Files that are neither code nor documentation (not present in all assignments)
 ├── doc/...                                # The pages describing the assignment's tasks
 ├── include/...                            # Unused, but required by the build system
 ├── lib/...                                # Unused, but required by the build system
 ├── src/...                                # The source code
 └── test/...                               # Constraint Check Tests
```
