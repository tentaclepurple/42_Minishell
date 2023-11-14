/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:50:48 by josu              #+#    #+#             */
/*   Updated: 2023/11/14 18:37:14 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <sys/ioctl.h>

//Function to handle SIGINT signal received
void	ft_handle_client(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_stat = 1;
	}
}

//Function to handle SIGINT signal received
void	ft_2nd_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_printf("Quit: 3\n");
	}
	else if (sig == SIGINT)
	{
		ft_printf("\n");
	}
}

//Function to free all the content in INFO
void	ft_free_info(t_info *info)
{
	if (info->envcp)
		ft_free_split(info->envcp);
	free (info);
}

int	main(int argc, char **argv, char **env)
{
	t_info	*info;

	(void)argv;
	g_stat = 0;
	if (!check_no_env(env))
		return (printf("Invalid env\n"), -1);
	if (argc != 1)
		return (printf("Invalid arguments\n"), -2);
	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error(MEM, NULL, 2), 2);
	info->envcp = ft_env_cpy(env);
	info->envcp = del_var(info->envcp, "_");
	info->envcp = add_var(info->envcp, "_=/usr/bin/env");
	info->envcp = del_var(info->envcp, "OLDPWD");
	info->homepath = getenv("HOME");
	if (!info->homepath)
		return (printf("Invalid Home\n"), -1);
	terminal(info);
	ft_free_info(info);
	return (g_stat);
}
