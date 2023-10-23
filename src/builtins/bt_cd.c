/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:32:00 by imontero          #+#    #+#             */
/*   Updated: 2023/10/23 10:49:14 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_cd(char **env, char **cmdargs)
{
	char	*path;

	if (cmdargs[1] == NULL || ft_strcmp(cmdargs[1], "--") == 0)
	{
		if (found_in_env("HOME=", env, &path) == 1)
		{
			ft_cd_update_env(env, path);
			free(path);
		}
		else
			perror("bash: cd: HOME not set"); //revisar error
	}
	else if (ft_strcmp(cmdargs[1], "~") == 0)
	{
		ft_cd_update_env(env, "/Users/imontero"); // OJO!!!!!!! Este path hay que substituirlo por el home guardado
	}
	else if (ft_strcmp(cmdargs[1], "-") == 0)
	{
		if (found_in_env("OLDPWD=", env, &path) == 1)
		{
			ft_cd_update_env(env, path);
			ft_pwd();
			free(path);
		}
		else
			perror("bash: cd: OLDPWD not set"); //revisar error
	}
	else
	{
		if (access(cmdargs[1], F_OK) == 0)
        	ft_cd_update_env(env, cmdargs[1]);
		else
			ft_error(NDIR, cmdargs[1], 30);
	}
}

char	**ft_cd_update_env(char **env, char *path)
{
	char *var;
	char *pwd;

	pwd = getcwd(NULL, 0);
	env = del_var(env, "OLDPWD");
	var = ft_strjoin("OLDPWD=", pwd);
	env = add_var(env, var);
	free(var);
	free(pwd);
	chdir(path);
	env = del_var(env, "PWD");
	pwd = getcwd(NULL, 0);
	var = ft_strjoin("PWD=", pwd);
	env = add_var(env, var);
	free(var);
	free(pwd);
	/*int i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("*****************************************************************************\n");*/
	return (env);
}

