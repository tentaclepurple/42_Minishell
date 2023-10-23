NAME = minichell
LIBNAME = libft.a
SRC = ./splitstr/split.c ./splitstr/clean_quotes.c ./splitstr/check_var.c  ./splitstr/correc_special.c ./parser/parser.c ./parser/iban.c ./terminal/terminal.c main.c \
		./error/error.c
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
READFLAG =  -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READINCLUDE = -I/Users/$(USER)/.brew/opt/readline/include
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ) $(LIBNAME)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS)   $(OBJ) $(LIBNAME) $(READFLAG)  -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

$(LIBNAME):
	@echo $(CURSIVE)$(GRAY) "     - Compiling LIBFT $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ../libft all
	@cp ../libft/libft.a $(LIBNAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

%.o: %.c
	$(CC) $(READINCLUDE) -c $(FLAGS) $^ -o $@

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@$(MAKE) -C ../libft clean
	@rm -rf $(OBJ)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME) And $(LIBNAME)..." $(NONE)
	@$(MAKE) -C ../libft fclean
	@rm -rf $(NAME) $(LIBNAME)

re: fclean all