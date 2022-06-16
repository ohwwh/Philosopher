#include "philosopher.h"

void	info_init_new(t_info *sh_info)
{
	struct timeval mytime;

	gettimeofday(&mytime, 0);
	sh_info->std_sec = mytime.tv_sec;
	sh_info->std_usec = mytime.tv_usec;
}

void	free_sem(int n, sem_t **sem_arr)
{
	sem_unlink("forks");
	sem_close(sem_arr[0]);
	sem_unlink("state");
	sem_close(sem_arr[1]);
	free(sem_arr);
}

void	aroutine(int n, sem_t **sem_arr, t_info *sh_info)
{
	int	state;
	int	i;
	long	former;
	struct timeval mytime;

	former = 0;
	state = 0;
	while (state < 10)
	{
		if (n % 2 && state == 0)
			ft_msleep(200);
		sem_wait(sem_arr[1]);
		sem_wait(sem_arr[0]);
		sem_wait(sem_arr[0]);
		gettimeofday(&mytime, 0);
		printf("at %ld %d grabs the fork\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		printf("at %ld %d start eating, waiting time: %ld\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n, 
		stamp(mytime.tv_sec, mytime.tv_usec, sh_info) - former);
		former = stamp(mytime.tv_sec, mytime.tv_usec, sh_info);
		ft_msleep(200);
		gettimeofday(&mytime, 0);
		printf("at %ld %d finish eating\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		sem_post(sem_arr[0]);
		sem_post(sem_arr[0]);
		sem_post(sem_arr[1]);
		printf("at %ld %d start sleeping\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		ft_msleep(200);
		gettimeofday(&mytime, 0);
		printf("at %ld %d start thinking\n", stamp(mytime.tv_sec, mytime.tv_usec, sh_info), n);
		usleep(200);
		state ++;
	}
}

int	main(int argc, char *argv[])
{
	int		i;
	t_philo	*philo;
	int		pid;
	int		status;
	int		n;
	int		*proc_arr;
	char	*str;
	sem_t **sem_arr;
	t_info	*sh_info;
	int		*pids;


	pid = 1;
	n = 190;
	/*if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));*/
	i = 0;
	sem_arr = (sem_t **)malloc(sizeof(sem_t *) * 2);
	sh_info = (t_info *)malloc(sizeof(t_info));
	pids = (int *)malloc(sizeof(int) * n);
	sem_arr[0] = sem_open("forks", O_CREAT, S_IXUSR, n);
	sem_arr[1] = sem_open("state", O_CREAT, S_IXUSR, n);
	info_init_new(sh_info);
	i = 0;
	while (i < n)
	{
		if (pid > 0)
		{
			pid = fork();
			pids[i] = pid;
		}
		else
			break ;
		i ++;
	}
	if (pid > 0)
	{
		i = 0;
		while (i < n)
			waitpid(pids[i ++], &status, 0);
		//printf("I am your father\n");
		//printf("%d, errno: %d\n", sem_arr[0], errno);
		free_sem(n, sem_arr);
		free(sh_info);
		free(pids);
		return (1);
	}
	else
	{
		//printf("I am a child\n");
		aroutine(i, sem_arr, sh_info);
		free_sem(n, sem_arr);
		free(sh_info);
		free(pids);
		return (1);
	}
}
