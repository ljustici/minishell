/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:24:00 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/03 19:38:11 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_command(int fd_in, int fd_out, char *cmd_path, char *cmd_args, char *envp)
{
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    close(fd_in);
    close(fd_out);
    execve(cmd_path, cmd_args, &envp);
    //liberar cmd_path
    //liberar cmd_args
}

int handle_end_id(pid_t end_id, pid_t child_id, int status)
{
    if (end_id == -1)
    {            
        perror("waitpid error");
        exit(EXIT_FAILURE);
    }
    //if it's end_if == 0 the child is still running
    //child ended
    else if (end_id == child_id)
    {
        if (WIFEXITED(status))
            printf("Child ended normally.\n");
        else if (WIFSIGNALED(status))
            printf("Child ended because of an uncaught signal.\n");
        else if (WIFSTOPPED(status))
            printf("Child process has stopped.\n");
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

void exec_father(pid_t pid, int *ends)
{
    int status;
    pid_t end_id;
    int i;
    
    i = 0;
    //cerrar todas las pipes
    while(ends[i])
    {
        close(ends[i]);
        i++;
    }
    end_id = waitpid(pid, &status, WNOHANG|WUNTRACED);
    handle_end_id(end_id, pid, status);
}

int create_forks(t_cmd cmd)
{
    pid_t pid;
    int i;

    i = 0;
    while(cmd.cmd_path[i])
    {
        pid = fork();
        if (pid == -1)
            return(-1);
        else if (pid == 0)
        {
            if (i == 0)
                exec_command(STDIN_FILENO, cmd.fd[2 * i + 1], cmd.cmd_path[i], cmd.cmd_args[i], cmd.env_path);
            else if (!cmd.cmd_path[i + 1])
                exec_command(cmd.fd[2 * i -2], STDOUT_FILENO, cmd.cmd_path[i], cmd.cmd_args[i], cmd.env_path);
            else
                exec_command(cmd.fd[2 * i -2], cmd.fd[2 * i + 1], cmd.cmd_path[i], cmd.cmd_args[i], cmd.env_path);
        }
        else if (pid > 0)
            exec_father(pid, cmd.fd);
        i++;
    }
    return(0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    char *text;
    char **all_paths;
    int i;
    char *path;
    int *ends;
    
    i = 0;
    text = find_path_in_envp(envp);
    all_paths = get_all_paths(text);
    while(i < ft_array_len(all_paths))
    {
        printf("PATH = %s\n", all_paths[i]);
        i++;
    }
    path = find_correct_path(all_paths, argv[1]);
    printf("The correct path is %s\n", path);
    if (path)
    {
        //initialize all needed pipes
        ends = malloc(sizeof(int) * ft_array_len(&path));
        if (pipe(ends) == -1)
            return(-1);
        else
            create_forks(ends);
    }
}