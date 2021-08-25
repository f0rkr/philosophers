# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 11:06:15 by mashad            #+#    #+#              #
#    Updated: 2021/08/25 08:46:16 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_bonus
CC=gcc
FLAGS=-Wall -Werror -Wextra -pthread
SRCS=philo_bonus.c philo_bonus_utils.c philo_bonus_routines.c philo_bonus_tools.c


all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
