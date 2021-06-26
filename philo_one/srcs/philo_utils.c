/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:26:59 by mashad            #+#    #+#             */
/*   Updated: 2021/06/25 21:22:00 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_print_status(int philo_status)
{
	if (philo_status == SLEEPING)
		printf("X is Sleeping.\n");
	else if (philo_status == EATING)
		printf("X is Eating.\n");
	else if (philo_status == THINKING)
		printf("X is Thinking.\n");
	return ;
}

t_philosopher	*init_philo()
{
	t_philosopher *philo;

	philo = (t_philosopher *) malloc(sizeof(t_philosopher) * 1);
	if (!philo)
		return (NULL);
	return (philo);
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*din_table;
	int		philo_count;

	philo_count = 0;
	din_table = (t_table *)malloc(sizeof(t_table) * 1);
	if (!din_table)
		return (NULL);
	pthread_mutex_init(&din_table->t_mutex, NULL);
	din_table->nb_philosopher = ft_atoi(argv[1]);
	din_table->time_to_die = ft_atoi(argv[2]);
	din_table->time_to_eat = ft_atoi(argv[3]);
	din_table->t_philoso = (t_philosopher **) malloc(sizeof(t_philosopher *) * din_table->nb_philosopher + 1);
	din_table->number_of_times_each_philosopher_must_eat = -1;
	din_table->inc_philo = 0;
	if (argc == 6)
		din_table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (!din_table->t_philoso)
		return (NULL);
	while (philo_count < din_table->nb_philosopher)
	{
		din_table->t_philoso[philo_count] = init_philo();
		din_table->t_philoso[philo_count]->philo_id = philo_count;
		philo_count++;
	}
	return (din_table);
}

size_t	ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != EOL)
		len++;
	return (len);
}

int		ft_atoi(const char *str)
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