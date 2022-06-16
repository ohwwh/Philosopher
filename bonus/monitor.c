#include "philosopher.h"

static int	end_simulation(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->end >= philo->sh_info->philo_num)
	{
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		ret = 1;
	}
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	return (ret);
}

static void	end_philo(t_philo *philo)
{
	if (philo->end == 1)
	{
		pthread_mutex_lock(&(philo->sh_info->mutex_c));
		philo->sh_info->end += 1;
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		philo->end += 1;
	}
}

static void	check_death(t_philo *philo)
{
	struct timeval	mytime;
	long			current_time;
	const int		time_to_die = philo->sh_info->time_to_die;

	gettimeofday(&mytime, 0);
	current_time = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	if (philo->end < 1 && philo->sh_info->death != 1)
	{
		if (current_time - philo->former > time_to_die)
		{
			printf("at %ld %dth died", current_time, philo->th_num);
			//printf(" - RIP: last eating: %ld\n", philo[j].former);
			philo->sh_info->death = 1;
		}
	}
}

void	*monitoring_routine(void *data)
{
	t_philo         *philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&(philo->sh_info->mutex_c));
		//end_philo(philo);
		check_death(philo);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	}
	return (0);
}
