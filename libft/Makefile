NAME = libft.a

SOURCES =	ft_atoi.c		\
			ft_atol.c		\
			ft_bzero.c		\
			ft_calloc.c		\
			ft_intlen.c		\
			ft_intlen_plus.c		\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isprint.c	\
			ft_itoa.c		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_printf.c			\
			ft_putendl_fd.c	\
			ft_split.c		\
			ft_strchr.c		\
			ft_strcmp.c		\
			ft_strdup.c		\
			ft_striteri.c	\
			ft_strjoin.c	\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_strlen_libft.c		\
			ft_strlen_plus.c	\
			ft_strmapi.c	\
			ft_strncmp.c	\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strtrim.c	\
			ft_substr.c		\
			ft_tolower.c	\
			ft_toupper.c	\
			functions1_printf.c	\
			functions2_printf.c	\
			get_next_line.c	\
			get_next_line_utils.c	\
			# get_next_line_bonus.c \
			# get_next_line_utils_bonus.c \
			# ft_lstnew.c		\
			# ft_lstadd_front.c\
			# ft_lstsize.c	\
			# ft_lstlast.c	\
			# ft_lstadd_back.c\
			# ft_lstdelone.c	\
			# ft_lstclear.c	\
			# ft_lstiter.c	\
			# ft_lstmap.c		\

OBJS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SILENT: