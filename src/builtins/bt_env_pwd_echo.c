/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env_pwd_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:50:29 by imontero          #+#    #+#             */
/*   Updated: 2023/10/23 11:04:02 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	ft_pwd()
{
 	char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("PWD ERROR"); //error PWD
	ft_putendl_fd(cwd, 1);
	free(cwd);
}

void	ft_echo(t_px *px)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (px->full_cmd[1] != NULL && !ft_strcmp(px->full_cmd[1], "-n"))
	{
		px->full_cmd++;
		flag++;
	}
	while (px->full_cmd[i])
	{
		if (i > 1)
			write(1, " ", 1);
		ft_putstr_fd(px->full_cmd[i], 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}
