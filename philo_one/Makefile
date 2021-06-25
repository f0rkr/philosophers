# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mashad <mashad@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 06:28:55 by mashad            #+#    #+#              #
#    Updated: 2021/06/25 17:53:28 by mashad           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo
CC=gcc
THREADSFLAGS=-pthread
DEBUG=-g
FLAGS=-Wall -Werror -Wextra
RM=rm -rf
INCLUDES= includes
SRCS= srcs/philo.c srcs/philo_utils.c

all: $(NAME)
	@echo "Compiling code..."

$(NAME): $(SRCS)
	$(CC) $(FLAGS) $(DEBUG) $(THREADSFLAGS) $(SRCS) -I $(INCLUDES) -o $(NAME)

clean:
	@$(RM) *.o

fclean: clean
	@$(RM) $(NAME)

re: fclean all
	@echo "Cleaning cache..."
	@echo "Recompiling code..."