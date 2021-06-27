/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/06/27 18:08:38 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** CHECKING FOR ARG ERRORS AND VALIDITY
** Before run time
*/
int	check_arg_errors(int argc, char **argv)
{
	(void) argv;
	if (argc <= 1 || argc > 6)
		return (ERROR);
	return (EXIT_SUCCESS);
}


void	din_destroy(t_table **din_table)
{
	pthread_mutex_destroy(&(*din_table)->write_mutex);
	return ;
}

/*
** THIS PHILOSPHER ROUTINE FUNCTION THAT BEING EXECUTED BY THREADS
*/
void	*philosopher_routine(void *data)
{
	t_philosopher *philo;

	philo = (t_philosopher *) data;
	philo->last_time_eat = timeInMilliseconds();
	philo->din_table->p_time = timeInMilliseconds();
	while (1)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
		usleep(100);
	}
	return (NULL);
}

/*
** MAIN FUNCTION FOR CREATING THREADS AND STARTING THE ROUTINES
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
		if (pthread_create(&(din_table->t_philoso[p_counter]->philo_thd), NULL, &philosopher_routine, din_table->t_philoso[p_counter]) != 0)
			return (ERROR);
		p_counter++;
		usleep(100);
	}
	kami_visor(din_table);
	din_destroy(&din_table);
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