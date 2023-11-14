/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/11/14 16:45:39 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse.h"

//Function to fill the complete args array
char	**ft_fill_full_cmd(t_px *node, int num_arg, char **str)
{
	int	i;

	i = 0;
	node->full_cmd = malloc(sizeof(char *) * (num_arg + 1));
	if (node->full_cmd && node->path)
		node->full_cmd[i++] = ft_strdup(node->path);
	else if (node->full_cmd)
		node->full_cmd[i++] = ft_strdup(("null"));
	str++;
	while (i < num_arg && node->full_cmd)
	{
		str = ft_inout_file(node, str);
		node->full_cmd[i] = ft_strdup(*str);
		i++;
		str++;
	}
	if (node->full_cmd)
		node->full_cmd[i] = NULL;
	return (str);
}

//Function to process and fill info of a single node
char	**ft_parse_loop(t_px *node, char **str, char **env)
{
	int		num_arg;

	str = ft_inout_file(node, str);
	while (*str && ft_strncmp("|", *str, 2))
	{
		if (!ft_is_cm(*str, node))
			node->path = get_cmd_or_cmdpath(env, *str);
		else
			node->path = ft_strdup(*str);
		num_arg = ft_num_args(str);
		if (num_arg == -1)
			exit (1);
		str = ft_fill_full_cmd(node, num_arg, str);
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
		nodes[i].type = 0;
		nodes[i].info = info;
		i++;
	}
	return (nodes);
}

//Check inapropriate node, returns 0 if OK
int	ft_err_node(t_px node)
{
	if (!node.path)
		return (ft_error(NCMD, NULL, 127), 2);
	if (!node.full_cmd)
		return (1);
	if (node.out_flag && !node.outfile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.out_flag && access(node.outfile, F_OK) < 0)
		return (0);
	else if (node.out_flag && access(node.outfile, W_OK) < 0)
		return (ft_error(NPERM, node.outfile, 126), 5);
	if (node.in_flag == 1 && !node.infile)
		return (ft_error(SYNERR, NULL, 20), 4);
	else if (node.in_flag == 1 && access(node.infile, F_OK) < 0)
		return (ft_error(NDIR, node.infile, 30), 6);
	else if (node.in_flag == 1 && access(node.infile, R_OK) < 0)
		return (ft_error(NPERM, node.infile, 126), 5);
	if (node.in_flag == 2 && !node.limit)
		return (ft_error(SYNERR, NULL, 20), 4);
	if (node.in_flag == 2 && (access(".tmp", F_OK) == 0
			&& access(".tmp", W_OK) < 0))
		return (ft_error(NPERM, ".temp", 126), 5);
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
