/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/11/14 15:43:34 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

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
	g_stat = 0;
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
