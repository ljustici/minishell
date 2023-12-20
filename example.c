/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:35:14 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/03 17:47:38 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int create_fork(int *ends)
{
    pid_t pid;
    int status;
    pid_t end_id;

    pid = fork();
    if (pid == -1)
        return(-1);
    else if (pid == 0)
    {
        //execute child
    }
    else if (pid > 0)
    {
        end_id = waitpid(pid, &status, WNOHANG|WUNTRACED);
        //error occurred
        
    }
    return(0);
}