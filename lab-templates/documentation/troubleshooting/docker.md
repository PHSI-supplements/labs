# When Docker Does Daffy Deeds

This document is organized around what you were attempting to accomplish when you encountered a problem.

- [`docker compose build`](#docker-daffiness-docker-compose-build)
- [`docker compose run --rm csce231`](#docker-daffiness-docker-compose-run---rm-csce231)
- [`docker compose up docs`](#docker-daffiness-docker-compose-up-docs)


## Docker Daffiness: `docker compose build`

You tried to build the course container:
```bash
docker compose build
```

But something went wrong.
- If the build failed while trying to `load metadata for docker.io/library/ubuntu:26.04`, and the error mentions a timeout, DNS/hostname lookup, or inability to connect,
  then this is probably a network issue.
  Check your internet connection and try again.
- If you saw *unable to get image 'csce231-1268': failed to connect to the docker API at ...; check if the path is correct and if the daemon is running: ... no such file or directory*<br>
  The most likely problem is that Docker isn't running.
  - On Windows, macOS, and Linux with Docker Desktop, try restarting Docker Desktop.
  - On Linux with Docker Engine, ensure that the Docker Service is running.
- If you're running Linux with Docker Engine and you saw a permission error such as: *permission denied while trying to connect to the Docker daemon socket*<br>
  then visit [Docker's daemon troublshooting page](https://docs.docker.com/engine/daemon/troubleshoot/).
- If you saw an error indicating that the configuration file could not be found, such as: *no configuration file provided: not found*<br>
  then use the `cd` command to go to the repository directory containing `compose.yaml` and try again.

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.


## Docker Daffiness: `docker compose run --rm csce231`

You tried to launch the course container:
```bash
docker compose run --rm csce231
```

You expected to see a command prompt from inside the container.
But you saw something different.
- If you saw *unable to get image 'csce231-1268': failed to connect to the docker API at ...; check if the path is correct and if the daemon is running: ... no such file or directory*<br>
  The most likely problem is that Docker isn't running.
    - On Windows, macOS, and Linux with Docker Desktop, try restarting Docker Desktop.
    - On Linux with Docker Engine, ensure that the Docker Service is running.
- If you're running Linux with Docker Engine and you saw a permission error such as: *permission denied while trying to connect to the Docker daemon socket*<br>
  then visit [Docker's daemon troublshooting page](https://docs.docker.com/engine/daemon/troubleshoot/).
- If you saw an error indicating that the configuration file could not be found, such as: *no configuration file provided: not found*<br>
  then use the `cd` command to go to the repository directory containing `compose.yaml` and try again.
- TODO: The Docker image hasn't been built (*i.e.*, you skipped `docker compose build`)
- If you saw a message about `SSH_AUTH_SOCK` not being set, such as:<br>
  *WARN[0000] The "SSH_AUTH_SOCK" variable is not set. Defaulting to a blank string.*<br>
  *invalid spec: :/ssh-agent: empty section between colons*<br>
  then your SSH agent is not running, or your shell does not know where its socket is.
  See the [SSH troubleshooting page](ssh.md#ssh-silliness-ssh_auth_sock-variable-is-not-set-or-ssh-agent-is-not-running).


If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.


## Docker Daffiness: `docker compose up docs`

You tried to launch a container instance that will present the assignment write-up as a website:
```bash
docker compose up docs
```

You expected to see a simple note
```text
Attaching to docs
```
and then be able to connect a web browser to `localhost:8000`.
But you saw something different.
- If you saw *unable to get image 'csce231-1268': failed to connect to the docker API at ...; check if the path is correct and if the daemon is running: ... no such file or directory*<br>
  The most likely problem is that Docker isn't running.
  - On Windows, macOS, and Linux with Docker Desktop, try restarting Docker Desktop.
  - On Linux with Docker Engine, ensure that the Docker Service is running.
- If you're running Linux with Docker Engine and you saw a permission error such as: *permission denied while trying to connect to the Docker daemon socket*<br>
  then visit [Docker's daemon troublshooting page](https://docs.docker.com/engine/daemon/troubleshoot/).
- If you saw an error indicating that the configuration file could not be found, such as: *no configuration file provided: not found*<br>
  then use the `cd` command to go to the repository directory containing `compose.yaml` and try again.
- You saw a message such as<br>
  *Bind for 127.0.0.1:8000 failed: port is already allocated*<br>
  or<br>
  *listen tcp 127.0.0.1:8000: bind: address is already in use*<br>
  then the most likely problem is that you already have the `docs` server running in another terminal.
  Try connecting your web browser to `localhost:8000`.
- TODO: The Docker image hasn't been built (*i.e.*, skipped `docker compose build`)
- If you saw Docker attempt to pull the csce231-1268 image, even though you *did* build the Docker image, followed by:<br>
  *✘ Image csce231-1268 Error pull access denied for csce231-1268, reposit... 3.7s*<br>
  *Error response from daemon: pull access denied for csce231-1268, repository does not exist or may require 'docker login'*<br>
  The simplest explanation is that Docker temporarily forgot that the image exists.
  I don't know why Docker sometimes does this.
  The "fix" is simple: re-run
  ```bash
  docker compose up docs
  ```

If you cannot resolve the problem(s) yourself, then talk with a TA or the instructor.
