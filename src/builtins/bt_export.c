/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/11/14 15:44:51 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

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

	i = 1;
	found = 0;
	while (cmdargs[i])
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
				j--;
			}
		}
		i++;
	}
	return (env);
}

char	**ft_export(char **env, char **cmdargs)
{
	int		i;

	g_stat = 0;
	if (!cmdargs[1])
		return (export_declare(env), env);
	env = ft_export_aux(env, cmdargs);
	i = 1;
	while (cmdargs[i])
	{
		if (ft_strchr(cmdargs[i], '='))
			env = add_var(env, cmdargs[i]);
		i++;
	}
	return (env);
}
