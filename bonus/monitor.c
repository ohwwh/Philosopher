/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:36:26 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:36:27 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	end_philo(t_philo *philo)
{
	if (philo->state == philo->sh_info->must_eat)
	{
		sem_post(philo->sh_info->end_eat[philo->th_num - 1]);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		exit(1);
	}
}

static void	check_death(t_philo *philo)
{
	int				i;
	struct timeval	mytime;
	long			current_time;
	const int		time_to_die = philo->sh_info->time_to_die;

	i = 0;
	gettimeofday(&mytime, 0);
	current_time = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	if (current_time - philo->former >= time_to_die)
	{
		sem_wait(philo->sh_info->print);
		printf("at %ld %dth died\n", current_time, philo->th_num);
		while (i < philo->sh_info->philo_num)
			sem_post(philo->sh_info->end_eat[i ++]);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		exit(1);
	}
}

static void	start_monitoring(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->sh_info->mutex_c));
		if (philo->sh_info->start == 1)
		{
			pthread_mutex_unlock(&(philo->sh_info->mutex_c));
			break ;
		}
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	}
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	start_monitoring(philo);
	while (1)
	{
		pthread_mutex_lock(&(philo->sh_info->mutex_c));
		end_philo(philo);
		check_death(philo);
		pthread_mutex_unlock(&(philo->sh_info->mutex_c));
		usleep(200);
	}
	return (0);
}
