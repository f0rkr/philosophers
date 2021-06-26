/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/06/26 17:14:48 by mashad           ###   ########.fr       */
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
	while (1)
	{
		p_eat(din_table);
		p_think(din_table);
		p_sleep(din_table);
	}
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