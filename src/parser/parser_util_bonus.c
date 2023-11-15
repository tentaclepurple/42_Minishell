/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:17:01 by jzubizar          #+#    #+#             */
/*   Updated: 2023/11/15 09:16:56 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

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
			&& ft_strncmp(*str, "||", 3) && ft_strncmp(*str, "(", 2)
			&& ft_strncmp(*str, ")", 2))
		{
			if (!flag)
			{
				flag = 1;
				i++;
			}
		}
		else
		{
			flag = 0;
			i++;
		}
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
		&& ft_strncmp(*str, "||", 3) && ft_strncmp(*str, "(", 2)
		&& ft_strncmp(*str, ")", 2))
	{
		if (!ft_strncmp(*str, ">>", 3) || !ft_strncmp(*str, ">", 2)
			|| !ft_strncmp(*str, "<<", 3) || !ft_strncmp(*str, "<", 3))
		{
			if (*(str + 1))
				i -= 2;
			else
				i--;
		}
		i++;
		str++;
	}
	return (i);
}

//Function to fill the node type
//Rerturns 0 if it is a cmd, 1 if not
int	ft_is_cm(char *str, t_px *node)
{
	if (!str)
		return (1);
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "exit"))
		return (node->type = BIp, 1);
	else if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "env"))
		return (node->type = BIc, 1);
	else if (!ft_strcmp(str, "&&"))
		node->type = T_AND;
	else if (!ft_strcmp(str, "||"))
		node->type = T_OR;
	else if (!ft_strcmp(str, "|"))
		node->type = T_PIPE;
	else if (!ft_strcmp(str, "("))
		node->type = L_PAR;
	else if (!ft_strcmp(str, ")"))
		node->type = R_PAR;
	if (node->type != NONE)
		return (2);
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
