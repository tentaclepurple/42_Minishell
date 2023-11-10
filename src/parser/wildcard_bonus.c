/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:02:32 by imontero          #+#    #+#             */
/*   Updated: 2023/10/31 20:15:22 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/parse_bonus.h"

int	ft_matlen(char **mat)
{
	int	len;

	len = 0;
	while (mat[len])
		len++;
	return (len);
}

int	count_dir(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		count++;
	}
	closedir(dir);
	return (count);
}

char	**create_exp_cmdargs(char **cmdargs, int *size)
{
	char	**exp_cmdargs;

	*size = (ft_matlen(cmdargs) * count_dir()) + 1;
	exp_cmdargs = malloc(sizeof(char *) * (*size));
	ft_bzero(exp_cmdargs, sizeof(char *) * (ft_matlen(cmdargs) * count_dir()));
	exp_cmdargs[0] = ft_strdup(cmdargs[0]);
	return (exp_cmdargs);
}

//Returns 1 if there is a wildcard, 0 if not
int	find_wild_match(char *pattern, char *str)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*str)
			{
				if (*str == *pattern && find_wild_match(pattern, str))
					return (1);
				str++;
			}
			return (0);
		}
		if (*str == '\0' || (*pattern != *str))
			return (0);
		pattern++;
		str++;
	}
	return (*str == '\0');
}

void	fill_exp_cmdargs(char *pattern, char ***exp_cmdargs)
{
	static int		j = 1;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{	
		if (!ft_strcmp("*", pattern))
		{
			if (entry->d_name[0] != '.')
			{
				(*exp_cmdargs)[j] = ft_strdup(entry->d_name);
				j++;
			}
		}
		else if (find_wild_match(pattern, entry->d_name))
		{
			(*exp_cmdargs)[j] = ft_strdup(entry->d_name);
			j++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
char	**trim_excess(char **exp, int size)
{
	char	**trim;
	int		len;
	int		i;

	(void)size;
	len = ft_matlen(exp);
	trim = malloc(sizeof(char *) * (len + 1));
	trim[len] = NULL;
	i = 0;
	//printf("len: %i\n", len);
	while (i < len)
	{
		trim[i] = ft_strdup(exp[i]);
		i++;
	}
	ft_free_split(exp);
	return (trim);	
}


void	ft_wildcard(t_px *node)
{
	int		i;
	int		size;
	char	**exp_cmdargs;
	char	**exp_trim;
	char	**cmdargs;

	i = 1;
	if (!node->full_cmd)
		return ;
	cmdargs = node->full_cmd;
	exp_cmdargs = create_exp_cmdargs(cmdargs, &size);
	while ((cmdargs)[i])
	{
		printf("CMND ARG %i: %s\n", i, (cmdargs)[i]);
		if (ft_strchr((cmdargs)[i], '*'))
			fill_exp_cmdargs((cmdargs)[i], &exp_cmdargs);
		i++;
	}
	exp_trim = trim_excess(exp_cmdargs, size);
	i = 0;
	while (exp_trim[i])
	{
		printf("el cmdargs expandido %i : %s\n", i, exp_trim[i]);
		i++;
	}
	ft_free_split(cmdargs);
	node->full_cmd = exp_trim;
	//ft_free_split(exp_trim); //este es el bueno
}

/*int	main()
{
	char	**cmdargs;

	cmdargs = malloc(sizeof(char *) * 10);
	cmdargs[0] = ft_strdup("ls");
	//cmdargs[1] = ft_strdup("*no*i*.*x*");
	cmdargs[1] = ft_strdup("*");
	cmdargs[2] = ft_strdup("man*");
	cmdargs[3] = ft_strdup("*a*t*.*");
	cmdargs[4] = NULL;
	ft_wildcard(&cmdargs);
	ft_free_split(cmdargs);
	return (0);
}*/
