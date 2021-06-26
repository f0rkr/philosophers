/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/06/26 01:51:56 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_errors(int argc, char **argv)
{
	(void) argv;
	if (argc <= 1 || argc != 5 || argc > 6)
		return (ERROR);
	write(1, "success\n", ft_strlen("success\n"));
	return (EXIT_SUCCESS);
}

/*
** ALLOCATING AND INITIALIZING MAIN DINING TABLE STRUCTURE
** IN CASE OF FAIL RETURN NULL
** OTHERWISE IT RETURNS ADDRESS OF THE DINING TABLE STRUCTURE
*/

void	din_destroy(t_table **din_table)
{
	pthread_mutex_destroy(&(*din_table)->t_mutex);
	return ;
}

/*
** THIS PHILOSPHER ROUTINE FUNCTION THAT BEING EXECUTED BY THREADS
*/
void	*philosopher_routine(void *data)
{
	t_table *din_table;

	din_table = (t_table *) data;
	pthread_mutex_lock(&din_table->t_mutex);
	printf("%d is philo pid\n", din_table->t_philoso[din_table->inc_philo]->philo_id + 1);
	printf("%d is ending\n", din_table->t_philoso[din_table->inc_philo++]->philo_id + 1);
	pthread_mutex_unlock(&din_table->t_mutex);
	usleep(100);
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
		if (pthread_create(&(din_table->t_philoso[p_counter]->philo_thd), NULL, &philosopher_routine, din_table) != 0)
			return (ERROR);
		p_counter++;
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