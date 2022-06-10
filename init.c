#include "philosopher.h"

t_info	*info_init(int num);

t_philo	*philo_init(int num)
{
	int	i;
	t_philo *philo;
	t_info *sh_info;

	//struct timeval mytime;
	//gettimeofday(&mytime, NULL);
	i = 0;
	philo = (t_philo *)malloc(num * sizeof(t_philo));
	sh_info = info_init(num);
	while (i < num)
	{
		philo[i].th_num = i;
		philo[i].sh_info = sh_info;
		philo[i].fork_own = 0;
		philo[i].state = 0;
		philo[i].former = 0;
		//philo[i].start = mytime.tv_usec;
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
	sh_info->mutex_s = (pthread_mutex_t *)malloc(num * sizeof(pthread_mutex_t));
	sh_info->std_usec = mytime.tv_usec;
	sh_info->std_sec = mytime.tv_sec;
	sh_info->end = 0;
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
	free(philo->sh_info->mutex_s);
	free(philo->sh_info);
	free(philo);
	//철학자 스레드들이 돌아가는 와중에 free된 메모리를 건드릴수도 있음
	//철학자 스레드들을 모조리 종료시키고 메인 스레드를 종료 시키는 방향으로 다시 짜야 하나......?
}