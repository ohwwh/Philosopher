#include "philosopher.h"

int	main(int argc, char *argv[])
{
	int		i;
	int		pid;
	int		n;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));
	pid = 1;
	philo = philo_init(argc, argv);
	n = 0;
	while (n < philo->sh_info->philo_num)
	{
		if (pid > 0)
		{
			pid = fork();
			philo->sh_info->pids[n] = pid;
		}
		else
			break ;
		n ++;
	}
	if (pid > 0)
	{
		i = 0;
		while (i < philo->sh_info->philo_num)
			sem_wait(philo->sh_info->end_eat[i ++]);
		printf("stuck?\n");
		i = 0;
		while (i < philo->sh_info->philo_num)
			kill(philo->sh_info->pids[i ++], SIGUSR1);
		//while (i < philo->sh_info->philo_num)
		//	waitpid(pids[i ++], 0, 0);
		free_all(philo);
		/*printf("%d\n", getpid());
		while (1);*/
		return (1);
	}
	else
	{
		philo->th_num = n;
		pthread_create(&(philo->thread_t), 0, monitoring, (void *)philo);
		routine(n, philo);
		pthread_join(philo->thread_t, 0);
		free_all(philo);
		return (1);
	}
}
