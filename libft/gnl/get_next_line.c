/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:13:31 by jzubizar          #+#    #+#             */
/*   Updated: 2023/05/04 21:10:02 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../libft.h"

//Function to get the whole first line of str (Until \n or \0)
char	*ft_fst_line(char *str)
{
	unsigned int	i;
	char			*line;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

//Function that returns a pointer to the first 'c' char found. NULL if not found
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

//Function that takes out the first line of str
char	*ft_cut_str(char *str)
{
	int		i;
	int		len;
	char	*strt;
	char	*new_str;

	i = -1;
	if (str == NULL)
		return (NULL);
	if (ft_strchr(str, '\n'))
		strt = ft_strchr(str, '\n') + 1;
	else
	{
		free(str);
		return (NULL);
	}
	len = ft_strlen(strt);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (strt[++i])
		new_str[i] = strt[i];
	new_str[i] = '\0';
	free (str);
	return (new_str);
}

//Function to add the readed values to str until a line is 
//complete or the end of the file
char	*ft_read_add(char *buf, char *str, int fd)
{
	ssize_t	rd;

	rd = 1;
	while (!ft_isin_str(str, '\n') && rd)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
		{
			if (str)
			{
				free (str);
				str = NULL;
			}
			return (NULL);
		}
		buf[rd] = '\0';
		str = ft_strbuf_join(str, buf);
	}
	return (str);
}

//Funtion that returns the next readed line of the fd input
char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*str;
	char		*line;

	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_add(buf, str, fd);
	if (!str)
		return (NULL);
	line = ft_fst_line(str);
	str = ft_cut_str(str);
	return (line);
}
/* 
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	line = get_next_line(fd);
	printf("%s", line);
	free (line);
	return (0);
} */
