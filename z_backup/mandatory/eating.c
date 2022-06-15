#include "philosopher.h"

static void	start_eating(int n, t_philo *philo)
{
	struct timeval	t;
	long			wait;

	gettimeofday(&t, NULL);
	pthread_mutex_lock(&(philo->sh_info->mutex_m[n - 1]));
	wait = stamp(t.tv_sec, t.tv_usec, philo) - philo->former;
	printf("at %ld %dth start eating\n", stamp(t.tv_sec, t.tv_usec, philo), n);
	//printf(" start eating\n");
	//printf(" waiting time: %ld, last eating: %ld\n", wait, philo->former);
	philo->former = stamp(t.tv_sec, t.tv_usec, philo);
	pthread_mutex_unlock(&(philo->sh_info->mutex_m[n - 1]));
}

static void	finish_eating(int n, t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	philo->state ++;
	printf("at %ld %dth finish eating\n", stamp(t.tv_sec, t.tv_usec, philo), n);
	//printf(" finish eating\n");
	//printf("    [%d]\n", philo->state);
}

int	eating(int n, t_philo *philo)
{
	if (philo->sh_info->death)
		return (1);
	start_eating(n, philo);
	ft_msleep(philo->sh_info->time_to_eat);
	if (philo->sh_info->death)
		return (1);
	finish_eating(n, philo);
	return (0);
}
