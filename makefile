# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 11:32:08 by mbatteux          #+#    #+#              #
#    Updated: 2023/07/17 11:32:10 by mbatteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CCC = minishell.c\
	utils.c \
	utils2.c \
	unset.c \
	prompt.c \
	sort_env.c \
	pwd.c \
	signal.c \
	export.c \
	echo.c\
	parser.c\
	parser2.c\
	parser3.c\

OOO = $(CCC:.c=.o)

FLAG = -Wall -Wextra -Werror

I = -Ilibft

LIBFT = $(I) -Llibft -lft

all: $(NAME)

$(NAME): $(OOO)
	make -C libft/
	cc $(OOO) $(LIBFT) $(FLAG) -o $(NAME) -lreadline -g3
.c.o:
	cc $(I) $(FLAG) -c $< -o ${<:.c=.o} -g3
clean:
	make clean -C libft/
	rm -f $(OOO)
fclean: clean
	make fclean -C libft/
	rm -f $(NAME)
re: fclean all
