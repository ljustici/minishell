/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:24:00 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/04 19:25:12 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_command(int fd_in, int fd_out, char *cmd_path, const char **cmd_args, char **envp)
{
    int res;
    char **args= malloc(sizeof(char*) * 2);
    args[0] = malloc(sizeof(char) * ft_strlen(cmd_path));
    args[0] = cmd_path;
    args[1] = malloc(sizeof(char) * 4);
    args[1] = "-la\0";
    (void)cmd_args;
    
    write(1,"aaa\n",4);
    dup2(fd_in, STDIN_FILENO);
    dup2(1, STDOUT_FILENO); //arreglar fds
    close(fd_in);
    close(fd_out);
    res = execve(args[0], args, envp);
    printf("res: %i\n", res);
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
        {
            printf("Child ended because of an uncaught signal.\n");
            printf("killed by signal=%d\n", WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
            printf("Child process has stopped.\n");
        return(0);
        //exit(EXIT_SUCCESS);
    }
    return(0);
    //exit(EXIT_FAILURE);
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
        printf("num pipe: %i\n", i);
        close(ends[i]);
        i++;
    }
    end_id = waitpid(pid, &status, 0);
    handle_end_id(end_id, pid, status);
}

int create_forks(t_cmd *cmd, char **envp)
{
    pid_t pid;
    int i;

    i = 0;
    printf("cmd path: %i\n",ft_array_len(cmd->cmd_path));
    while(i < ft_array_len(cmd->cmd_path))
    {
        if (cmd->cmd_path[i])
        {
            pid = fork();
            //printf("pid: %i\n", pid);
            if (pid == -1)
                return(-1);
            else if (pid == 0)
            {
                printf("pid: %i   i: %i \n", pid, i);
                
                exec_command(cmd->fd[0], cmd->fd[1], cmd->cmd_path[i], NULL, envp);
                /*if (i == 0)
                    exec_command(STDIN_FILENO, cmd->fd[2 * i + 1], cmd->cmd_path[i], cmd->cmd_args[i], cmd->env_path);
                else if (!cmd->cmd_path[i + 1])
                    exec_command(cmd->fd[2 * i -2], STDOUT_FILENO, cmd->cmd_path[i], cmd->cmd_args[i], cmd->env_path);
                else
                    exec_command(cmd->fd[2 * i -2], cmd->fd[2 * i + 1], cmd->cmd_path[i], cmd->cmd_args[i], cmd->env_path);*/
            }
            else if (pid > 0)
            {
                printf("pid child: %i\n", pid);
                exec_father(pid, cmd->fd);
            }
        }
        i++;
    }
    return(0);
}

t_cmd *init_cmd(char **argv, char **envp)
{
    t_cmd *cmd;
    char *text;
    char **all_paths;
    int i;
    int j;

    cmd = (t_cmd*)malloc(sizeof(t_cmd));
    cmd->cmd_path = (char**)malloc(sizeof(char) * sizeof(ft_array_len(argv)));
    i = 0;
    text = find_path_in_envp(envp);
    all_paths = get_all_paths(text);
    while(i < ft_array_len(all_paths))
    {
        printf("PATH = %s\n", all_paths[i]);
        i++;
    }
    i = 1;
    j = 0;
    while(i < ft_array_len(argv))
    {
        printf("argv array len: %i\n", ft_array_len(argv));
        cmd->cmd_path[j] = find_correct_path(all_paths, argv[i]);
        if (!cmd->cmd_path[j])
            j++;
        printf("--%i %s\n", i,cmd->cmd_path[i]);
        i++;
    }
    return(cmd);
}


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    t_cmd *cmd;
    int i;
    
    cmd = init_cmd(argv, envp);
    if (cmd->cmd_path)
    {
        //initialize all needed pipes
        cmd->fd = malloc(sizeof(int) * ft_array_len(cmd->cmd_path) + 1);
        i = 0;
        while(i < ft_array_len(cmd->cmd_path))
        {
            if (pipe(cmd->fd) == -1)
                return(-1);
            else
            {
                printf("cmd path en main: %s\n", cmd->cmd_path[0]);
                create_forks(cmd, envp);
            }
            i++;
        }
    }
}