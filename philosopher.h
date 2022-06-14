#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdint.h>

#define LEFT     (n - 1 + number) % number
#define RIGHT    (n - 2 + number) % number

typedef struct s_info
{
	int	philo_num;
	int *fork_num;
	int	std_sec;
	int	std_usec;
	int	end;
	int	cnt;
	pthread_mutex_t mutex_c;
	pthread_mutex_t *mutex_s;
	pthread_mutex_t	*mutex_m;
}t_info; //공유자원들

typedef struct s_philo
{
	int	th_num;
	int fork_own;
	int state;
	long former;
	pthread_t thread_t;
	t_info *sh_info;
}t_philo; //철학자 개개인의 속성들

t_philo	*philo_init(int num);
t_info	*info_init(int num);
void	free_all(t_philo *philo);