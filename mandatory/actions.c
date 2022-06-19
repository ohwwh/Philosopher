#include "philosopher.h"

void	fork_mutex_lock(int n, t_philo *philo)
{
	const int	number = philo->sh_info->philo_num;

	if (n % 2)
		pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
	else
	{
		if (philo->state == 0)
			ft_msleep(philo->sh_info->time_to_eat);
		pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
	}
	if (n % 2)
		pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
	else
		pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
}

void	fork_mutex_unlock(int n, t_philo *philo)
{
	const int	number = philo->sh_info->philo_num;

	if (n % 2)
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
	else
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
	if (n % 2)
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
	else
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
}

int	sleeping(int n, t_philo *philo)
{
	struct timeval	t;
	long			current;

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
		printf("at %ld %dth start sleeping", current, n);
		printf("                      [%d]\n", philo->state);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		ft_msleep(philo->sh_info->time_to_sleep);
	}
	return (0);
}

int	thinking(int n, t_philo *philo)
{
	struct timeval	t;
	long			current;

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
		printf("at %ld %dth start thinking", current, n);
		printf("                      [%d]\n", philo->state);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		usleep(500);
	}
	return (0);
}
