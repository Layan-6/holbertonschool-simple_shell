# Simple Shell

A simple UNIX command line interpreter written in C.

## Description
This project implements a basic UNIX shell that can read commands, execute programs, and handle basic shell operations.

## Features
- Execute commands with arguments
- Support for PATH environment variable
- Built-in commands: `exit` and `env`
- Interactive and non-interactive modes
- Error handling similar to `/bin/sh`

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
