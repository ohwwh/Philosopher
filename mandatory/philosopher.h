/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:37:07 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:37:08 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_info
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				std_sec;
	int				std_usec;
	int				cnt;
	int				end;
	int				death;
	pthread_mutex_t	mutex_c;
	pthread_mutex_t	*mutex_s;
	pthread_mutex_t	*mutex_m;
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

void	monitoring(t_philo *philo, int n);
void	*routine(void *data);
int		eating(int n, t_philo *philo);
int		sleeping(int n, t_philo *philo);
int		thinking(int n, t_philo *philo);
void	ft_msleep(int time);
long	stamp(long sec, long usec, t_philo *philo);
void	fork_mutex_lock(int n, t_philo *philo);
void	fork_mutex_unlock(int n, t_philo *philo);
t_philo	*philo_init(int argc, char *argv[]);
t_info	*info_init(int argc, char *argv[]);
void	free_all(t_philo *philo);

#endif