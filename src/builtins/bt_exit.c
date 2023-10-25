/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:37:05 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/24 17:50:34 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	ft_atoi_exit(const char *str, long  *nbr)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	*nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		*nbr = *nbr * 10 + str[i] - '0';
		i++;
	}
	if (!str[i])
	{
		*nbr *= sign;
		return (0);
	}
	return (-1);
}

int	ft_bt_exit(t_px *node)
{
	long	nbr[1];
	
	ft_printf("exit\n");
	if (!node->full_cmd[1])
		return (1);
	if (ft_atoi_exit(node->full_cmd[1], nbr) < 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", node->full_cmd[1]);
		g_stat= 255;
	}
	else if (node->full_cmd[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		g_stat = 1;
		return (0);
	}
	else
		g_stat = *nbr % 256;
	return (1);
}