/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/10/11 15:41:16 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

char	*ft_ask_path(char *str)
{
	return (ft_strdup(str));
}

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
		{
			//i++;
			flag = 0;	
		}
		str++;
	}
	return (i);
}

//Returns value of how many different arguments do we have (including the cmd command)
int	ft_num_args(char **str)
{
	int	i;

	i = 0;
	while (ft_strncmp(*str, "|", 2) && ft_strncmp(*str, ">", 2)
		&& ft_strncmp(*str, ">>", 3) && ft_strncmp(*str, "&&", 3)
		&& ft_strncmp(*str, "||", 3) && ft_strncmp(*str, "<<", 3))
	{
		i++;
		str++;
	}
	return (i);
}

//Function to process and fill info of a single node
char	**ft_parse_loop(t_px *node, char **str)
{
	int		num_arg;
	int		i;

	i = 0;
	if (!ft_strncmp("<", *str, 2))
	{
		node->in_flag = 1;
		node->infile = ft_strdup(*(str + 1));
		str += 2;
	}
	while (*str && ft_strncmp("|", *str, 2))
	{
		node->path = ft_ask_path(*str);//Funcion de iban que devvuelve el path completo del comando
		num_arg = ft_num_args(str);
		node->full_cmd = malloc(sizeof(char *) * num_arg + 1);
		if (!node->full_cmd)
			return (NULL);
		node->full_cmd[i++] = node->path;
		str++;
		while (i < num_arg)
		{
			node->full_cmd[i++] = ft_strdup(*str);
			str++;
		}
		node->full_cmd[i] = NULL;
		if (!ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, ">>", 3))
		{
			if (!ft_strncmp(*str, ">", 2))
				node->out_flag = 1;
			else
				node->out_flag = 2;
			node->infile = ft_strdup(*(str + 1));
			str += 2;
		}
		else if (!ft_strncmp(*str, "<<", 3))
		{
			node->in_flag = 2;
			node->limit = ft_strdup(*(str + 1));
			str += 2;
		}
	}
	return (++str);
}

//Function to init in zeros the array of t_px
t_px	*ft_init_nodes(t_info *info)
{
	t_px	*nodes;
	int		i;

	i = 0;
	nodes = malloc(sizeof(t_px) * info->cmd_amount);
	if (!nodes)
		return (NULL);
	while (i < info->cmd_amount)
	{
		nodes[i].full_cmd = NULL;
		nodes[i].path = NULL;
		nodes[i].infile = NULL;
		nodes[i].outfile = NULL;
		nodes[i].in_flag = 0;
		nodes[i].out_flag = 0;
		nodes[i].info = info;
		i++;
	}
	return (nodes);
}

//Returns the str info into an array of t_px
//Mallocs space for array of t_px and for the general info
//It does not free the str
t_px	*ft_parse(char **str)
{
	t_px	*nodes;
	t_info	*info;
	int		i;

	i = 0;
	info = malloc(sizeof(t_info));
	/* if (!info)
		return ; */
	info->cmd_amount = ft_node_quant(str);
	info->fd = NULL;
	nodes = ft_init_nodes(info);
	while (i < info->cmd_amount)
	{
		str = ft_parse_loop(&nodes[i], str);
		i++;
	}
	/* int j=0;
	while (j < info->cmd_amount)
	{
		i = 0;
		printf("NODO %i\n", j + 1);
		printf("PATH: %s\nOutput: %i\nInput: %i\n", nodes[j].path, nodes[j].out_flag, nodes[j].in_flag);
		printf("Infile: %s\nOutfile: %s\nLimit: %s\n", nodes[j].infile, nodes[j].outfile, nodes[j].limit);
		printf("ARGS: ");
		while (nodes[j].full_cmd[i])
		{
			printf("%s ", nodes[j].full_cmd[i]);
			i++;
		}
		printf("\n");
		j++;
	} */
	return (nodes);
}
