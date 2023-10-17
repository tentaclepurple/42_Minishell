/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:33:42 by imontero          #+#    #+#             */
/*   Updated: 2023/10/16 18:28:04 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void	ft_echo(t_px *px)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (px->full_cmd[1] != NULL && !ft_strcmp(px->full_cmd[1], "-n"))
	{
		px->full_cmd++;
		flag++;
	}
	while (px->full_cmd[i])
	{
		if (i > 1)
			write(1, " ", 1);
		ft_putstr_fd(px->full_cmd[i], 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
}

/*int	main()
{
	char	**full_cmd;
	
	full_cmd = malloc(sizeof(char **) * 7);
	full_cmd[0] = "echo";
	full_cmd[1] = "pepe";
	full_cmd[2] = "joserra";
	full_cmd[3] = "manolete";
	full_cmd[4] = "potxolito";
	full_cmd[5] = NULL;

	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (full_cmd[1] != NULL && !ft_strcmp(full_cmd[1], "-n"))
	{
		full_cmd++;
		flag++;
	}
	while (full_cmd[i])
	{
		if (i > 1)
			write(1, " ", 1);
		ft_putstr_fd(full_cmd[i], 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	free(full_cmd);
}*/
