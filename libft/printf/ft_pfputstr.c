/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfputstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:30:39 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:42:42 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_null_pfstrlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (6);
	while (s[i])
		i++;
	return (i);
}

static void	ft_null_pfputstr(char *str, int fd, int len)
{
	if (str == NULL)
		write(fd, "(null)", len);
	else
		write(fd, str, len);
}

int	ft_pfputargstr_fd(const char *s, int fd, t_flag flags)
{
	int		len;
	char	*str;
	int		aux;

	str = (char *)s;
	if (flags.precision && flags.precwidth < (int)ft_null_pfstrlen(str))
		len = flags.precwidth;
	else
		len = ft_null_pfstrlen(str);
	if (flags.justify == 1)
		ft_null_pfputstr(str, fd, len);
	aux = ft_print_width(flags.width, len, 0);
	if (flags.justify == 0)
		ft_null_pfputstr(str, fd, len);
	return (len + aux);
}

int	ft_pfputstr_fd(const char *s, int fd)
{
	int		len;
	char	*str;

	str = (char *)s;
	len = ft_pfstrlen(str);
	write(fd, str, len);
	return (len);
}
