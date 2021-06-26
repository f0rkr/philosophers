/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 06:55:20 by mashad            #+#    #+#             */
/*   Updated: 2021/06/25 21:06:03 by mashad           ###   ########.fr       */
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

typedef struct s_philosopher
{
	int					philo_id;
	pthread_t			f_fork;
	pthread_t			s_fork;
	pthread_t			philo_thd;
}				t_philosopher;

typedef struct s_din_table
{
	t_philosopher	**t_philoso;
	pthread_mutex_t	t_mutex;
	pthread_t		**t_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				nb_philosopher;
	int				inc_philo;
}				t_table;


size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
t_table			*init_table(int argc, char **argv);
t_philosopher	*init_philo( void );
#endif