/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:01:13 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:23 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len;
	unsigned int	len1;
	char			*str;
	unsigned int	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	len1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
