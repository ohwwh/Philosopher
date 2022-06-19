#include "philosopher.h"

int	main(int argc, char *argv[])
{
	int		i;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (printf("arguments error!\n"));
	i = 0;
	philo = philo_init(argc, argv);
	if (!philo)
		return (printf("init error!\n"));
	while (i < philo->sh_info->philo_num)
	{
		if (pthread_create(&(philo[i].thr), 0, routine, (void *)(&philo[i])))
			return (printf("thread create error!\n"));
		pthread_detach(philo[i].thr);
		i ++;
	}
	monitoring(philo, philo->sh_info->philo_num);
	i = 0;
	while (i < philo->sh_info->philo_num)
		pthread_mutex_destroy(&(philo->sh_info->mutex_s[i ++]));
	pthread_mutex_destroy(&(philo->sh_info->mutex_c));
	free_all(philo);
}
