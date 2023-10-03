/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:36:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:43:07 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_ptr_len(uintptr_t	num)
{
	int	dig;

	dig = 1;
	while (num > 15)
	{
		num = num / 16;
		dig++;
	}
	return (dig);
}

static void	ft_putxptr_rec(uintptr_t	num, int fd)
{
	if (num > 15)
	{
		ft_putxptr_rec(num / 16, fd);
		ft_putxptr_rec(num % 16, fd);
	}
	else
	{
		ft_putchar_fd("0123456789abcdef"[num], fd);
	}
}

int	ft_putxptr_fd(void *n, int fd, t_flag flags)
{
	int	dig;
	int	aux;

	dig = 2;
	dig += ft_ptr_len((uintptr_t)n);
	if (flags.justify == 1)
	{
		write(fd, "0x", 2);
		ft_putxptr_rec((uintptr_t)n, fd);
	}
	aux = ft_print_width(flags.width, dig, 0);
	if (flags.justify == 0)
	{
		write(fd, "0x", 2);
		ft_putxptr_rec((uintptr_t)n, fd);
	}
	return (dig + aux);
}
