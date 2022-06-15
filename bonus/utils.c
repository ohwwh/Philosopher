#include "philosopher.h"

void    ft_msleep(int time)
{
    struct timeval mytime;
    long target;

    gettimeofday(&mytime, 0);
    target = time * 1000 + (mytime.tv_sec * 1000000) + (mytime.tv_usec);
    while (target > (mytime.tv_sec * 1000000) + (mytime.tv_usec))
    {
        usleep(1000);
        gettimeofday(&mytime, 0);
    }
}

void    fork_mutex_lock(int n, t_philo *philo)
{
    const int       number = philo->sh_info->philo_num;

    if (n % 2)
        pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
    else
    {
        if (philo->state == 0)
            usleep(200 * 1000);
        pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
    }
    if (n % 2)
        pthread_mutex_lock(&(philo->sh_info->mutex_s[LEFT]));
    else
        pthread_mutex_lock(&(philo->sh_info->mutex_s[RIGHT]));
}

void    fork_mutex_unlock(int n, t_philo *philo)
{
    const int       number = philo->sh_info->philo_num;

    if (n % 2)
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
    else
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
    if (n % 2)
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[LEFT]));
    else
        pthread_mutex_unlock(&(philo->sh_info->mutex_s[RIGHT]));
}

long    stamp(long sec, long usec, t_info *sh_info)
{
    long    ret;
    long    s_ret;
    long    u_ret;

    s_ret = (sec - sh_info->std_sec) * 1000;
    u_ret = (usec - sh_info->std_usec) / 1000;
    ret = s_ret + u_ret;
    return (ret);
}