NAME = libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
SRC = lib/ft_isalpha.c lib/ft_isdigit.c lib/ft_isalnum.c lib/ft_isascii.c lib/ft_isprint.c lib/ft_strlen.c \
lib/ft_memset.c lib/ft_bzero.c lib/ft_memcpy.c lib/ft_memmove.c lib/ft_strlcpy.c lib/ft_strlcat.c lib/ft_toupper.c \
lib/ft_tolower.c lib/ft_strchr.c lib/ft_strrchr.c lib/ft_strncmp.c lib/ft_memchr.c lib/ft_memcmp.c lib/ft_strnstr.c \
lib/ft_atoi.c lib/ft_calloc.c lib/ft_strdup.c lib/ft_substr.c lib/ft_strjoin.c lib/ft_strtrim.c lib/ft_split.c \
lib/ft_itoa.c lib/ft_strmapi.c lib/ft_striteri.c lib/ft_putchar_fd.c lib/ft_putstr_fd.c lib/ft_putendl_fd.c \
lib/ft_putnbr_fd.c lib/ft_lstnew.c lib/ft_lstadd_front.c lib/ft_lstsize.c lib/ft_lstlast.c lib/ft_lstadd_back.c \
lib/ft_lstdelone.c lib/ft_lstclear.c lib/ft_lstiter.c lib/ft_lstmap.c
SRCPF = printf/ft_printf.c printf/ft_putunbr.c printf/ft_putxnbr.c printf/ft_putxptr.c printf/ft_putXmnbr.c \
printf/ft_printf_func.c printf/ft_pfputstr.c printf/ft_pfputnbr.c printf/ft_pfflags.c printf/ft_pfputchar.c printf/ft_pfputnbr_aux.c
SRCGNL = gnl/get_next_line.c gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)
OBJPF = $(SRCPF:.c=.o)
OBJGNL = $(SRCGNL:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJPF) $(OBJGNL) libft.h
	ar -crs $(NAME) $(OBJ) $(OBJPF) $(OBJGNL)
	$(RM) $(OBJ) $(OBJPF) $(OBJGNL)

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ) $(OBJPF) $(OBJGNL)

fclean: clean
	$(RM) $(NAME)

re: fclean all
