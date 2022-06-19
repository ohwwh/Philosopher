#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdint.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>

typedef struct s_info
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	int	std_sec;
	int	std_usec;
	int	start;
	int	*pids;
	pthread_mutex_t mutex_c;
	sem_t *fork;
	sem_t *deadlock_check;
	sem_t *print;
	sem_t **end_eat;
	sem_t **sim_start;
}t_info; //공유자원들

typedef struct s_philo
{
	int	th_num;
	int state;
	int	end;
	long former;
	pthread_t thread_t;
	t_info *sh_info;
}t_philo; //철학자 개개인의 속성들

void	*monitoring(void *data);
void	routine(int num, t_philo *philo);
int 	picking(int n, t_philo *philo);
void 	eating(int n, t_philo *philo);
void    sleeping(int n, t_philo *philo);
void	thinking(int n, t_philo *philo);
void    ft_msleep(int time);
void	fork_sem_lock(int n, t_philo *philo);
void	fork_sem_unlock(t_philo *philo);
long    stamp(long sec, long usec, t_philo *philo);
t_philo	*philo_init(int argc, char *argv[]);
t_info	*info_init(int argc, char *argv[]);
void	ft_sem_init(t_info *sh_info);
void	free_all(t_philo *philo);

char	*ft_itoa(int n);