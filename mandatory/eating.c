#include "philosopher.h"

static int	start_eating(int n, t_philo *philo)
{
	struct timeval	t;
	long			wait;

	gettimeofday(&t, NULL);
	wait = stamp(t.tv_sec, t.tv_usec, philo) - philo->former;
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		return (1);	
	}
	else
	{
		printf("at %ld %dth start eating", stamp(t.tv_sec, t.tv_usec, philo), n);
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

	gettimeofday(&t, 0);
	philo->state ++;
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		return (1);	
	}
	else
		printf("at %ld %dth finish eating\n", stamp(t.tv_sec, t.tv_usec, philo), n);
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
