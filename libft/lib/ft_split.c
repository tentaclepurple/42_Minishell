/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:12 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:41:12 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

static int	ft_nbr_wrd(char const *s, char c)
{
	unsigned int	i;
	unsigned int	flag;
	int				num;

	i = 0;
	flag = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != c)
			flag = 1;
		else if (flag && s[i] == c)
		{
			num++;
			flag = 0;
		}
		i++;
	}
	if (flag)
		num++;
	return (num);
}

static int	ft_str_chlen(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_fill_word(char *wrd, char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		wrd[i] = str[i];
		i++;
	}
	wrd[i] = '\0';
	return (wrd);
}

static int	ft_split_low(char **split, char const *s, char c)
{
	char	*str;
	char	*word;
	int		len;
	int		i;

	str = (char *)s;
	i = 0;
	while (i < ft_nbr_wrd(s, c))
	{
		len = ft_str_chlen(str, c);
		if (len > 0)
		{
			word = malloc(sizeof(char) * (len + 1));
			if (word == NULL)
				return (i + 1);
			word = ft_fill_word(word, str, c);
			split[i] = word;
			str += len + 1;
			i++;
		}
		else
			str++;
	}
	split[ft_nbr_wrd(s, c)] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		err;
	int		i;

	split = malloc(sizeof(char *) * (ft_nbr_wrd(s, c) + 1));
	if (split == NULL)
		return (NULL);
	err = ft_split_low(split, s, c);
	if (err)
	{
		i = 0;
		while (i < err - 1)
		{
			free(split[i]);
			i++;
		}
		free (split);
		return (NULL);
	}
	return (split);
}
/*
#include<stdio.h>

int	main(void)
{
	char	**res;
	int		i = 0;

	res = ft_split("hello!", ' ');
	while (res[i] != NULL)
	{
		printf("%s\n", res[i]);
		i++;
	}
}*/
