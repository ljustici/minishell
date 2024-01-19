/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/19 11:56:07 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   **  ONLY CHECKS CTRL+C, NOT CTRL+\ (TO IGNORE) **
 *  Cuando nuestro shell recibe una señal SIGINT, el comportamiento por defecto
 * es terminar el proceso. Para cambiar este comportamiento, podemos establecer
 * un manejador de señales para SIGINT. Un manejador de señales es una función
 * que se ejecuta cuando se recibe una señal. Para establecer un manejador de
 * señales, usamos la función sigaction. Lo que pretendemos con esta función es
 * que nuestro shell ignore la señal SIGINT, para que no termine la ejecución
 * del programa sino que, simplemente, se quede esperando una nueva entrada del
 * usuario.
 * 
 *  La función isatty se usa para saber si la entrada estándar es un terminal.
 * La función isatty devuelve 1 si el descriptor de fichero que le pasamos
 * corresponde a un terminal, y 0 si no. Si el descriptor de fichero es 0, se
 * refiere a la entrada estándar (stdin). Por lo tanto, si el resultado de
 * isatty es 1, significa que la entrada estándar es un terminal, y si es 0,
 * significa que la entrada estándar no es un terminal, es decir, que la
 * entrada estándar está redirigida desde un fichero o desde la salida de otro
 * programa.
 * 
 *  La función ioctl se usa para controlar dispositivos. En este caso, la
 * función ioctl se usa para controlar la entrada estándar.
 * 	La función ioctl recibe tres argumentos: 
 * - el descriptor de fichero,
 * - el comando que queremos ejecutar 
 * - y un puntero a una estructura de datos (por ejemplo, un puntero a un
 *  carácter, un puntero a un entero, etc.).
 * En este caso, el comando que queremos ejecutar es TIOCSTI, que significa
 * "Terminal Input Output Control STdIn".
 * Este comando se usa para insertar un carácter en la entrada estándar. El
 * puntero a la estructura es un puntero a un carácter, que es el carácter que
 * queremos insertar en la entrada estándar. En este caso, el carácter que
 * queremos insertar es un salto de línea, que es el carácter '\n'.
 * 
 *  AMBOS PROCESOS RECIBEN EL CTRL+C Y RESPONDEN A ÉL:
 *  - elimina del hijo el comportamiento sobrante
 * 
 * @param sig      The signal (SIGINT, in this case)
 * @param info 
 * @param context 
 */
void	ft_handler(int sig, siginfo_t *info, void *context)

{
	(void)info;
	(void)context;
	if (SIGINT == sig) // user press CTRL+C
	{
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
	//	rl_replace_line("   ", 0);
		ft_putstr_fd("   ", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	//	rl_redisplay();
	}
}

/**
 * @brief    **  IT'S NOT A SIGNAL, ONLY A SPECIAL CHARACTER **
 * 	-	rl_on_new_line(); // parece que limpia el búffer
 *	-	rl_redisplay();	// y parece que se pone al inicio de la misma línea
 * 
 * @param data 
 */
void	ft_ctrl_d(t_msh *data)
{
	if (!data->pipeline)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS); // te saca de minishell
	}
}
