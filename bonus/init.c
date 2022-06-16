#include "philosopher.h"

t_info	*info_init(int argc, char *argv[]);

t_philo	*philo_init(int argc, char *argv[])
{
	t_philo		*philo;
	t_info		*sh_info;

	philo = (t_philo *)malloc(sizeof(t_philo));
	sh_info = info_init(argc, argv);
	philo->sh_info = sh_info;
	philo->state = 0;
	philo->end = 0;
	philo->former = 0;
	return (philo);
}

static void	main_arg_init(int num, int argc, char *argv[], t_info *sh_info)
{
	sh_info->philo_num = num;
	sh_info->time_to_die = atoi(argv[2]);
	sh_info->time_to_eat = atoi(argv[3]);
	sh_info->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		sh_info->must_eat = atoi(argv[5]);
	else
		sh_info->must_eat = -1;
}

t_info	*info_init(int argc, char *argv[])
{
	int				i;
	t_info			*sh_info;
	const int		num = atoi(argv[1]);
	struct timeval	mytime;

	i = 0;
	gettimeofday(&mytime, NULL);
	sh_info = (t_info *)malloc(sizeof(t_info));
	main_arg_init(num, argc, argv, sh_info);
	sh_info->std_sec = mytime.tv_sec;
	sh_info->std_usec = mytime.tv_usec;
	sh_info->death = 0;
	sh_info->end = 0;
	sh_info->cnt = 0;
	sh_info->fork = sem_open("forks", O_CREAT, S_IXUSR, num);
	sh_info->deadlock_check = sem_open("deadlock", O_CREAT, S_IXUSR, (num / 2));
	sh_info->end_death = sem_open("end_death", O_CREAT, S_IXUSR, 0);
	sh_info->end_eat = sem_open("end_eat", O_CREAT, S_IXUSR, num);
	pthread_mutex_init(&(sh_info->mutex_c), 0);
	return (sh_info);
}

void	free_all(t_philo *philo)
{
	sem_unlink("forks");
	sem_close(philo->sh_info->fork);
	sem_unlink("deadlock");
	sem_close(philo->sh_info->deadlock_check);
	sem_unlink("end_death");
	sem_close(philo->sh_info->end_death);
	sem_unlink("end_eat");
	sem_close(philo->sh_info->end_eat);
	pthread_mutex_destroy(&(philo->sh_info->mutex_c));
	free(philo->sh_info);
	free(philo);
}
