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

void	sleeping(t_philo *philo)
{
	ft_msleep(philo->sh_info->time_to_sleep);
}

void	thinking(void)
{
	usleep(500);
}
