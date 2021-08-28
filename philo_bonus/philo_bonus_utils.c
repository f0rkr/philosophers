/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 09:26:02 by mashad            #+#    #+#             */
/*   Updated: 2021/08/28 09:41:49 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ft_check(unsigned long pt, int s)
{
	if (pt > 9223372036854775807 && s == -1)
		return (0);
	else if (pt > 2147483647)
		return (OFLOW);
	return (pt * s);
}

int		ft_atoi(const char *str)
{
	unsigned long long int	j;
	unsigned long long int	t_p;
	int						tt;

	tt = 1;
	j = 0;
	t_p = 0;
	while (*str >= 8 && *str <= 32)
	{
		if (*str == 27)
			return (0);
		str++;
	}
	if (*str == '-')
	{
		tt = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*(str + j) >= 48 && *(str + j) <= 57)
		t_p = t_p * 10 + (unsigned long long int)(*(str + j++) - '0');
	return (ft_check(t_p, tt));
}

/* Mainly check if the in string
** doesn't contain any ascii than numbers
*/
int   ft_is_number(char *string)
{
  int   i;

  i = 0;
  while (string[i] != EOL)
  {
    if (string[i] <= '0' || string[i] >= '9')
      return (ERROR);
    i++;
  }
  return (GOOD);
}

/*
** Get the current time in ms
*/
long long ft_time_in_ms() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

/*
** Initialize philosophers struct
*/
t_philo   **initialize_philosphers(t_din *din_table)
{
  t_philo  **philos;
  int      i;

  i = 0;
  philos = (t_philo **)malloc(sizeof(t_philo *) * din_table->nop + 1);
  if (philos == NULL)
    return (NULL);
  while (i < din_table->nop)
  {
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (philos[i] == NULL)
			return (NULL);
		sem_unlink("eating");
		philos[i]->eating = sem_open("eating", O_CREAT, 0644, 1);
		if (din_table->write == SEM_FAILED)
			return (NULL);
    philos[i]->din_table = din_table;
    philos[i]->pid = i;
    philos[i]->nta = 0;
    i++;
  }
  return (philos);
}

/*
** Initialize forks semaphores
*/
int 	initialize_sems(t_din *din_table)
{
	if (din_table->nop == OFLOW || din_table->ttd == OFLOW || din_table->tte
		== OFLOW || din_table->tts == OFLOW || din_table->ntpme == OFLOW)
	{
		write(2, "Error: Argument overflow\n", 23);
		return (NULL);
	}
	sem_unlink("forking");
  din_table->forks = sem_open("forking", O_CREAT, S_PERM, din_table->nop);
  if (din_table->forks == SEM_FAILED)
    return (ERROR);
	sem_unlink("death");
	din_table->death = sem_open("death", O_CREAT, 0644, 1);
	if (din_table->death == SEM_FAILED)
		return (ERROR);
	sem_unlink("writing");
	din_table->write = sem_open("writing", O_CREAT, 0644, 1);
	if (din_table->write == SEM_FAILED)
		return (ERROR);
	sem_unlink("eatcounter");
	din_table->eat = sem_open("eatcounter", O_CREAT, 0644, 1);
	if (din_table->eat == SEM_FAILED)
		return (ERROR);
  return (GOOD);
}
