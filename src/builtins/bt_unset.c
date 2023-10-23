/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/23 13:01:10 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

/* 	Iterates throug the cmd args and deletes the vars if founded. 
	Returns a copy of env with vars deleted
*/
/*char	**ft_unset(char **env, char **cmdargs)
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
}*/

char	**ft_unset(t_px *px)
{
	int	i;
	char	**envaux;

	//envcopy = env;
	i = 1;
	while (px->full_cmd[i])
	{
		envaux = del_var(px->info->envcp, px->full_cmd[i]);
		//free(px->info->envcp);
		//px->info->envcp = envaux;
		i++;
	}
	return (envaux);
	
}

