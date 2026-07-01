# Build the Course Container

The development environment used in this course is packaged in a Docker image.

A file named `Dockerfile` is located at the top level of your repository.
This file contains the instructions Docker uses to create the course development environment.


## Navigate to Your Repository

- [ ] Open a terminal window and use `cd` to navigate to the top level of your repository.
  The exact path will depend on where you cloned your repository.
- [ ] Verify that you are in the correct directory:
  ```bash
  ls
  ```
  You should see files and directories including:
  ```text
  compose.yaml
  Dockerfile
  documentation
  README.md
  ```
[//]: # (  along with any lab directories that have been released.)


## Build the Docker Image

- [ ] Run the command
  ```bash
  docker compose build
  ```

  This command tells Docker to:
  - Read the instructions in `compose.yaml`.
  - Use those instructions to build a Docker image from `Dockerfile`.

The first build may take several minutes because Docker must download an Ubuntu image and install the required software.


## Verify That the Image Was Created

- [ ] Run the command
  ```bash
  docker images
  ```
  You should see an entry similar to:
  ```text
  REPOSITORY   TAG       IMAGE ID       CREATED        SIZE
  csce231-dev  latest    abcdef123456   1 minute ago   ...
  ```

<!--

## Rebuilding the Image 

We expect that you will only need to build the image once.

However, if we need to update the `Dockerfile`, you will need to rebuild the image:

```bash
docker compose build
```

Docker will reuse any previously-built layers that have not changed, so rebuilding is generally faster than the initial build.

-->
