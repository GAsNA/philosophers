/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:33:53 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/06 16:51:22 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	calcul_ms(t_infos *infos)
{
	return (get_time() - infos->ms_start);
}

static unsigned	ft_gettime(struct timeval *start_time)
{
	struct timeval	current;
	unsigned		time;

	gettimeofday(&current, NULL);
	time = (((current.tv_sec - start_time->tv_sec) * 1000000)
			+ (current.tv_usec - start_time->tv_usec));
	return (time);
}

void	ft_usleep(unsigned wait)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	while (ft_gettime(&time) < wait)
		usleep(100);
}
