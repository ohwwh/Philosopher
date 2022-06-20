/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:37:32 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:37:34 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	const int	must = philo->sh_info->must_eat;

	while (!philo->sh_info->death && philo->state != must)
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
		if (sleeping(n, philo))
			break ;
		if (thinking(n, philo))
			break ;
	}
}

void	*routine(void *data)
{
	t_philo	*philo;
	int		number;
	int		n;

	philo = (t_philo *)data;
	number = philo->sh_info->philo_num;
	n = philo->th_num;
	start_simulation(number, philo);
	simulation(philo->th_num + 1, number, philo);
	pthread_mutex_lock(&(philo->sh_info->mutex_m[n - 1]));
	philo->end = 1;
	pthread_mutex_unlock(&(philo->sh_info->mutex_m[n - 1]));
	return (0);
}
