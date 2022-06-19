#include "philosopher.h"

static int	start_eating(int n, t_philo *philo)
{
	struct timeval	t;
	long			wait;
	long			current;

	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		return (1);
	}
	else
	{
		gettimeofday(&t, NULL);
		current = stamp(t.tv_sec, t.tv_usec, philo);
		wait = current - philo->former;
		printf("at %ld %dth has grab forks\n", current, n);
		printf("at %ld %dth start eating", current, n);
		printf(" waiting time: %ld, last eating: %ld\n", wait, philo->former);
	}
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	pthread_mutex_lock(&(philo->sh_info->mutex_m[n - 1]));
	philo->former = stamp(t.tv_sec, t.tv_usec, philo);
	pthread_mutex_unlock(&(philo->sh_info->mutex_m[n - 1]));
	return (0);
}

static int	finish_eating(int n, t_philo *philo)
{
	struct timeval	t;
	long			current;

	philo->state ++;
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		return (1);
	}
	else
	{
		gettimeofday(&t, 0);
		current = stamp(t.tv_sec, t.tv_usec, philo);
		printf("at %ld %dth finish eating\n", current, n);
	}
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	//printf(" finish eating\n");
	//printf("    [%d]\n", philo->state);
	return (0);
}

int	eating(int n, t_philo *philo)
{
	if (start_eating(n, philo) == 1)
		return (1);
	ft_msleep(philo->sh_info->time_to_eat);
	if (finish_eating(n, philo) == 1)
		return (1);
	return (0);
}
