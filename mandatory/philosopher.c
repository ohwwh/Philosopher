#include "philosopher.h"

int	main(int argc, char *argv[])
{
	int		j;
	t_philo	*philo;

	if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));
	j = 0;
	philo = philo_init(argc, argv);
	while (j < philo->sh_info->philo_num)
	{
		pthread_create(&(philo[j].thread_t), 0, routine, (void *)(&philo[j]));
		pthread_detach(philo[j].thread_t);
		j ++;
	}
	monitoring(philo, philo->sh_info->philo_num);
	j = 0;
	while (j < philo->sh_info->philo_num)
		pthread_mutex_destroy(&(philo->sh_info->mutex_s[j ++]));
	pthread_mutex_destroy(&(philo->sh_info->mutex_c));
	free_all(philo);
}
