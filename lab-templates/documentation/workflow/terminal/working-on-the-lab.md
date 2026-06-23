# Working on the Lab using the Terminal

- Connecting to the Server
- Linux-Native Code
    - [Configuring the Project](#configuring-compiling-running-and-testing-linux-native-code)
    - [Compiling the Project](#compiling-the-project-linux-native-code)
    - [Running the Program](#running-the-program-linux-native-code)
    - [Testing the Program](#testing-the-program-linux-native-code)
- Cow Pi Code
    - [Configuring the Project](#configuring-the-project-cow-pi-code)
    - [Compiling the Project](#compiling-the-project-cow-pi-code)
    - [Uploading the Program](#uploading-the-program-to-the-cow-pi-board-cow-pi-code)


## Connecting to the Server

Open a terminal window on your laptop and run the command
```
ssh USERNAME@nuros.unl.edu
```
After the connection is established, use the `cd` command to navigate to the *FooLab* directory.


## Configuring, Compiling, Running, and Testing (Linux-Native Code)

### Configuring the Project (Linux-Native Code)

Navigate to the *FooLab* directory (the same directory that has CMakeLists.txt).
If you're working on Nuros, run the command:
```shell
cmake --preset=default
```
If you're working on your personal computer, run the command:
```shell
cmake --preset=personal-computer
```
or, if you need to specify a particular compiler:
```shell
cmake --preset=personal-computer -DCMAKE_C_COMPILER=/path/to/the/compiler
```

### Compiling the Project (Linux-Native Code)

Navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
cmake --build build
```
or, to build a specific target:
```shell
cmake --build build --target foolab
```

### Running the Program (Linux-Native Code)

Navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
build/foolab
```

### Testing the Program (Linux-Native Code)

We expect you to test your own code.
Most labs' driver code is designed to facilitate this: provide your inputs, and the driver code will show you the actual output and compare it with the expected output.

We do, however, provide one automated test.
Most labs have particular constraints that require you to write your code in a way that will help you attain the learning objectives.
We provide an automated test that checks for violations of the assignment's constraints.

[//]: # (TODO: Build a "test recorder" to turn student tests into automated tests for regression testing)

Navigate to the *FooLab* directory (the same directory that has CMakeLists.txt) and run the command:
```shell
ctest --test-dir build --output-on-failure
```

Any constraint violations will result in a failed test, and `--output-on-failure` will show you what the constraint violations are.


## Configuring, Compiling, and Uploading (Cow Pi Code)

### Configuring the Project (Cow Pi Code)

Navigate to the *FooLab* directory (the same directory that has platformio.ini).
Further configuration will occur the first time that you compile the project.

### Compiling the Project (Cow Pi Code)

Navigate to the *FooLab* directory (the same directory that has platformio.ini) and run the command:
```shell
pio run
```
- There are many parts of MBED&nbsp;OS that generate compiler warnings the first time that you build the project.

The constraint checker will run automatically at the end of the build process.
After a successful build, any constraint violations will be listed after any compiler warnings and before the `[SUCCESS]` message.

### Uploading the Program to the Cow Pi Board (Cow Pi Code)

1. Press the RESET button
2. While still pressing the RESET button, press the BOOTSEL button
3. Release the RESET button
4. Release the BOOTSEL button
    - This will present the microcontroller's flash memory to your computer as a USB mass storage device.
5. Drag & drop the .uf2 file from the *FooLab/build* directory to the USB mass storage device.
    - After the upload has finished, the USB mass storage device will disconnect.

[//]: # (TODO: ...or use `cp` command)