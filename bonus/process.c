#include "philosopher.h"

void	start_eating(int n, t_philo * philo)
{
	struct timeval mytime;

	gettimeofday(&mytime, 0);
	sem_wait(philo->sh_info->print);
	//printf("at %ld %d grabs the fork\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
	printf("at %ld %d start eating, waiting time: %ld, last eating: %d\n"
	,stamp(mytime.tv_sec, mytime.tv_usec, philo), n, 
	stamp(mytime.tv_sec, mytime.tv_usec, philo) - philo->former, philo->former);
	sem_post(philo->sh_info->print);
	//printf("at %ld %d start eating\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
}

void	finish_eating(int n, t_philo * philo)
{
	struct timeval mytime;

	gettimeofday(&mytime, 0);
	philo->state ++;
	sem_wait(philo->sh_info->print);
	//printf("at %ld %d finish eating     [%d]\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n, philo->state);
	//printf("at %ld %d finish eating\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
	sem_post(philo->sh_info->print);
}

void	eating(int n, t_philo *philo)
{
	start_eating(n, philo);
	ft_msleep(philo->sh_info->time_to_eat);
	finish_eating(n, philo);
}

void	fork_sem_lock(int n, t_philo *philo)
{
	if (n % 2 && philo->state == 0)
		ft_msleep(philo->sh_info->time_to_eat);
	sem_wait(philo->sh_info->deadlock_check);
	sem_wait(philo->sh_info->fork);
	sem_wait(philo->sh_info->fork);
}

void	fork_sem_unlock(t_philo *philo)
{
	sem_post(philo->sh_info->fork);
	sem_post(philo->sh_info->fork);
	sem_post(philo->sh_info->deadlock_check);
}

static void    start_simulation(int n, t_philo *philo)
{
	int	i;
	struct timeval mytime;

    i = 0;
	while (i < philo->sh_info->philo_num)
	{
		sem_post(philo->sh_info->sim_start[n - 1]);
		i ++;
	}
	i = 0;
	while (i < philo->sh_info->philo_num)
		sem_wait(philo->sh_info->sim_start[i ++]);
	gettimeofday(&mytime, 0);
	philo->former = stamp(mytime.tv_sec, mytime.tv_usec, philo);
	pthread_mutex_lock(&(philo->sh_info->mutex_c));
	philo->sh_info->start = 1;
	pthread_mutex_unlock(&(philo->sh_info->mutex_c));
}

static void    simulation(int n, t_philo *philo)
{
	struct timeval mytime;

    while (1)
	{
		fork_sem_lock(n, philo);
		eating(n, philo);
		fork_sem_unlock(philo);
		//printf("at %ld %d start sleeping\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
		ft_msleep(philo->sh_info->time_to_sleep);
		gettimeofday(&mytime, 0);
		//printf("at %ld %d start thinking\n", stamp(mytime.tv_sec, mytime.tv_usec, philo), n);
		usleep(200);
	}
}

void	routine(int n, t_philo *philo)
{
	int	i;

	start_simulation(n, philo);
	simulation(n, philo);
}