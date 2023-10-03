/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:10:54 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:44 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*lastchar;

	i = 0;
	lastchar = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			lastchar = (char *) &s[i];
		i++;
	}
	if (s[i] == (char)c)
		lastchar = (char *) &s[i];
	return (lastchar);
}
