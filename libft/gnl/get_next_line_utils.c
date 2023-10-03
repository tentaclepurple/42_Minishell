/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:07:35 by jzubizar          #+#    #+#             */
/*   Updated: 2023/05/04 21:08:45 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

//Boolean function. Returns 1 if 'ch' is in str. 0 if not
int	ft_isin_str(char *str, char ch)
{
	unsigned int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == ch)
			return (1);
		i++;
	}
	if (str[i] == ch)
		return (1);
	return (0);
}

//Returns string length
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

//Function to add s2 to s1
char	*ft_strbuf_join(char *s1, char const *s2)
{
	unsigned int	j;
	char			*str;
	int				i;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
	{
		free (s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free (s1);
	return (str);
}
