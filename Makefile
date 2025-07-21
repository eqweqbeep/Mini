
NAME = minishell
CC = gcc
CFLAGS = -g 

SRCS = main_program/minishell.c \
       main_program/signals.c \
       main_program/check_input.c \
       main_program/get_tokens.c \
       execution/execution.c \
       execution/ft_split.c \
       execution/utils.c \
       execution/path_extraction_utils.c \
       execution/exec_relative_absolute_path.c \
       execution/red_in_out.c \
       execution/heredoc.c \
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
	@rm -fv $(OBJS)

fclean: clean
	@rm -fv $(NAME)

re: fclean all
