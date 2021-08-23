/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_routines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:24:51 by mashad            #+#    #+#             */
/*   Updated: 2021/08/23 10:11:31 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Print status using a write mutex
** to avoid other philospher status be scrambled or intertwined
** with another philosopher’s status.
*/
void    print_status(t_din  *din_table, int pid, char *string)
{
  pthread_mutex_lock(&din_table->write);
  printf("%lld %d %s", ft_time_in_ms() - din_table->st, pid + 1, string);
  if (string[0] != 'd')
    pthread_mutex_unlock(&din_table->write);
}
/*
** Philosopher get both forks then start eating
** for an amount of time ( tte ).
*/
void  eat_routine(t_philo *philo)
{
  pthread_mutex_lock(&philo->din_table->forks[philo->lf]);
  print_status(philo->din_table, philo->pid, "taken left fork\n");
  pthread_mutex_lock(&philo->din_table->forks[philo->rf]);
  print_status(philo->din_table, philo->pid, "taken right fork\n");
  philo->eating = 1;
  philo->lta = ft_time_in_ms();
  print_status(philo->din_table, philo->pid, "is eating\n");
  usleep(philo->din_table->tte * 1000);
  philo->nta++;
  pthread_mutex_unlock(&philo->din_table->forks[philo->lf]);
  pthread_mutex_unlock(&philo->din_table->forks[philo->rf]);
  philo->eating = 0;
  return ;
}

/*
** Philospher time to sleep routine.
*/
void  sleep_routine(t_philo *philo)
{
  print_status(philo->din_table, philo->pid, "is sleeping\n");
  usleep(philo->din_table->tts * 1000);
  return ;
}

/*
** Philospher time to think routine
*/
void  think_routine(t_philo *philo)
{
  print_status(philo->din_table, philo->pid, "is thinking\n");
  return ;
}

/*
** Routine start here with infinite loop
** that includes all routines that philospher must do
** which are eat - sleep - think.
*/
void  *start_routine(void *data)
{
  t_philo   *philo;

  philo = (t_philo *)data;
  philo->lta = ft_time_in_ms();
  while (philo->din_table->death)
  {
    eat_routine(philo);
    sleep_routine(philo);
    think_routine(philo);
  }
  return (NULL);
}
