# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 11:06:15 by mashad            #+#    #+#              #
#    Updated: 2021/08/22 11:11:27 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=gcc
FLAGS=-Wall -Werror -Wextra -pthread
SRCS=philo.c philo_utils.c philo_routines.c


all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
