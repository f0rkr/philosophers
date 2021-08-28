/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:38:13 by mashad            #+#    #+#             */
/*   Updated: 2021/08/27 20:37:22 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** Mainly check arguments validity and return acceptance
 ** In case of an error a -1 is returned
 */
int	check_arg_validity(int argSize, char **args)
{
	int	i;

	i = 1;
	if (argSize - 1 < ARGVALUE || argSize - 1 > 6)
		return (ERROR);
	while (i < argSize)
	{
		if (args[i][0] == '-' && ft_is_number(args[i]) != GOOD)
			return (ERROR);
		i++;
	}
	return (GOOD);
}

/*
 ** Parse arguments into a valid struct
 ** Which we will use later
 */
t_din	*fill_table(int argSize, char **args)
{
	t_din	*din_table;
	int		counter;

	counter = 1;
	din_table = (t_din *) malloc(sizeof(t_din) * 1);
	if (din_table == NULL)
		return (NULL);
	din_table->nop = ft_atoi(args[counter++]);
	din_table->ttd = ft_atoi(args[counter++]);
	din_table->tte = ft_atoi(args[counter++]);
	din_table->tts = ft_atoi(args[counter++]);
	din_table->ntpme = -1;
	din_table->death = 1;
	if (argSize - 1 == 5)
		din_table->ntpme = ft_atoi(args[counter]);
	din_table->forks = initialize_forks(din_table);
	if (din_table->forks == NULL)
		return (NULL);
	din_table->philos = initialize_philosphers(din_table);
	if (din_table->philos == NULL || din_table->nop == 0)
		return (NULL);
	if (pthread_mutex_init(&din_table->write, 0) != 0)
		return (NULL);
	return (din_table);
}

/*
 ** Mr mayhem check for a reason to kill
 ** one of the philospher either their
 ** time to die or number_of_times_each_philosopher_must_eat
 ** Each philosopher has it's own death master
 */
void	*mr_mayhem(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->din_table->death)
	{
		if (!philo->is_eating
			&& ft_time_in_ms() - philo->lta >= philo->din_table->ttd)
		{
			pthread_mutex_lock(&philo->eating);
			print_status(philo->din_table, philo->pid, "died\n");
			philo->din_table->death = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->din_table->philos[philo->din_table->nop - 1]->nta
			== philo->din_table->ntpme)
			philo->din_table->death = 0;
		usleep(100);
	}
	return (NULL);
}

/*
 ** Initialize threads and start philospher
 */
int	start_threads(t_din *din_table)
{
	int	i;

	i = 0;
	din_table->st = ft_time_in_ms();
	while (i < din_table->nop)
	{
		din_table->philos[i]->lta = ft_time_in_ms();
		if (pthread_create(&din_table->philos[i]->thd_philo, NULL,
			&start_routine, (void *)din_table->philos[i]) != 0)
			return (ERROR);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < din_table->nop)
	{
		if (pthread_create(&din_table->philos[i]->myhem, NULL, &mr_mayhem,
		(void *)din_table->philos[i]) != 0)
			return (ERROR);
		usleep(100);
		i++;
	}
	while (din_table->death)
		continue ;
	return (GOOD);
}

int	main(int argc, char **argv)
{
	t_din	*din_table;
	int		p_counter;

	p_counter = 0;
	din_table = NULL;
	if (check_arg_validity(argc, argv) != GOOD)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (ERROR);
	}
	din_table = fill_table(argc, argv);
	if (din_table == NULL)
		return (ERROR);
	if (start_threads(din_table) != GOOD)
		return (ERROR);
	return (GOOD);
}
