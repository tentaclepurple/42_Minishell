/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:50:48 by josu              #+#    #+#             */
/*   Updated: 2023/10/23 09:05:52 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"
#include<libc.h>

//Function to handle SIGINT signal received
void	ft_handle_client(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

//Function to handle SIGINT signal received
void	ft_2nd_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
	}
	else if (sig == SIGQUIT)
		ft_printf("Quit: %i\n", errno);
}

/* 
	comp -lreadline terminal.c libft.a -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include && ./a.out
*/
int	main(int argc, char **argv, char **env)
{
	(void)argv;
	
	g_stat = 0;
	if (!check_no_env(env))
		return (printf("Invalid env\n"), -1);
	if (argc != 1)
		return(printf("Invalid arguments\n"), -2);
	terminal(env);
	//printf("status = %i\n", g_stat);
	return (0);
}
