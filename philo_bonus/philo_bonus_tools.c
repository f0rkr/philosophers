/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 08:43:02 by mashad            #+#    #+#             */
/*   Updated: 2021/08/28 09:43:59 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void  ft_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
  return ;
}

/*
** put number function
** uses write
*/
void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

/*
 ** Mr mayhem check for a reason to kill
 ** one of the philospher either their
 ** time to die or number_of_times_each_philosopher_must_eat
 */
void	*mr_mayhem(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->eating);
		if (ft_time_in_ms() - philo->lta >= philo->din_table->ttd)
		{
			print_status(philo->din_table, philo->pid, "died\n");
			exit(1);
		}
		sem_post(philo->eating);
		usleep(100);
	}
	return (NULL);
}

/*
** Await for philosohper their number_of_times_each_philosopher_must_eat[ntpme]
** then kill all childs
*/
void  *eat_reaper(void *data)
{
  t_din *din_table;
  int   eat_counter;
  int   i;

  din_table = (t_din *)data;
  eat_counter = 0;
  while (eat_counter < din_table->ntpme)
  {
    i = 0;
    while (i < din_table->nop)
    {
      sem_wait(din_table->eat);
      i++;
    }
    eat_counter++;
  }
  sem_wait(din_table->write);
  if (eat_counter == din_table->ntpme)
    kill(din_table->philos[0]->fpid, SIGKILL);
  return (NULL);
}
