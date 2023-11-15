/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imontero <imontero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:47:42 by imontero          #+#    #+#             */
/*   Updated: 2023/11/15 09:16:35 by imontero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsebonus.h"

/* 
	if there is more than 1 command, make dups.
	cases:
		- first cmd: dup2 stdout (if there is no >, >>)
		- middle cmd: dup2 stdin & stdout (if there is no >, >> or <, <<)
		- last cmd: dup2 stdin (if there is no <, <<)
*/
void	ft_fd_pipes(t_px *px, int n)
{
	n = (n / 2) + (n % 2);
	if (n == 0 && px->out_flag == 0)
	{
		if (dup2(px->info->fd[n][1], STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
	}
	else if (n == px->cmd_num - 1 && px->in_flag == 0)
	{
		if (dup2(px->info->fd[n - 1][0], STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
	}
	else if (n > 0 && n < px->cmd_num - 1)
	{
		if (px->out_flag == 0)
		{
			if (dup2(px->info->fd[n][1], STDOUT_FILENO) < 0)
				ft_error(DUPERR, NULL, 5);
		}
		if (px->in_flag == 0)
		{
			if (dup2(px->info->fd[n - 1][0], STDIN_FILENO) < 0)
				ft_error(DUPERR, NULL, 5);
		}
	}
}

/* 
	dup2 command input:
	if n = 1:  < (infile)
	if n = 2:  << (here_doc)
*/
void	ft_input_redirect(t_px *px)
{
	int	fd_in;

	if (px->in_flag == 1)
	{
		fd_in = open(px->infile, O_RDONLY);
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
		close(fd_in);
	}
	if (px->in_flag == 2)
	{
		write_here_doc_tmp(px);
		fd_in = open(".tmp", O_RDONLY);
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
		unlink(".tmp");
		close(fd_in);
	}
}

/* 
	dup2 command output:
	if n = 1:  > (output file trunc?)
	if n = 2:  >> (output file append)
*/
void	ft_output_redirect(t_px *px)
{
	int	fd_out;

	if (px->out_flag == 1)
	{
		fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
		close(fd_out);
	}
	if (px->out_flag == 2)
	{
		fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5);
		close(fd_out);
	}
}

int	pipex_p(t_px *px)
{
	pid_t				pid;
	int					i;
	struct sigaction	sa;

	i = 0;
	while (i < px->cmd_real_num)
	{
		if (px[i].in_flag == 2)
		{
			sa.sa_handler = SIG_IGN;
			sigaction(SIGQUIT, &sa, NULL);
		}
		if (px[i].type != BIp && px[i].type != T_PIPE)
		{
			pid = fork();
			if (pid < 0)
				return (ft_error(FORKERR, NULL, 4), 1);
			pipex_p_aux(px, i, pid);
		}
		else if (px[i].type != T_PIPE)
			ft_fd_close(px, i);
		i++;
	}
	return (0);
}

void	pipex(t_px *px)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_2nd_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	ft_alloc_fd(px);
	if (!px->info->fd)
		return ;
	if (pipex_p(px))
		return ;
	ft_free_fd(px);
}
