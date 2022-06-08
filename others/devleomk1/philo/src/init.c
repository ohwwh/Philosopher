/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:37:09 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/14 15:38:00 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_philos_forks(t_info *info)
{
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (info->philo == NULL)
		return (EXIT_FAILURE);
	info->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_philo);
	if (info->forks_mutex == NULL)
	{
		free(info->philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_philos_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].num = i + 1;
		info->philo[i].eat_cnt = 0;
		info->philo[i].stat = THINK;
		info->philo[i].starve = FILL;
		info->philo[i].info = info;
		info->philo[i].r_fork = &(info->forks_mutex[i]);
		if (i + 1 == info->num_philo)
			info->philo[i].l_fork = &(info->forks_mutex[0]);
		else
			info->philo[i].l_fork = &(info->forks_mutex[i + 1]);
		if (pthread_mutex_init(info->forks_mutex + i, NULL) != PTH_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_pth_mutex(t_info *info)
{
	if (pthread_mutex_init(&(info->print_mutex), NULL) != PTH_SUCCESS)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(info->main_mutex), NULL) != PTH_SUCCESS)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(info->dead_mutex), NULL) != PTH_SUCCESS)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(info->main_mutex));
	return (EXIT_SUCCESS);
}

int	init_info(t_info *info, int argc, int *argv_num)
{
	info->num_philo = argv_num[NUM_PHIL];
	info->time_die = argv_num[TIME_DIE];
	info->time_eat = argv_num[TIME_EAT];
	info->time_sleep = argv_num[TIME_SLP];
	if (argc != 6)
		info->num_must_eat = PEAT_INF;
	else
		info->num_must_eat = argv_num[NUM_PEAT];
	info->num_phi_full = 0;
	info->end = FALSE;
	if (malloc_philos_forks(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos_forks(info) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_pth_mutex(info) != PTH_SUCCESS)
		return (EXIT_FAILURE);
	printf("TIME\tPHILO\tSTATUS\t\t\tEAT_CNT\n"\
	"===============================================\n");
	return (EXIT_SUCCESS);
}
