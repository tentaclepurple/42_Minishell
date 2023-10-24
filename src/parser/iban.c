
#include"../parse.h"

void	ft_fd_close(t_px *px, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		close(px->info->fd[i][0]);
		close(px->info->fd[i][1]);
		i++;
	}
}

void	ft_alloc_fd(t_px *px)
{
	int	i;

	i = 0;
	px->info->fd = malloc(sizeof(int *) * (px->info->cmd_amount - 1));
	if (!px->info->fd)
		return ;
	while (i < px->info->cmd_amount - 1)
	{
		px->info->fd[i] = malloc(sizeof(int) * 2);
		pipe(px->info->fd[i]);
		i++;
	}
}

void	ft_free_fd(t_px *px)
{
	int	i;

	i = 0;
	while (i < px->info->cmd_amount - 1)
	{
		free(px->info->fd[i]);
		i++;
	}
	free(px->info->fd);
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

char	*ft_getline(int fd)
{
	char	c;
	char	*str;
	char	*tmp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		tmp = malloc(2 * sizeof(char));
		tmp[0] = c;
		tmp[1] = 0;
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}

/* 
	if there is more than 1 command, make dups.
	cases:
		- first cmd: dup2 stdout (if there is no >, >>)
		- middle cmd: dup2 stdin & stdout (if there is no >, >> or <, <<)
		- last cmd: dup2 stdin (if there is no <, <<)
*/
void	ft_fd_pipes(t_px *px, int n)
{
	
	if (n == 0) //first cmd
	{
		//fprintf(stderr, "pipes first cmd\n");
		if (dup2(px->info->fd[n][1], STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
	}
	else if (n == px->info->cmd_amount - 1 && px->in_flag == 0) //last cmd
	{
		//fprintf(stderr, "pipes last cmd\n");
		if (dup2(px->info->fd[n - 1][0], STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
	}
	else //middle cmd
	{
		//fprintf(stderr, "pipes mid cmd output red flag: %i\n", px->out_flag);
		if (px->out_flag == 0)
		{
			if (dup2(px->info->fd[n][1], STDOUT_FILENO) < 0)
				ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		}
		//fprintf(stderr, "pipes mid cmd input red flag: %i\n", px->in_flag);
		if (px->in_flag == 0)
		{
			if (dup2(px->info->fd[n - 1][0], STDIN_FILENO) < 0)
				ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		}
	}
	//fprintf(stderr, "he pasado por pipes\n");
}

/* 
	dup2 command input:
	if n = 1:  < (infile)
	if n = 2:  << (here_doc)
*/
void	ft_input_redirect(t_px *px)
{
	int	fd_in;
	
	//fprintf(stderr, "inp redir: %i\n", px->in_flag);
	if (px->in_flag == 1)
	{
		//fprintf(stderr, "redir <\n");
		fd_in = open(px->infile, O_RDONLY);
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		close(fd_in);
	}
	if (px->in_flag == 2)
	{
		//fprintf(stderr, "redir <<\n");
		write_here_doc_tmp(px);
		fd_in = open(".tmp", O_RDONLY);
		if (dup2(fd_in, STDIN_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		unlink(".tmp");
		close(fd_in);
	}
	//fprintf(stderr, "he pasado por redirect input\n");
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
		//printf("redir >\n");
		fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		close(fd_out);
	}
	if (px->out_flag == 2)
	{
		//printf("redir >>\n");
		fd_out = open(px->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (dup2(fd_out, STDOUT_FILENO) < 0)
			ft_error(DUPERR, NULL, 5); //ft_error_free_exit("dup error 1", NULL, px);
		close(fd_out);
	}
	//fprintf(stderr, "he pasado por redirect output\n");
}

/* 
	n = command index
*/
void	ft_child(t_px *px, int n)
{
	struct sigaction	sa;

	
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	//fprintf(stderr, "estoy en childs\n");
	if (px->info->cmd_amount > 1) 
		ft_fd_pipes(px, n); 
	if (px->in_flag > 0)
		ft_input_redirect(px); // open input file, dup - (<, <<)
	if (px->out_flag > 0)
		ft_output_redirect(px); // open output file, dup - (>, >>)
	ft_fd_close(px, px->info->cmd_amount - 1);
	sa.sa_handler = &ft_2nd_handler;
	sigaction(SIGQUIT, &sa, NULL);
	if (px->type == BIc)
	{
		ft_execbi_child(px);
		exit(1);			//provisional, liberar y cerrar mierdas
	}
	execve(px->path, px->full_cmd, NULL);
}


void	pipex(t_px *px)
{
	pid_t	pid;
	int		i;
	struct sigaction	sa;

	
	sa.sa_handler = &ft_2nd_handler;
	sigaction(SIGINT, &sa, NULL);
	//sigaction(SIGQUIT, &sa, NULL);
	ft_alloc_fd(px);
	if (!px->info->fd)
		return ;
	i = 0;
	while (i < px->info->cmd_amount)
	{
		if (px[i].type != BIp)
		{
			pid = fork();
			if (pid < 0)
			{
				ft_error(FORKERR, NULL, 4);
				return ;
			}
			if (pid == 0)
				ft_child(&px[i], i);
			ft_fd_close(px, i);
			waitpid(pid, &g_stat, 0);
			g_stat = WEXITSTATUS(g_stat);
		}
		else
			ft_fd_close(px, i);
		i++;
	}
	if (px->info->cmd_amount > 1)
		ft_free_fd(px);
}

/* -----------------GET COMMAND WITH PATH--------------------------- */



int	check_slash(char *str)
{
	int	i;
	int slash;

	slash = 0;
	i = 0;
	while (str[i]) //buscar si hay '/' en el str que llega
	{
		if (str[i] == '/')
			slash++;
		i++;
	}
	return (slash);
}

char	**get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])  
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return(ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

/* 
	Checks if cmd or /path/cmd exists.
	Returns (/path/cmd) allocated if so
	Returns (NULL) otherwise
*/
char	*get_cmd_or_cmdpath(char **env, char *str)
{
	int	i;
	char	**env_path;
	char	*aux;
	char	*path_and_cmd;

	env_path = NULL;
	i = 0;
	if (check_slash(str) > 0 && !access(str, F_OK)) // si hay '/' probar si es ruta + comando valido
	//if (check_slash(str) > 0)
		return (ft_strdup(str)); //BE CAREFUL check if str comes allocated!!!!!!
	else if (check_slash(str) == 0) 	// si no hay '/' comprobar si es un comando valido:
	{		// buscar path y splitearlo
		env_path = get_path(env);
		i = 0;
		while (env_path[i]) //ir probando paths y ver si ruta + (join) comando existe
		{
			aux = ft_strjoin(env_path[i++], "/");
			path_and_cmd = ft_strjoin(aux, str);
			free(aux);
			if (access(path_and_cmd, F_OK) == 0)
				return (ft_free_split(env_path), path_and_cmd);
			free(path_and_cmd);
		}
		ft_free_split(env_path);
	}
	return (NULL);
}
