#include "philosopher.h"

void	fork_sem_lock(int n, t_philo *philo)
{
	if (n % 2 && philo->state == 0)
		ft_msleep(philo->sh_info->time_to_eat);
	sem_wait(philo->sh_info->deadlock_check);
	sem_wait(philo->sh_info->fork);
	sem_wait(philo->sh_info->fork);
}

void	fork_sem_unlock(t_philo *philo)
{
	sem_post(philo->sh_info->fork);
	sem_post(philo->sh_info->fork);
	sem_post(philo->sh_info->deadlock_check);
}

void	sleeping(t_philo *philo)
{
	//printf("at %ld %d start sleeping\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
	ft_msleep(philo->sh_info->time_to_sleep);
}

void	thinking(void)
{
	//printf("at %ld %d start thinking\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
	usleep(500);
}
