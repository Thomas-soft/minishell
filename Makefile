# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttofil <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 12:54:00 by ttofil            #+#    #+#              #
#    Updated: 2023/11/08 19:08:28 by ttofil           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = parsing/split_master.c \
	parsing/split_word.c \
	parsing/count_token.c \
	parsing/len_token.c \
	parsing/get_token.c \
	parsing/count_word.c \
	parsing/len_word.c \
	parsing/get_word.c \
	parsing/quotes_and_pr.c \
	parsing/put_types.c \
	parsing/env.c \
	parsing/len_env_token.c \
	parsing/get_env_token.c \
	parsing/verif.c \
	parsing/free.c \
	parsing/sort_tokens.c \
	parsing/sort_count_tokens.c \
	parsing/len_cmd_sort.c \
	parsing/get_sort_tokens.c \
	parsing/get_sort_cmd_tokens.c \
	parsing/get_cmd_path.c \
	parsing/utils.c \
	exec/ft_echo.c \
	exec/ft_cd.c \
	exec/ft_pwd.c \
	exec/ft_export.c \
	exec/ft_unset.c \
	exec/ft_env.c \
	exec/ft_exit.c \
	exec/exec.c \
	exec/signal.c \
	exec/heredoc.c \
	exec/pop_list.c \
	exec/push_list.c \
	exec/list_utils.c \
	exec/redirections.c \
	exec/handle_cmd.c \
	exec/execve_cmd.c \
	exec/utils.c \
	exec/utils2.c \
	minishell.c

OBJ = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	@make -C Libft
	@$(CC) $(OBJ) $(CFLAGS) -I Libft Libft/libft.a -lreadline -o $(NAME)

all: ${NAME}

clean:
	@make clean -C Libft
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C Libft
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
