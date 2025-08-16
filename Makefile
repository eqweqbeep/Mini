
NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = main_program/minishell.c \
       main_program/expand_utils.c \
       main_program/expand.c\
       main_program/ft_alloc.c\
       main_program/ft_getenv.c\
       main_program/linked_list.c\
       main_program/input_analysis.c\
       main_program/list.c\
       main_program/print.c\
       main_program/static_functions.c \
       main_program/ft_utils.c \
       main_program/check_input.c \
       main_program/get_tokens.c \
       main_program/signals.c \
       main_program/exec_relative_absolute_path.c\
       main_program/path_extraction_utils.c \
       builtins/builtins.c \
       builtins/ft_echo.c \
       builtins/ft_cd.c \
       builtins/ft_pwd.c \
       builtins/ft_env.c \
       builtins/ft_exit.c \
       builtins/ft_export.c \
       builtins/ft_unset.c \
       main_program/utils.c \
       main_program/ft_split.c \
       main_program/execution.c \
       main_program/red_in_out.c \
       main_program/heredoc.c

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
