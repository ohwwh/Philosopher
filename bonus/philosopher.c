#include "philosopher.h"

int	main(int argc, char *argv[])
{
	int		j;
	t_philo	*philo;
	int		pid;
	int		n;

	n = 10;
	/*if (argc != 6 && argc != 5)
		return (printf("Arguments error!\n"));*/
	j = 0;
	while (j < n)
	{
		if (!fork())
		{
			printf("%d process\n", j + 1);
		}
	}
}
