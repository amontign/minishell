NAME = minishell

SOURCES =	./sources/main.c										\
			./sources/print_cmds.c									\
			./sources/lexing/lexing.c								\
			./sources/lexing/split_cmd.c							\
			./sources/lexing/utils_lexing.c							\
			./sources/lexing/utils_list.c							\
			./sources/builtins/echo.c								\
			./sources/builtins/cd.c									\
			./sources/builtins/unset.c								\
			./sources/expand/expand.c								\
			./sources/expand/pre_expand_dollars.c					\
			./sources/expand/expand_dollars.c						\
			./sources/expand/utils_expand_dollars.c					\
			./sources/expand/expand_cmd_quotes.c					\
			./sources/expand/expand_redir_quotes.c					\
			./sources/expand/utils_pre_expand_dollar.c				\
			./sources/expand/split_args.c							\
			./sources/getenv/create_env.c							\
			./sources/getenv/utils_create_env.c						\
			./sources/non_interactive_sh/non_interactive.c			\
			./sources/non_interactive_sh/find_path.c				\
			./sources/non_interactive_sh/utils_non_interactive.c	\
			./sources/execution/main_execution.c					\
			./sources/execution/cmd_struct_utils.c					\
			./sources/execution/execution_utils.c					\
			./sources/execution/cmd_to_struct.c						\
			# ./sources/main_tester.c								\

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

OBJETS = $(SOURCES:.c=.o)

LIB = @make -C ./libft

all: $(NAME)

$(NAME): $(OBJETS)
		$(LIB)
		$(CC) $(CFLAGS) $(OBJETS) libft/libft.a -o $(NAME) -lreadline

clean:
		@rm -f $(OBJETS)

fclean: clean
		@rm -f $(NAME)
		@cd ./libft && make fclean

re: fclean all

.PHONY: all clean fclean re
.SILENT: