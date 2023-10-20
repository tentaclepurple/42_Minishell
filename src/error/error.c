/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:26:06 by jzubizar          #+#    #+#             */
/*   Updated: 2023/10/20 11:10:45 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../parse.h"

void	*ft_error(int err_type, char *param, int err)
{
	g_stat = err;
	if (err_type == QUOTE)
		ft_printf("minishell: error while looking for matching quote\n");
	else if (err_type == NDIR)
		ft_printf("minishell: No such file or directory: %s\n", param);
	else if (err_type == NPERM)
		ft_printf("minishell: permission denied: %s\n", param);
	else if (err_type == NCMD)
		ft_printf("minishell: command not found\n");
	else if (err_type == DUPERR)
		ft_printf("minishell: dup2 failed\n");
	else if (err_type == FORKERR)
		ft_printf("minishell: fork failed\n");
	else if (err_type == PIPERR)
		ft_printf("minishell: error creating pipe\n");
	else if (err_type == SYNERR)
		ft_printf("minishell: syntax error near unexpected token\n");
	else if (err_type == MEM)
		ft_printf("minishell: no memory left on device\n");
	else if (err_type == IS_DIR)
		ft_printf("minishell: Is a directory: %s\n", param);
	else if (err_type == NOT_DIR)
		ft_printf("minishell: Not a directory: %s\n", param);
	return (NULL);
}