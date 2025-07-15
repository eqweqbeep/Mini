
NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main_program/minishell.c \
       execution/execution.c \
       execution/ft_split.c \
       execution/utils.c \
       builtins/builtins.c \
       builtins/ft_echo.c \
       builtins/ft_cd.c \
       builtins/ft_pwd.c \
       builtins/ft_env.c \
       builtins/ft_exit.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
