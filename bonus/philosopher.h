/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:36:33 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:36:34 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_info
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				std_sec;
	int				std_usec;
	int				start;
	int				*pids;
	pthread_mutex_t	mutex_c;
	sem_t			*fork;
	sem_t			*deadlock_check;
	sem_t			*print;
	sem_t			**end_eat;
	sem_t			**sim_start;
}t_info;

typedef struct s_philo
{
	int			th_num;
	int			state;
	int			end;
	long		former;
	pthread_t	thr;
	t_info		*sh_info;
}t_philo;

void	*monitoring(void *data);
void	routine(int num, t_philo *philo);
void	eating(int n, t_philo *philo);
void	sleeping(int n, t_philo *philo);
void	thinking(int n, t_philo *philo);
void	ft_msleep(int time);
long	stamp(long sec, long usec, t_philo *philo);
char	*ft_itoa(int n);
void	fork_sem_lock(int n, t_philo *philo);
void	fork_sem_unlock(t_philo *philo);
t_philo	*philo_init(int argc, char *argv[]);
t_info	*info_init(int argc, char *argv[]);
void	ft_sem_init(t_info *sh_info);
void	free_all(t_philo *philo);

#endif