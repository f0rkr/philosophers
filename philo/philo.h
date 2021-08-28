/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:39:08 by mashad            #+#    #+#             */
/*   Updated: 2021/08/27 17:51:05 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define ERROR		-1
# define OFLOW		-2
# define STDIN		0
# define STDOUT		1
# define STDERR		2
# define GOOD		3
# define ARGVALUE	4
# define EOL		'\0'

/*
 ** Philosopher struct
 ** Each philospher shoud have the same options: id[pid] number_of_ate[nta]
 ** last_time_ate[lta]
*/

typedef struct s_philo
{
	pthread_mutex_t	eating;
	pthread_t		thd_philo;
	pthread_t		myhem;
	int				pid;
	int				nta;
	int				lf;
	int				rf;
	int				is_eating;
	long long		lta;
	struct s_din	*din_table;
}				t_philo;

/*
 ** Each program should have the same options: number_of_philosophers[nop]
 ** time_to_die[ttd] time_to_eat[tte]
 ** time_to_sleep[tts] [number_of_times_each_philosopher_must_eat[ntpme]]
 ** starting_time[st]
 */

typedef struct s_din
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			**philos;
	long long		st;
	int				death;
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				ntpme;
}	t_din;

t_philo	**initialize_philosphers(t_din *din_table);
pthread_mutex_t							*initialize_forks(t_din *din_table);
int		ft_is_number(char *string);
long long			ft_time_in_ms(void);
int		ft_atoi(const char *str);
void	*start_routine(void *data);
void	print_status(t_din *din_table, int pid, char *string);

#endif
