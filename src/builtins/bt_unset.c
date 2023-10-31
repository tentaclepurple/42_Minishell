/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/26 19:21:18 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	**ft_unset(t_px *px)
{
	int		i;
	char	**envaux;

	i = 1;
	while (px->full_cmd[i])
	{
		envaux = del_var(px->info->envcp, px->full_cmd[i]);
		i++;
	}
	return (envaux);
}

/*
	Returns 0 if any mthfckr suppresed env
*/	
int	check_no_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i == 0)
		return (0);
	else
		return (1);
}

int	check_env_and_vars(char **env)
{
	if (check_no_env(env))
		return (1);
	else
		return (0);
}
