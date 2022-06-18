#include <stdio.h>
#include <unistd.h>

void    test(void)
{
    printf("doomsday\n");
}

int main(void)
{
    int pid;
    int n;

    n = 0;
    test();
    while (n < 5)
	{
		if (pid > 0)
			pid = fork();
		else
			break ;
		n ++;
	}
    if (pid > 0)
        printf("father\n");
    else
        printf("child\n");
}