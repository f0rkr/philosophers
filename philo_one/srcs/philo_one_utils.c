/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:26:59 by mashad            #+#    #+#             */
/*   Updated: 2021/04/28 05:44:14 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	p_print_status(int flag)
{
	printf("X is eating.\n")
}

size_t	ft_strlen(const char *str)
{
	size_t len;

	len = 0;
	while (str[len] != EOL)
		len++;
	return (len);
}