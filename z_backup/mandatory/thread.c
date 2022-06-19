#include "philosopher.h"

static int	is_one(int number, t_philo *philo)
{
	int	ret;

	ret = 0;
	if (number == 1)
	{
		ft_msleep(philo->sh_info->time_to_die + 100);
		ret = 1;
	}
	return (ret);
}

static int	iter_condition(t_philo *philo)
{
	int	ret;

	ret = philo->state < philo->sh_info->must_eat;
	ret = ret && !philo->sh_info->death;
	if (philo->sh_info->must_eat == -1)
		return (!philo->sh_info->death);
	else
		return (ret);
}

static void	start_simulation(int number, t_philo *philo)
{
	struct timeval	mytime;

	while (1)
	{
		pthread_mutex_lock(&(philo->sh_info->mutex_c));
		if (philo->sh_info->cnt != number)
			philo->sh_info->cnt ++;
		if (philo->sh_info->cnt == number)
		{
			gettimeofday(&mytime, 0);
			philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
			pthread_mutex_unlock(&(philo->sh_info->mutex_c));
			break ;
		}
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	}
}

static void	simulation(int n, int number, t_philo *philo)
{
	while (iter_condition(philo))
	{
		if (is_one(number, philo))
			break ;
		fork_mutex_lock(n, philo);
		if (eating(n, philo))
		{
			fork_mutex_unlock(n, philo);
			break ;
		}
		fork_mutex_unlock(n, philo);
		sleeping(philo);
		thinking();
	}
}

void	*routine(void *data)
{
	t_philo	*philo;
	int		number;

	philo = (t_philo *)data;
	number = philo->sh_info->philo_num;
	start_simulation(number, philo);
	simulation(philo->th_num + 1, number, philo);
	philo->end = 1;
	//pause();
	return (0);
}
