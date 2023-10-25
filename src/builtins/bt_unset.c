/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/25 19:41:41 by imontero         ###   ########.fr       */
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
