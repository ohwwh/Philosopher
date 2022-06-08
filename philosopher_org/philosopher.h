#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <stdint.h>

typedef struct s_info
{
	int	philo_num;
	int *fork_num;
	int *fork_own; // 공유변수일 필요 x
	int *state;	// 공유변수일 필요 x
	int *former; // 공유변수일 필요 x
	pthread_mutex_t *mutex_s;
	int	start;
	int	last;
	pthread_mutex_t mutex_c;
}t_info;

typedef struct s_philo
{
	int	th_num;
	int	start;
	pthread_t thread_t;
	t_info *sh_info;
}t_philo;

t_philo	*philo_init(int num);
t_info	*info_init(int num);
void	free_all(t_philo *philo);