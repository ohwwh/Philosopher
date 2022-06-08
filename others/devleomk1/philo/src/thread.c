/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 01:26:40 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/14 15:35:22 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *philo_void)
{
	t_philo	*p;

	p = (t_philo *)philo_void;
	p->diecnt_start_time = p->info->main_start_time;
	while (p->info->end != TRUE)
	{
		philo_take_forks(philo_void);
		philo_eat(philo_void);
		philo_sleep(philo_void);
		philo_think(philo_void);
		usleep(100);
	}
	return ((void *)EXIT_SUCCESS);
}

static int	run_philo(t_info *info, int p_num)
{
	void		*p;
	pthread_t	tid;

	while (p_num < info->num_philo)
	{
		p = (void *)(&(info->philo[p_num]));
		if (pthread_create(&tid, NULL, &philo_routine, p) != PTH_SUCCESS)
			return (EXIT_FAILURE);
		pthread_detach(tid);
		p_num += 2;
	}
	if (p_num % 2 == 0)
		usleep(500 * info->time_eat);
	return (EXIT_SUCCESS);
}

int	thread_run(t_info *info)
{
	pthread_t	tid;

	info->main_start_time = get_time_ms();
	if (run_philo(info, 0) == EXIT_FAILURE
		|| run_philo(info, 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_create(&tid, NULL, &monitor_all_philo, info) != PTH_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
