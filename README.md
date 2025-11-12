# simple_shell

A simple UNIX command line interpreter (shell) written in C for educational purposes.

## Description
This project implements a lightweight shell capable of:
- Reading and parsing commands from stdin
- Executing simple binaries using `fork` and `execve`
- Searching `$PATH` for executables
- Handling basic errors and exit statuses

## Files
- `main.c` - shell entrypoint, main loop
- `execute.c` - functions to fork & execve commands
- `parse.c` - command parsing utilities
- `builtin.c` - built-in commands (exit, env, etc.)
- `man_1_simple_shell` - man page for the shell
- `AUTHORS` - contributors list

## Compilation
Compile with:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
