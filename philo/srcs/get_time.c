/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:40:04 by mashad            #+#    #+#             */
/*   Updated: 2021/07/13 18:38:37 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

extern long long	timeInMilliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

extern	int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

extern int	check_eat_time(t_table *din_table)
{
	if (din_table->t_philoso[din_table->nb_philosopher - 1]->time_ate
		== din_table->number_of_times_each_philosopher_must_eat)
	{
		din_table->death = 1;
		return (1);
	}
	return (0);
}

extern	int	str_isdigit(char *string)
{
	int	p_count;

	p_count = 0;
	while (string[p_count] != '\0')
	{
		if (!ft_isdigit(string[p_count]))
			return (0);
		p_count++;
	}
	return (1);
}
