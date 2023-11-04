/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env_pwd_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:50:29 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 11:16:23 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

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

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd:");
		exit(-1);
	}
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

int	ft_is_dir(const char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	if (errno == ENOTDIR)
		return (1);
	return (-1);
}
