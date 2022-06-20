/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:37:18 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:37:19 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_mutex_lock(int n, t_philo *philo)
{
	const int	number = philo->sh_info->philo_num;
	const int	left = (n - 1 + number) % number;
	const int	right = (n - 2 + number) % number;

	if (n % 2)
		pthread_mutex_lock(&(philo->sh_info->mutex_s[right]));
	else
	{
		if (philo->state == 0)
			ft_msleep(philo->sh_info->time_to_eat);
		pthread_mutex_lock(&(philo->sh_info->mutex_s[left]));
	}
	if (n % 2)
		pthread_mutex_lock(&(philo->sh_info->mutex_s[left]));
	else
		pthread_mutex_lock(&(philo->sh_info->mutex_s[right]));
}

void	fork_mutex_unlock(int n, t_philo *philo)
{
	const int	number = philo->sh_info->philo_num;
	const int	left = (n - 1 + number) % number;
	const int	right = (n - 2 + number) % number;

	if (n % 2)
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[right]));
	else
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[left]));
	if (n % 2)
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[left]));
	else
		pthread_mutex_unlock(&(philo->sh_info->mutex_s[right]));
}

int	sleeping(int n, t_philo *philo)
{
	struct timeval	t;
	long			current;
	const int		must = philo->sh_info->must_eat;

	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1 || philo->state == must)
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
	const int		must = philo->sh_info->must_eat;

	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	if (philo->sh_info->death == 1 || philo->state == must)
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
