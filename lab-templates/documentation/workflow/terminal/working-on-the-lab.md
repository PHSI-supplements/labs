# Working on the Lab using the Terminal

These instructions assume that you have already [started the development container](accessing-the-container.md) in one or more terminal windows.

- Linux-Native Code
    - [Configuring the Project](#configuring-compiling-running-and-testing-linux-native-code)
    - [Compiling the Project](#compiling-the-project-linux-native-code)
    - [Running the Program](#running-the-program-linux-native-code)
    - [Testing the Program](#testing-the-program-linux-native-code)
- Cow Pi Code
    - [Configuring the Project](#configuring-the-project-cow-pi-code)
    - [Compiling the Project](#compiling-the-project-cow-pi-code)
    - [Uploading the Program](#uploading-the-program-to-the-cow-pi-board)
    - [Testing the Program](#testing-the-program-cow-pi-code)


## Configuring, Compiling, Running, and Testing (Linux-Native Code)

Unless otherwise noted, these commands should be run from the *FooLab* directory (the directory containing `CMakeLists.txt`).

- [ ] Use `cd` to navigate to the *FooLab* directory.

### Configuring the Project (Linux-Native Code)

You normally only need to configure the project once.

- [ ] Generate the build files:
  ```bash
  cmake --preset=default
  ```


### Compiling the Project (Linux-Native Code)

- [ ] Run the command:
  ```bash
  cmake --build build
  ```
  or, to build a specific target:
  ```bash
  cmake --build build --target foolab
  ```

### Running the Program (Linux-Native Code)

- [ ] Run the command:
  ```bash
  build/foolab
  ```

If you wish to use an interactive debugger
- [ ] Launch GDB:
  ```bash
  gdb build/foolab
  ```


### Testing the Program (Linux-Native Code)

We expect you to test your own code.
Most labs' driver code is designed to facilitate this: provide your inputs, and the driver code will show you the actual output and compare it with the expected output.
We also provide automated tests that correspond to any examples in the assignment's instructions.

Further, most labs have particular constraints that require you to write your code in a way that will help you attain the learning objectives.
We provide an automated test that checks for violations of the assignment's constraints.

[//]: # (TODO: Build a "test recorder" to turn student tests into automated tests for regression testing)

- [ ] Use `cd` to navigate to the *FooLab* directory (the same directory that has CMakeLists.txt).
- [ ] Run the command:
  ```bash
  ctest --test-dir build --output-on-failure
  ```


## Configuring, Compiling, and Uploading (Cow Pi Code)

### Configuring the Project (Cow Pi Code)

PlatformIO won't configure the build system until the first time that you compile the project.

### Compiling the Project (Cow Pi Code)

- [ ] Use `cd` to navigate to the *FooLab* directory (the same directory that has platformio.ini).
- Run the command:
  ```bash
  pio run
  ```
- There are many parts of MBED&nbsp;OS that generate compiler warnings the first time that you build the project.
  You do not need to address *these* compiler warnings: fixing MBED&nbsp;OS is outside the scope of this course.

The constraint checker will run automatically at the end of the build process.
After a successful build, any constraint violations will be listed after any compiler warnings and before the `[SUCCESS]` message.

### Uploading the Program to the Cow Pi Board

- [ ] Open a file browser on your host computer and navigate to the *FooLab* directory.
- [ ] Prepare the Cow Pi to receive the program.
  1. Press the RESET button on the Cow Pi
  2. While still pressing the RESET button, press the BOOTSEL button on the Cow Pi
  3. Release the RESET button
  4. Release the BOOTSEL button
     - This will present the microcontroller's flash memory to your computer as a USB mass storage device.
- [ ] Drag & drop the .uf2 file from the *FooLab/build* directory to the USB mass storage device.
  - After the upload has finished, the USB mass storage device will disconnect.

[//]: # (TODO: Debugging)

### Testing the Program (Cow Pi Code)

There are no automated tests for code running on the Cow Pi boards.
You will need to manually test your code.

The constraint checker, however, will run as part of the build process.
