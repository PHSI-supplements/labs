# Working on the Lab using VS Code

[//]: # (TODO: screenshots)

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

Open the project in the *FooLab* directory (the same directory that has CMakeLists.txt).
- Select **Remote-SSH: Connect to Host...** from the Command Palette.
- Use USERNAME@nuros.unl.edu
- After the connection is established, use **File** ⇒ **Open...** to navigate to FooLab.


## Configuring, Compiling, Running, and Testing (Linux-Native Code)

### Configuring the Project (Linux-Native Code)

Navigate to the directory that has the *CMakeLists.txt* file and the *CMakePresets.json* file.

VS Code should configure the project for you.
If you're working on your personal computer instead of Nuros, you may be prompted to identify the compiler you'll use.


### Compiling the Project (Linux-Native Code)

There should be a "Build" button.
You can also select one of these commands from the command palette:
```
CMake: Build                                # Builds all targets
CMake: Build Target                         # Build a specific target
```

[//]: # (TODO: be more specific than "there should be...")

### Running the Program (Linux-Native Code)

There should be a "Run" button.
You can also select one of these commands from the command palette:
```
CMake: Run Without Debugging
CMake: Debug
```

[//]: # (TODO: be more specific than "there should be...")

### Testing the Program (Linux-Native Code)

We expect you to test your own code.
Most labs' driver code is designed to facilitate this: provide your inputs, and the driver code will show you the actual output and compare it with the expected output.

We do, however, provide one automated test.
Most labs have particular constraints that require you to write your code in a way that will help you attain the learning objectives.
We provide an automated test that checks for violations of the assignment's constraints.

There should be controls to run the test.
You can also select this command from the command palette:
```
CMake: Run Tests
```

[//]: # (TODO: be more specific than "there should be...")


## Configuring, Compiling, and Uploading (Cow Pi Code)

### Configuring the Project (Cow Pi Code)

Open the project in the *FooLab* directory (the same directory that has platformio.ini).
It should configure the project for you.
If it does not, then launch the PlatformIO plugin, select "Open Project" from the PlatformIO Home, and navigate to the *FooLab* directory.

### Compiling the Project (Cow Pi Code)

Click on the Checkmark icon on the PlatformIO toolbar.
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

[//]: # (TODO: confirm that this can be done from VS Code's file explorer)
