/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/07/06 19:08:43 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** CHECKING FOR ARG ERRORS AND VALIDITY
** Before run time
*/
int	check_arg_errors(int argc, char **argv)
{
	int	counter;

	counter = 1;
	if (argc < 5 || argc > 6)
		return (ERROR);
	while (counter < argc)
	{
		if (!ft_isdigit(argv[counter][0]))
			return (ERROR);
		counter++;
	}
	return (EXIT_SUCCESS);
}

void	din_destroy(t_table **din)
{
	int		philo_count;
	t_table	*din_table;

	din_table = *din;
	philo_count = 0;
	usleep(200000);
	while (philo_count < din_table->nb_philosopher)
	{
		free(din_table->t_philoso[philo_count]);
		din_table->t_philoso[philo_count] = NULL;
		pthread_mutex_destroy(&din_table->t_forks[philo_count]);
		philo_count++;
	}
	pthread_mutex_destroy(&din_table->write_mutex);
	free(din_table->t_philoso);
	din_table->t_philoso = NULL;
	free(din_table->t_forks);
	din_table->t_forks = NULL;
	free(*din);
	*din = NULL;
	return ;
}

/*
** THIS PHILOSPHER ROUTINE FUNCTION THAT BEING EXECUTED BY THREADS
*/
void	*philosopher_routine(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) data;
	philo->last_time_eat = timeInMilliseconds();
	philo->din_table->p_time = timeInMilliseconds();
	while (philo->din_table->death != 1)
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
	t_table		*din_table;
	int			p_counter;

	p_counter = 0;
	din_table = init_table(argc, argv);
	if (!din_table)
		return (ERROR);
	while (p_counter < din_table->nb_philosopher)
	{
		if (pthread_create(&(din_table->t_philoso[p_counter]->philo_thd), NULL,
				&philosopher_routine, din_table->t_philoso[p_counter]) != 0)
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
	{
		printf("Error: Bad arguments.\n");
		return (ERROR);
	}
	if (dining_init(argc, argv) == ERROR)
		return (ERROR);
	return (EXIT_SUCCESS);
}
