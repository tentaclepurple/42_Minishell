/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:20:24 by imontero          #+#    #+#             */
/*   Updated: 2023/10/18 12:21:32 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

=======
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:11:20 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/17 16:11:50 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

//Function to free a 2D array
>>>>>>> 2c21e5ef51a6fc448fb6507236a4e02f91d6bb39
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
<<<<<<< HEAD
}
=======
}
>>>>>>> 2c21e5ef51a6fc448fb6507236a4e02f91d6bb39
