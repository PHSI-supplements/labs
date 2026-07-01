# Start the Course Container

The previous step created a Docker image named `csce231-dev` that is a blueprint this course's development environment.
To use that environment, you must create and start a container from the image.


## Navigate to Your Repository

- [ ] Open a terminal window and use `cd` to navigate to the top level of your repository.
  The exact path will depend on where you cloned your repository.


## Start the Container

- [ ] Run the command
  ```bash
  docker compose run --rm csce231
  ```

  This command:
  - Creates a container from the image.
  - Follows the instructions in `compose.yaml` to:
    - Open an interactive terminal inside the container.
    - Make your repository available inside the container at `/csce231`.
  - Automatically removes the container when you exit.

After a moment, you should see a command prompt from inside the container.
The command prompt will look something like this:
```text
root@a9b8c7d6e5f4:/csce231#
```

### Future Troubleshooting

After you reboot your computer, Docker Desktop may not restart automatically.

In the future, if you run a `docker` command and get an error indicating that Docker cannot connect to the Docker daemon or Docker API, the first thing to check is whether Docker is running.
- On Windows, macOS, and Linux with Docker Desktop, try restarting Docker Desktop.
- On Linux with Docker Engine, ensure that the Docker Service is running (see XYZ for details).

[//]: # (TODO: link to Docker Engine troubleshooting after we create that page.)


## Verify That You Are Inside the Container

- [ ] Run the command
  ```bash
  pwd
  ```
  You should see:
  ```text
  /csce231
  ```

- [ ] Verify that you can see the files in your repository:
  ```bash
  ls
  ```
  You should see files and directories from your repository, including:
  ```text
  compose.yaml
  documentation
  Dockerfile
  README.md
  ```

- Verify that the development tools are available:
  - [ ] GCC
    ```bash
    gcc --version
    ```
  - [ ] CMake
    ```bash
    cmake --version
    ```
  - [ ] Git
    ```bash
    git --version
    ```
  Each command should display version information.


- [ ] Show a TA that you have successfully launched the container.


## Exit the Container

- [ ] When you are finished working inside the container, run:
  ```bash
  exit
  ```
  or press:
  ```text
  Ctrl+D
  ```
  Because the container was started with the `--rm` option, Docker will automatically remove it after you exit.

  Your files will remain in your repository on your computer.


## Starting the Container Again Later

Whenever you want to work from a terminal, navigate to the top level of your repository and run:

```bash
docker compose run --rm csce231
```

This creates a fresh container that uses the same repository files.
