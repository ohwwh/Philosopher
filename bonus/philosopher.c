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
	/*printf("%d\n", getpid());
	while (1);*/
	return (1);
}

int	child_process(int n, t_philo *philo)
{
	philo->th_num = n;
	pthread_create(&(philo->thread_t), 0, monitoring, (void *)philo);
	routine(n, philo);
	pthread_join(philo->thread_t, 0);
	free_all(philo);
	return (1);
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
