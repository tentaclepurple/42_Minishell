/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:32:00 by imontero          #+#    #+#             */
/*   Updated: 2023/10/24 12:20:35 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//char	**ft_cd(char **env, char **cmdargs)
char	**ft_cd(t_px *px)
{
	char	*path;
	char	**envcpy;

	//printf("%s\n", px->info->homepath);
	envcpy = NULL;
	if (px->full_cmd[1] == NULL || ft_strcmp(px->full_cmd[1], "--") == 0)
	{
		if (found_in_env("HOME=", px->info->envcp, &path) == 1)
		{
			envcpy = ft_cd_update_env(px->info->envcp, path);
			free(path);
		}
		else
			perror("bash: cd: HOME not set"); //revisar error
	}
	else if (ft_strcmp(px->full_cmd[1], "~") == 0)
		envcpy = ft_cd_update_env(px->info->envcp, px->info->homepath); // OJO!!!!!!! Este path hay que substituirlo por el home guardado
	else if (ft_strcmp(px->full_cmd[1], "-") == 0)
	{
		if (found_in_env("OLDPWD=", px->info->envcp, &path) == 1)
		{
			envcpy = ft_cd_update_env(px->info->envcp, path);
			ft_pwd();
			free(path);
		}
		else
			perror("bash: cd: OLDPWD not set"); //revisar error
	}
	else
	{
		if (access(px->full_cmd[1], F_OK) == 0)
        	envcpy = ft_cd_update_env(px->info->envcp, px->full_cmd[1]);
		else
			ft_error(NDIR, px->full_cmd[1], 30);
	}
	return (envcpy);
}

char	**ft_cd_update_env(char **env, char *path)
{
	char	 *var;
	char	 *pwd;
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

