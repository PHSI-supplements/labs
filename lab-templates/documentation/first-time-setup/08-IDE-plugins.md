# Install IDE Plugins

Most students will need to install a plugin to their IDE that will allow it to process the settings files that instruct the IDE to 
launch the course container, connect to the course container, and make use of additional plugins within the container.


## Using the Terminal

If you prefer to work from the command line and use TUI editors and debuggers, there is no further configuration needed.
The course's Docker container has Vim and GDB installed, along with all of the command-line tools needed for this course.
If you prefer a different editor or debugger, talk with Dr. Bohn before modifying the Dockerfile.


## CLion

[//]: # (There is one necessary CLion plugin, and one recommended plugin.)

- [ ] Install CLion's [Dev Containers plugin](https://plugins.jetbrains.com/plugin/21962-dev-containers).

[//]: # (- [ ] Optionally install CLion's [Mermaid plugin]&#40;https://plugins.jetbrains.com/plugin/20146-mermaid&#41; to view diagrams in some of the assignments' instructions.)

[//]: # (The components needed for this course are already bundled into CLion.)


## VS Code

[//]: # (You only need to manually install one VS Code extension.)

- [ ] Install VS Code's [Remote Development extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack).

[//]: # (The remaining extensions for this course will be automatically installed inside the container.)
