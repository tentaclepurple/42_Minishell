/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzubizar <jzubizar@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:34:23 by jzubizar          #+#    #+#             */
/*   Updated: 2023/08/03 11:26:00 by jzubizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<stdlib.h>
# include<unistd.h>
# include<stdarg.h>
# include<stdint.h>
# include<fcntl.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
//Next
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
//Special
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
//Bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list	*lst);
t_list	*ft_lstlast(t_list	*lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//Printf
typedef struct s_flag
{
	int	zeros;
	int	justify;
	int	precision;
	int	precwidth;
	int	width;
	int	hash;
	int	space;
	int	plus;
}				t_flag;

int		ft_putunbr_fd(unsigned int n, int fd, t_flag flags);
int		ft_putxnbr_fd(unsigned int n, t_flag flags);
int		ft_putxmnbr_fd(unsigned int n, t_flag flags);
int		ft_putxptr_fd(void *n, int fd, t_flag flags);
size_t	ft_pfstrlen(const char *s);
int		ft_pfputstr_fd(const char *s, int fd);
char	ft_is_type(char c);
int		ft_printf(const char *str, ...);
int		ft_pfputnbr_fd(int n, int fd, t_flag flags);
int		ft_pfputargstr_fd(const char *s, int fd, t_flag flags);
int		ft_print_nbr(char *nbr, t_flag flags, int n);
int		ft_precision_nul(t_flag *flags);
int		ft_print_char_fd(char c, t_flag flags, int fd);
t_flag	ft_flags_zeros(void);
int		ft_process_flags(int i, t_flag *flags, const char *str);
int		ft_print_width(int tot_width, int filled, int zeros);


//Get Next Line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_isin_str(char *str, char ch);
size_t	ft_strlen(const char *s);
char	*ft_strbuf_join(char *s1, char const *s2);
char	*ft_fst_line(char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_cut_str(char *str);
char	*get_next_line(int fd);

#endif
