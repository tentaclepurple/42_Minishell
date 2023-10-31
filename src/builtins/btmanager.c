/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btmanager.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:00:14 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 11:16:23 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

void	ft_execbi_child(t_px *px)
{
	if (!ft_strcmp(px->full_cmd[0], "echo"))
		ft_echo(px);
	else if (!ft_strcmp(px->full_cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(px->full_cmd[0], "env"))
		ft_env(px->info->envcp);
}

int	ft_execbi_parent(t_px *px)
{
	if (!ft_strcmp(px->full_cmd[0], "cd"))
		px->info->envcp = ft_cd(px);
	else if (!ft_strcmp(px->full_cmd[0], "unset"))
		px->info->envcp = ft_unset(px);
	else if (!ft_strcmp(px->full_cmd[0], "export"))
		px->info->envcp = ft_export(px->info->envcp, px->full_cmd);
	else if (!ft_strcmp(px->full_cmd[0], "exit"))
		if (ft_bt_exit(px))
			return (1);
	return (0);
}
