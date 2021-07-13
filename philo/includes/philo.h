/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 06:55:20 by mashad            #+#    #+#             */
/*   Updated: 2021/07/13 18:33:53 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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
	int					l_fork;
	int					r_fork;
	pthread_t			philo_thd;
	int					num_time_eat;
	long long			last_time_eat;
	int					is_eating;
	int					time_ate;
	struct s_din_table	*din_table;
}				t_philosopher;

typedef struct s_din_table
{
	t_philosopher	**t_philoso;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*t_forks;
	int				time_to_die;
	int				time_to_eat;
	int				death;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				nb_philosopher;
	int				inc_philo;
	long long		p_time;
}				t_table;

size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
t_table			*init_table(int argc, char **argv);
t_philosopher	**init_philo( t_table *din_table );
void			p_eat(t_philosopher *philo);
void			p_think(t_philosopher *philo);
void			p_sleep(t_philosopher *philo);
void			kami_visor(t_table *din_table);
long long		timeInMilliseconds(void);
int				ft_isdigit(int c);
int				check_eat_time(t_table *din_table);
int				str_isdigit(char *string);

#endif
