# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 15:43:13 by mbatteux          #+#    #+#              #
#    Updated: 2023/04/17 15:43:14 by mbatteux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): fichier_o
	ar rc libft.a ft_*.o
fichier_o:
	gcc -c ft_*.c $(FLAG)
clean:
	rm -rf ft_*.o
fclean: clean
	rm -rf libft.a
re: fclean all

