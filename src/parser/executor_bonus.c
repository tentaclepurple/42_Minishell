/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:47:42 by imontero          #+#    #+#             */
/*   Updated: 2023/11/09 13:08:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parse_bonus.h"

/* 
	if there is more than 1 command, make dups.
	cases:
		- first cmd: dup2 stdout (if there is no >, >>)
		- middle cmd: dup2 stdin & stdout (if there is no >, >> or <, <<)
		- last cmd: dup2 stdin (if there is no <, <<)
*/
void	ft_fd_pipes(t_px *px, int qn)
{
	int	n;

	n = (qn / 2) + (qn % 2);
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

	i = 0;
	while (i < px->cmd_real_num)
	{
		if (px[i].type == T_PIPE)
		{
			i++;
			continue ;
		}
		if (px[i].type != BIp)
		{
			pid = fork();
			if (pid < 0)
			{
				ft_error(FORKERR, NULL, 4);
				return (1);
			}
			if (pid == 0)
				ft_child(&px[i], i);
			ft_fd_close(px, i);
			waitpid(pid, &g_stat, 0);
			ft_stat_signaled();
		}
		else
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
	ft_alloc_fd(px);
	if (!px->info->fd)
		return ;
	if (pipex_p(px))
		return ;
	if (px->cmd_num > 1)
		ft_free_fd(px);
}
