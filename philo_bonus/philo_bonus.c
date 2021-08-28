/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:38:13 by mashad            #+#    #+#             */
/*   Updated: 2021/08/28 09:43:48 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (argSize - 1 == 5)
		din_table->ntpme = ft_atoi(args[counter]);
	if (initialize_sems(din_table) != GOOD)
		return (NULL);
	din_table->philos = initialize_philosphers(din_table);
	if (din_table->philos == NULL || din_table->nop == 0)
		return (NULL);
	return (din_table);
}

/*
 ** Await for child to finish
 ** Then automatically kill them
 */
void	childs_reaper(t_din *din_table)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < din_table->nop)
	{
		j = 0;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) || WIFSIGNALED(status))
			while (j < din_table->nop)
				kill(din_table->philos[j++]->fpid, SIGKILL);
		i++;
	}
	return ;
}

/*
 ** Initialize threads and start philospher
 */
int	start_threads(t_din *din_table)
{
	int	i;

	i = 0;
	if (din_table->ntpme != ERROR && pthread_create(&din_table->eatcounter,
		NULL, &eat_reaper, (void *)din_table) != 0)
		return (ERROR);
	din_table->st = ft_time_in_ms();
	while (i < din_table->nop)
	{
		din_table->philos[i]->fpid = fork();
		din_table->philos[i]->lta = ft_time_in_ms();
		if (din_table->philos[i]->fpid == 0)
		{
			if (pthread_create(&din_table->philos[i]->myhem, NULL, &mr_mayhem,
				(void *)din_table->philos[i]) != 0)
				return (ERROR);
			start_routine(din_table->philos[i]);
			exit(1);
		}
		usleep(100);
		i++;
	}
	childs_reaper(din_table);
	return (GOOD);
}

int	main(int argc, char **argv)
{
	t_din		*din_table;
	int			p_counter;

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
