/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:53:30 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/15 09:40:26 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

//Return 1 in wrong check, 0 if all OK
int	ft_check_inout(char **str)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if (flag == 0 && (!ft_strncmp(*str, ">>", 3)
				|| !ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, "<<", 3)
				|| !ft_strncmp(*str, "<", 2)))
			flag = 1;
		else if (flag == 1 && (!ft_strncmp(*str, ">>", 3)
				|| !ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, "<<", 3)
				|| !ft_strncmp(*str, "<", 2)))
			return (ft_error(SYNERR, NULL, 1), 1);
		else
			flag = 0;
		str++;
	}
	return (0);
}
