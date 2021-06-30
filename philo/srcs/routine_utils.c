#include "philo.h"

extern void	print_status(long long time, int id,
	char *string, t_table *din_table)
{
	pthread_mutex_lock(&din_table->write_mutex);
	printf("%lld %d %s", time, id, string);
	pthread_mutex_unlock(&din_table->write_mutex);
}

extern void	p_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->din_table->t_forks[philo->l_fork]);
	print_status(timeInMilliseconds() - philo->din_table->p_time,
		philo->philo_id + 1, "has taken a fork\n",
		philo->din_table);
	pthread_mutex_lock(&philo->din_table->t_forks[philo->r_fork]);
	print_status(timeInMilliseconds() - philo->din_table->p_time,
		philo->philo_id + 1, "has taken a fork\n",
		philo->din_table);
	print_status(timeInMilliseconds() - philo->din_table->p_time,
		philo->philo_id + 1, "is eating\n", philo->din_table);
	philo->last_time_eat = timeInMilliseconds();
	philo->is_eating = 1;
	usleep(philo->din_table->time_to_eat * 1000 - 14000);
	while (timeInMilliseconds() - philo->last_time_eat
		< philo->din_table->time_to_eat);
	pthread_mutex_unlock(&philo->din_table->t_forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->din_table->t_forks[philo->r_fork]);
	philo->time_ate++;
	philo->is_eating = 0;
	return ;
}

extern void	p_think(t_philosopher *philo)
{
	print_status(timeInMilliseconds() - philo->din_table->p_time,
		philo->philo_id + 1, "is thinking\n", philo->din_table);
	return ;
}

extern void	p_sleep(t_philosopher *philo)
{
	long long	time;

	print_status(timeInMilliseconds() - philo->din_table->p_time,
		philo->philo_id + 1, "is sleping\n", philo->din_table);
	time = timeInMilliseconds();
	usleep(philo->din_table->time_to_sleep * 1000 - 14000);
	while (timeInMilliseconds() - time
		< philo->din_table->time_to_sleep);
	return ;
}

extern void	kami_visor(t_table *din_table)
{
	int	i;

	while (!din_table->death)
	{
		i = 0;
		while (i < din_table->nb_philosopher)
		{
			if ((timeInMilliseconds()
					- (din_table->t_philoso[i]->last_time_eat))
				>= din_table->time_to_die
				&& !din_table->t_philoso[i]->is_eating)
			{
				din_table->death = 1;
				print_status(timeInMilliseconds() - din_table->p_time,
					din_table->t_philoso[i]->philo_id + 1, "is dead\n",
					din_table);
				pthread_mutex_lock(&din_table->write_mutex);
				return ;
			}
			if (din_table->t_philoso[din_table->nb_philosopher - 1]->time_ate == din_table->number_of_times_each_philosopher_must_eat)
			{
				din_table->death = 1;	
				return ;
			}
			i++;
		}
		usleep(100);
	}
	return ;
}
