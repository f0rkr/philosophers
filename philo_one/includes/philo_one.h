/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 06:55:20 by mashad            #+#    #+#             */
/*   Updated: 2021/05/06 16:39:32 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>

# define FORK 		101
# define EATING 	102
# define SLEEPING 	103
# define THINKING 	104
# define DIED 		105

# define EOL	'\0'
# define NEL	'\n'
# define STDIN	0
# define STDOUT 1
# define STDERR 2
# define ERROR  -1

typedef struct s_din_game
{
	t_philosopher	**t_philoso;
	int				nb_philosopher;

}				t_game;

typedef struct s_fork
{

}				t_fork;

typedef struct s_philosopher
{
	int		philo_id;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	t_fork	*f_fork;
	t_fork	*s_fork;
	pthread	philo_thd;
}				t_philosopher;


#endif