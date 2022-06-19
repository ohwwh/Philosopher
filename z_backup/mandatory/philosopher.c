#include "philosopher.h"

int	main(int argc, char *argv[])
{
	int		i;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));
	i = 0;
	philo = philo_init(argc, argv);
	while (i < philo->sh_info->philo_num)
	{
		pthread_create(&(philo[i].thread_t), 0, routine, (void *)(&philo[i]));
		pthread_detach(philo[i].thread_t);
		i ++;
	}
	monitoring(philo, philo->sh_info->philo_num);
	i = 0;
	while (i < philo->sh_info->philo_num)
		pthread_mutex_destroy(&(philo->sh_info->mutex_s[i ++]));
	pthread_mutex_destroy(&(philo->sh_info->mutex_c));
	free_all(philo);
}
