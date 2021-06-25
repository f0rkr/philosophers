/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:26:59 by mashad            #+#    #+#             */
/*   Updated: 2021/06/25 16:16:59 by mashad           ###   ########.fr       */
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