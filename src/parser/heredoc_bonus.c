/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:52:08 by imontero          #+#    #+#             */
/*   Updated: 2023/11/15 09:16:43 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

void	ft_getline_aux(char c, char **str)
{
	char	*aux;
	char	*tmp;

	aux = *str;
	tmp = malloc(2 * sizeof(char));
	tmp[0] = c;
	tmp[1] = 0;
	*str = ft_strjoin(*str, tmp);
	free(tmp);
	free(aux);
}

char	*ft_getline(int fd)
{
	char	c;
	char	*str;
	int		re;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	re = read(fd, &c, 1);
	while (re >= 0)
	{
		if (!str[0] && re == 0)
			return (NULL);
		ft_getline_aux(c, &str);
		if (c == '\n')
			break ;
		c = 0;
		re = read(fd, &c, 1);
	}
	return (str);
}

void	write_here_doc_tmp(t_px *px)
{
	char	*line;
	char	*limit_n;
	int		fd;

	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = ft_getline(0);
		if (line == NULL)
			break ;
		limit_n = ft_strjoin(px->limit, "\n");
		if (ft_strcmp(limit_n, line) == 0)
		{
			free(limit_n);
			break ;
		}
		free(limit_n);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}

void	ft_free_fd(t_px *px)
{
	int	i;

	i = 0;
	while (i < px->cmd_num - 1)
	{
		free(px->info->fd[i]);
		i++;
	}
	free(px->info->fd);
}

/* 
	n = command index
*/
void	ft_child(t_px *px, int n)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	if (px->cmd_num > 1)
		ft_fd_pipes(px, n);
	if (px->in_flag > 0)
		ft_input_redirect(px);
	if (px->out_flag > 0)
		ft_output_redirect(px);
	ft_fd_close(px, px->cmd_real_num - 1);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
	if (px->type == BIc)
	{
		ft_execbi_child(px);
		exit(1);
	}
	execve(px->path, px->full_cmd, NULL);
}
