/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfputchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:33:05 by novadecordi       #+#    #+#             */
/*   Updated: 2023/08/03 11:42:27 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_printchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_print_char_fd(char c, t_flag flags, int fd)
{
	int	i;

	i = 0;
	if (flags.justify == 1)
		i += ft_printchar(c, fd);
	i += ft_print_width(flags.width, 1, 0);
	if (flags.justify == 0)
		i += ft_printchar(c, fd);
	return (i);
}
