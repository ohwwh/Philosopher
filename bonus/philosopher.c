/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:35:53 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:35:54 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parent_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->sh_info->philo_num)
		sem_wait(philo->sh_info->end_eat[i ++]);
	i = 0;
	while (i < philo->sh_info->philo_num)
		kill(philo->sh_info->pids[i ++], SIGUSR1);
	free_all(philo);
	return (0);
}

int	child_process(int n, t_philo *philo)
{
	philo->th_num = n;
	if (pthread_create(&(philo->thr), 0, monitoring, (void *)philo))
		return (printf("thread create error!\n"));
	routine(n, philo);
	pthread_join(philo->thr, 0);
	free_all(philo);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		pid;
	int		n;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));
	n = 1;
	philo = philo_init(argc, argv);
	while (n <= philo->sh_info->philo_num)
	{
		pid = fork();
		if (pid > 0)
			philo->sh_info->pids[n - 1] = pid;
		else
			break ;
		n ++;
	}
	if (pid > 0)
		return (parent_process(philo));
	else
		return (child_process(n, philo));
}
