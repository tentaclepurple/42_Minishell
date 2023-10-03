/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:11:11 by jzubizar          #+#    #+#             */
/*   Updated: 2023/04/27 19:00:08 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!src && !dst)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	if (dst <= src)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (n)
	{
		i = n;
		while (i--)
			d[i] = s[i];
	}
	return (dst);
}
