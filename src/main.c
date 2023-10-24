/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:50:48 by josu              #+#    #+#             */
/*   Updated: 2023/10/24 13:09:32 by imontero         ###   ########.fr       */
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
	{
		perror("Quit");
	}
	//	ft_printf("Quit: %i\n", errno);
}

/* 
	comp -lreadline terminal.c libft.a -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include && ./a.out
*/
int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_info	*info;
	
	g_stat = 0;
	if (!check_no_env(env))
		return (printf("Invalid env\n"), -1);
	if (argc != 1)
		return(printf("Invalid arguments\n"), -2);
	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error(MEM, NULL, 2), 2);
	info->envcp = ft_env_cpy(env);
	info->envcp = del_var(info->envcp, "OLDPWD");
	info->homepath = getenv("HOME");
	if (!info->homepath)
		return(printf("Invalid Home\n"), -1);
	terminal(info);
	//printf("status = %i\n", g_stat);
	return (0);
}
