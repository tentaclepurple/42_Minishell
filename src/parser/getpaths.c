/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpaths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:47:42 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 11:16:41 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

int	check_slash(char *str)
{
	int	i;
	int	slash;

	slash = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			slash++;
		i++;
	}
	return (slash);
}

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

/* 
	Checks if cmd or /path/cmd exists.
	Returns (/path/cmd) allocated if so
	Returns (NULL) otherwise
*/
char	*get_cmd_or_cmdpath(char **env, char *str)
{
	int		i;
	char	**env_path;
	char	*aux;
	char	*path_and_cmd;

	env_path = NULL;
	if (check_slash(str) > 0 && !access(str, F_OK))
		return (ft_strdup(str));
	else if (check_slash(str) == 0)
	{
		env_path = get_path(env);
		i = 0;
		while (env_path && env_path[i])
		{
			aux = ft_strjoin(env_path[i++], "/");
			path_and_cmd = ft_strjoin(aux, str);
			free(aux);
			if (access(path_and_cmd, F_OK) == 0)
				return (ft_free_split(env_path), path_and_cmd);
			free(path_and_cmd);
		}
		if (env_path)
			ft_free_split(env_path);
	}
	return (NULL);
}

void	ft_fd_close(t_px *px, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		close(px->info->fd[i][0]);
		close(px->info->fd[i][1]);
		i++;
	}
}

void	ft_alloc_fd(t_px *px)
{
	int	i;

	i = 0;
	px->info->fd = malloc(sizeof(int *) * (px->info->cmd_amount - 1));
	if (!px->info->fd)
		return ;
	while (i < px->info->cmd_amount - 1)
	{
		px->info->fd[i] = malloc(sizeof(int) * 2);
		pipe(px->info->fd[i]);
		i++;
	}
}
