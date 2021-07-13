# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 06:28:55 by mashad            #+#    #+#              #
#    Updated: 2021/07/13 18:58:17 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=gcc
THREADSFLAGS=-pthread
DEBUG=-g
SANITIZE=-fsanitize=address
FLAGS=-Wall -Werror -Wextra
RM=rm -rf
INCLUDES= includes
SRCS= srcs/philo.c srcs/get_time.c srcs/philo_utils.c srcs/routine_utils.c


all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(THREADSFLAGS) $(SRCS) -I $(INCLUDES) -o $(NAME)

clean:
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all
	@echo "Cleaning cache..."
	@echo "Recompiling code..."