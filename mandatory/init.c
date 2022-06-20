/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:37:21 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:37:22 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_info	*info_init(int argc, char *argv[]);

t_philo	*philo_init(int argc, char *argv[])
{
	int			i;
	t_philo		*philo;
	t_info		*sh_info;
	const int	num = atoi(argv[1]);

	i = 0;
	philo = (t_philo *)malloc(num * sizeof(t_philo));
	if (!philo)
		return (0);
	sh_info = info_init(argc, argv);
	if (!sh_info)
		return (0);
	while (i < num)
	{
		philo[i].th_num = i;
		philo[i].sh_info = sh_info;
		philo[i].state = 0;
		philo[i].end = 0;
		philo[i].former = 0;
		i ++;
	}
	return (philo);
}

static void	main_arg_init(int num, int argc, char *argv[], t_info *sh_info)
{
	sh_info->philo_num = num;
	sh_info->time_to_die = atoi(argv[2]);
	sh_info->time_to_eat = atoi(argv[3]);
	sh_info->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		sh_info->must_eat = atoi(argv[5]);
	else
		sh_info->must_eat = -1;
}

void	mutex_init(int num, t_info *sh_info)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(sh_info->mutex_s[i]), 0);
		pthread_mutex_init(&(sh_info->mutex_m[i ++]), 0);
	}
	pthread_mutex_init(&(sh_info->mutex_c), 0);
}

t_info	*info_init(int argc, char *argv[])
{
	t_info			*sh_info;
	const int		num = atoi(argv[1]);
	struct timeval	mytime;

	gettimeofday(&mytime, NULL);
	sh_info = (t_info *)malloc(sizeof(t_info));
	sh_info->mutex_s = (pthread_mutex_t *)malloc(num * sizeof(pthread_mutex_t));
	sh_info->mutex_m = (pthread_mutex_t *)malloc(num * sizeof(pthread_mutex_t));
	if (!sh_info || !sh_info->mutex_s || !sh_info->mutex_m)
	{
		free(sh_info->mutex_s);
		free(sh_info->mutex_m);
		free(sh_info);
		return (0);
	}
	main_arg_init(num, argc, argv, sh_info);
	sh_info->std_sec = mytime.tv_sec;
	sh_info->std_usec = mytime.tv_usec;
	sh_info->death = 0;
	sh_info->end = 0;
	sh_info->cnt = 0;
	mutex_init(num, sh_info);
	return (sh_info);
}

void	free_all(t_philo *philo)
{
	free(philo->sh_info->mutex_s);
	free(philo->sh_info->mutex_m);
	free(philo->sh_info);
	free(philo);
}
