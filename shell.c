cmd_path = find_command_path(line);
if (cmd_path)
{
    if (fork() == 0)
    {
        execve(cmd_path, args, environ);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        free(cmd_path);
    }
}
else
{
    write(STDOUT_FILENO, "Command not found: No such file or directory\n", 46);
}
