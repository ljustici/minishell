/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:24:00 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/09 13:18:08 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_command(int i, t_cmd *cmd, char **envp)
{
    int res;
    char **args= malloc(sizeof(char*) * 2);
    args[0] = malloc(sizeof(char) * ft_strlen(cmd->cmd_path[i]));
    args[0] = cmd->cmd_path[i];
    /*args[1] = malloc(sizeof(char) * 4);
    args[1] = ".\0";*/
    
    printf("VALOR DE I: %i\n", i);
    if (i == 0)
    {
        printf("cmd: %s\n", cmd->cmd_path[i]);
        close(cmd->fd[READ_END]);
        // redirect stdout to the write end of pipe1:
        dup2(cmd->fd[1], STDOUT_FILENO);
        close(cmd->fd[1]); //send EOF
    }
    else
    {
        dup2(cmd->fd[0], STDIN_FILENO);
        //dup2(1, cmd->fd[1]);
        //close(cmd->fd[1]);
        close(cmd->fd[0]);
    }
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
            printf("Child exited normally.");
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

void exec_father(pid_t pid, int *ends, int num_pipes)
{
    int status;
    pid_t end_id;
    (void)num_pipes;
    (void)ends;
    int i;
    
    i = 0;
    /*
    while(i <= num_pipes)
    {
        printf("num pipe: %i\n", i);
        close(ends[i]);
        i++;
    }*/
    //close(ends[0]); <-- si se cierra no funciona el pipe
    if (num_pipes == 2)
        close(ends[1]);
    end_id = waitpid(pid, &status, 0);
    handle_end_id(end_id, pid, status);
}

int create_forks(t_cmd *cmd, char **envp)
{
    pid_t pid;
    int i;

    i = 0;
    while(i < cmd->n_cmd)
    {
        if (cmd->cmd_path[i])
        {
            if (i == 0 || pid > 0)
            {
                printf("Está creando fork el pid %d\n", pid);
                pid = fork();
            }
            //printf("pid: %i\n", pid);
            if (pid == -1)
            {
                printf("pid: -1\n");
                return(-1);
            }
            else if (pid == 0)
            {
                printf("pid: %i   i: %i \n", pid, i);
                exec_command(i, cmd, envp);
            }
            else if (pid > 0)
            {
                exec_father(pid, cmd->fd, cmd->n_cmd);
            }
        }
        i++;
    }
    return(0);
}

/*pipes[0] 0 * 2 = 0
pipes[1]

pipes[2] 1 * 2 = 2
pipes[3]

pipes[4] 2 * 2 = 4
pipes[5]

pipes[6] 3 * 2 = 6
pipes[7]*/

int init_pipes(t_cmd *cmd)
{
    int i;

    i = 0;
    while(i < cmd->n_cmd)
    {
        if (pipe(&cmd->fd[i * 2]) == -1)
            return (-1);
        i++;
    }
    return (0);
}

t_cmd *init_cmd(int argc, char **argv, char **envp)
{
    t_cmd *cmd;
    char *text;
    char **all_paths;
    int i;
    int j;

    cmd = (t_cmd*)malloc(sizeof(t_cmd));
    cmd->cmd_path = (char**)malloc(sizeof(char) * (argc - 1));
    i = 0;
    cmd->n_cmd = 0;
    text = find_path_in_envp(envp);
    all_paths = get_all_paths(text);
    while(i < ft_array_len(all_paths))
        i++;
    i = 1;
    j = 0;
    printf("ARGC %i\n", argc);
    while(i < argc)
    {
        cmd->cmd_path[j] = find_correct_path(all_paths, argv[i]);
        printf("correct path: %s j: %i\n", cmd->cmd_path[j], j);
        if (cmd->cmd_path[j])
        {
            cmd->n_cmd++;
            j++;
        }
        i++;
    }
    return(cmd);
}

//ft_pipex
int main(int argc, char **argv, char **envp)
{
    (void)argc;
    t_cmd *cmd;
    
    cmd = init_cmd(argc, argv, envp);
    if (cmd->cmd_path)
    {
        cmd->fd = malloc(sizeof(int) * (cmd->n_cmd - 1));
        if (init_pipes(cmd) == -1)
            return(-1);
        else
            create_forks(cmd, envp);
    }
}
