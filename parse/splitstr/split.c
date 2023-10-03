/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:14:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/03 19:14:18 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

char	*ft_expand_var(char **envp, char *var)
{
	int		i;
	char	*res;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var + 1, ft_strlen(var) - 1))
		{
			res = ft_strdup(&envp[i][5]);
			free(var);
			return (res);
		}
		i++;
	}
	return (var);
}

void	ft_mv_in_quotes(char const *s, unsigned int *i)
{
	char			quote;

	if (s[*i] == '\"' || s[*i] == '\'')
	{
		quote = s[(*i)++];
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

void	ft_check_var(char **str, char **env)
{
	while (*str)
	{
		if (*str[0] == '$')
			*str = ft_expand_var(env, *str);
		str++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str = "$USER -la | gre p \'Ma ke file\' $HOME";
	char	**res;
	int		i = 0;
	
	(void)argc;
	(void)argv;
	res = ft_split_str(str, ' ');
	ft_check_var(res, env);
	while (res[i])
	{
		printf("%s ", res[i]);
		i++;
	}
	printf("\n");
	/* res[0] = ft_expand_var(env, res[0]);
	while (*res)
	{
		printf("%s ", *res);
		res++;
	}
	printf("\n"); */
	return (0);
}
