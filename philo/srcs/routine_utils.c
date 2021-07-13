#include "philo.h"

extern void	print_status(int id,
	char *string, t_table *din_table)
{
	pthread_mutex_lock(&din_table->write_mutex);
	printf("%lld %d %s", timeInMilliseconds() - din_table->p_time, id, string);
	if (strcmp(string, "is dead\n") != 0)
		pthread_mutex_unlock(&din_table->write_mutex);
}

extern void	p_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->din_table->t_forks[philo->l_fork]);
	print_status(philo->philo_id + 1, "has taken a fork\n", philo->din_table);
	pthread_mutex_lock(&philo->din_table->t_forks[philo->r_fork]);
	print_status(philo->philo_id + 1, "has taken a fork\n", philo->din_table);
	print_status(philo->philo_id + 1, "is eating\n", philo->din_table);
	philo->is_eating = 1;
	philo->last_time_eat = timeInMilliseconds();
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
	print_status(philo->philo_id + 1, "is thinking\n", philo->din_table);
	return ;
}

extern void	p_sleep(t_philosopher *philo)
{
	long long	time;

	print_status(philo->philo_id + 1, "is sleping\n", philo->din_table);
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
		if (check_eat_time(din_table))
			return ;
		while (i < din_table->nb_philosopher)
		{
			if ((timeInMilliseconds()
					- (din_table->t_philoso[i]->last_time_eat))
				>= din_table->time_to_die
				&& !din_table->t_philoso[i]->is_eating)
			{
				print_status(din_table->t_philoso[i]->philo_id + 1,
					"is dead\n", din_table);
				din_table->death = 1;
				return ;
			}
			i++;
		}
		usleep(100);
	}
	return ;
}
