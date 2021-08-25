/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:39:08 by mashad            #+#    #+#             */
/*   Updated: 2021/08/25 08:43:24 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
#	include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

# define ERROR		-1
# define OFLOW		-2
# define STDIN 		0
# define STDOUT 	1
# define STDERR		2
# define GOOD			3
# define ARGVALUE 4
# define EOL 			'\0'
# define S_PERM		(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

/*
** Philosopher struct
** Each philospher shoud have the same options: id[pid] number_of_ate[nta]
** last_time_ate[lta]
*/

typedef struct	s_philo
{
	int							pid;
	int 						fpid;
	int							nta;
	int 						eating;
	pthread_t				thd_philo;
	sem_t 					*forks;
	long long				lta;
	struct s_din		*din_table;
}				t_philo;

/*
** Each program should have the same options: number_of_philosophers[nop]
** time_to_die[ttd] time_to_eat[tte]
** time_to_sleep [number_of_times_each_philosopher_must_eat[ntpme]]
** starting_time[st]
*/

typedef struct 	s_din
{
	t_philo			**philos;
	sem_t				*forks;
	sem_t				*write;
	sem_t				*death;
	pthread_t		*myhem;
	int 				nop;
	int 				ttd;
	int					tte;
	int					tts;
	int					ntpme;
	long long		st;

}								t_din;


t_philo   				**initialize_philosphers(t_din *din_table);
int 							initialize_sems(t_din *din_table);
int								ft_is_number(char *string);
long long					ft_time_in_ms();
int								ft_atoi(const char *str);
void  						*start_routine(void *data);
void    					print_status(t_din  *din_table, int pid, char *string);
void							ft_putnbr_fd(int n, int fd);
#endif
