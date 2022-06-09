#include "philosopher.h"

int    test(int n, t_philo *philo)
{
    const int   number = philo->sh_info->philo_num;
    int         ret;

    ret = 0;
    if (philo->sh_info->fork_num[LEFT] == 1)
    {
        if (philo->sh_info->fork_num[RIGHT] ==1)
            ret = 1;
    }
    return (ret);
}

void    print_start_eating(int n, t_philo *philo)
{
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher start eating! waiting time: %d, last eating: %d\n", 
    mytime.tv_usec - philo->sh_info->start, n, 
    mytime.tv_usec - philo->former,
    philo->former - philo->sh_info->start);
}

void    print_finish_eating(int n, t_philo *philo)
{
    int i;
    const int   number = philo->sh_info->philo_num;

    i = 0;
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    //printf("at %d %dth philosopher finish eating!\n", mytime.tv_usec - philo->sh_info->start, n);
    philo->former = mytime.tv_usec;
}

void    print_picking(int n, t_philo *philo)
{
    int i;

    i = 0;
    struct timeval mytime;
    gettimeofday(&mytime, NULL);
    printf("at %d %dth philosopher grab the forks!\n ", mytime.tv_usec - philo->sh_info->start, n);
}

void    picking(int n, t_philo *philo)
{
    struct timeval mytime;
    const int   number = philo->sh_info->philo_num;
    int flag;

    //print_picking(n, philo);
    philo->sh_info->fork_num[LEFT] --;
    philo->sh_info->fork_num[RIGHT] --;
    //philo->sh_info->fork_own[n - 1] += 2;
}

void    eating(int n, t_philo *philo)
{
    struct timeval mytime;
    const int   number = philo->sh_info->philo_num;

    /*if (philo->sh_info->fork_own[n - 1] == 2)
    {   
        print_start_eating(n, philo);
        usleep(200);
        print_finish_eating(n, philo);
    }*/

    print_start_eating(n, philo);
    usleep(200);
    print_finish_eating(n, philo);
    philo->sh_info->fork_num[LEFT] ++;
    philo->sh_info->fork_num[RIGHT] ++;
    //philo->sh_info->fork_own[n - 1] = 0;
    philo->state ++;
}

void sleeping(void)
{
    usleep(200);
}

void thinking(void)
{
    usleep(200);
}

void    *philo_routine(void *data)
{
    t_philo *philo = (t_philo *)data;
    struct timeval mytime;
    gettimeofday(&mytime, 0);
    const int   n = philo->th_num + 1;
    const int   number = philo->sh_info->philo_num;
    int         flag;

    philo->former = mytime.tv_usec; //스레드의 탄생시점
    while (philo->state < 100)
    {
        /*if (n % 2 == 0)
            usleep(100);
        if (n == philo->sh_info->last + 2)
        {
            pthread_mutex_lock(&(philo->sh_info->mutex_c));
            if (n == number - 1)
                philo->sh_info->last = 0;
            else
                philo->sh_info->last = n;
            pthread_mutex_unlock(&(philo->sh_info->mutex_c));
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
            picking(n, philo);
            eating(n, philo);
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
            sleeping();
            thinking();
        } // 1 3 5 7 9 2 4 6 8 10을 강제하는 코드 -> 쓰레기*/

        if (n % 2)
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
        else
        {
            usleep(200);
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
        }
        if (n % 2)
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
        else
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
        picking(n, philo);
        eating(n, philo);
        if (n % 2)
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        else
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
        if (n % 2)
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
        else
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        sleeping();
        thinking(); //비대칭으로 포크를 잡게 하여 데드락을 해결하는 코드

        /*if (n % 2 == 0)
            usleep(100);
        pthread_mutex_lock(&(philo->sh_info->mutex_c));
        flag = test(n, philo);
        pthread_mutex_unlock(&(philo->sh_info->mutex_c));
        if (flag == 1)
        {
            pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
            picking(n, philo);
            eating(n, philo);
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
            pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
        }
        sleeping();
        thinking();*/ //양 쪽 포크를 다 집을 수 있을 때만 잡게 하여 데드락을 해결하는 코드
    }
    return ((void *)n);
}

int main(int argc, char *argv[])
{
    int status;
    int j = 0;
    const int   n = atoi(argv[1]);
    t_philo *philo;

    philo = philo_init(n);
    while (j < n)
    {
        pthread_create(&(philo[j].thread_t), NULL, philo_routine, (void *)(&philo[j]));
        j ++;
    }
    j = 0;
    while (j < n)
    {
        pthread_join(philo[j].thread_t, NULL);
        j ++;
    }
    pthread_mutex_destroy(&(philo->sh_info->mutex_c));
    free_all(philo);
}
//포크를 집는 시간: 31 25 31 25
//41 32 23 22 31

