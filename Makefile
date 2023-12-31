NAME = minishell

SOURCES =	./sources/main.c										\
			./sources/lexing/lexing.c								\
			./sources/lexing/split_cmd.c							\
			./sources/lexing/utils_lexing.c							\
			./sources/lexing/utils_list.c							\
			./sources/lexing/utils_list_2.c							\
			./sources/builtins/echo.c								\
			./sources/builtins/pwd.c								\
			./sources/builtins/export.c								\
			./sources/builtins/export_verif.c						\
			./sources/builtins/env.c								\
			./sources/builtins/exit.c								\
			./sources/builtins/cd.c									\
			./sources/builtins/unset.c								\
			./sources/expand/expand.c								\
			./sources/expand/expand_2.c								\
			./sources/expand/pre_expand_dollars.c					\
			./sources/expand/expand_dollars.c						\
			./sources/expand/utils_expand_dollars.c					\
			./sources/expand/expand_cmd_quotes.c					\
			./sources/expand/expand_redir_quotes.c					\
			./sources/expand/utils_pre_expand_dollar.c				\
			./sources/expand/split_args.c							\
			./sources/getenv/create_env.c							\
			./sources/getenv/utils_create_env.c						\
			./sources/execution/main_execution.c					\
			./sources/execution/main_execution2.c					\
			./sources/execution/main_execution_utils.c				\
			./sources/execution/child_execution.c					\
			./sources/execution/builtins_execution.c				\
			./sources/execution/cmd_struct_utils.c					\
			./sources/execution/execution_utils.c					\
			./sources/execution/cmd_to_struct.c						\
			./sources/execution/heredoc.c							\
			./sources/execution/struct_redirects.c					\
			./sources/execution/struct_paths.c						\
			./sources/execution/struct_custom_path.c				\
			./sources/parsing/parsing.c								\
			./sources/parsing/parsing_utils.c						\
			./sources/signals/main_signals.c						\

CC = cc

CFLAGS = -Wall -Werror -Wextra

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