/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:08:01 by imontero          #+#    #+#             */
/*   Updated: 2023/10/24 18:14:27 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

char	**ft_unset(t_px *px)
{
	int	i;
	char	**envaux;

	i = 1;
	while (px->full_cmd[i])
	{
		envaux = del_var(px->info->envcp, px->full_cmd[i]);
		i++;
	}
	return (envaux);
	
}

