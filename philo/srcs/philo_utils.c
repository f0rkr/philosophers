/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:26:59 by mashad            #+#    #+#             */
/*   Updated: 2021/06/30 16:36:53 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** ALLOCATING N PHILOSOPHER INTO A DOUBLE POINTER
** FILL IMPORTANT VARIABLES
** REATURN DOUBLE POINTER TO PHILOSOPHER
*/
t_philosopher	**init_philo(t_table *din_table)
{
	t_philosopher	**philosopher;
	int				philo_count;

	philo_count = 0;
	philosopher = (t_philosopher **) malloc(sizeof(t_philosopher *)
			* din_table->nb_philosopher + 1);
	if (!philosopher)
		return (NULL);
	while (philo_count < din_table->nb_philosopher)
	{
		philosopher[philo_count] = (t_philosopher *)
			malloc(sizeof(t_philosopher) * 1);
		if (!philosopher[philo_count])
			return (NULL);
		philosopher[philo_count]->din_table = din_table;
		philosopher[philo_count]->time_ate = 0;
		philosopher[philo_count]->num_time_eat = 0;
		philosopher[philo_count]->is_eating = 0;
		philosopher[philo_count]->philo_id = philo_count;
		philosopher[philo_count]->l_fork = philo_count;
		philosopher[philo_count]->r_fork = philo_count + 1
			% din_table->nb_philosopher;
		philo_count++;
	}
	return (philosopher);
}

/*
** ALLOCATING AND INITIALIZING MAIN DINING TABLE STRUCTURE
** IN CASE OF FAIL RETURN NULL
** OTHERWISE IT RETURNS ADDRESS OF THE DINING TABLE STRUCTURE
*/
t_table	*init_table(int argc, char **argv)
{
	t_table		*din_table;
	int			philo_count;

	philo_count = 0;
	din_table = (t_table *)malloc(sizeof(t_table) * 1);
	if (!din_table)
		return (NULL);
	pthread_mutex_init(&din_table->write_mutex, NULL);
	din_table->nb_philosopher = ft_atoi(argv[1]);
	din_table->time_to_die = ft_atoi(argv[2]);
	din_table->time_to_eat = ft_atoi(argv[3]);
	din_table->time_to_sleep = ft_atoi(argv[4]);
	din_table->death = 0;
	din_table->t_forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * din_table->nb_philosopher);
	while (philo_count < din_table->nb_philosopher)
		pthread_mutex_init(&din_table->t_forks[philo_count++], NULL);
	din_table->number_of_times_each_philosopher_must_eat = -1;
	din_table->inc_philo = 0;
	if (argc == 6)
		din_table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (!din_table->t_philoso)
		return (NULL);
	din_table->t_philoso = init_philo(din_table);
	return (din_table);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != EOL)
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		r;
	int		s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			r = r * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (s * r);
}
