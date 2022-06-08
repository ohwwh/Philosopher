#include "philosopher.h"

t_info	*info_init(int num);

t_philo	*philo_init(int num)
{
	int	i;
	t_philo *philo;
	t_info *sh_info;

	i = 0;
	philo = (t_philo *)malloc(num * sizeof(t_philo));
	sh_info = info_init(num);
	while (i < num)
	{
		philo[i].th_num = i;
		philo[i].sh_info = sh_info;
		i ++;
	}
	return (philo);
}

t_info	*info_init(int num)
{
	int	i;
	t_info	*sh_info;

	i = 0;
	struct timeval mytime;
	gettimeofday(&mytime, NULL);
	sh_info = (t_info *)malloc(sizeof(t_info));
	sh_info->fork_num = (int *)malloc(num * sizeof(int));
	sh_info->fork_own = (int *)malloc(num * sizeof(int));
	sh_info->state = (int *)malloc(num * sizeof(int));
	sh_info->former = (int *)malloc(num * sizeof(int));
	sh_info->mutex_s = (pthread_mutex_t *)malloc(num * sizeof(pthread_mutex_t));
	memset(sh_info->fork_own, 0, num * sizeof(int));
	memset(sh_info->state, 0, num * sizeof(int));
	memset(sh_info->former, 0, num * sizeof(int));
	sh_info->start = mytime.tv_usec;
	while (i < num)
	{
		sh_info->fork_num[i] = 1;
		pthread_mutex_init(&(sh_info->mutex_s[i]), 0);
		i ++;
	}
	sh_info->philo_num = num;
	pthread_mutex_init(&(sh_info->mutex_c), 0);
	return (sh_info);
}

void	free_all(t_philo *philo)
{
	free(philo->sh_info->fork_num);
	free(philo->sh_info->fork_own);
	free(philo->sh_info->state);
	free(philo->sh_info->former);
	free(philo->sh_info->mutex_s);
	free(philo->sh_info);
	free(philo);
}