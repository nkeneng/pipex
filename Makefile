NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

SRCS = main.c includes/command_execution.c includes/io_handling.c includes/pipe_management.c includes/process_management.c includes/resource_management.c includes/utils.c
SRCS_BONUS = main_bonus.c includes/command_execution.c includes/io_handling.c includes/pipe_management.c includes/process_management.c includes/resource_management.c includes/utils.c

LIBFT = -Llibft -lft

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: submodules libft $(NAME)
bonus: submodules libft $(NAME_BONUS)
valgrind: all
	# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) a "grep world" "wc -l" b
	# valgrind --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --track-origins=yes ./$(NAME) basic.txt "cat -e" "nonexistingcommand" outfile
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) basic.txt "cat -e" "" outfile

run: all
	./$(NAME) infile.out "grep world" "wc -l" outfile.out

submodules:
	if [ ! -d "libft" ]; then \
		mkdir libft; \
	fi
	if [ -z "$(shell ls -A libft)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		git submodule init && git submodule update --recursive; \
	fi
	if [ -z "$(shell ls -A libft/ft_printf)" -o -z "$(shell ls -A libft/get_next_line)" ]; then \
		echo "libft submodule not initialized, initializing..."; \
		cd libft && git submodule init && git submodule update --recursive; \
	fi

libft:
	$(MAKE) -C libft

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re submodules libft test bonus
