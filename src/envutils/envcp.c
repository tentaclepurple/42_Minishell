/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/20 17:45:07 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	**ft_env_cpy(char **env)
{
	int		i;
	char	**envcp;

	i = 0;
	while (env[i])
		i++;
	envcp = malloc(sizeof(char *) * (i + 1));
	envcp[i] = NULL;
	i = 0;
	while (env[i])
	{
		envcp[i] = ft_strdup(env[i]);
		i++;
	}
	return (envcp);
}

char	**add_var(char **env, char *var)
{
	int		len;
	int		i;
	char	**envcp;

	len = 0;
	while (env[len])
		len++;
	envcp = malloc(sizeof(char *) * (len + 2));
	envcp[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		envcp[i] = env[i];
		i++;
	}
	envcp[i] = ft_strdup(var);
	free (env);
	return (envcp);
}

char	**del_var_aux(int found, char **env, char **envcpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != found)
		{
			envcpy[j] = ft_strdup(env[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	//ft_free_split(env);
	return (envcpy);
}
/* 	deletes the var and returns a copy of env
	if not found, returns env */
char	**del_var(char **env, char *var)
{
	int		found;
	int		len;
	char	**envcpy;
	char	*varok;

	found = 0;
	varok = ft_strjoin(var, "=");
	while (env[found])
	{
		if (ft_strncmp(varok, env[found], ft_strlen(varok)) == 0)
			break ;
		found++;
	}
	if (env[found] == NULL)
		return (free(varok), env);
	free(varok);
	len = 0;
	while (env[len])
		len++;
	envcpy = malloc(sizeof(char *) * (len));
	envcpy[len - 1] = NULL;
	del_var_aux(found, env, envcpy);
	return (envcpy);
}


//-----------------------UNSET-----------------------------
/* 	Iterates throug the cmd args and deletes the vars if founded. 
	Returns a copy of env with vars deleted
*/
char	**ft_unset(char **env, char **cmdargs)
{
	int	i;
	char	**envcopy;

	envcopy = env;
	i = 1;
	while (cmdargs[i])
	{
		envcopy = del_var(envcopy, cmdargs[i]);
		i++;
	}
	return (envcopy);
}
//----------------------------------------------------------




//-----------------------EXPORT----------------------------

int	find_equal(char *var, int *found)
{
	int	i;

	i = 0;
	*found = 0;
	while (var[i])
	{
		if (var[i] == '=')
			*found = i;
		i++;		
	}
	return (*found);
}

void	export_declare(char **env)
{
	int	i;
	int	j;
	int	first_eq;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
			i++;
		else
		{
			j = 0;
			ft_putstr_fd("declare -x ", 1);
			while (env[i][j])
			{
				write(1, &env[i][j], 1);
				if (j == find_equal(env[i], &first_eq))
					write(1, "\"", 1);
				j++;
			}
			ft_putendl_fd("\"", 1);
			i++;
		}
	}
}
char	**ft_export_aux_del(char **env, char **cmdargs, int i, int found)
{
	char	*var_only;

	var_only = ft_substr(cmdargs[i], 0, found);
	env = del_var(env, var_only);
	free(var_only);
	return (env);
}


char	**ft_export_aux(char **env, char **cmdargs)
{
	int		i;
	int		j;
	int		found;
	//char	*var_only;

	i = 0;
	found = 0;
	while (cmdargs[++i])
	{
		if (find_equal(cmdargs[i], &found) == 0)
		{
			i++;
			continue ;
		}
		j = 0;
		while (env[++j])
		{
			if (ft_strncmp(cmdargs[i], env[j], found + 1) == 0)
			{
				env = ft_export_aux_del(env, cmdargs, i, found);
				/*var_only = ft_substr(cmdargs[i], 0, found);
				env = del_var(env, var_only);
				free(var_only);*/
				j--;
			}
		}
	}
	return (env);
}

char	**ft_export(char **env, char **cmdargs)
{
	int		i;
	//int		j;
	//int		found;
	//char	*var_only;

	if (!cmdargs[1])
		return (export_declare(env), env);
	env = ft_export_aux(env, cmdargs);
	/*i = 1;
	found = 0;
	while (cmdargs[i])
	{
		if (find_equal(cmdargs[i], &found) == 0)
		{
			i++;
			continue ;
		}
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(cmdargs[i], env[j], found + 1) == 0)
			{
				var_only = ft_substr(cmdargs[i], 0, found);
				env = del_var(env, var_only);
				free(var_only);
				j--;
			}
			j++;
		}
		i++;
	}*/
	i = 1;
	while (cmdargs[i])
	{
		if (ft_strchr(cmdargs[i], '='))
			env = add_var(env, cmdargs[i]);
		i++;
	}
	return (env);
}
//----------------------------------------------------------

//---------------------------PWD---------------------------
void	ft_pwd(void)
{
 	char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("PWD ERROR");
	ft_putendl_fd(cwd, 1);
	free(cwd);
}

//--------------------------------------------------------

//---------------------------CD----------------------------
/* 
	returns 1 if found
*/
int	found_in_env(char *var, char **env, char **path)
{
	int	i;
	int	foundeq;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
		{
			find_equal(env[i], &foundeq);
			*path = ft_substr(env[i], foundeq + 1, ft_strlen(env[i]) - foundeq );
			return (1);
		}
		i++;
	}
	return (0);
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
	int i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("*****************************************************************************\n");
	return (env);
}

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
			perror("bash: cd: HOME not set");
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
			perror("bash: cd: OLDPWD not set");
	}
	else
		if (access(cmdargs[1], F_OK) == 0)
        	ft_cd_update_env(env, cmdargs[1]);
		else
		    perror("bash: ERRORCIKO");
	    	
	
}

		
	/*}
	if (cmdargs[1] == "~")
		chdir(HOMEguardado);
	else
		chdir(cmdargs[1]);*/

//----------------------------------------------------------




int	main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	char	**envcpy = ft_env_cpy(env);
	char	*cmdargs[6] = {"cd", ".."};
	
	int i = 0;
	while (envcpy[i])
	{
		printf("%s :: %i\n", envcpy[i], i);
		i++;	
	}
	printf("*****************************************************************************\n");
	
	printf("\n..........................................\n\n");
	printf("BEFORE: %s\n", (getcwd(NULL, 0)));
	printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
	ft_cd(envcpy, cmdargs);
	
	
	printf("\n..........................................\n\n");
	printf("AFTER: %s\n", (getcwd(NULL, 0)));
	
	
	cmdargs[1] = "-";
	
	ft_cd(envcpy, cmdargs);
	
	printf("\n..........................................\n\n");
	printf("AFTER LAST: %s\n", (getcwd(NULL, 0)));



	
	return (0);
}
/*int	main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	char	**envcpy = ft_env_cpy(env);
	char	*cmdargs[6] = {"export"};

	printf("..........................................\n");
 
	int i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\n");
	envcpy = ft_export(envcpy, cmdargs);
	i = 0;
	while (envcpy[i])
	{
		printf("%s :: %i\n", envcpy[i], i);
		i++;	
	}
	printf("*****************************************************************************\n");
	ft_free_split(envcpy);
	return (0);
}*/
