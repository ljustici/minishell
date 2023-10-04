/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:20:10 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/04 14:50:43 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_path_in_envp(char **envp)
{
    char    *envp_path;
	int		i;

    i = 0;
    while(envp[i])
    {
		envp_path = ft_strnstr(envp[i], ENV_PATH, ft_strlen(envp[i]));
        if (envp_path)
        {
            envp_path = ft_substr(envp[i], ft_strlen(ENV_PATH), ft_strlen(envp[i]));
            break;
        }
        i++;
    }
    return (envp_path);
}

int ft_array_len (char **array)
{
    int i;

    i = 0;
    while(array[i])
        i++;
    return (i);
}

char	**get_all_paths(char *path)
{
    char	**paths;
    char    **result;
    int		i;

    i = 0;
    paths = ft_split(path, ':');
    result = (char **)malloc(sizeof(char*) * (ft_array_len(paths) + 1));
    while(i < ft_array_len(paths))
    {
        result[i] = ft_strjoin(paths[i], "/");
        printf(">>> %zu %s\n", ft_strlen(result[i]), result[i]);
        printf("path: %zu %s\n", ft_strlen(paths[i]), paths[i]);
        if (i > 0)
        {
            printf("path anterior: %zu %s\n", ft_strlen(paths[i - 1]), paths[i-1]);
            printf("anterior: %zu %s\n", ft_strlen(result[i - 1]), result[i - 1]);
        }
        i++;
    }
    return (result);
}

char	*find_correct_path(char **paths, char *cmd)
{
    char	*cmd_path;
    int		i;

    i = 0;
    while(paths[i])
    {
        cmd_path = ft_strjoin(paths[i], cmd);
        if (access(cmd_path, F_OK & X_OK) == 0)
        {
            printf("[%s]\n",cmd_path);
            return (cmd_path);
        }
        printf(">>%s<<\n",cmd_path);
        free(cmd_path);
        i++;
    }
    return (NULL);
}