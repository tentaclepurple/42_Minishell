/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:17:01 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/14 17:08:03 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

//Returns the node quantity tto be allocated for the parsing of str
int	ft_node_quant(char **str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (ft_strncmp(*str, "|", 2) && ft_strncmp(*str, "&&", 3)
			&& ft_strncmp(*str, "||", 3))
		{
			if (!flag)
			{
				flag = 1;
				i++;
			}
		}
		else
			flag = 0;
		str++;
	}
	return (i);
}

//Returns value of how many different arguments 
//do we have (including the cmd command)
int	ft_num_args(char **str)
{
	int	i;

	i = 0;
	while (*str && ft_strncmp(*str, "|", 2) && ft_strncmp(*str, "&&", 3)
		&& ft_strncmp(*str, "||", 3))
	{
		if (!ft_strncmp(*str, ">>", 3) || !ft_strncmp(*str, ">", 2)
			|| !ft_strncmp(*str, "<<", 3) || !ft_strncmp(*str, "<", 2))
		{
			if (*(str + 1) && !ft_strchr("<|>", **(str + 1)))
				i -= 2;
			else
				i--;
		}
		i++;
		str++;
	}
	return (i);
}

int	ft_is_cm(char *str, t_px *node)
{
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "exit"))
	{
		node->type = BIp;
		return (1);
	}
	else if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "env"))
	{
		node->type = BIc;
		return (1);
	}
	node->type = CMD;
	return (0);
}

char	**ft_inout_file_condit(t_px *node, char **s, int *f)
{
	if (*s && (!ft_strncmp(*s, ">", 2) || !ft_strncmp(*s, ">>", 3)
			|| !ft_strncmp("<", *s, 2) || !ft_strncmp(*s, "<<", 3)) && ++(*f))
	{
		if (!ft_strncmp("<", *s, 2))
			node->in_flag = 1;
		else if (!ft_strncmp(*s, ">", 2))
			node->out_flag = 1;
		else if (!ft_strncmp(*s, ">>", 3))
			node->out_flag = 2;
		else
			node->in_flag = 2;
		s++;
		if (*s && !ft_strchr("<|>", **s))
		{
			if (node->out_flag)
				node->outfile = ft_strdup(*s);
			else if (node->in_flag == 1)
				node->infile = ft_strdup(*(s));
			else if (node->in_flag == 2)
				node->limit = ft_strdup(*(s));
		}
		if (*s)
			s++;
	}
	return (s);
}

char	**ft_inout_file(t_px *node, char **str)
{
	int	flag;

	flag = 0;
	str = ft_inout_file_condit(node, str, &flag);
	if (flag)
		str = ft_inout_file(node, str);
	return (str);
}
