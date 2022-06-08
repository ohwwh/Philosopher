/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:50:36 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/14 15:41:30 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_cnt_eat(t_info *info)
{
	if (info->num_phi_full == info->num_philo)
	{
		if (pthread_mutex_lock(&(info->print_mutex)) == PTH_SUCCESS)
		{
			printf(BLUE "🍝All philosophers have finished their meals.\n" RESET);
			usleep(100);
			pthread_mutex_unlock(&(info->main_mutex));
			return (EXIT_SUCCESS);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_PASS);
}

int	monitor_health(t_info *info, int i)
{
	if (get_time_ms() - info->philo[i].diecnt_start_time > info->time_die)
	{
		if (pthread_mutex_lock(&(info->dead_mutex)) == PTH_SUCCESS)
		{
			info->philo[i].stat = DEAD;
			print_message(&(info->philo[i]), "dead\t\t");
			info->end = TRUE;
			usleep(100);
			pthread_mutex_unlock(&(info->main_mutex));
			return (EXIT_SUCCESS);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_PASS);
}

void	*monitor_all_philo(void *info_void)
{
	int		i;
	t_info	*info;

	info = (t_info *)info_void;
	i = 0;
	while (TRUE)
	{
		if (info->end == TRUE)
			return (EXIT_SUCCESS);
		if (i == info->num_philo)
			i = 0;
		if (monitor_cnt_eat(info) == EXIT_FAILURE)
			return ((void *)EXIT_FAILURE);
		if (monitor_health(info, i) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		i++;
		usleep(100);
	}
}
