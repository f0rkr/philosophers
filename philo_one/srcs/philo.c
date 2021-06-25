/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/06/25 18:37:44 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_errors(int argc, char **argv)
{
	(void) argv;
	if (argc <= 1 || argc > 6)
		return (ERROR);
	write(1, "success\n", ft_strlen("success\n"));
	return (EXIT_SUCCESS);
}

t_philosopher	*init_philo(t_table *din_table)
{
	t_philosopher *philo;

	philo = (t_philosopher *) malloc(sizeof(t_philosopher) * 1);
	if (!philo)
		return (NULL);
	philo->din_table = din_table;
	return (philo);
}

/*
** Initailizing dining table variables 
*/
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
		din_table->t_philoso[philo_count] = init_philo(din_table);
		din_table->t_philoso[philo_count]->philo_id = philo_count + 1;
		philo_count++;
	}
	return (din_table);
}

void	din_destroy(t_table **din_table)
{
	pthread_mutex_destroy(&(*din_table)->t_mutex);
	return ;
}

/*
** This is the philosopher routine that threads execute
*/
void	*philosopher_routine(void *data)
{
	t_table *din_table;

	din_table = (t_table *) data;
	printf("%d is philo pid\n", din_table->t_philoso[din_table->inc_philo]->philo_id);
	printf("%d is ending\n", din_table->t_philoso[din_table->inc_philo]->philo_id);
	return (NULL);
}

/*
** Initializing threads and starting main loops for philosopher
*/
int	dining_init(int argc, char **argv)
{
	t_table *din_table;
	int		p_counter;

	p_counter = 0;
	din_table = init_table(argc, argv);
	if (!din_table)
		return (ERROR);
	while (p_counter < din_table->nb_philosopher)
	{
		if (pthread_create(&(din_table->t_philoso[p_counter]->philo_thd), NULL, &philosopher_routine, din_table) != 0)
			return (ERROR);
		p_counter++;
		if (din_table->inc_philo < din_table->nb_philosopher)
			din_table->inc_philo++;
		usleep(100);
	}
	pthread_mutex_destroy(&din_table->t_mutex);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	if (check_arg_errors(argc, argv) == ERROR)
		return (ERROR);
	if (dining_init(argc, argv) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}