/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:40:04 by mashad            #+#    #+#             */
/*   Updated: 2021/06/28 19:40:17 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

extern long long	timeInMilliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long) tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}