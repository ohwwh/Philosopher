/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:35:33 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:35:34 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	start_eating(int n, t_philo *philo)
{
	struct timeval	mytime;
	long			wait;
	long			current;

	sem_wait(philo->sh_info->print);
	gettimeofday(&mytime, 0);
	current = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	wait = current - philo->former;
	printf("at %ld %dth has grab the fork\n", current, n);
	printf("at %ld %dth start eating", current, n);
	printf(", waiting time: %ld,    [%d]\n", wait, philo->state);
	sem_post(philo->sh_info->print);
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
}

static void	finish_eating(int n, t_philo *philo)
{
	struct timeval	mytime;
	long			current;

	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	philo->state ++;
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
	sem_wait(philo->sh_info->print);
	gettimeofday(&mytime, 0);
	current = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	printf("at %ld %dth finish eating", current, n);
	printf("                       [%d]\n", philo->state);
	sem_post(philo->sh_info->print);
}

void	eating(int n, t_philo *philo)
{
	start_eating(n, philo);
	ft_msleep(philo->sh_info->time_to_eat);
	finish_eating(n, philo);
}
