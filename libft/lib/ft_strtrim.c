/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:26:54 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:47 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

static int	ft_isin(char const *set, char c)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_set(unsigned int	*i, unsigned int *end, char *s1, char *set)
{
	while (ft_isin(set, s1[*i]))
		*i += 1;
	if (*i != ft_strlen(s1))
	{
		*end = ft_strlen(s1) - 1;
		while (ft_isin(set, s1[*end]))
			*end -= 1;
	}
	else
		*end = *i - 1;
	return (*end - *i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	len;
	unsigned int	i;
	unsigned int	end;
	char			*str;

	i = 0;
	end = 0;
	if (*s1)
		len = (unsigned int)ft_set(&i, &end, (char *)s1, (char *)set);
	else
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	end = 0;
	while (end < len)
	{
		str[end] = s1[i];
		end++;
		i++;
	}
	str[end] = '\0';
	return (str);
}
/*
#include<stdio.h>

int	main(void)
{
	char *s1 = "abababababbbaa";
    char *set = "ab";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
