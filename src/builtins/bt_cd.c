/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:32:00 by imontero          #+#    #+#             */
/*   Updated: 2023/11/14 15:43:12 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

void	ft_cd_home(t_px *px, char ***envcpy)
{
	char	*path;
	int		found;

	found = found_in_env("HOME=", px->info->envcp, &path);
	if (found && ft_is_dir(path) == -1)
		ft_error(NDIR, path, 1);
	else if (found)
		*envcpy = ft_cd_update_env(px->info->envcp, path);
	else
		ft_bt_error(HOMSET, "cd:", 1);
	if (found)
		free(path);
}

void	ft_cd_oldpwd(t_px *px, char ***envcpy)
{
	char	*path;

	if (found_in_env("OLDPWD=", px->info->envcp, &path) == 1)
	{
		*envcpy = ft_cd_update_env(px->info->envcp, path);
		ft_pwd();
		free(path);
	}
	else
		ft_bt_error(OPWDSET, "cd:", 1);
}

void	ft_cd_tilde(t_px *px, char ***envcpy)
{
	int		found;
	char	*path;

	found = found_in_env("HOME=", px->info->envcp, &path);
	if (found && !ft_is_dir(path))
		*envcpy = ft_cd_update_env(px->info->envcp, path);
	else if (found && ft_is_dir(path) == -1)
		ft_error(NDIR, path, 1);
	else
		*envcpy = ft_cd_update_env(px->info->envcp, px->info->homepath);
	if (found)
		free(path);
}

char	**ft_cd(t_px *px)
{
	char	**envcpy;

	envcpy = px->info->envcp;
	if (px->full_cmd[1] == NULL || ft_strcmp(px->full_cmd[1], "--") == 0)
		ft_cd_home(px, &envcpy);
	else if (ft_strcmp(px->full_cmd[1], "~") == 0)
		ft_cd_tilde(px, &envcpy);
	else if (ft_strcmp(px->full_cmd[1], "-") == 0)
		ft_cd_oldpwd(px, &envcpy);
	else
	{
		if (access(px->full_cmd[1], F_OK) == 0 && !ft_is_dir(px->full_cmd[1]))
			envcpy = ft_cd_update_env(px->info->envcp, px->full_cmd[1]);
		else if (ft_is_dir(px->full_cmd[1]) == 1)
			ft_error(NOT_DIR, px->full_cmd[1], 1);
		else
			ft_error(NDIR, px->full_cmd[1], 1);
	}
	g_stat = 0;
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
