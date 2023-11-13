/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:11:20 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/23 11:59:33 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//Function to free a 2D array
void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}
