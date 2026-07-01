# Accessing the Development Container using the Terminal

- [ ] Open a terminal window and use `cd` to navigate to the top level of your repository.
- [ ] Start the development container:
  ```bash
  docker compose run --rm csce231
  ```

After a moment, you should see a command prompt from inside the container.
The command prompt will look something like this:
```text
root@a9b8c7d6e5f4:/csce231#
```

[//]: # (TODO: link to Docker Engine troubleshooting after we create that page.)

> ⓘ **Note**
> 
> Using multiple terminal windows, you can have multiple instances of the Docker container running.
> Because your repository is shared between all instances of the development container.
> Changes made in one container instance will be immediately visible in the other container instance(s).
> 
> An example use of this feature would be to run Vim in one terminal window,
> while compiling, running, or debugging it in another terminal window.


## How to verify that you're in the container

You can confirm that you're in the container by looking at the command line prompt.
If your prompt shows `root@...:/csce231#` then you're working in the container.
(This assumes that you don't normally use the `root` account on your host computer.)


## How to exit the container

- [ ] When you are finished working inside the container, run:
  ```bash
  exit
  ```
  or press:
  ```text
  Ctrl+D
  ```
  This returns you to the terminal on your computer.
