/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:32:00 by imontero          #+#    #+#             */
/*   Updated: 2023/10/25 20:03:39 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

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

void	ft_cd_home(t_px *px, char ***envcpy)
{
	char	*path;

	if (found_in_env("HOME=", px->info->envcp, &path) == 1)
	{
		*envcpy = ft_cd_update_env(px->info->envcp, path);
		free(path);
	}
	else
		ft_bt_error(HOMSET, "cd:", 1);
}

char	**ft_cd(t_px *px)
{
	char	*path;
	char	**envcpy;

	path = NULL;
	envcpy = NULL;
	if (px->full_cmd[1] == NULL || ft_strcmp(px->full_cmd[1], "--") == 0)
	{
		ft_cd_home(px, &envcpy);
		/*if (found_in_env("HOME=", px->info->envcp, &path) == 1)
		{
			envcpy = ft_cd_update_env(px->info->envcp, path);
			free(path);
		}
		else
			ft_bt_error(HOMSET, "cd:", 1);*/
	}
	else if (ft_strcmp(px->full_cmd[1], "~") == 0)
		envcpy = ft_cd_update_env(px->info->envcp, px->info->homepath);
	else if (ft_strcmp(px->full_cmd[1], "-") == 0)
	{
		if (found_in_env("OLDPWD=", px->info->envcp, &path) == 1)
		{
			envcpy = ft_cd_update_env(px->info->envcp, path);
			ft_pwd();
			free(path);
		}
		else
			ft_bt_error(OPWDSET, "cd:", 1);
	}
	else
	{
		if (access(px->full_cmd[1], F_OK) == 0 && !ft_is_dir(px->full_cmd[1]))
			envcpy = ft_cd_update_env(px->info->envcp, px->full_cmd[1]);
		else if (ft_is_dir(px->full_cmd[1]) == 1)
			ft_error(NOT_DIR, px->full_cmd[1], 1);
		else
			ft_error(NDIR, px->full_cmd[1], 1);
	}
	return (envcpy);
}

char	**ft_cd_update_env(char **env, char *path)
{
	char	*var;
	char	*pwd;
	char	**envcpy;

	pwd = getcwd(NULL, 0);
	envcpy = del_var(env, "OLDPWD");
	var = ft_strjoin("OLDPWD=", pwd);
	envcpy = add_var(envcpy, var);
	free(var);
	free(pwd);
	chdir(path);
	envcpy = del_var(envcpy, "PWD");
	pwd = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", pwd);
	envcpy = add_var(envcpy, var);
	free(var);
	free(pwd);
	return (envcpy);
}
