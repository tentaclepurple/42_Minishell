/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/10/24 12:46:17 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

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
	/* while (*str && ft_strncmp(*str, "|", 2) && ft_strncmp(*str, ">", 2)
		&& ft_strncmp(*str, ">>", 3) && ft_strncmp(*str, "&&", 3)
		&& ft_strncmp(*str, "||", 3) && ft_strncmp(*str, "<<", 3)
		&& ft_strncmp(*str, "<", 3)) */
	while (*str && ft_strncmp(*str, "|", 2) && ft_strncmp(*str, "&&", 3)
		&& ft_strncmp(*str, "||", 3))
	{
		if (!ft_strncmp(*str, ">>", 3) || !ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, "<<", 3) || !ft_strncmp(*str, "<", 3))
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

int	ft_is_cm(char *str, t_px *node)
{
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "unset") ||
			!ft_strcmp(str, "exit"))
	{
		node->type = BIp;
		return (1);
	}
	else if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd") || !ft_strcmp(str, "env"))
	{
		node->type = BIc;
		return (1);
	}
	node->type = CMD;
	return (0);
}

char	**ft_inout_file(t_px *node, char **str)
{
	if (*str && !ft_strncmp("<", *str, 2))
	{
		node->in_flag = 1;
		str++;
		if (*str && !ft_strchr("<|>", **str))
			node->infile = ft_strdup(*(str++));
		if (*str)
			str++;
	}
	else if (*str && (!ft_strncmp(*str, ">", 2) || !ft_strncmp(*str, ">>", 3)))
	{
		if (!ft_strncmp(*str, ">", 2))
			node->out_flag = 1;
		else
			node->out_flag = 2;
		str++;
		if (*str && !ft_strchr("<|>", **str))
			node->outfile = ft_strdup(*(str++));
		if (*str)
			str++;
	}
	else if (*str && !ft_strncmp(*str, "<<", 3))
	{
		node->in_flag = 2;
		str++;
		if (*str && !ft_strchr("<|>", **str))
			node->limit = ft_strdup(*(str++));
		if (*str)
			str++;
	}
	return (str);
}

//Function to process and fill info of a single node
char	**ft_parse_loop(t_px *node, char **str, char **env)
{
	int		num_arg;
	int		i;

	i = 0;
	str = ft_inout_file(node, str);
	while (*str && ft_strncmp("|", *str, 2))
	{
		if (!ft_is_cm(*str, node))
			node->path = get_cmd_or_cmdpath(env, *str);//Funcion de iban que devvuelve el path completo del comando
		else
			node->path = ft_strdup(*str);
		num_arg = ft_num_args(str);
		node->full_cmd = malloc(sizeof(char *) * (num_arg + 1));
		if (node->full_cmd)
			node->full_cmd[i++] = node->path;
		str++;
		while (i < num_arg && node->full_cmd)
		{
			str = ft_inout_file(node, str);
			node->full_cmd[i++] = ft_strdup(*str);
			str++;
		}
		if (node->full_cmd)
			node->full_cmd[i] = NULL;
		str = ft_inout_file(node, str);
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
		return (ft_error(MEM, NULL, 2));
	while (i < info->cmd_amount)
	{
		nodes[i].full_cmd = NULL;
		nodes[i].path = NULL;
		nodes[i].infile = NULL;
		nodes[i].outfile = NULL;
		nodes[i].limit = NULL;
		nodes[i].in_flag = 0;
		nodes[i].out_flag = 0;
		nodes[i].info = info;
		i++;
	}
	return (nodes);
}

//Check inapropriate node, returns 0 if OK
int	ft_err_node(t_px node)
{
	if (!node.path)
		return (ft_error(NCMD, NULL, 50), 2);
	if (!node.full_cmd)
		return (1);
	if (node.out_flag && !node.outfile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.out_flag && access(node.outfile, F_OK) < 0)
		return (ft_error(NDIR, node.outfile, 30), 6);
	else if (node.out_flag && access(node.outfile, R_OK) < 0)
		return (ft_error(NPERM, node.outfile, 10), 5);
	if (node.in_flag == 1 && !node.infile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.in_flag == 1 && access(node.infile, F_OK) < 0)
		return (ft_error(NDIR, node.infile, 30), 6);
	else if (node.in_flag == 1 && access(node.infile, R_OK) < 0)
		return (ft_error(NPERM, node.infile, 10), 5);
	if (node.in_flag == 2 && !node.limit)
		return (ft_error(SYNERR, NULL, 20), 4);
	if (node.in_flag == 2 && (access(".tmp", F_OK) == 0 && access(".tmp", W_OK) < 0))
		return (ft_error(NPERM, ".temp", 10), 5);
	return (0);
}

//Function to check if every malloc filling the nodes where correctly done
int	ft_check_nodes(t_px *nodes)
{
	int	len;
	int	i;

	len = (*nodes).info->cmd_amount;
	i = 0;
	while (i < len)
	{
		if (ft_err_node(*(nodes + i)))
			return (1);
		i++;
	}
	return (0);
}

//Function to free the nodes array
void	ft_free_nodes(t_px *nodes)
{
	int	len;
	int	i;

	len = (*nodes).info->cmd_amount;
	i = 0;
	while (i < len)
	{
		if (nodes[i].full_cmd)
		{
			ft_free_split(nodes[i].full_cmd);
			nodes[i].path = NULL;
		}
		if (nodes[i].path)
			free(nodes[i].path);
		if (nodes[i].infile)
			free(nodes[i].infile);
		if (nodes[i].outfile)
			free(nodes[i].outfile);
		if (nodes[i].limit)
			free(nodes[i].limit);
		i++;
	}
	free((*nodes).info);
	free(nodes);
}

//Returns the str info into an array of t_px
//Mallocs space for array of t_px and for the general info
//It does not free the str
//t_px	*ft_parse(char **str, char **env)
t_px	*ft_parse(char **str, t_info *info)
{
	t_px	*nodes;
	//t_info	*info;
	int		i;
	/*static int	cont;

	if (!cont)
		cont = 0;*/
	i = 0;
	/*info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error(MEM, NULL, 2));*/
	info->cmd_amount = ft_node_quant(str);
	info->fd = NULL;
	//info->envcp = env;
	/*printf("cont: %i\n", cont);
	if (cont == 0)
		info->envcp = env;
	cont += 1;*/

	/*printf("\n***************************\n\n");
	int n = 0;
	while (info->envcp[n])
	{
		printf("%s\n", info->envcp[n]);
		n++;
	}*/
	nodes = ft_init_nodes(info);
	if (!nodes)
		return (free(info), NULL);
	while (i < info->cmd_amount)
	{
		str = ft_parse_loop(&nodes[i], str, info->envcp);
		i++;
	}
	if (ft_check_nodes(nodes))
	{
		return (ft_free_nodes(nodes), NULL);
	}

	return (nodes);
}

