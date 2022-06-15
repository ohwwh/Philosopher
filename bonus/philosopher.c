#include "philosopher.h"

void	aroutine(int n)
{
	printf("%d process\n", n);
}

int	main(int argc, char *argv[])
{
	int		j;
	t_philo	*philo;
	int		pid;
	int		status;
	int		n;
	int		*proc_arr;
	char	*str;
	sem_t **sem_arr;

	pid = 1;
	n = 5;
	sem_arr = (sem_t **)malloc(sizeof(sem_t *) * n);
	str = ft_itoa(n);
	printf("%s\n", str);
	sem_arr[0] = sem_open(str, O_CREAT, S_IXUSR, 1);
	/*if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));*/
	j = 0;
	while (j < n)
	{
		if (pid > 0)
			pid = fork();
		else
			break ;
		j ++;
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		printf("I am your father\n");
		printf("%d, errno: %d\n", sem_arr[0], errno);
		sem_unlink(str);
		sem_close(sem_arr[0]);
		free(str);
		free(sem_arr);
	}
	else
	{
		//printf("I am a child\n");
		aroutine(j);
		free(str);
		free(sem_arr);
	}
}
