/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:14:34 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/23 11:15:46 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

//Function to advnce the index i from quote to quote
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

//Returns the number of different words you have in s
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

//Returns the length of the next word ins
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

//Fills the wrd string with str and a specific length
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

/* Sub function for ft_split_str */
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

//Splits a String into a 2D string array, taking quotes into account"
char	**ft_split_str(char const *s, char c)
{
	char	**split;
	int		err;
	int		i;

	if (!ft_nbr_wrd(s, c))
		return (NULL);
	split = malloc(sizeof(char *) * (ft_nbr_wrd(s, c) + 1));
	if (split == NULL)
		return (ft_error(MEM, NULL, 2));
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
		return (ft_error(MEM, NULL, 2));
	}
	return (split);
}

/* //Function to free a 2D array
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
} */

//Returns the length of the corrected string fot ft_correct_str
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

//Auxiliar function of correct string, with the conditional statements
void	ft_aux_correct_str(char *res, char *str, int *i, int *extra)
{
	char	quote;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		quote = str[*i];
		res[*i + *extra] = str[*i];
		(*i)++;
		while (str[*i])
		{
			res[*i + *extra] = str[*i];
			if (str[*i] == quote)
				break ;
			(*i)++;
		}
	}
	if (ft_strchr("<>|&", str[*i]))
	{
		res[*i + *extra] = ' ';
		res[*i + *extra + 1] = str[*i];
		res[*i + *extra + 2] = ' ';
		(*extra) += 2;
	}
	else
		res[*i + *extra] = str[*i];
}

//Adds spaces into the string, separating the special characters
// str is freed in terminal function
char	*ft_correct_str(char *str)
{
	char	*res;
	int		i;
	int		extra;

	i = 0;
	extra = 0;
	res = malloc(ft_strcorr_len(str, "<>|&") + 1);
	if (!res)
		return (ft_error(MEM, NULL, 2));
	while (str[i])
	{
		ft_aux_correct_str(res, str, &i, &extra);
		i++;
	}
	res[i + extra] = '\0';
	return (res);
}

/* int	main(int argc, char **argv, char **env)
{
	//char	*str = "$USER -la | grep \"Ma$USER ke file\"da $HOME";
	//char	*str = "ls -la << EOF |awk \"<$HOME d\" | cat";
	//char	*str = "ls -l | cat << lim | cat > outfile | cat >> outfile";
	//char	*str = "ls -l | cat << lim | cat | cat";
	char	*str = "ls | cat | cat | cat > file | cat | cat |cat >> outfile";
	char	**res;
	//t_px	*nodes;
	int		i = 0;
	
	(void)argc;
	(void)argv;
	str = ft_correct_str(str);
	res = ft_split_str(str, ' ');
	ft_check_var(res, env);
	res = ft_correc_special(res, "<>|&");
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	//nodes = malloc(sizeof(t_px) * 1);
	ft_parse(res);
	ft_free_split(res);
	free(str);
	
	return (0);
} */
