# Parent-Child Process Management

## Description
This project consists of two programs: `parent` and `child`. The `parent` process manages the environment and spawns `child` processes using `fork()` and `execve()`. The `child` processes retrieve and display environment variables based on the mode of execution.

## Features
- The `parent` process reads environment variables from a file (`env`).
- It can spawn multiple `child` processes (`child_XX`, where `XX` is a sequential number from 00 to 99).
- Two modes of execution for `child` processes:
  - `+` mode: Reads environment variables from the `env` file.
  - `*` mode: Receives the environment directly from the `parent` process.
- The `parent` process listens for user input:
  - `+`: Spawns a new `child_XX` process using the `env` file.
  - `*`: Spawns a new `child_XX` process with the inherited environment.
  - `q`: Terminates the `parent` process after all `child` processes finish.

## Files
- `parent.c`: Implements the `parent` process.
- `child.c`: Implements the `child` process.
- `env`: A text file listing environment variables to be used.

## Installation & Compilation
```sh
gcc -o parent parent.c
gcc -o child child.c
export CHILD_PATH=$(pwd)
```

## Installation & Compilation with script
```sh
./run.sh
```

## Running the Program
```sh
./parent
```

### User Commands
- Press `+` to spawn a `child_XX` using the `env` file.
- Press `*` to spawn a `child_XX` with inherited environment variables.
- Press `q` to quit the `parent` process after all child processes exit.

## Example `env` File
```sh
SHELL
HOME
HOSTNAME
LOGNAME
LANG
TERM
USER
LC_COLLATE
PATH
```

## Expected Output
When a `child` process starts, it prints:
```
Child process: child_00 (PID: 12345, PPID: 6789)
SHELL=/bin/bash
HOME=/home/user
...
```


