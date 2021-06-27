#include "philo.h"

extern long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

extern void     print_status(long long time, int id, char *string, pthread_mutex_t write_mutex)
{
    pthread_mutex_lock(&write_mutex);
    printf("%lld %d %s", time, id , string);
    pthread_mutex_unlock(&write_mutex);
}

extern void    p_eat(t_philosopher *philo)
{

    pthread_mutex_lock(&philo->din_table->t_forks[philo->l_fork]);
    print_status(timeInMilliseconds() - philo->din_table->p_time, philo->philo_id + 1, "has taken a fork\n", philo->din_table->write_mutex);
    pthread_mutex_lock(&philo->din_table->t_forks[philo->r_fork]);
    print_status(timeInMilliseconds() - philo->din_table->p_time, philo->philo_id + 1, "has taken a fork\n", philo->din_table->write_mutex);
    print_status(timeInMilliseconds() - philo->din_table->p_time, philo->philo_id + 1, "is eating\n", philo->din_table->write_mutex);
    while (timeInMilliseconds() - philo->last_time_eat < philo->din_table->time_to_eat)
    pthread_mutex_unlock(&philo->din_table->t_forks[philo->l_fork]);
    pthread_mutex_unlock(&philo->din_table->t_forks[philo->r_fork]);
    // if (philo->din_table->number_of_times_each_philosopher_must_eat != -1)
    //     din_table->number_of_times_each_philosopher_must_eat--;
    return ;
}

extern void    p_think(t_philosopher *philo)
{
    print_status(timeInMilliseconds() - philo->din_table->p_time, philo->philo_id + 1, "is thinking\n", philo->din_table->write_mutex);
    return ;
}

extern void    p_sleep(t_philosopher *philo)
{
    print_status(timeInMilliseconds() - philo->din_table->p_time, philo->philo_id + 1, "is sleping\n", philo->din_table->write_mutex);
    usleep(philo->din_table->time_to_sleep * 1000);
    return ;
}

extern void    kami_visor(t_table *din_table)
{
    int i;

    while (1)
    {
        i = 0;
        while (i < din_table->nb_philosopher)
        {
            if ((din_table->t_philoso[i]->last_time_eat - timeInMilliseconds()) >= din_table->time_to_die)
            {
                print_status(timeInMilliseconds() - din_table->p_time, din_table->t_philoso[i]->philo_id + 1, "is dead\n", din_table->write_mutex);
                exit(0);
            }
            i++;
        }
    }
    return ;
}