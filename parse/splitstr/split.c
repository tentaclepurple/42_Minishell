/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:14:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/04 13:38:52 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

size_t	ft_strlen_var(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

char	*ft_fill_expand(char *env, char  *str, int index)
{
	int		len_var;
	int		len_post;
	char	*res;
	int		i;

	i = 0;
	len_var = ft_strlen(&env[ft_strlen_var(&str[index + 1])]);
	len_post = ft_strlen(&str[index + 1 + ft_strlen_var(&str[index + 1])]);
	res = malloc(len_var + len_post + index + 2);
	if (!res)
		return (NULL);
	while (str[i] != '$')
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = '\0';
	while (*env != '=')
		env++;
	env++;
	ft_strlcat(res, env, len_var + len_post + index + 2);
	ft_strlcat(res, &str[index + 1 + ft_strlen_var(&str[index + 1])],
		len_var + len_post + index + 2);
	return (res);
}

char	*ft_expand_var(char **envp, char *str, int index)
{
	int		i;
	char	*res;
	
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], &str[index + 1], ft_strlen_var(&str[index + 1]))
			&& envp[i][ft_strlen_var(&str[index + 1])] == '=')
		{
			res = ft_fill_expand(envp[i], str, index);
			free(str);
			return (res);
		}
		i++;
	}
	return (NULL);
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
	int	i;

	while (*str)
	{
		i = 0;
		while (*str && (*str)[i])
		{
			if ((*str)[i] == '\'')
			{
				i++;
				while ((*str)[i] != '\'' && (*str)[i])
					i++;
			}
			else if ((*str)[i] == '$')
			{
				*str = ft_expand_var(env, *str, i);
			}
			i++;
		} 
		str++;
	}
}

int	ft_strarrlen(char **s, char *act)
{
	unsigned int	i;
	int				j;
	char			quote;
	int				cnt;
	
	j = 0;
	cnt = 0;
	while (s && s[j])
	{
		i = 0;
		while (s[j][i])
		{
			/* if (s[j][i] == '\'' || s[j][i] == '"')
			{
				quote = s[j][i];
				i++;
				while (s[j][i] != quote && s[j][i])
					i++;
			} */
			ft_mv_in_quotes(s[j], &i);
			if (ft_strchr(act, s[j][i]))
			{
				cnt++;
				if (i > 0)
					cnt++;
				if (s[j][i + 1])
					cnt++;
			}
			i++;
		}
		j++;
	}
	cnt += j;
	return (cnt);
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

int	main(int argc, char **argv, char **env)
{
	//char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
	char	*str = "USER|grep $HOME";
	char	**res;
	int		i = 0;
	
	(void)argc;
	(void)argv;
	res = ft_split_str(str, ' ');
	ft_check_var(res, env);
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	printf("Here\n");
	printf("%i\n", ft_strarrlen(res, "<|>"));
	//ft_free_split(res);
	/* res[0] = ft_expand_var(env, res[0]);
	while (*res)
	{
		printf("%s ", *res);
		res++;
	}
	printf("\n"); */
	//system ("leaks splitstr");
	return (0);
}
