/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 07:03:14 by mashad            #+#    #+#             */
/*   Updated: 2021/04/28 05:44:15 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char **argv)
{
	if (!check_arg_errors(argc, argv))
		return (ERROR);
	if (!dining_init())
		return (ERROR);
	return (0);
}