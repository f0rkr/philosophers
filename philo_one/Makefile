# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 06:28:55 by mashad            #+#    #+#              #
#    Updated: 2021/04/27 07:27:20 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_one
CC=gcc
THREADSFLAGS=-lthread
FLAGS=-Wall -Werror -Wextra
RM=rm -rf
INCLUDES= includes
SRCS= srcs/philo_one.c

all: $(NAME):
	@echo "Compiling code..."

$(NAME): $(SRCS)
	@$(CC) $(FLAGS) $(THREADSFLAGS) $(SRCS) -I $(INCLUDES) -o $(NAME)

clean:
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all
	@echo "Cleaning cache..."
	@echo "Recompiling code..."