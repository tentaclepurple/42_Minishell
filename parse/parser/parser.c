/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josu <josu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:59:57 by josu              #+#    #+#             */
/*   Updated: 2023/10/10 18:36:29 by josu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

t_node	*ft_parse_loop(char **str)
{
	t_node	node;
	int		num_arg;

	if (!ft_strncmp("<", *str, 2))
	{
		node.input = open(*(str + 1), O_RDONLY);
		if (node.input < 0)
			perror("No se puede abrir el archivo de entrada");
		str += 2;
	}
	while (*str && !ft_strncmp(*str, "|", 2))
	{
		node.path = ft_ask_path(*str);
		num_arg = ft_num_args(str);
		node.cmd = malloc(sizeof(char *) * num_arg + 1);
		if (!node.cmd)
			return(NULL);
		
	}
}