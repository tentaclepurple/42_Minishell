/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:14:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/05 13:06:15 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

void	ft_mv_in_quotes(char const *s, unsigned int *i)
{
	char			quote;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		quote = s[*i];
		(*i)++;
		while (s[*i])
		{
			if (s[*i] == quote)
				break ;
			(*i)++;
		}
	}
}

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
		ft_mv_in_quotes(s, &i);
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
	{
		ft_mv_in_quotes(s, &i);
		i++;
	}
	return (i);
}

static char	*ft_fill_word(char *wrd, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
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
			word = ft_fill_word(word, str, len);
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

char	**ft_split_str(char const *s, char c)
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

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

int	ft_strcorr_len(char	*str, char *act)
{
	unsigned int	i;
	int				extra;

	i = 0;
	extra = 0;
	while (str[i])
	{
		ft_mv_in_quotes(str, &i);
		if (ft_strchr(act, str[i]))
			extra += 2;
		i++;
	}
	return (i + extra);
}

char	*ft_correct_str(char *str)
{
	char	*res;
	int		i;
	int		lim;
	char	quote;
	int		extra;
	
	i = 0;
	extra = 0;
	//calculate new length
	//new malloc
	res = malloc(ft_strcorr_len(str, "<>|") + 1);
	if (!res)
		return (NULL);
	//Loop strlcat " ? " + following string until ?
	while (str[i])
	{

		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			res[i + extra] = str[i];
			i++;
			while (str[i])
			{
				res[i + extra] = str[i];
				if (str[i] == quote)
					break ;
				i++;
			}
		}
		if (ft_strchr("<>|", str[i]))
		{
			res[i + extra] = ' ';
			res[i + extra + 1] = str[i];
			res[i + extra + 2] = ' ';
			extra += 2;
		}
		else
			res[i + extra] = str[i];
		i++;
	}
	res[i + extra] = '\0';
	//free previous string
	//free (str);
	//set str to new string
	return (res);
}

int	main(int argc, char **argv, char **env)
{
	//char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
	char	*str = "USER|grep \"<$HOME\"";
	char	**res;
	int		i = 0;
	
	(void)argc;
	(void)argv;
	str = ft_correct_str(str);
	res = ft_split_str(str, ' ');
	ft_check_var(res, env);
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	return (73);
}
