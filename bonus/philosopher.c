#include "philosopher.h"

void	free_sem(int n, sem_t **sem_arr)
{
	int	i;

	i = 0;
	sem_unlink("forks");
	sem_close(sem_arr[0]);
	sem_unlink("state");
	sem_close(sem_arr[1]);
	free(sem_arr);
}

void	aroutine(int n, t_philo *philo)
{
	int	i;
	struct timeval mytime;

	i = 0;
	//sem_post(philo->sh_info->end_eat[philo->th_num - 1]);
	/*while (i < philo->sh_info->philo_num)
	{
		if (i != philo->th_num - 1)
			sem_wait(philo->sh_info->end_eat[i]);
		i ++;
	}*/
	gettimeofday(&mytime, 0);
	philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	while (1)
	{
		if (n % 2 && philo->state == 0)
			ft_msleep(200);
		sem_wait(philo->sh_info->deadlock_check);
		sem_wait(philo->sh_info->fork);
		sem_wait(philo->sh_info->fork);
		gettimeofday(&mytime, 0);
		printf("at %ld %d grabs the fork\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
		printf("at %ld %d start eating, waiting time: %ld\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n, 
		stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former);
		philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
		ft_msleep(philo->sh_info->time_to_eat);
		gettimeofday(&mytime, 0);
		philo->state ++;
		printf("at %ld %d finish eating     [%d]\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n, philo->state);
		sem_post(philo->sh_info->fork);
		sem_post(philo->sh_info->fork);
		sem_post(philo->sh_info->deadlock_check);
		//printf("at %ld %d start sleeping\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		ft_msleep(philo->sh_info->time_to_sleep);
		gettimeofday(&mytime, 0);
		//printf("at %ld %d start thinking\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		usleep(200);
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	int		pid;
	int		status;
	int		n;
	int		*proc_arr;
	sem_t **sem_arr; // 포크 + 데드락 방지 세마포어 // 죽음 측정용 세마포어
	t_philo	*philo;
	int		*pids;
	pthread_t thread_t;


	pid = 1;
	if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));
	i = 0;
	philo = philo_init(argc, argv);
	pids = (int *)malloc(sizeof(int) * philo->sh_info->philo_num);
	i = 0;
	while (i < philo->sh_info->philo_num)
	{
		if (pid > 0)
		{
			pid = fork();
			pids[i] = pid;
		}
		else
			break ;
		i ++;
	}
	if (pid > 0)
	{
		i = 0;
		while (i < philo->sh_info->philo_num)
			sem_wait(philo->sh_info->end_eat[i ++]);
		i = 0;
		while (i < philo->sh_info->philo_num)
			kill(pids[i ++], SIGUSR1);
		//while (i < philo->sh_info->philo_num)
		//	waitpid(pids[i ++], 0, 0);
		free_all(philo);
		free(pids);
		/*printf("%d\n", getpid());
		while (1);*/
		return (1);
	}
	else
	{
		//printf("I am a child\n");
		philo->th_num = i;
		pthread_create(&thread_t, 0, monitoring_routine, (void *)philo);
		aroutine(i, philo);
		pthread_join(thread_t, 0);
		free_all(philo);
		free(pids);
		return (1);
	}
}
