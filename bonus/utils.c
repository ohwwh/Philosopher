/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:36:38 by hoh               #+#    #+#             */
/*   Updated: 2022/06/20 11:36:39 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_msleep(int time)
{
	struct timeval	mytime;
	long			target;

	gettimeofday(&mytime, 0);
	target = time * 1000 + (mytime.tv_sec * 1000000) + (mytime.tv_usec);
	while (target > (mytime.tv_sec * 1000000) + (mytime.tv_usec))
	{
		usleep(1000);
		gettimeofday(&mytime, 0);
	}
}

long	stamp(long sec, long usec, t_philo *philo)
{
	long	ret;
	long	s_ret;
	long	u_ret;

	s_ret = (sec - philo->sh_info->std_sec) * 1000;
	u_ret = (usec - philo->sh_info->std_usec) / 1000;
	ret = s_ret + u_ret;
	return (ret);
}
