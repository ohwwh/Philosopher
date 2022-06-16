#include "philosopher.h"

int	picking(int n, t_philo *philo)
{
	const int		number = philo->sh_info->philo_num;
	struct timeval	mytime;
	long			wait;

	gettimeofday(&mytime, NULL);
	wait = stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former;
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		return (1);
	}
	printf("at %ld %dth has grab forks\n", wait + philo->former, n);
	//printf(" has grab forks\n");
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	return (0);
}

void	sleeping(t_philo *philo)
{
	ft_msleep(philo->sh_info->time_to_sleep);
	//usleep(200 * 1000);
}

void	thinking(void)
{
	usleep(500);
}
