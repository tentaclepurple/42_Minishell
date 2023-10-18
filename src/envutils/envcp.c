/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/18 19:54:50 by imontero         ###   ########.fr       */
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
	envcp = malloc((sizeof(char *) * i) + 1);
	envcp[i] = NULL;
	i = 0;
	while (env[i])
	{
		envcp[i] = ft_strdup(env[i]);
		i++;
	}
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
	ft_free_split(env);
	return (envcpy);
}

char	**add_var(char **env, char *var)
{
	int		len;
	int		i;
	char	**envcp;

	len = 0;
	while (env[len])
		len++;
	envcp = malloc((sizeof(char *) * len) + 2);
	envcp[len + 1] = NULL;
	i = 0;
	while (i < len - 1)
	{
		envcp[i] = env[i];
		i++;
	}
	envcp[i] = ft_strdup(var);
	//free(var)???????????????????????????????????????????????
	//ft_free_split(env);
	return (envcp);
}

char	**del_var(char **env, char *var)
{
	int		found;
	int		len;
	int		j;
	char	**envcpy;
	char	*varok;

	found = 0;
	varok = ft_strjoin(var, "=");
	//free(var);
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
	envcpy = malloc(sizeof(char *) * len);
	envcpy[len] = NULL;
	len = 0;
	j = 0;
	while (env[len])
	{
		if (len != found)
		{
			envcpy[j] = ft_strdup(env[len]);
			len++;
			j++;
		}
		else
			len++;
	}
	//ft_free_split(px->info->envcp);
	return (envcpy);
}
















int	main(int c, char **v, char **env)
{
	(void)c;
	(void)v;
	
	
	int i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("----------\n");
	/*env = add_var(env, "PAYASO=fuckyou");
	i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("----------\n");*/
	env = del_var(env, "PAYASO");
	i = 0;
	while (env[i])
	{
		printf("%s :: %i\n", env[i], i);
		i++;	
	}
	printf("----------\n");
	return (0);
}
