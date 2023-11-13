/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:10:54 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/05 11:01:46 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//Returns a ponter to the first character 'c' found i  str. NULL if not found
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
